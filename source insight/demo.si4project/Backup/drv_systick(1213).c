
static uint8_t fs_us=0;
static uint16_t fs_ms=0;
void drv_systick_init(void)
{
	SysTick->CTRL &= ~0x05;
	


}
