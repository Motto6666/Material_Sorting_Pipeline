#ifndef __BSP_TIM7_H
#define __BSP_TIM7_H

#include "stm32f10x.h"

#define            BASIC_TIM7                   TIM7
#define            BASIC_TIM7_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            BASIC_TIM7_CLK               RCC_APB1Periph_TIM7
#define            BASIC_TIM7_Period            1000-1
#define            BASIC_TIM7_Prescaler         71
#define            BASIC_TIM7_IRQ               TIM7_IRQn
#define            BASIC_TIM7_IRQHandler        TIM7_IRQHandler

#define            TIM7_ENABLE                  TIM_Cmd(BASIC_TIM7, ENABLE);
#define            TIM7_DISABLE                 TIM_Cmd(BASIC_TIM7, DISABLE);

extern volatile uint8_t TIM7_Count;
extern volatile uint8_t USART_RX_Over;

void BASIC_TIM7_Init(void);

#endif /*__BSP_TIM7_H*/
