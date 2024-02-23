#include "drv_led.h"
#include "drv_systick.h"
#include "drv_key.h"
#include "drv_usart.h"
#include "drv_exti.h"
#include "drv_timer.h"
#include "drv_at24cxx.h"
#include "drv_spi.h"
#include "drv_w25qxx.h"
#include "drv_dma.h"
#include "drv_adc.h"
#include "oled.h"
#include "bmp.h"
#include "FreeRTOS.h"
#include "task.h"
#include "drv_timer.h"
#include "drv_dht11.h"
#include "drv_beep.h"
#include "drv_esp12s.h"
#define stack_size 128

void oledMenue(u8 * temp1,u8 * temp2 , u8 * temp3);
void LEDController(void);
void beepController(void);
void LEDMode1(void);
void LEDMode2(void);
void wifiIfon(void);

extern uint16_t adc_data[100];
extern uint8_t key1_flg;
extern uint8_t key2_flg;
extern uint8_t key3_flg;
extern uint8_t key4_flg;
extern uint8_t  Uart2RecvBuf[128];
extern uint8_t  Uart2RecvLen;

uint8_t led0TempClear = 0;
uint8_t led1TempClear = 0;
uint8_t led2TempClear = 0;
uint8_t led3TempClear = 0;
uint8_t led4TempClear = 0;
u8 T = 0;
u8 H = 0;
u8 ledTemp = 0;
char buf1[20] = {0};
int indx1= 0;

TaskHandle_t oledMenueTask;

int main()
{	
	u8 temp1 =0;
	u8 temp2 = 0;
	u8 temp3 = 0;
	
	
	
//	drv_esp12s_init();
//	//�����Ƕ������ȼ���		���ȼ���Ϊ2�飬��ռ����Ӧ���ȼ���߶�Ϊ8
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
// 	OLED_Init();
//	drv_led_init();
//	drv_exti_init();
//	drv_exitKey1_init();
//	drv_exitKey2_init();
//	drv_exitKey3_init();

//	drv_timer1_init();
//	drv_beep_init();
//		drv_usart1_init();
		drv_esp12s_init();
//	drv_adc_init();
//	drv_systick_init(168);	
//	DHT11_Init();
//	
//	wifi_start();
	
	
	while(1)
	{
//		DHT11_Read_Data(&T , &H);
//		oledMenue(&temp1,&temp2 , &temp3);
//		LEDController();
//		beepController();
//		wifiIfon();
		//drv_systick_delayms(2000);
		//printf("check = %d ,�¶�=%d , ʪ��=%d \n\r" ,check , T  ,H);
		
	}
}

