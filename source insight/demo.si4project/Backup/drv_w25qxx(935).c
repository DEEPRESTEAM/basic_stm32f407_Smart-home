#include "drv_w25qxx.h"
#include "drv_spi.h"

uint16_t drv_w25qxx_readID(void)
{
	uint16_t readid=0;
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_2);
	drv_spi_wdata(0x90);

	drv_spi_wdata(0x00);
	drv_spi_wdata(0x00);
	drv_spi_wdata(0x00);

	readid = drv_spi_wdata(0xff);
	readid |= readid <<8;
	readid = drv_spi_wdata(0xff);
	readid |= readid;
	GPIO_SetBits(GPIOB, GPIO_Pin_2);
	return readid;
}

