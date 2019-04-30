#include "bsp_buzzer.h"

/**
  * @brief  ��ʼ��������
  * @retval ��
  */
void Buzzer_Init(void)
{
	/*��ʼ���������˿�ʱ��*/
	RCC_APB2PeriphClockCmd(BUZZER_PORT_CLOCK,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	
	/*��ʼ������������*/
	GPIO_InitStruct.GPIO_Pin = BUZZER_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	/*��ʼ���������˿�*/
	GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);
}


