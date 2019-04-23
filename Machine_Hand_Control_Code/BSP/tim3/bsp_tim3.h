#ifndef __BSP_TIM3_H
#define __BSP_TIM3_H

#include "stm32f10x.h"

#define            GENERAL_TIM3                   TIM3
#define            GENERAL_TIM3_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM3_CLK               RCC_APB1Periph_TIM3
#define            GENERAL_TIM3_Period            1000-1
#define            GENERAL_TIM3_Prescaler         71
#define            GENERAL_TIM3_IRQ               TIM3_IRQn
#define            GENERAL_TIM3_IRQHandler        TIM3_IRQHandler

#define            TIM3_ENABLE                  	TIM_Cmd(GENERAL_TIM3, ENABLE);
#define            TIM3_DISABLE                 	TIM_Cmd(GENERAL_TIM3, DISABLE);

#define 					 TRUE														1

extern volatile uint8_t TIM3_Count;
extern volatile uint8_t USART_RX_Over;

void TIM3_Config_Init(void);

#endif /*__BSP_TIM3_H*/
