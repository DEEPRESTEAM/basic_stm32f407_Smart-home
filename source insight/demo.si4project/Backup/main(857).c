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
		if(drv_key_scan())
		{

		}
		else
		{

		}
		
	}
}


