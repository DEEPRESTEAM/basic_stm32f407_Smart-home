#include "drv_timer.h"
/******************************************
��������drv_timer6base_init

�������ܣ�������ʱ��6��ʼ��

�����������

�����������

����˵����500MS�ж�һ��

*********************************************/ 
void drv_timer6base_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//���������ʱ���ṹ��
	NVIC_InitTypeDef  NVIC_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);//��ʱ��
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//ʱ�ӷָ�
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStruct.TIM_Period = 5000;//��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler =8400-1;//Ԥ��Ƶֵ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);//�����������õĲ�����ʼ����ʱ��6

	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);//���ö�ʱ��6�����жϣ������ж�Դ��
	

	NVIC_InitStruct.NVIC_IRQChannel = TIM6_DAC_IRQn;//�ж�ͨ����
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;//��Ӧ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//ʹ���ж�
	NVIC_Init(&NVIC_InitStruct);

	TIM_Cmd(TIM6, ENABLE);//ʹ�ܶ�ʱ��6
}

void drv_timer1_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;  //����ṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);

	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//ʱ�ӷָ�
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInitStruct.TIM_Period = 500;//��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler =1-1;//Ԥ��Ƶֵ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);//�����������õĲ�����ʼ����ʱ��1

	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 0;
	TIM_OC1Init(TIM1, &TIM_OCInitStruct);

	TIM_ARRPreloadConfig(TIM1, ENABLE);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
	TIM_Cmd(TIM1, ENABLE);

}
