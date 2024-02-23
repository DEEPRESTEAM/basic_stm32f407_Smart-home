#include "drv_esp12s.h"


void drv_esp12s_init(void){
		GPIO_InitTypeDef GPIO_InitStruct;
		USART_InitTypeDef USART_InitStruct;//����USART�ṹ��
		NVIC_InitTypeDef  NVIC_InitStruct;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//����GPIOAʱ��
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//����USART1ʱ��
	
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;//GPIO�ĳ�ʼ��
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOD, &GPIO_InitStruct);
	
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);//ָ�����ŵķ��ù���
		GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);
	
		//���ڳ�ʼ��
		USART_InitStruct.USART_BaudRate = 115200;//������
		USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ������
		USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;//��������2�Ľ��պͷ��͹���
		USART_InitStruct.USART_Parity = USART_Parity_No;//У��λ
		USART_InitStruct.USART_StopBits = USART_StopBits_1;//ֹͣλ
		USART_InitStruct.USART_WordLength = USART_WordLength_8b;//����λ
		USART_Init(USART2, &USART_InitStruct);//��������Ĵ������ó�ʼ������2
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//���ý����ж�
		//USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//���ÿ����ж�
		
		NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn; // �ж�ͨ����
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;//��Ӧ���ȼ�
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStruct);
		
		USART_ClearFlag(USART2, USART_FLAG_TC);
		
		USART_Cmd(USART2, ENABLE);//ʹ�ܴ���2

//	GPIO_InitTypeDef GPIO_InitStruct;
//	USART_InitTypeDef USART_InitStruct;
//	NVIC_InitTypeDef NVIC_InitStruct;
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
//	
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_Init(GPIOD,&GPIO_InitStruct);
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
//	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
//	
//	USART_InitStruct.USART_BaudRate = 115200;
//	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
//	USART_InitStruct.USART_Parity = USART_Parity_No;
//	USART_InitStruct.USART_StopBits = USART_StopBits_1;
//	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
//	USART_Init(USART2,&USART_InitStruct);

//	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
//	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStruct);
//	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
//	//USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);
//	USART_Cmd( USART2, ENABLE);
}

void UartSend(int ch)
{ 	
	USART_ClearFlag(USART2, USART_FLAG_TC);
	USART_SendData(USART2, ch);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET);
	USART_ClearFlag(USART2, USART_FLAG_TC);    
	return ;
}
 
void Uart2SendBuf(uint8_t *buf, int slen)
{
	int i = 0;
	for(i = 0; i < slen; i++)
	{
		UartSend(buf[i]);
	}
}


uint8_t  Uart2RecvBuf[128] = {0};
uint8_t  Uart2RecvLen = 0;
int timeout=0;
void wifi_start(void)
{
	//AT
	Uart2RecvLen = 0;
	memset(Uart2RecvBuf,0,128);
	Uart2SendBuf("AT\r\n", strlen("AT\r\n"));
	printf("AT\r\n");
	drv_systick_delayms(400);
	printf("Recv AtCmd Ack:%s\r\n", Uart2RecvBuf);
	//AT+CWMODE=2
	Uart2RecvLen = 0;
	memset(Uart2RecvBuf,0,128);
	Uart2SendBuf("AT+CWMODE=2\r\n", strlen("AT+CWMODE=2\r\n"));
	printf("AT+CWMODE=2\r\n");
	drv_systick_delayms(400);
	printf("Recv AtCmd Ack:%s\r\n", Uart2RecvBuf);
	//AT+CWSAP="LWX","1234567890",5,3
	Uart2RecvLen = 0;
	memset(Uart2RecvBuf,0,128);
	Uart2SendBuf("AT+CWSAP=\"aaa\",\"1111\",8,0\r\n", strlen("AT+CWSAP=\"aaa\",\"1111\",8,0\r\n"));
	printf("AT+CWSAP=\"aaa\",\"1111\",8,0\r\n");
	drv_systick_delayms(400);
	printf("Recv AtCmd Ack:%s\r\n", Uart2RecvBuf);
	//AT+CIPMUX=1
	Uart2RecvLen = 0;
	memset(Uart2RecvBuf,0,128);
	Uart2SendBuf("AT+CIPMUX=1\r\n", strlen("AT+CIPMUX=1\r\n"));
	printf("AT+CIPMUX=1\r\n");
	drv_systick_delayms(400);
	printf("Recv AtCmd Ack:%s\r\n", Uart2RecvBuf);
	//AT+CIPSEVER=1001
	Uart2RecvLen = 0;
	memset(Uart2RecvBuf,0,128);
	Uart2SendBuf("AT+CIPSERVER=1,1001\r\n", strlen("AT+CIPSERVER=1,1001\r\n"));
	printf("AT+CIPSERVER=1,1001\r\n");
	drv_systick_delayms(400);
	printf("Recv AtCmd Ack:%s\r\n", Uart2RecvBuf);
	Uart2RecvLen = 0;
	memset(Uart2RecvBuf,0,128);
}
