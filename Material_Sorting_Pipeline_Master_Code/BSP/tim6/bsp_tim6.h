#ifndef __BSP_TIM6_H
#define __BSP_TIM6_H

#include "stm32f10x.h"

#define            BASIC_TIM6                   TIM6
#define            BASIC_TIM6_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            BASIC_TIM6_CLK               RCC_APB1Periph_TIM6
#define            BASIC_TIM6_Period            50000-1
#define            BASIC_TIM6_Prescaler         71
#define            BASIC_TIM6_IRQ               TIM6_IRQn
#define            BASIC_TIM6_IRQHandler        TIM6_IRQHandler

#define            TIM6_ENABLE                  TIM_Cmd(BASIC_TIM6, ENABLE);
#define            TIM6_DISABLE                 TIM_Cmd(BASIC_TIM6, DISABLE);
#define						 FIVE_SECONDS                 100

extern volatile uint32_t TIM6_Count;

void BASIC_TIM6_Init(void);
void TIM6_Shut_Down(void);

#endif /*__BSP_TIM6_H*/
