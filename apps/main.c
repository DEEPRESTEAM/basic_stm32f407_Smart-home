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
//	//这里是定义优先级组		优先级组为2组，抢占和响应优先级最高都为8
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
		//printf("check = %d ,温度=%d , 湿度=%d \n\r" ,check , T  ,H);
		
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
					
					//判断LED灯的亮灭
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
					
					//判断蜂鸣器的开光状态
					if(GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_10) == 0){
						//蜂鸣器开
						OLED_ShowString(0 , 18 , "BEEP" , 16 , 1);
						OLED_ShowChinese(41 , 18 , 10 , 16 ,1);
						OLED_ShowChinese(57 , 18 , 11 , 16 ,1);
						OLED_ShowString(73 , 18 , ":" , 16 , 1);
						OLED_ShowChinese(89 , 18 , 16 , 16 ,1);
					}else{
						//蜂鸣器关
						OLED_ShowString(0 , 18 , "BEEP" , 16 , 1);
						OLED_ShowChinese(41 , 18 , 10 , 16 ,1);
						OLED_ShowChinese(57 , 18 , 11 , 16 ,1);
						OLED_ShowString(73 , 18 , ":" , 16 , 1);
						OLED_ShowChinese(89 , 18 , 15 , 16 ,1);
					}
					
					//OLED_Refresh();
					//这里需要实现led状态，蜂鸣器状态，以及光敏电阻的ADC值
					//首先通过按键外部中断触发LED灯与蜂鸣器?
					if(drv_adcdata_sum() > 200 && drv_adcdata_sum() < 2000){
							//正常亮度
						OLED_ShowChinese(18 , 48 , 4 , 16 , 1);
						OLED_ShowChinese(36 , 48 , 5 , 16 , 1);
						OLED_ShowString(65 , 48 , "ADC:" , 16 , 1);
						OLED_ShowNum(95,48 , drv_adcdata_sum() , 4 , 16 , 1);
						OLED_Refresh();
					}
					if(drv_adcdata_sum() > 2000 ){
						//过暗亮度
						OLED_ShowChinese(18 , 48 , 7 , 16 , 1);
						OLED_ShowChinese(36 , 48 , 8 , 16 , 1);
						OLED_ShowString(65 , 48 , "ADC:" , 16 , 1);
						OLED_ShowNum(95,48 , drv_adcdata_sum() , 4 , 16 , 1);
						OLED_Refresh();
					}
					if(drv_adcdata_sum() < 200 ){
							//过亮
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
	//当按键按下时
	//通过key1_flag来判断亮灯个数
	//首先判断是自动模式还是手动模式，自动模式下灯的亮度通过ADC的值进行变化
	if(key3_flg){
		//开始是手动模式
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
	//LED手动模式
	if(key1_flg){
		drv_led_open(GPIO_Pin_9);
	}else{
		drv_led_close(GPIO_Pin_9);
	}
}
void LEDMode2(){
	//自动模式通过PWM调节光的亮度，分为三档
	//drv_led_open(GPIO_Pin_8);
	//首先分为三档
	if(drv_adcdata_sum()*100/4095 > 48 ){
		//太暗了，需要调节光的亮度
		TIM_SetCompare1(TIM1 , 800);
	}
	if(drv_adcdata_sum()*100/4095 >=7 && drv_adcdata_sum()*100/4095 < 45){
		//正常，给一半的光的亮度
		TIM_SetCompare1(TIM1 , 200);
	}
	if(drv_adcdata_sum()*100/4095 < 5){
		//过亮，不给灯
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
	printf("手机端发送的信号=%s\n\r" , buf1);
	memset(Uart2RecvBuf , 0 , sizeof(Uart2RecvBuf));
	memset(buf1 , 0 , sizeof(buf1));
	indx1 = 0;
	Uart2RecvLen = 0;
}
