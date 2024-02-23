#ifndef __DRV_ESP12S_H__
#define __DRV_ESP12S_H__
#include "stm32f4xx.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "drv_systick.h"

void drv_esp12s_init(void);

void UartSend(int ch);

void Uart2SendBuf(uint8_t *buf, int slen);

void wifi_start(void);
#endif//__DRV_ESP12S_H__
