 /**************************************************************************
 作  者 ：大鱼电子
 淘宝地址：https://shop119207236.taobao.com
 
 微信公众号【大鱼机器人】
 后台回复【平衡小车】：获取平衡小车全套DIY资料
 后台回复【电子开发工具】：获取电子工程师必备开发工具
 后台回复【电子设计资料】：获取电子设计资料包
 
 知乎：张巧龙 
**************************************************************************/
#include "sys.h"
#include "jkd_oled.h"
/****************************全局变量*************************************/    
float Voltage;  															 //电池电压采样相关的变量
float SR04_Distance;                 //超声波测距
int   Encoder_Left,Encoder_Right;         		 //左右编码器的脉冲计数
int 	Moto1=0,Moto2=0,Target_A=0,Target_B = 0;												 //计算出来的最终赋给电机的PWM
float pitch,roll,yaw; 								  			 //欧拉角(姿态角)
u8 		CTRL_MODE=97,Mode_Change=0;   //在此选择小车模式  //97超声波避障；98蓝牙；99红外循迹；100 PS2；101自动跟随

u8 		Flag_Direction=0;
int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY; //PS2相关变量
u8 PS2_Plugin=0;

int Velocity=0,Turn=0;
int jiance = 0;
//int Uart_Receive=0;
u8 TkSensor=0;
int x,y;
/***********************************************************************/
int mode = 0,flag = 0;
float Yaw = 0;
int sensor[8] = {0};
extern int act[300];
extern int Mode;
extern int pos_x[200],pos_y[200];
void Track(void);
void Judge(void);
int j =0;
extern int x_i,y_i;
extern int i;
extern int count,color_i;
int Track_count = 0;
int act_i = 0;
int Act_i = 0;
extern int color[100];
int temp;
void Track_slow(void);




void Track_back(void)
{
		sensor[0] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
		sensor[1] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);
		sensor[2] = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);
		sensor[3] = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);
		sensor[4] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
		sensor[5] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3);
		sensor[6] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12);
		sensor[7] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);

	if((sensor[3] == 0)&&(sensor[4] == 1))
	{
		Target_A = -38;
		Target_B = -42;
	}
	if((sensor[4] == 0)&&(sensor[3] == 1))
	{
		Target_A = -42;
		Target_B = -38;
	}
	if((sensor[2] == 0)&&(sensor[3] == 0))
	{
		Target_A = -37;
		Target_B = -43;
	}
	if((sensor[4] == 0)&&(sensor[5] == 0))
	{
		Target_A = -43;
		Target_B = -37;
	}
	if((sensor[2] == 0)&&(sensor[3] == 1))
	{
		Target_A = -30;
		Target_B = -45;
	}
	if((sensor[5] == 0)&&(sensor[4] == 1))
	{
		Target_A = -45;
		Target_B = -30;
	}
	
	if((sensor[1] == 0)&&(sensor[2] == 0))
	{
		Target_A = -28;
		Target_B = -45;
	}
	if((sensor[5] == 0)&&(sensor[6] == 0))
	{
		Target_A = -45;
		Target_B = -28;
	}
	if((sensor[1] == 0)&&(sensor[2] == 1))
	{
		Target_A = -25;
		Target_B = -45;
	}
	if((sensor[5] == 1)&&(sensor[6] == 0))
	{
		Target_A = -45;
		Target_B = -25;
	}
	if((sensor[3] == 0)&&(sensor[4] == 0))
	{
		Target_A = -42;
		Target_B = -42;
	}
}


