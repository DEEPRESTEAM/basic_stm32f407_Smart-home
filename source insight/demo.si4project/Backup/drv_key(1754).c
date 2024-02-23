

void drv_key_init(void)
{
	GPIO_InitTypeDef	GPIO_InitStruct
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_Init(GPIOE, GPIO_InitTypeDef * GPIO_InitStruct)

}
