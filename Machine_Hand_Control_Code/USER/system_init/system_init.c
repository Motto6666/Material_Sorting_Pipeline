#include "system_init.h"

/**
	* @brief  ϵͳ��ʼ��
	* @retval ��
	*/
void System_Init(void)
{
	Servo_GPIO_Init();
	Servo_Pulse_Width_Init();
	USART1_Config();
	USART2_Config();
	TIM2_Config_Init();
	TIM3_Config_Init();
	SysTick_Delay_ms(2000);	
	Curl_Up_Action();//��е��ִ����������
}
