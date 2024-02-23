#include "drv_usart.h"
/******************************************
函数名：drv_usart1_init

函数功能：串口1初始化

输入参数：无

输出参数：无

其它说明：PA9-TX、PA10-RX
			波特率：115200

*********************************************/ 
void drv_usart1_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//定义GPIO结构
	USART_InitTypeDef USART_InitStruct;//定义USART结构体
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//开启GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//开启USART1时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;//GPIO的初始化
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);//指定引脚的服用功能
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	//串口初始化
	USART_InitStruct.USART_BaudRate = 115200;//波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//硬件流控
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//开启串口1的接收和发送功能
	USART_InitStruct.USART_Parity = USART_Parity_No;//校验位
	USART_InitStruct.USART_StopBits = USART_StopBits_1;//停止位
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//数据位
	USART_Init(USART1, &USART_InitStruct);//按照上面的串口配置初始化串口1
	USART_Cmd(USART1, ENABLE);//使能串口1
}

int fputc(int ch,FILE *f)
{
	USART_SendData(USART1, ch);


}
