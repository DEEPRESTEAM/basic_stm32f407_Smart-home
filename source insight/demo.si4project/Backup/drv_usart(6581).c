#include "drv_usart.h"
/******************************************
��������drv_usart1_init

�������ܣ�����1��ʼ��

�����������

�����������

����˵����PA9-TX��PA10-RX
			�����ʣ�115200

*********************************************/ 
void drv_usart1_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;//����GPIO�ṹ
	USART_InitTypeDef USART_InitStruct;//����USART�ṹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//����GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//����USART1ʱ��
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;//GPIO�ĳ�ʼ��
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);//ָ�����ŵķ��ù���
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	//���ڳ�ʼ��
	USART_InitStruct.USART_BaudRate = 115200;//������
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ������
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//��������1�Ľ��պͷ��͹���
	USART_InitStruct.USART_Parity = USART_Parity_No;//У��λ
	USART_InitStruct.USART_StopBits = USART_StopBits_1;//ֹͣλ
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//����λ
	USART_Init(USART1, &USART_InitStruct);//��������Ĵ������ó�ʼ������1
	USART_Cmd(USART1, ENABLE);//ʹ�ܴ���1
}

int fputc(int ch,FILE *f)
{
	USART_SendData(USART1, ch);


}
