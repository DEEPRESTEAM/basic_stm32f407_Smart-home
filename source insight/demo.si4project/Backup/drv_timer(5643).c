
void drv_timerbase_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 5000;
	TIM_TimeBaseInitStruct.TIM_Prescaler =8400-1;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);


}