void oledMenue(u8 * temp1,u8 * temp2 , u8 * temp3){
			switch(key4_flg){
				case 0:
					if(*temp1 == 0){
						OLED_Clear();
						(*temp1)++;
						*temp2 = 0;
						*temp3 = 0;
					}
					OLED_ShowChinese(26,18,0,16,1);
					OLED_ShowChinese(44,18,1,16,1);
					OLED_ShowChinese(62,18,2,16,1);
					OLED_ShowChinese(80,18,3,16,1);
					OLED_Refresh();
					break;
				case 1:
					if(*temp2 == 0){
						OLED_Clear();
						(*temp2)++;
						*temp1 = 0;
						*temp3 = 0;
					}
					OLED_ShowChinese(26,0,0,16,1);
					OLED_ShowChinese(44,0,1,16,1);
					OLED_ShowChinese(62,0,2,16,1);
					OLED_ShowChinese(80,0,3,16,1);
					OLED_ShowString(0 , 32 , "LED" , 16 , 1);
					OLED_ShowChinese(25 , 32 , 12 , 16 ,1);
					OLED_ShowChinese(41 , 32 , 10 , 16 ,1);
					OLED_ShowChinese(57 , 32 , 11 , 16 ,1);
					OLED_ShowString(73 , 32 , ":" , 16 , 1);
					
					//�ж�LED�Ƶ�����
					if(GPIO_ReadInputDataBit(GPIOE , GPIO_Pin_9) == 0){
						OLED_ShowNum(80 , 32 , 2 , 1, 16 , 1);
						OLED_ShowChinese(85 , 32 , 14 , 16 , 1);
						OLED_ShowChinese(101 , 32 , 12 , 16 , 1);
						OLED_ShowChinese(117 , 32 , 6 , 16 , 1);
					}else{
						OLED_ShowNum(80 , 32 , 2 , 1, 16 , 1);
						OLED_ShowChinese(85 , 32 , 14 , 16 , 1);
						OLED_ShowChinese(101 , 32 , 12 , 16 , 1);
						OLED_ShowChinese(117 , 32 , 9 , 16 , 1);
					}
					
					//�жϷ������Ŀ���״̬
					if(GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_10) == 0){
						//��������
						OLED_ShowString(0 , 18 , "BEEP" , 16 , 1);
						OLED_ShowChinese(41 , 18 , 10 , 16 ,1);
						OLED_ShowChinese(57 , 18 , 11 , 16 ,1);
						OLED_ShowString(73 , 18 , ":" , 16 , 1);
						OLED_ShowChinese(89 , 18 , 16 , 16 ,1);
					}else{
						//��������
						OLED_ShowString(0 , 18 , "BEEP" , 16 , 1);
						OLED_ShowChinese(41 , 18 , 10 , 16 ,1);
						OLED_ShowChinese(57 , 18 , 11 , 16 ,1);
						OLED_ShowString(73 , 18 , ":" , 16 , 1);
						OLED_ShowChinese(89 , 18 , 15 , 16 ,1);
					}
					
					//OLED_Refresh();
					//������Ҫʵ��led״̬��������״̬���Լ����������ADCֵ
					//����ͨ�������ⲿ�жϴ���LED���������?
					if(drv_adcdata_sum() > 200 && drv_adcdata_sum() < 2000){
							//��������
						OLED_ShowChinese(18 , 48 , 4 , 16 , 1);
						OLED_ShowChinese(36 , 48 , 5 , 16 , 1);
						OLED_ShowString(65 , 48 , "ADC:" , 16 , 1);
						OLED_ShowNum(95,48 , drv_adcdata_sum() , 4 , 16 , 1);
						OLED_Refresh();
					}
					if(drv_adcdata_sum() > 2000 ){
						//��������
						OLED_ShowChinese(18 , 48 , 7 , 16 , 1);
						OLED_ShowChinese(36 , 48 , 8 , 16 , 1);
						OLED_ShowString(65 , 48 , "ADC:" , 16 , 1);
						OLED_ShowNum(95,48 , drv_adcdata_sum() , 4 , 16 , 1);
						OLED_Refresh();
					}
					if(drv_adcdata_sum() < 200 ){
							//����
						OLED_ShowChinese(18 , 48 , 7 , 16 , 1);
						OLED_ShowChinese(36 , 48 , 6 , 16 , 1);
						OLED_ShowString(65 , 48 , "ADC:" , 16 , 1);
						OLED_ShowNum(95,48 , drv_adcdata_sum() , 4 , 16 , 1);
						OLED_Refresh();
					}				
					break;
				case 2:
					if(*temp3 == 0){
						OLED_Clear();
						(*temp3)++;
						*temp1 = 0;
						*temp2 = 0;
					}
					OLED_ShowChinese(26,0,0,16,1);
					OLED_ShowChinese(44,0,1,16,1);
					OLED_ShowChinese(62,0,2,16,1);
					OLED_ShowChinese(80,0,3,16,1);
					
					OLED_ShowChinese(18 , 48 , 17 , 16 , 1);
					OLED_ShowChinese(36 , 48 , 19 , 16 , 1);
					OLED_ShowNum(72 , 48 , T , 3 , 16 , 1);
					
					
					OLED_ShowChinese(18 , 28 , 18 , 16 , 1);
					OLED_ShowChinese(36 , 28 , 19 , 16 , 1);
					OLED_ShowNum(72 , 28 , H , 3 , 16 , 1);
					OLED_Refresh();
					break;
	}
}

