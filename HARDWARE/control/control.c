#include "control.h"	
/**************************************************************************
 作  者 ：大鱼电子
 淘宝地址：https://shop119207236.taobao.com
 微信公众号【大鱼机器人】
 后台回复【平衡小车】：获取平衡小车全套DIY资料
 后台回复【电子开发工具】：获取电子工程师必备开发工具
 后台回复【电子设计资料】：获取电子设计资料包
 知乎：张巧龙 
**************************************************************************/
/**************************************************************************
函数功能：所有的控制代码都在这里面
         Timer3 10ms定时中断
**************************************************************************/

#define SPEED_Y 40 //前后最大设定速度
#define SPEED_Z 100//左右最大设定速度 


//针对不同车型参数，在sys.h内设置define的电机类型
float velocity_KP=SPD_KP;     // 小车速度环PI参数
float velocity_KI=SPD_KI;
extern float pitch,roll,yaw; 								  			 //欧拉角(姿态角)
int count;
extern int x,y,act_i;
extern int Yaw,flag,Track_count;
extern int jiance,Act_i;
extern int sensor[8];
void TIM3_IRQHandler(void)   //TIM3中断
{
	static u8 Voltage_Counter=0;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		sensor[0] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
		sensor[1] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);
		sensor[2] = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);
		sensor[3] = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);
		sensor[4] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
		sensor[5] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3);
		sensor[6] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12);
		sensor[7] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);
		count++;
		Track_count++;
		oled_show();

			Encoder_Right=-Read_Encoder(2);                           //===读取编码器的值，因为两个电机的旋转了180度的，所以对其中一个取反，保证输出极性一致
			Encoder_Left=Read_Encoder(4);                           //===读取编码器的值

			Moto1=Incremental_PI_A(Encoder_Left,Target_A);                 //===计算左轮电机最终PWM
			Moto2=Incremental_PI_B(Encoder_Right,Target_B);                 //===计算右轮电机最终PWM
			Xianfu_Pwm();  																					 //===PWM限幅
			Turn_Off(Voltage);															 //===检查角度以及电压是否正常
			Set_Pwm(Moto1,Moto2);                                    //===赋值给PWM寄存器  
	}
}

/**************************************************************************
函数功能：增量PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI_A (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //计算偏差
	 Pwm+=velocity_KP*(Bias-Last_bias)+velocity_KI*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //计算偏差
	 Pwm+=velocity_KP*(Bias-Last_bias)+velocity_KI*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}


/**************************************************************************
函数功能：小车运动数学模型
入口参数：速度和转角
返回  值：无
**************************************************************************/
void Kinematic_Analysis(int velocity,int turn)
{
		Target_A=velocity+turn; 
		Target_B=velocity-turn;      //后轮差速
}