void Judge(void)
{
	if(act[act_i] == '3' && act[act_i + 1] == '3'&&act[act_i+2] != '3')
	{
		Track_count = 0;
		do{
					Track();
				
		}while(Track_count <70);
		Track_count = 0;
		do{
					Track_slow();
				
		}while(Track_count <10);
		act_i++;
		
	}
	if(act[act_i] == '3' && act[act_i + 1] == '3'&& act[act_i + 2] == '3'&& act[act_i + 3] != '3')
	{
		Track_count = 0;
		do{
					Track();
				
		}while(Track_count <163);
		act_i = act_i +2;
	}
	if(act[act_i] == '3' && act[act_i + 1] == '3'&& act[act_i + 2] == '3'&& act[act_i + 3] == '3'&&act[act_i + 4] != '3')
	{
		Track_count = 0;
		do{
					Track();
				
		}while(Track_count <244);
		act_i = act_i +3;
	}
	if(act[act_i] == '3' && act[act_i + 1] == '3'&& act[act_i + 2] == '3'&& act[act_i + 3] == '3'&&act[act_i + 4] == '3'&&act[act_i + 5] != '3')
	{
		Track_count = 0;
		do{
					Track();
				
		}while(Track_count <376);
		act_i = act_i +4;
	}
	if(act[act_i] == '3' && act[act_i + 1] == '3'&& act[act_i + 2] == '3'&& act[act_i + 3] == '3'&&act[act_i + 4] == '3'&&act[act_i + 5] == '3')
	{
		Track_count = 0;
		do{
					Track();
				
		}while(Track_count <407);
		act_i = act_i +5;
	}
	if(act[act_i] == '3' && act[act_i + 1] == '2')
	{
		Track_count = 0;
		while(Track_count <100){
//				Target_A = 20;
//				Target_B = 20;
					Track();
		}
		act_i++;
	}
	
	switch(act[act_i])
	{
		case 48:
		{
			
				Track_count = 0;
			while(Track_count <= 2)
			{
				Target_A = 20;
				Target_B = 20;
			}
			
				Track_count = 0;
				while(Track_count<29)
				{
					Target_A = -40;
					Target_B = 40;
				}
				
			
			Track_count = 0;
			while(Track_count<15)
			{
				Target_A = 0;
				Target_B = 0;
			}
		break;
		}
		case 49:
		{
				
			Track_count = 0;
			while(Track_count <= 2)
			{
				Target_A = 20;
				Target_B = 20;
			}
			Track_count = 0;
				while(Track_count<28)
				{
					Target_A = 40;
					Target_B = -40;
				}
				
			
			Track_count = 0;
			while(Track_count<15)
			{
				Target_A = 0;
				Target_B = 0;
			}
		break;
		}
		case 50:
		{
			Track_count = 0;
			while(Track_count<30)
			{

				Track();
			}
			
				Track_count = 0;
				while(Track_count<54)
				{
					Target_A = 40;
					Target_B = -40;
				}
				Track_count = 0;
				while(Track_count<15)
				{
					Target_A = 0;
					Target_B = 0;
				}

			break;
		}
		case 51:
		{
			Track_count = 0;
				while(Track_count<30)
				{
					Track();
				}
				while((sensor[0] == 1)&&(sensor[7] == 1)){
				
					Track_slow();
				
				}
				
			break;
				
		}
		case 52:
		{
//			Track_count = 0;
//			while(Track_count<50)
//			{
//				Target_A = 0;
//				Target_B = 0;
//			}
//		
//				Track_count = 0;
//				while(Track_count<20)
//				{
//					Track_back();
//				}
//				Track_count = 0;
//				while(Track_count<20)
//				{
//					Target_A = 40;
//					Target_B = 40;
//					Track();
//				}
			break;
		}
		case 53:
		{
			Set_Pwm(0,0);
		}
	}
	
	
	act_i++;

}


void Track(void)
{
	sensor[0] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
		sensor[1] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);
		sensor[2] = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);
		sensor[3] = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);
		sensor[4] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
		sensor[5] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3);
		sensor[6] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12);
		sensor[7] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);
//	if((sensor[0] == 1)&&(sensor[1] == 1)&&(sensor[2] == 1)&&(sensor[3] == 1)&&(sensor[4] == 1)&&(sensor[5] == 1))
//	{
//		if((Target_A > Target_B)||(Target_A < Target_B))
//		{
//			
//			temp = Target_A ;
//			Target_A = Target_B;
//			Target_B = temp;
//		}
//		if(Target_A == Target_B)
//		{
//			Target_A = 23;
//			Target_B = 23;
//		}
//	}
	if((sensor[3] == 0)&&(sensor[4] == 1))
	{
		Target_A = 62;
		Target_B = 58;
	}
	if((sensor[4] == 0)&&(sensor[3] == 1))
	{
		Target_A = 58;
		Target_B = 62;
	}
	if((sensor[2] == 0)&&(sensor[3] == 0))
	{
		Target_A = 63;
		Target_B = 57;
	}
	if((sensor[4] == 0)&&(sensor[5] == 0))
	{
		Target_A = 57;
		Target_B = 63;
	}
	if((sensor[2] == 0)&&(sensor[3] == 1))
	{
		Target_A = 65;
		Target_B = 50;
	}
	if((sensor[5] == 0)&&(sensor[4] == 1))
	{
		Target_A = 50;
		Target_B = 65;
	}
	
	if((sensor[1] == 0)&&(sensor[2] == 0))
	{
		Target_A = 66;
		Target_B = 48;
	}
	if((sensor[5] == 0)&&(sensor[6] == 0))
	{
		Target_A = 45;
		Target_B = 66;
	}
	if((sensor[1] == 0)&&(sensor[2] == 1))
	{
		Target_A = 66;
		Target_B = 40;
	}
	if((sensor[5] == 1)&&(sensor[6] == 0))
	{
		Target_A = 40;
		Target_B = 66;
	}
	if((sensor[3] == 0)&&(sensor[4] == 0))
	{
		Target_A = 62;
		Target_B = 62;
	}
}

