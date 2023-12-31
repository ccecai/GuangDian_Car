#include "key.h"
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
函数功能：按键初始化
入口参数：无
返回  值：无 
**************************************************************************/
extern int mode;
int mode_count,Mode;

void KEY_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能PA端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	           //端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
  GPIO_Init(GPIOC, &GPIO_InitStructure);					      //根据设定参数初始化GPIOA 
} 
/**************************************************************************
函数功能：按键扫描
入口参数：无
返回  值：按键状态 0：无动作 1：长按 
**************************************************************************/
u8 KEY_Press(int Ticks)
{
	mode_count++;
	if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14) == 0)
	{
		delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14) == 0)
		{
			
		}
		
		
		mode++;
		delay_ms(20);
	}
	
	return 0;
}
