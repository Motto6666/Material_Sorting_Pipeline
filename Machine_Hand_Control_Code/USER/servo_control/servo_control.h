#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include "stm32f10x.h"
#include "bsp_servo_gpio.h"

#define SERVO_NUM  6
#define HIGH       1
#define LOW        0

typedef struct 
{
	uint16_t 	Pulse_Width_Aim;	      //������Ŀ��ֵ
 	uint16_t 	Time;	                  //ִ��ʱ��		
	float 		Current_Pulse_Width;	  //��ǰ������
	float 		Pulse_Width_Increment;	//����������	
}Servo;

void Servo_Init(void);
void Servo_IO_Set(uint8_t Index, uint8_t Level) ; 
void Servo_Pin_Set(GPIO_TypeDef* GPIOx, uint16_t Pin, uint8_t Level); 

#endif /*SERVO_CONTROL_H*/
