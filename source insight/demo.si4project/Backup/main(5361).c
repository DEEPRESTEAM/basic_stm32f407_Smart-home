#include "drv_led.h"
#include "drv_systick.h"

int main()
{	
	drv_led_init();
	drv_systick_init(168)
	while(1)
	{
		drv_led_open();
		delay(1000);
		drv_led_close();
		delay(1000);
	}
}


