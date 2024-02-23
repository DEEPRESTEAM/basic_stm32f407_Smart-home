#include "drv_key.h"
#include "drv_systick.h"
/******************************************
函数名：drv_key_init

函数功能：按键初始化

输入参数：无

输出参数：无

其它说明：PE4 - KEY1

*********************************************/
void drv_key_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
}
/******************************************
函数名：drv_keydata

函数功能：按键处理

输入参数：无

输出参数：按键按下返回1

其它说明：PE4 - KEY1

*********************************************/
uint8_t drv_key_scan(void)
{
	uint8_t ret=0;
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0)//检测GPIOE4电平是否为低电平
	{
		drv_systick_delayms(20);//延时20ms
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0)//检测GPIOE4电平是否为低电平
		{
			while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0);//等待按键抬起（检测GPIOE4电平是否为高电平）
			ret=1;
			
		}

	}
	return ret;
}
