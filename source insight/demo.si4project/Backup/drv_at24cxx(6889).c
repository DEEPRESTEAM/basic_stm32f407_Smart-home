#include "drv_at24cxx.h"
void drv_24cxx_init(void)
{
	drv_iic_init();
}

void drv_24cxx_write(uint8_t addr,uint8_t w_data)
{
	drv_iic_start();
	drv_iic_sendByte(0xa0);
	if(drv_wait_ACK()!=ACK)
	{
		drv_iic_stop();
		return;
	}
	
	drv_iic_sendByte(addr);
	if(drv_wait_ACK()!=ACK)
	{
		drv_iic_stop();
		return;
	}

	drv_iic_sendByte(w_data)
	if(drv_wait_ACK()!=ACK)
	{
		drv_iic_stop();
		return;
	}
	drv_iic_stop();
}

uint8_t drv_at24cxx_read(uint8_t addr)
{	
	uint8_t read_data=0;
	drv_iic_start();
	drv_iic_sendByte(0xa0);
	if(drv_wait_ACK()!=ACK)
	{
		drv_iic_stop();
		return 0;
	}

	drv_iic_sendByte(addr);
	if(drv_wait_ACK()!=ACK)
	{
		drv_iic_stop();
		return 0;
	}

	drv_iic_start();
	drv_iic_sendByte(0xa1);
	if(drv_wait_ACK()!=ACK)
	{
		drv_iic_stop();
		return 0;
	}
	read_data = drv_iic_readByte(NOACK);
	drv_iic_sendNOACK();
	drv_iic_stop();
	return read_data;
}
