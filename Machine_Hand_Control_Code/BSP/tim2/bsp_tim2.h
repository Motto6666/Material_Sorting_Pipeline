#ifndef __BSP_TIM2_H
#define	__BSP_TIM2_H


#include "stm32f10x.h"

#define TIM2_ENABLE				TIM_Cmd(TIM2, ENABLE);
#define TIM2_DISABLE			TIM_Cmd(TIM2, DISABLE);

void TIM2_Config_Init(void);

#endif /* __BSP_TIM2_H */
