
static uint8_t fs_us=0;
static uint16_t fs_ms=0;
void drv_systick_init(uint32_t systick)
{
	SysTick->CTRL &= ~0x05;
	fs_us = systick/8;
	fs_ms = 1000*fs_us;
}
void drv_systick_delayms(uint16_t ms)
{
	SysTick->LOAD = fs_ms*ms;
	SysTick->VAL = 0;
	



}

