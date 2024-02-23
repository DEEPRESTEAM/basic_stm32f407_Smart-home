#include "drv_w25q.h"
#include "drv_spi.h"

uint16_t drv_w25qxx_readID(void)
{
	uint16_t readid=0;
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_2);
	drv_spi_wdata(0x90);
	
}

