#ifndef __DRV_LED_H__
#define __DRV_LED_H__
#include "stm32f4xx.h" 
void drv_led_init(void);
void drv_led_open(uint16_t GPIO_Pin);
void drv_led_close(uint16_t GPIO_Pin);
#endif //__DRV_LED_H__

