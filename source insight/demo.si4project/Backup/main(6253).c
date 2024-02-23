#include "drv_led.h"
#include "drv_systick.h"

int main()
{	
	drv_led_init();
	drv_systick_init(168);
	while(1)
	{
		drv_led_open();
		drv_systick_delayms(500);
		drv_led_close();
		drv_systick_delayms(500);
		
	}
}


