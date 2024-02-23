#include "drv_led.h"
#include "drv_systick.h"
#include "drv_key.h"
#include "drv_usart.h"
#include "drv_exti.h"
#include "drv_timer.h"
#include "drv_at24cxx.h"
uint8_t key1_flag=0;
uint8_t key_vule=0;
extern uint8_t exti_flg;
uint16_t dir=0,ledpwm=0;

int main()
{	
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//drv_led_init();
	drv_systick_init(168);
	//drv_key_init();
	drv_usart1_init();
	drv_at24cxx_init();
	//drv_exti_init();
	//drv_timer6base_init();
	//drv_timer1_init();
	printf("hello 2308 class\r\n");
	drv_at24cxx_write(0x11, 0x99);
	printf("at24cxx_writ data=0x99\r\n");
	drv_systick_delayms(1000);
	printf("at24cxx_readdata=0x%x\r\n",drv_at24cxx_read(0x11));
	while(1)
	{
	
	}
}


