#include "drv_led.h"
/*****************************************************
函数名称：drv_led_init

函数功能：初始化led

输入参数：无

输出参数：无

其它说明：PE8-LED1 低电平亮
*******************************************************/
void drv_led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	//开时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;//输出模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//推挽
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;//引脚
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;//速率
	
	GPIO_Init(GPIOE, &GPIO_InitStruct);//按照上面的配置来初始化GPIOE
	GPIO_SetBits(GPIOE, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);//初始化默认关闭led
}
/*****************************************************
函数名称：drv_led_open

函数功能：打开led

输入参数：无

输出参数：无

其它说明：PE8-LED1 低电平打开
*******************************************************/
void drv_led_open(uint16_t GPIO_Pin)
{
	GPIO_ResetBits(GPIOE , GPIO_Pin);
}
/*****************************************************
函数名称：drv_led_close

函数功能：关闭led

输入参数：无

输出参数：无

其它说明：PE8-LED1 高电平关闭
*******************************************************/
void drv_led_close(uint16_t GPIO_Pin)
{
	GPIO_SetBits(GPIOE, GPIO_Pin);
}

