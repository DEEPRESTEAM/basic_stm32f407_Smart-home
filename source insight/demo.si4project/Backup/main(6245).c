#include "drv_led.h"
#include "drv_systick.h"
/*****************************************************
�������ƣ�delay

�������ܣ���ʱ����

�����������

�����������

����˵�����������ã��������ɾ��
*******************************************************/
void delay(uint32_t   tim)
{
	uint32_t i,j;
	for(i=0;i<tim;i++)
	{
		for(j=0;j<10000;j++);
	}
}

int main()
{	
	drv_led_init();
	while(1)
	{
		drv_led_open();
		delay(1000);
		drv_led_close();
		delay(1000);
	}
}


