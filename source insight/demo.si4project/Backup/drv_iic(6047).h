#ifndef __DRV_IIC_H__
#define __DRV_IIC_H__
#include "stm32f4xx.h" 
void drv_iic_init(void);
void drv_iic_sdain(void);
void drv_iic_sdaout(void);
void drv_iic_start(void);
void drv_iic_stop();


#endif //__DRV_IIC_H__

