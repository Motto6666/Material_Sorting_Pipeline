#ifndef __BSP_USART2_H
#define	__BSP_USART2_H


#include "stm32f10x.h"
#include "bsp_systick.h"
#include "bsp_tim7.h"
#include <stdio.h>

// 串口2-USART2
#define  DEBUG_USART2                   USART2
#define  DEBUG_USART2_CLK                RCC_APB1Periph_USART2
#define  DEBUG_USART2_APBxClkCmd         RCC_APB1PeriphClockCmd
#define  DEBUG_USART2_BAUDRATE           115200

// USART GPIO 引脚宏定义
#define  DEBUG_USART2_GPIO_CLK           (RCC_APB2Periph_GPIOA)
#define  DEBUG_USART2_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DEBUG_USART2_TX_GPIO_PORT       GPIOA   
#define  DEBUG_USART2_TX_GPIO_PIN        GPIO_Pin_2
#define  DEBUG_USART2_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART2_RX_GPIO_PIN        GPIO_Pin_3

#define  DEBUG_USART2_IRQ                USART2_IRQn
#define  DEBUG_USART2_IRQHandler         USART2_IRQHandler

extern uint8_t USART2_RX_Pack[50];
extern volatile uint16_t USART2_RX_Count;

void USART2_Config(void);
void USART2_Printf(uint8_t *Str);
void Debug_USART2_Printf(char *Str);//调试使用，调试完毕删除

#endif /* __BSP_USART2_H */
