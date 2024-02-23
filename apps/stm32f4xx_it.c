/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "drv_led.h"
#include "string.h"
#include "drv_systick.h"
#include "drv_led.h"
#include "drv_beep.h"
#include "FreeRTOS.h"
#include "task.h"


extern TaskHandle_t oledMenueTask;
/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
//void SVC_Handler(void)
//{
//}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{
//}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
//void SysTick_Handler(void)
//{
//}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f40xx.s/startup_stm32f427x.s/startup_stm32f429x.s).    */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
char buf[10];
uint8_t idex=0;
/*****************************************************
函数名称：USART1_IRQHandler

函数功能：串口1的中断服务函数

输入参数：无

输出参数：无

其它说明：
*******************************************************/

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE))//判断是否产生接收中断
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);//清除接收中断
		USART_SendData(USART1, USART_ReceiveData(USART1));//将接收到的数据通过串口1发送出去
//		buf[idex] = USART_ReceiveData(USART1);//将接收到的数据保存到buf
//			idex++;
	}	
//	if(USART_GetITStatus(USART1, USART_IT_IDLE))//判断是否产生空闲中断
//	{
//		USART_ReceiveData(USART1);//清楚空闲中断 
//		USART_SendData(USART1, 'a');
//		if(strcmp("open",(const char *)buf) == 0)//字符串比对
//		{
//			drv_led_open(GPIO_Pin_8);
//		}
//		if(strcmp("close",(const char *)buf) == 0)
//		{
//			drv_led_close(GPIO_Pin_8);
//		}
//		idex =0;//清空索引
//		memset(buf,0,sizeof(buf));//清空BUF
//	}
	
}


extern uint8_t  Uart2RecvBuf[128];
extern uint8_t  Uart2RecvLen;
void USART2_IRQHandler(void){
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  
	{
			//Uart2RecvLen = 0;
			//memset(Uart2RecvBuf,0,128);
			Uart2RecvBuf[Uart2RecvLen] = (uint8_t)USART_ReceiveData(USART2);
			Uart2RecvLen++;
			USART_ClearFlag(USART2, USART_IT_RXNE);
	}
//	if(USART_GetITStatus(USART2 , USART_IT_IDLE)){
//			
//			USART_ReceiveData(USART2);
////			memset(Uart2RecvBuf , 0 , sizeof(Uart2RecvBuf));
////			Uart2RecvLen = 0;
////			if(!strcmp((char *)Uart2RecvBuf , "openLed1")){
////				drv_led_open(GPIO_Pin_8);			
////			}
////			if(!strcmp((char *)Uart2RecvBuf , "closeLed1")){
////				drv_led_close(GPIO_Pin_8);
////			}
////			if(!strcmp((char *)Uart2RecvBuf , "openLed2")){
////				drv_led_open(GPIO_Pin_9);				
////			}
////			if(!strcmp((char *)Uart2RecvBuf , "closeLed2")){
////				drv_led_close(GPIO_Pin_9);
////			}
////			if(!strcmp((char *)Uart2RecvBuf , "openLed3")){
////				drv_led_open(GPIO_Pin_10);				
////			}
////			if(!strcmp((char *)Uart2RecvBuf , "closeLed3")){
////				drv_led_close(GPIO_Pin_10);
////			}
////			if(!strcmp((char *)Uart2RecvBuf , "openBeep")){
////				drv_beep_open();
////			}
////			if(!strcmp((char *)Uart2RecvBuf , "closeBeep")){
////				drv_beep_close();
////			}
////			if(!strcmp((char *)Uart2RecvBuf , "open")){
////				drv_led_open(GPIO_Pin_8);
////				drv_led_open(GPIO_Pin_9);
////				drv_led_open(GPIO_Pin_10);
////			}
////			if(!strcmp((char *)Uart2RecvBuf , "close")){
////				drv_led_close(GPIO_Pin_8);
////				drv_led_close(GPIO_Pin_9);
////				drv_led_close(GPIO_Pin_10);
////			}
////			if(Uart2RecvBuf[0] == '+'){
////			}
//			
//		}
}








//按键4外部中断，用于控制OLED翻页
uint8_t key4_flg=0;
uint8_t key2_flg=0;
uint8_t key3_flg=0;
void EXTI15_10_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line13);
	while(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 0);
	key4_flg++;
	if(key4_flg > 2)
		key4_flg = 0;
}

//按键1外部中断，控制LED灯的亮灭
uint8_t key1_flg= 0;
void EXTI4_IRQHandler(void){
	EXTI_ClearITPendingBit(EXTI_Line4);
	while(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4) == 0);
	//这个时候是手动控制
	if(key3_flg == 0){
		key1_flg = ~key1_flg;     
	}		
}

//按键2外部中断，控制蜂鸣器叫

void  EXTI9_5_IRQHandler(void){
	EXTI_ClearITPendingBit(EXTI_Line5);
	EXTI_ClearITPendingBit(EXTI_Line6);
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5) == 0){
		key2_flg = ~key2_flg;
	}
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6) == 0){
		key3_flg = ~key3_flg;
	}
}

void TIM6_DAC_IRQHandler(void)
{
}

/**
  * @}
  */ 

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
