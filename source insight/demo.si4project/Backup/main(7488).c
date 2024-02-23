#include "drv_led.h"
#include "drv_systick.h"
#include "drv_key.h"
uint8_t key1_flag=0;
uint8_t key_vule=0;
int main()
{	
	drv_led_init();
	drv_systick_init(168);
	drv_key_init();
	while(1)
	{
		if(drv_key_scan())
		{
			key1_flag = ~key1_flag;
		}
		if(key1_flag==0)
		{
			drv_led_close();
		}
		else
		{
			drv_led_open();
		}
	}
}


