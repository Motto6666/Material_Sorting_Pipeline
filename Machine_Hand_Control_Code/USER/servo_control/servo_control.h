#ifndef __SERVO_CONTROL_H
#define __SERVO_CONTROL_H

#include "stm32f10x.h"
#include "bsp_servo_gpio.h"

#define SERVO_NUM               6
#define HIGH                    1
#define LOW                     0
#define TIM2_INTERRUPT_TIME     TIM2->ARR

typedef struct 
{
	uint16_t 	Pulse_Width_Aim;	      //脉冲宽度目标值
 	uint16_t 	Time;	                  //执行时间		
	float 		Current_Pulse_Width;	  //当前脉冲宽度
	float 		Pulse_Width_Increment;	//脉冲宽度增量	
}Servo;

void Servo_Pulse_Width_Init(void);
void Servo_IO_Set(uint8_t Index, uint8_t Level) ; 
void Servo_Pin_Set(GPIO_TypeDef* GPIOx, uint16_t Pin, uint8_t Level);
void Servo_Pulse_Width_Control(void);
void Servo_Pulse_Width_Increment_Control(uint8_t Servo_Num); 
float Abs_Float(float Value); 


#endif /*SERVO_CONTROL_H*/
