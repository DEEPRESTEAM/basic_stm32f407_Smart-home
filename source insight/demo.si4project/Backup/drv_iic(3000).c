#include "drv_iic.h"
#include "drv_systick.h"


/******************************************
��������drv_iic_init

�������ܣ�IIC��ʼ��

�����������

�����������

����˵����//PB6-SCL
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
��������drv_iic_sdain

�������ܣ��������ߣ�sda������Ϊ����

�����������

�����������

����˵����//PB6-SCL
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
��������drv_iic_sdaout

�������ܣ��������ߣ�sda������Ϊ���

�����������

�����������

����˵����//PB6-SCL
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
��������drv_iic_start

�������ܣ�IIC��ʼ�ź�

�����������

�����������

����˵����//PB6-SCL
		  //PB7-SDA
		  ��ʱ����Ϊ�ߵ�ƽʱ���������ɸ߱�ͣ�����һ����Ч���½���

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
��������drv_iic_stop

�������ܣ�IICֹͣ�ź�

�����������

�����������

����˵����//PB6-SCL
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
��������drv_iic_sendACK

�������ܣ�IIC����Ӧ���ź�

�����������

�����������

����˵����//PB6-SCL
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
��������drv_iic_sendACK

�������ܣ�IIC����Ӧ�Ǵ��ź�

�����������

�����������

����˵����//PB6-SCL
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
��������drv_wait_ACK

�������ܣ�IIC�ȴ�Ӧ���ź�

�����������

�����������

����˵����//PB6-SCL
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
��������drv_iic_sendByte

�������ܣ�IIC����һ���ֽ�����

���������data ��Ҫ���͵�����

�����������

����˵����//PB6-SCL
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
��������drv_iic_readByte

�������ܣ�IIC��ȡһ���ֽ�����

���������ack_flg ACK��־��Ϊ0 ����ACK�źš� Ϊ1 ����noACK�ź�

�����������

����˵����//PB6-SCL
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



