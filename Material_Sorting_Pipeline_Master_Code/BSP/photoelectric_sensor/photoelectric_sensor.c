#include "photoelectric_sensor.h"

/**
  * @brief  ����NVIC
  * @retval ��
  */
static void Sensor_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	/*��һ���������ж����ȼ��ķ���*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/*�ڶ���������NVIC��ʼ���ṹ��*/
	NVIC_InitStruct.NVIC_IRQChannel = SENSOR_EXTI_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 5;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	/*������������NVIC��ʼ�����������úõĽṹ��д���Ĵ�����*/
	NVIC_Init(&NVIC_InitStruct);
}


/**
  * @brief  ��ʼ��Ҫ���ӵ�EXTI��Sensor_GPIO
  * @retval ��
  */
void Sensor_EXTI_Config(void)
{ 
	GPIO_InitTypeDef GPIO_InitStruct;
  EXTI_InitTypeDef EXTI_InitStruct;	
	
	/*��ʼ��Sensor�˿�ʱ��*/
	RCC_APB2PeriphClockCmd(SENSOR_PORT_CLOCK,ENABLE);
	/*��ʼ��Sensor����*/
	GPIO_InitStruct.GPIO_Pin = SENSOR_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	/*��ʼ��Sensor�˿�*/
	GPIO_Init(SENSOR_PORT, &GPIO_InitStruct);
	
	/*��ʼ�����ù��ܵ�AFIO����*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	/*��PAO���ӵ�EXTI��*/
	GPIO_EXTILineConfig(SENSOR_PORTSOURCE,SENSOR_EXTI_GPIO_PINSOURCE);
	
	/*��ʼ��EXTI����ṹ��*/
	EXTI_InitStruct.EXTI_Line     = SENSOR_EXTI_LINE;
	EXTI_InitStruct.EXTI_Mode     = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger  = EXTI_Trigger_Falling;
	EXTI_InitStruct.EXTI_LineCmd  = ENABLE;
	
	/*��ʼ��EXTI����*/
	EXTI_Init(&EXTI_InitStruct);
}


/**
  * @brief  ��ʼ����紫����
  * @retval ��
  */
void Photoelectric_Sensor_Init(void)
{
	Sensor_NVIC_Config();
	Sensor_EXTI_Config();
}


/**
  * @brief  �ⲿ�жϷ�����������紫������⵽����ʱ��ִ�иú���
  * @retval ��
  */
volatile uint8_t Check_Object = 0;//�����ж��Ƿ��⵽����,��ȡֵ��Χ��0��1

void SENSOR_EXTI_IRQHandler(void)
{	
  if(EXTI_GetITStatus(SENSOR_EXTI_LINE) != RESET)
	{
		Check_Object = 1;//��ʾ��⵽����
		EXTI_ClearITPendingBit(SENSOR_EXTI_LINE);
	}
}
