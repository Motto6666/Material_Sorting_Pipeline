#ifndef __PHOTOELECTRIC_SENSOR_H
#define __PHOTOELECTRIC_SENSOR_H

#include "stm32f10x.h"

#define SENSOR_PORT_CLOCK        				RCC_APB2Periph_GPIOC
#define SENSOR_PORT              				GPIOC
#define SENSOR_PIN                  		GPIO_Pin_2
#define SENSOR_PORTSOURCE   						GPIO_PortSourceGPIOC
#define SENSOR_EXTI_GPIO_PINSOURCE  		GPIO_PinSource2
#define SENSOR_EXTI_LINE            		EXTI_Line2
#define SENSOR_EXTI_IRQn            		EXTI2_IRQn
#define SENSOR_EXTI_IRQHandler      		EXTI2_IRQHandler

#define PHOTOELECTRIC_SENSOR_ENABLE			{ EXTI->IMR |= SENSOR_EXTI_LINE; Check_Object = 0;} 
#define PHOTOELECTRIC_SENSOR_DISABLE		{ EXTI->IMR &= ~(SENSOR_EXTI_LINE); Check_Object = 0;}  

extern volatile uint8_t Check_Object;
void Photoelectric_Sensor_Init(void);

#endif /*__PHOTOELECTRIC_SENSOR_H*/

