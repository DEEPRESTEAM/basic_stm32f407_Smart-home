#ifndef __DRV_USART_H__
#define __DRV_USART_H__
#include "stm32f4xx.h"
#include "stdio.h"
void drv_usart1_init(void);
int fputc(int ch,FILE *f);
#endif //__DRV_USART_H__
