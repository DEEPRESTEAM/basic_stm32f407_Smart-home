#include "drv_led.h"
#include "drv_systick.h"
#include "drv_key.h"
#include "drv_usart.h"
#include "drv_exti.h"
#include "drv_timer.h"
#include "drv_at24cxx.h"
#include "drv_spi.h"
#include "drv_w25qxx.h"
uint8_t key1_flag=0;
uint8_t key_vule=0;
extern uint8_t exti_flg;
uint16_t dir=0,ledpwm=0;
uint32_t dma_src[10]={	0x11111111,0x11111122,0x11111133,0x11111144,0x11111155,
						0x11111166,0x11111177,0x11111188,0x11111199,0x111111aa
						};
uint32_t dma_drc[10];

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
	
	//drv_at24cxx_write(0x11, 0x99);
	//printf("at24cxx_writ data=0x99\r\n");
	drv_systick_delayms(1000);
	printf("at24cxx_readdata=0x%x\r\n",drv_at24cxx_read(0x11));

	drv_spi_init();
	printf("W25QXX_readID=0x%x\r\n",drv_w25qxx_readID());
	while(1)
	{
	
	}
}