void LEDController(){
	//����������ʱ
	//ͨ��key1_flag���ж����Ƹ���
	//�����ж����Զ�ģʽ�����ֶ�ģʽ���Զ�ģʽ�µƵ�����ͨ��ADC��ֵ���б仯
	if(key3_flg){
		//��ʼ���ֶ�ģʽ
		drv_timer1_init();
		LEDMode2();
	}else{
		if(ledTemp == 0){
			drv_led_init();
		}
		LEDMode1();
	}
}


void LEDMode1(){
	//LED�ֶ�ģʽ
	if(key1_flg){
		drv_led_open(GPIO_Pin_9);
	}else{
		drv_led_close(GPIO_Pin_9);
	}
}
void LEDMode2(){
	//�Զ�ģʽͨ��PWM���ڹ�����ȣ���Ϊ����
	//drv_led_open(GPIO_Pin_8);
	//���ȷ�Ϊ����
	if(drv_adcdata_sum()*100/4095 > 48 ){
		//̫���ˣ���Ҫ���ڹ������
		TIM_SetCompare1(TIM1 , 800);
	}
	if(drv_adcdata_sum()*100/4095 >=7 && drv_adcdata_sum()*100/4095 < 45){
		//��������һ��Ĺ������
		TIM_SetCompare1(TIM1 , 200);
	}
	if(drv_adcdata_sum()*100/4095 < 5){
		//������������
		TIM_SetCompare1(TIM1 , 0);
	}
}


void beepController(){
	if(key2_flg){
		drv_beep_open();
	}else{
		drv_beep_close();
	}
}



void wifiIfon(void){
	int flag = 0;
	int i = 0 ;
	if(Uart2RecvLen != 0){
		for(i = 0 ; i < Uart2RecvLen ; i++){
			if(Uart2RecvBuf[i] == ':'){
				while(1){
					if(Uart2RecvBuf[i] == '\n'){
						flag = 1;
						break;
					}
					i++;
					buf1[indx1++] = Uart2RecvBuf[i];
				}
			}
			if(flag){
				break;
			}
		}
	}else{
		printf("1\n\r");
		return;
	}
	if(!strcmp((char *)buf1 , "openLed1")){
		ledTemp = 1;
		drv_led_open(GPIO_Pin_8);			
	}
	if(!strcmp((char *)buf1 , "closeLed1")){
		ledTemp = 0;
		drv_led_close(GPIO_Pin_8);
	}
	if(!strcmp((char *)buf1 , "openLed2")){
		ledTemp = 1;
		key1_flg = 1;
		drv_led_open(GPIO_Pin_9);				
	}
	if(!strcmp((char *)buf1 , "closeLed2")){
		ledTemp = 0;
		key1_flg = 0;
		drv_led_close(GPIO_Pin_9);
	}
	if(!strcmp((char *)buf1 , "openLed3")){
		ledTemp = 1;
		drv_led_open(GPIO_Pin_10);				
	}
	if(!strcmp((char *)buf1 , "closeLed3")){
		ledTemp = 0;
		drv_led_close(GPIO_Pin_10);
	}
	if(!strcmp((char *)buf1 , "openBeep")){
		key2_flg = 1;
		drv_beep_open();
	}
	if(!strcmp((char *)buf1, "closeBeep")){
		key2_flg = 0;
		drv_beep_close();
	}
	if(!strcmp((char *)buf1 , "open")){
		ledTemp = 1;
		key1_flg = 1;
		drv_led_open(GPIO_Pin_8);
		drv_led_open(GPIO_Pin_9);
		drv_led_open(GPIO_Pin_10);
	}
	if(!strcmp((char *)buf1 , "close")){
		key1_flg = 0;
		ledTemp = 0;
		drv_led_close(GPIO_Pin_8);
		drv_led_close(GPIO_Pin_9);
		drv_led_close(GPIO_Pin_10);
	}
	printf("�ֻ��˷��͵��ź�=%s\n\r" , buf1);
	memset(Uart2RecvBuf , 0 , sizeof(Uart2RecvBuf));
	memset(buf1 , 0 , sizeof(buf1));
	indx1 = 0;
	Uart2RecvLen = 0;
}
