#include "drv_timer.h"
/******************************************
函数名：drv_timer6base_init

函数功能：基本定时器6初始化

输入参数：无

输出参数：无

其它说明：500MS中断一次

*********************************************/ 
void drv_timer6base_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//定义基本定时器结构体
	NVIC_InitTypeDef  NVIC_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);//开时钟
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//时钟分割
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_Period = 5000;//重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler =8400-1;//预分频值
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);//根据上面配置的参数初始化定时器6

	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);//配置定时器6更新中断（配置中断源）
	

	NVIC_InitStruct.NVIC_IRQChannel = TIM6_DAC_IRQn;//中断通道号
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;//响应优先级
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//使能中断
	NVIC_Init(&NVIC_InitStruct);

	TIM_Cmd(TIM6, ENABLE);//使能定时器6
}

void drv_timer1_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, GPIO_InitTypeDef * GPIO_InitStruct)


}
