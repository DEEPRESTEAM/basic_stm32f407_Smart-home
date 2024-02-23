#define SCL_H	GPIO_SetBits(GPIOB, GPIO_Pin_6)//时钟线输出高电平
#define SCL_L	GPIO_ResetBits(GPIOB, GPIO_Pin_6)//时钟线输出低电平

#define SDA_H	GPIO_SetBits(GPIOB, GPIO_Pin_7)//数据线输出高电平
#define SDA_L	GPIO_ResetBits(GPIOB, GPIO_Pin_7)//数据线输出低电平

#define SDA_READ GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)//获取数据线上的数据


//PB6-SCL
//PB7-SDA
void drv_iic_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct
	GPIO_Init(GPIOB, GPIO_InitTypeDef * GPIO_InitStruct)

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


void drv_iic_in(void)
{


}

void drv_iic_out(void)
{


}
