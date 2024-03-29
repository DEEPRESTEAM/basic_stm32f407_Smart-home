#define SCL_H	GPIO_SetBits(GPIOB, GPIO_Pin_6)//时钟线输出高电平
#define SCL_L	GPIO_ResetBits(GPIOB, GPIO_Pin_6)//时钟线输出低电平

#define SDA_H	GPIO_SetBits(GPIOB, GPIO_Pin_7)//数据线输出高电平
#define SDA_L	GPIO_ResetBits(GPIOB, GPIO_Pin_7)//数据线输出低电平

#define SDA_READ GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)//获取数据线上的数据


//PB6-SCL
//PB7-SDA
void drv_iic_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

}
void drv_iic_sdain(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

}

void drv_iic_sdaout(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

}

void drv_iic_start(void)
{

}
void drv_iic_stop()
{

}

void drv_iic_sendACK(void)
{

}
void drv_iic_sendNOACK(void)
{

}

void drv_wait_ACK(void)
{

}

void drv_iic_sendByte(uint8_t data)
{


}

uint8_t drv_iic_readByte(uint8_t adc_flg)
{


}



