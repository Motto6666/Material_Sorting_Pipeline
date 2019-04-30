#ifndef __BSP_BUZZER_H
#define __BSP_BUZZER_H

#include "stm32f10x.h"

#define BUZZER_PORT_CLOCK        RCC_APB2Periph_GPIOC
#define BUZZER_PORT              GPIOC
#define BUZZER_PIN               GPIO_Pin_1
#define BUZZER_NO								 GPIO_SetBits(BUZZER_PORT, BUZZER_PIN)
#define BUZZER_OFF							 GPIO_ResetBits(BUZZER_PORT, BUZZER_PIN)

void Buzzer_Init(void);

#endif /*__BSP_BUZZER_H*/
