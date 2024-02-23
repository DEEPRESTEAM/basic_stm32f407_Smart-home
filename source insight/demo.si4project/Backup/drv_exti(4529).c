
void drv_exti_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode= GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	

	EXTI_InitStruct.EXTI_Line = EXTI_Line13;//PC13��Ӧ�ⲿ�ж���13
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;//�ж�
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
	EXTI_InitStruct.EXTI_LineCmd = ENABLE //ʹ���ⲿ�ж�
	EXTI_Init(&EXTI_InitStruct)
}

