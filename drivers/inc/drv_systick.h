#ifndef	__DRV_SYSYTICK_H__
#define __DRV_SYSYTICK_H__
#include "stm32f4xx.h"
void drv_systick_init(uint32_t systick);

void drv_systick_delayms(uint16_t ms);
void drv_systick_delayus(uint16_t us);
#endif //__DRV_SYSYTICK_H__


