#include "control.h"	
/**************************************************************************
 ��  �� ���������
 �Ա���ַ��https://shop119207236.taobao.com
 ΢�Ź��ںš���������ˡ�
 ��̨�ظ���ƽ��С��������ȡƽ��С��ȫ��DIY����
 ��̨�ظ������ӿ������ߡ�����ȡ���ӹ���ʦ�ر���������
 ��̨�ظ�������������ϡ�����ȡ����������ϰ�
 ֪���������� 
**************************************************************************/
/**************************************************************************
�������ܣ����еĿ��ƴ��붼��������
         Timer3 10ms��ʱ�ж�
**************************************************************************/

#define SPEED_Y 40 //ǰ������趨�ٶ�
#define SPEED_Z 100//��������趨�ٶ� 


//��Բ�ͬ���Ͳ�������sys.h������define�ĵ������
float velocity_KP=SPD_KP;     // С���ٶȻ�PI����
float velocity_KI=SPD_KI;
extern float pitch,roll,yaw; 								  			 //ŷ����(��̬��)
int count;
extern int x,y,act_i;
extern int Yaw,flag,Track_count;
extern int jiance,Act_i;
extern int sensor[8];
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	static u8 Voltage_Counter=0;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
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

			Encoder_Right=-Read_Encoder(2);                           //===��ȡ��������ֵ����Ϊ�����������ת��180�ȵģ����Զ�����һ��ȡ������֤�������һ��
			Encoder_Left=Read_Encoder(4);                           //===��ȡ��������ֵ

			Moto1=Incremental_PI_A(Encoder_Left,Target_A);                 //===�������ֵ������PWM
			Moto2=Incremental_PI_B(Encoder_Right,Target_B);                 //===�������ֵ������PWM
			Xianfu_Pwm();  																					 //===PWM�޷�
			Turn_Off(Voltage);															 //===���Ƕ��Լ���ѹ�Ƿ�����
			Set_Pwm(Moto1,Moto2);                                    //===��ֵ��PWM�Ĵ���  
	}
}

/**************************************************************************
�������ܣ�����PI������
��ڲ���������������ֵ��Ŀ���ٶ�
����  ֵ�����PWM
��������ʽ��ɢPID��ʽ 
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
pwm�����������
�����ǵ��ٶȿ��Ʊջ�ϵͳ���棬ֻʹ��PI����
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI_A (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //����ƫ��
	 Pwm+=velocity_KP*(Bias-Last_bias)+velocity_KI*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
int Incremental_PI_B (int Encoder,int Target)
{ 	
	 static int Bias,Pwm,Last_bias;
	 Bias=Target-Encoder;                //����ƫ��
	 Pwm+=velocity_KP*(Bias-Last_bias)+velocity_KI*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}


/**************************************************************************
�������ܣ�С���˶���ѧģ��
��ڲ������ٶȺ�ת��
����  ֵ����
**************************************************************************/
void Kinematic_Analysis(int velocity,int turn)
{
		Target_A=velocity+turn; 
		Target_B=velocity-turn;      //���ֲ���
}

