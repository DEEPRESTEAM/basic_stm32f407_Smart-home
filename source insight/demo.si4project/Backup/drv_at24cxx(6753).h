#ifndef __DRV_AT24CXX_H__
#define __DRV_AT24CXX_H__
#include "stm32f4xx.h" 
void drv_24cxx_init(void);
void drv_24cxx_write(uint8_t addr,uint8_t w_data);
uint8_t drv_at24cxx_read(uint8_t addr);

#endif //__DRV_AT24CXX_H__

