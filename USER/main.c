#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "beep.h"
#include "key.h"
#include "exti.h"
#include "snake.h"

//ALIENTEK ̽����STM32F407������ ʵ��5
//�ⲿ�ж�ʵ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//������������ӿƼ����޹�˾    
//���ߣ�����ԭ�� @ALIENTEK 

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);    //��ʼ����ʱ����
	uart_init(115200); 	//���ڳ�ʼ�� 
	LED_Init();				  //��ʼ��LED�˿�  
	LCD_Init();         //��ʼ��LCD�ӿ�
	BEEP_Init();        //��ʼ���������˿�
	EXTIX_Init();       //��ʼ���ⲿ�ж����� 
	
	while(1){
		LCD_Fill(0,0,500,800,0xFFFF);
		snake_main();
		delay_ms(1000);
		while(KEY_Scan(0)!=WKUP_PRES) delay_ms(100);
	}
}
