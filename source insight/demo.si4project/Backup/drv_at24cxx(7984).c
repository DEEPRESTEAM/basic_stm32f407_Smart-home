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
	
}
