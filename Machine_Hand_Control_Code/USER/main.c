#include "stm32f10x.h"
#include "bsp_servo_gpio.h"
#include "servo_control.h"
#include "bsp_systick.h"
#include "bsp_usart1.h"
// #include <stdio.h>//����ʹ�ã��������ɾ��
#include "bsp_tim2.h"

// extern Servo  Servo_Action[SERVO_NUM];//����ʹ�ã��������ɾ��

// char s[] = {'0'};//����ʹ�ã��������ɾ��

int main(void) 
{	
	Servo_GPIO_Init();
	Servo_Init();
	USART1_Config();
	TIM2_Config_Init();
		
// 	sprintf(s,"%d\n",((uint32_t)Servo_Action[1].Current_Pulse_Width)); //����ʹ�ã��������ɾ��
// 	Printf(s);//����ʹ�ã��������ɾ��
// 	Printf("123456\n");//����ʹ�ã��������ɾ��

// 	
// 	Servo_IO_Set(6, LOW);//����ʹ�ã��������ɾ��
// 	SysTick_Delay_us(18500);//����ʹ�ã��������ɾ��
// 	Servo_IO_Set(6, HIGH);//����ʹ�ã��������ɾ��
// 	SysTick_Delay_us(1500);//����ʹ�ã��������ɾ��
// 	Servo_IO_Set(6, LOW);//����ʹ�ã��������ɾ��
// 	SysTick_Delay_us(18500);//����ʹ�ã��������ɾ��
	
	while(1)
	{
	}
}