void Track_slow(void)
{
	sensor[0] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
		sensor[1] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);
		sensor[2] = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);
		sensor[3] = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);
		sensor[4] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
		sensor[5] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3);
		sensor[6] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12);
		sensor[7] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);
//	if((sensor[0] == 1)&&(sensor[1] == 1)&&(sensor[2] == 1)&&(sensor[3] == 1)&&(sensor[4] == 1)&&(sensor[5] == 1))
//	{
//		if((Target_A > Target_B)||(Target_A < Target_B))
//		{
//			
//			temp = Target_A ;
//			Target_A = Target_B;
//			Target_B = temp;
//		}
//		if(Target_A == Target_B)
//		{
//			Target_A = 23;
//			Target_B = 23;
//		}
//	}
	if((sensor[3] == 0)&&(sensor[4] == 1))
	{
		Target_A = 52;
		Target_B = 48;
	}
	if((sensor[4] == 0)&&(sensor[3] == 1))
	{
		Target_A = 48;
		Target_B = 52;
	}
	if((sensor[2] == 0)&&(sensor[3] == 0))
	{
		Target_A = 53;
		Target_B = 47;
	}
	if((sensor[4] == 0)&&(sensor[5] == 0))
	{
		Target_A = 47;
		Target_B = 53;
	}
	if((sensor[2] == 0)&&(sensor[3] == 1))
	{
		Target_A = 55;
		Target_B = 40;
	}
	if((sensor[5] == 0)&&(sensor[4] == 1))
	{
		Target_A = 40;
		Target_B = 55;
	}
	
	if((sensor[1] == 0)&&(sensor[2] == 0))
	{
		Target_A = 56;
		Target_B = 38;
	}
	if((sensor[5] == 0)&&(sensor[6] == 0))
	{
		Target_A = 35;
		Target_B = 56;
	}
	if((sensor[1] == 0)&&(sensor[2] == 1))
	{
		Target_A = 56;
		Target_B = 30;
	}
	if((sensor[5] == 1)&&(sensor[6] == 0))
	{
		Target_A = 30;
		Target_B = 56;
	}
	if((sensor[3] == 0)&&(sensor[4] == 0))
	{
		Target_A = 52;
		Target_B = 52;
	}
}


int main(void)
{
	LED_Init();                    //=====初始化与 LED 连接的IO
	KEY_Init();                    //=====初始化与按键连接的IO
	delay_init();	    	           //=====延时函数初始化	
	uart1_init(115200);	           //=====串口1初始化
	uart3_init(1200);            //=====初始化串口3
//	uart2_init(19200);            //=====初始化串口2
	NVIC_Configuration();					 //=====中断优先级分组,其中包含了所有的中断优先级的配置,方便管理和一次性修改。
//	Adc_Init();                    //=====初始化ADC
	Encoder_Init_TIM2();           //=====初始化编码器2
	Encoder_Init_TIM4();           //=====初始化编码器4
	TIM1_PWM_Init(7199,0);   			 //=====初始化PWM 10KHZ,用于驱动电机。 
	OLED_Init();
	OLED_Clear();
	oled_first_show();
	
	Motor_Init();									 //=====初始化与电机连接的硬件IO接口 
	Timer3_Init(100,7199);           //=====10MS进一次中断服务函数，中断服务函数在control.c
//	MPU_Init();					    			 //=====初始化MPU6050
//	mpu_dmp_init();								 //=====初始化MPU6050的DMP模式	
	Tracking_Init();	
	
  while(1)	
	{
		

		KEY_Press(1);
		Target_A = 50;
//		if(mode >= 1)
//		{
//			
//			Judge();
//			
//		}
	}
}

void Tracking_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能PA端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_12|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_15|GPIO_Pin_2|GPIO_Pin_3;	           //端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能PA端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4;	           //端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA 
} 


