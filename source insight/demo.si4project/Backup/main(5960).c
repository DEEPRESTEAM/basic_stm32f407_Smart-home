#include "drv_led.h"
#include "drv_systick.h"
#include "drv_key.h"
int main()
{	
	drv_led_init();
	drv_systick_init(168);
	drv_key_init();
	while(1)
	{
		drv_led_open();
		drv_systick_delayms(1000);
		drv_led_close();
		drv_systick_delayms(1000);
		
	}
}


