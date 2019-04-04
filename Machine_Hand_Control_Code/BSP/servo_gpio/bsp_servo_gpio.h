#ifndef __BSP_SERVO_GPIO_H
#define __BSP_SERVO_GPIO_H

#include "stm32f10x.h"

#define SERVO_1_PIN  GPIO_Pin_15
#define SERVO_2_PIN  GPIO_Pin_8
#define SERVO_3_PIN  GPIO_Pin_5
#define SERVO_4_PIN  GPIO_Pin_4
#define SERVO_5_PIN  GPIO_Pin_3
#define SERVO_6_PIN  GPIO_Pin_15

#define SERVO_PORT_1 GPIOA
#define SERVO_PORT_2 GPIOB


void Servo_GPIO_Init(void);


#endif /*__BSP_SERVO_GPIO_H*/
