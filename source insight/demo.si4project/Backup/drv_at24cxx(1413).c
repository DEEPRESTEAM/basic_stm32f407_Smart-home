void drv_24cxx_init(void)
{
	drv_iic_init();
}

void drv_24cxx_write(uint8_t addr,uint8_t data)
{
	drv_iic_start();
	drv_iic_sendByte(0xa0);
	if(drv_wait_ACK()!=ACK)
	{

	}


}
