#include "drv_led.h"
#include "drv_systick.h"
#include "drv_key.h"
#include "drv_usart.h"
#include "drv_exti.h"
#include "drv_timer.h"
uint8_t key1_flag=0;
uint8_t key_vule=0;
extern uint8_t exti_flg;
int main()
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	drv_led_init();
	drv_systick_init(168);
	drv_key_init();
	drv_usart1_init();
	drv_exti_init();
	drv_timerbase_init();
	printf("hello 2308 class\r\n");
	while(1)
	{
		/*if(drv_key_scan())
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
		}*/
//		printf("exti_flg = %d\r\n",exti_flg);
//		if(exti_flg ==0)
//		{
//			drv_led_close();
//		}
//		else
//		{
//			drv_led_open();
//		}
//		drv_systick_delayms(500);
	}
}


