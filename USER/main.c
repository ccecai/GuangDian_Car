 /**************************************************************************
 ��  �� ���������
 �Ա���ַ��https://shop119207236.taobao.com
 
 ΢�Ź��ںš���������ˡ�
 ��̨�ظ���ƽ��С��������ȡƽ��С��ȫ��DIY����
 ��̨�ظ������ӿ������ߡ�����ȡ���ӹ���ʦ�ر���������
 ��̨�ظ�������������ϡ�����ȡ����������ϰ�
 
 ֪���������� 
**************************************************************************/
#include "sys.h"
#include "jkd_oled.h"
/****************************ȫ�ֱ���*************************************/    
float Voltage;  															 //��ص�ѹ������صı���
float SR04_Distance;                 //���������
int   Encoder_Left,Encoder_Right;         		 //���ұ��������������
int 	Moto1=0,Moto2=0,Target_A=0,Target_B = 0;												 //������������ո��������PWM
float pitch,roll,yaw; 								  			 //ŷ����(��̬��)
u8 		CTRL_MODE=97,Mode_Change=0;   //�ڴ�ѡ��С��ģʽ  //97���������ϣ�98������99����ѭ����100 PS2��101�Զ�����

u8 		Flag_Direction=0;
int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY; //PS2��ر���
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
	LED_Init();                    //=====��ʼ���� LED ���ӵ�IO
	KEY_Init();                    //=====��ʼ���밴�����ӵ�IO
	delay_init();	    	           //=====��ʱ������ʼ��	
	uart1_init(115200);	           //=====����1��ʼ��
	uart3_init(1200);            //=====��ʼ������3
//	uart2_init(19200);            //=====��ʼ������2
	NVIC_Configuration();					 //=====�ж����ȼ�����,���а��������е��ж����ȼ�������,��������һ�����޸ġ�
//	Adc_Init();                    //=====��ʼ��ADC
	Encoder_Init_TIM2();           //=====��ʼ��������2
	Encoder_Init_TIM4();           //=====��ʼ��������4
	TIM1_PWM_Init(7199,0);   			 //=====��ʼ��PWM 10KHZ,������������� 
	OLED_Init();
	OLED_Clear();
	oled_first_show();
	
	Motor_Init();									 //=====��ʼ���������ӵ�Ӳ��IO�ӿ� 
	Timer3_Init(100,7199);           //=====10MS��һ���жϷ��������жϷ�������control.c
//	MPU_Init();					    			 //=====��ʼ��MPU6050
//	mpu_dmp_init();								 //=====��ʼ��MPU6050��DMPģʽ	
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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //ʹ��PA�˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_12|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_15|GPIO_Pin_2|GPIO_Pin_3;	           //�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //ʹ��PA�˿�ʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4;	           //�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOA 
} 


