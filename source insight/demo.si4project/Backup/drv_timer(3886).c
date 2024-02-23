#include "drv_timer.h"
/******************************************
函数名：drv_timer6base_init

函数功能：基本定时器6初始化

输入参数：无

输出参数：无

其它说明：PA9-TX、PA10-RX
			波特率：115200

*********************************************/ 
void drv_timer6base_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef  NVIC_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 5000;
	TIM_TimeBaseInitStruct.TIM_Prescaler =8400-1;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);

	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	

	NVIC_InitStruct.NVIC_IRQChannel = TIM6_DAC_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	TIM_Cmd(TIM6, ENABLE);
}
