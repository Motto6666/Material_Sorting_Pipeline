#ifndef __BSP_MOTOR_CONTROL_H
#define __BSP_MOTOR_CONTROL_H

#include "stm32f10x.h"

/******初始化TB6612电机驱动板上的AIN1、AIN2引脚******/
#define TB6612_GPIO_PORT_CLOCK    								RCC_APB2Periph_GPIOA
#define TB6612_GPIO_PORT          								GPIOA

#define AIN1_PIN               										GPIO_Pin_5
#define AIN2_PIN               										GPIO_Pin_7 	

#define AIN1_ON                										GPIO_SetBits(TB6612_GPIO_PORT, AIN1_PIN)
#define AIN1_OFF               										GPIO_ResetBits(TB6612_GPIO_PORT, AIN1_PIN)
     
#define AIN2_ON                										GPIO_SetBits(TB6612_GPIO_PORT, AIN2_PIN)
#define AIN2_OFF               										GPIO_ResetBits(TB6612_GPIO_PORT, AIN2_PIN)

#define PWMA_PIN																	GPIO_Pin_6
#define PWMA_ON																		GPIO_SetBits(TB6612_GPIO_PORT, PWMA_PIN)
#define PWMA_OFF																	GPIO_ResetBits(TB6612_GPIO_PORT, PWMA_PIN)



#define MOTOR_TIM                   							TIM2
#define MOTOR_TIM_APBxClock_FUN     							RCC_APB1PeriphClockCmd
#define MOTOR_TIM_CLK               							RCC_APB1Periph_TIM2
#define MOTOR_TIM_Period            							10
#define MOTOR_TIM_Prescaler         							71
#define MOTOR_TIM_IRQ               							TIM2_IRQn
#define MOTOR_TIM_IRQHandler        							TIM2_IRQHandler

#define MOTOR_TIM_ENABLE            							TIM_Cmd(MOTOR_TIM, ENABLE);
#define MOTOR_TIM_DISABLE           							TIM_Cmd(MOTOR_TIM, DISABLE);
#define MOTOR_TIM_INTERRUPT_TIME     							MOTOR_TIM->ARR


/*电机运动控制*/
#define CLOCKWISE_ROTATION       									{AIN1_ON;AIN2_OFF;MOTOR_TIM_ENABLE;}//顺时针转动
#define ANTI_CLOCKWISE_ROTATION  								  {AIN2_ON;AIN1_OFF;MOTOR_TIM_ENABLE;}//逆时针转动
#define MOTOR_STOP																{AIN1_OFF;AIN2_OFF;PWMA_OFF;MOTOR_TIM_DISABLE;}//停止运转

void Motor_Init(void);
void TB6612_PWM_Pin_Control(void);

#endif /*__BSP_MOTOR_CONTROL_H*/
