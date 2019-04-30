#include "bsp_buzzer.h"

/**
  * @brief  初始化蜂鸣器
  * @retval 无
  */
void Buzzer_Init(void)
{
	/*初始化蜂鸣器端口时钟*/
	RCC_APB2PeriphClockCmd(BUZZER_PORT_CLOCK,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	
	/*初始化蜂鸣器引脚*/
	GPIO_InitStruct.GPIO_Pin = BUZZER_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	/*初始化蜂鸣器端口*/
	GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);
}


