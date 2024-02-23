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
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);

	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	

	NVIC_InitStruct.NVIC_IRQChannel = TIM6_DAC_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	TIM_Cmd(TIM6, ENABLE);
}
