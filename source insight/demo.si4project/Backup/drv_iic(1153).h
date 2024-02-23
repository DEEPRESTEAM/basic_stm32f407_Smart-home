#ifndef __DRV_IIC_H__
#define __DRV_IIC_H__
#include "stm32f4xx.h" 
#define SCL_H	GPIO_SetBits(GPIOB, GPIO_Pin_6)//时钟线输出高电平
#define SCL_L	GPIO_ResetBits(GPIOB, GPIO_Pin_6)//时钟线输出低电平

#define SDA_H	GPIO_SetBits(GPIOB, GPIO_Pin_7)//数据线输出高电平
#define SDA_L	GPIO_ResetBits(GPIOB, GPIO_Pin_7)//数据线输出低电平

#define SDA_READ GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)//获取数据线上的数据

#define NOACK 1
#define ACK 0

void drv_iic_init(void);
void drv_iic_sdain(void);
void drv_iic_sdaout(void);
void drv_iic_start(void);
void drv_iic_stop(void);
void drv_iic_sendACK(void);
void drv_iic_sendNOACK(void);
void drv_wait_ACK(void);
void drv_iic_sendByte(uint8_t data);
uint8_t drv_iic_readByte(uint8_t ack_flg);


#endif //__DRV_IIC_H__

