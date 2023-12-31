#include "usart2.h"
/**************************************************************************
 作  者 ：大鱼电子
 淘宝地址：https://shop119207236.taobao.com
 微信公众号【大鱼机器人】
 后台回复【平衡小车】：获取平衡小车全套DIY资料
 后台回复【电子开发工具】：获取电子工程师必备开发工具
 后台回复【电子设计资料】：获取电子设计资料包
 知乎：张巧龙 
**************************************************************************/
int i = 0;
//int act[300] = {51,51,48,51};
int act[300] = {51,49,51,49,51,48,51,48,51,49,51,48,51,49,51,49,51,51,49,50,52,51,51,51,48,51,49,51,48,51,49,51,48,51,49,51,49,51,51,51,49,51,50,52,51,51,48,51,51,51,51,48,51,51,49,51,51,48,51,49,51,51,49,51,48,51,49,51,49,51,48,51,48,51,51,53};
int pos_x[200],pos_y[200];
int x_i,y_i;
int color[100]={0};
int color_i = 0;
int a_i;
int t_flag = 1;
void uart2_init(u32 bound)
{  	 
	  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	//NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);	//使能UGPIOA时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART2时钟
	//USART2_TX  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA2	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);
   
  //USART2_RX	  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);

   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART2, &USART_InitStructure);     //初始化串口2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口2 
}

/**************************************************************************
函数功能：串口3初始化
入口参数： bound:波特率
返回  值：无
**************************************************************************/
void uart3_init(u32 bound)
{  	 
	  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	//NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能GPIOB时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART3时钟
	//USART3_TX  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);
   
  //USART3_RX	  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);

   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART3, &USART_InitStructure);     //初始化串口3
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART3, ENABLE);                    //使能串口3 
}

/**************************************************************************
函数功能：串口2接收中断
入口参数：无
返回  值：无
**************************************************************************/
void USART3_IRQHandler(void)
{	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //接收到数据
	{	 
//		static int Uart_Receive[200]={0};//蓝牙接收相关变量
//		Led_Flash(100);
//		Uart_Receive[i]=USART_ReceiveData(USART3); 
//		act[a_i] = Uart_Receive[i];
//		i++;a_i++;
////		if(act[a_i] == 51)
//		{
//			t_flag = 0;
//		}
//		if(act[a_i] != 51&&t_flag == 1)
//		{
//			a_i--;
//		}
//		if(i%8 == 1)
//		{
//			pos_x[x_i] = Uart_Receive[i];
//			x_i++;
//		}
//		if(i%8 == 4)
//		{
//			pos_y[y_i] = Uart_Receive[i];
//			y_i++;
//		}
//		if((Uart_Receive[i] == '[')||(Uart_Receive[i] == ']'))
//		{
//			i = -1;
//		}
//		if(Uart_Receive[i] == Uart_Receive[i-1])
//		{
//			i--;
//		}
//		i++;
	}
}
void BluetoothCMD(u8 Uart_Receive)
{
	if(Uart_Receive>=0x41&&Uart_Receive<=0x48)  
	{	
		Flag_Direction=Uart_Receive-0x40;
	}
	else	if(Uart_Receive<=8)   
	{			
		Flag_Direction=Uart_Receive;
	}	
	else  Flag_Direction=0;
}
/**************************************************************************
函数功能：串口3接收中断
入口参数：无
返回  值：无
**************************************************************************/
void USART2_IRQHandler(void)
{	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //接收到数据
	{
		static int Uart_Receive[200]={0};//蓝牙接收相关变量
		
		Uart_Receive[i]=USART_ReceiveData(USART3); 
//		color[color_i] = Uart_Receive[i];
//		if(color_i == 100)
//		{
//			i = -1;
//			color_i = -1;
//		}
//		i++;color_i++;
	}
}


