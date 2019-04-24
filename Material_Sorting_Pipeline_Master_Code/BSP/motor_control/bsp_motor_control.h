#ifndef __BSP_MOTOR_CONTROL_H
#define __BSP_MOTOR_CONTROL_H

#include "stm32f10x.h"

/******初始化TB6612电机驱动板上的AIN1、AIN2引脚******/
#define AIN_GPIO_PORT_Clock    		RCC_APB2Periph_GPIOA
#define AIN_GPIO_PORT          		GPIOA

#define AIN1_PIN               		GPIO_Pin_5
#define AIN2_PIN               		GPIO_Pin_7 	

#define AIN1_ON                		GPIO_SetBits(AIN_GPIO_PORT, AIN1_PIN)
#define AIN1_OFF               		GPIO_ResetBits(AIN_GPIO_PORT, AIN1_PIN)
     
#define AIN2_ON                		GPIO_SetBits(AIN_GPIO_PORT, AIN2_PIN)
#define AIN2_OFF               		GPIO_ResetBits(AIN_GPIO_PORT, AIN2_PIN)

#define Clockwise_Rotation       	{AIN1_ON;AIN2_OFF;}//顺时针转动
#define Anti_Clockwise_Rotation  	{AIN2_ON;AIN1_OFF;}//逆时针转动


/************通用定时器TIM3参数定义************/
/*TIM3 输出比较通道1*/
#define            GENERAL_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM_CH1_PORT          GPIOA
#define            GENERAL_TIM_CH1_PIN           GPIO_Pin_6

/*初始化TIM3*/
#define            GENERAL_TIM                   TIM3
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB1Periph_TIM3
#define            GENERAL_TIM_Period            9
#define            GENERAL_TIM_Prescaler         71

void Motor_Init(void);
void Motor_Speed_Change(uint16_t Motor_Speed);

#endif /*__BSP_MOTOR_CONTROL_H*/
