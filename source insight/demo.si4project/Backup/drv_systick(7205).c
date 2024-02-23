

void drv_systick_init(void)
{
	SysTick->CTRL &= ~0x05;


}
