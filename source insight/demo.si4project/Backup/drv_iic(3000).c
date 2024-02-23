#include "drv_iic.h"
#include "drv_systick.h"


/******************************************
函数名：drv_iic_init

函数功能：IIC初始化

输入参数：无

输出参数：无

其它说明：//PB6-SCL
		  //PB7-SDA

*********************************************/
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
/******************************************
函数名：drv_iic_sdain

函数功能：将数据线（sda）设置为输入

输入参数：无

输出参数：无

其它说明：//PB6-SCL
		  //PB7-SDA

*********************************************/
void drv_iic_sdain(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

}
/******************************************
函数名：drv_iic_sdaout

函数功能：将数据线（sda）设置为输出

输入参数：无

输出参数：无

其它说明：//PB6-SCL
		  //PB7-SDA

*********************************************/
void drv_iic_sdaout(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

}
/******************************************
函数名：drv_iic_start

函数功能：IIC起始信号

输入参数：无

输出参数：无

其它说明：//PB6-SCL
		  //PB7-SDA
		  当时钟线为高电平时，数据线由高变低，产生一个有效的下降沿

*********************************************/
void drv_iic_start(void)
{
	SCL_L;	
	drv_iic_sdaout();	
	SDA_H;
	SCL_H;
	drv_systick_delayus(5);
	SDA_L;
	drv_systick_delayus(5);
	SCL_L;
}
/******************************************
函数名：drv_iic_stop

函数功能：IIC停止信号

输入参数：无

输出参数：无

其它说明：//PB6-SCL
		  //PB7-SDA

*********************************************/
void drv_iic_stop(void)
{
	SCL_L;	
	drv_iic_sdaout();
	
	SDA_L;
	SCL_H;
	drv_systick_delayus(5);
	SDA_H;
	drv_systick_delayus(5);
}
/******************************************
函数名：drv_iic_sendACK

函数功能：IIC发送应答信号

输入参数：无

输出参数：无

其它说明：//PB6-SCL
		  //PB7-SDA

*********************************************/
void drv_iic_sendACK(void)
{
	SCL_L;	
	drv_iic_sdaout();

	SDA_L;
	SCL_H;
	drv_systick_delayus(5);
	SCL_L;	
}
/******************************************
函数名：drv_iic_sendACK

函数功能：IIC发送应非答信号

输入参数：无

输出参数：无

其它说明：//PB6-SCL
		  //PB7-SDA

*********************************************/
void drv_iic_sendNOACK(void)
{
	SCL_L;	
	drv_iic_sdaout();

	SDA_H;
	SCL_H;
	drv_systick_delayus(5);
	SCL_L;	
}
/******************************************
函数名：drv_wait_ACK

函数功能：IIC等待应答信号

输入参数：无

输出参数：无

其它说明：//PB6-SCL
		  //PB7-SDA

*********************************************/

void drv_wait_ACK(void)
{
	uint16_t timeout=0;
	SCL_L;	
	drv_iic_sdain();

	SCL_H;
	while(SDA_READ)
	{
		timeout++;
		if(timeout > 300);
		{
			drv_iic_stop();
			return NOACK;
		}
	}
	
	return ACK;
}
/******************************************
函数名：drv_iic_sendByte

函数功能：IIC发送一个字节数据

输入参数：data 需要发送的数据

输出参数：无

其它说明：//PB6-SCL
		  //PB7-SDA

*********************************************/
void drv_iic_sendByte(uint8_t data)
{
	uint8_t i=0;
	SCL_L;	
	drv_iic_sdaout();

	for(i=0;i<8;i++)
	{
		if(data & 0x80)
		{
			SDA_H;
		}
		else
		{
			SDA_L;
		}
		SCL_H;
		drv_systick_delayus(5);
		SCL_L;
		drv_systick_delayus(5);
		data =data<<1;
	}
	SCL_L;

}
/******************************************
函数名：drv_iic_readByte

函数功能：IIC读取一个字节数据

输入参数：ack_flg ACK标志：为0 发送ACK信号、 为1 发送noACK信号

输出参数：无

其它说明：//PB6-SCL
		  //PB7-SDA

*********************************************/
uint8_t drv_iic_readByte(uint8_t ack_flg)
{
	uint8_t read_data=0;
	uint8_t i=0;
	SCL_L;	
	drv_iic_sdain();
	for(i=0;i<8;i++)
	{
		SCL_H;
		read_data = read_data << 1;
		if(SDA_READ)
		{
			read_data = read_data | 0x01;
		}
		drv_systick_delayus(5);
		SCL_L;
		drv_systick_delayus(5);
	}
	
	if(ack_flg == ACK)
	{
		drv_iic_sendACK();
	}
	else
	{
		drv_iic_sendNOACK();
	}
	SCL_L;
	return read_data;
}



