#include "bsp_exti_key.h"

static void Key1_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	/*��һ���������ж����ȼ��ķ���*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/*�ڶ���������NVIC��ʼ���ṹ��*/
	NVIC_InitStruct.NVIC_IRQChannel = KEY1_EXTI_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	/*������������NVIC��ʼ�����������úõĽṹ��д���Ĵ�����*/
	NVIC_Init(&NVIC_InitStruct);
}

void Key1_EXTI_Config(void)
{ 
	GPIO_InitTypeDef GPIO_InitStruct;
  EXTI_InitTypeDef EXTI_InitStruct;		
	
	/*��ʼ��KEY1�˿�ʱ��*/
	RCC_APB2PeriphClockCmd(KEY1_GPIO_PORT_Clock,ENABLE);
	/*��ʼ��KEY1����*/
	GPIO_InitStruct.GPIO_Pin = KEY1_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	/*��ʼ��KEY1�˿�*/
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStruct);
	

	/*��ʼ�����ù��ܵ�AFIO����*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	/*��PAO���ӵ�EXTI��*/
	GPIO_EXTILineConfig(KEY1_EXTI_GPIO_PortSource,KEY1_EXTI_GPIO_PinSource);
	
	/*��ʼ��EXTI����ṹ��*/
	EXTI_InitStruct.EXTI_Line     = KEY1_EXTI_LINE;
	EXTI_InitStruct.EXTI_Mode     = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger  = EXTI_Trigger_Rising;
	EXTI_InitStruct.EXTI_LineCmd  = ENABLE;
	
	/*����EXTI��ʼ����������EXTI��ʼ���ṹ��д��Ĵ�����*/
	EXTI_Init(&EXTI_InitStruct);
	
}


/**
  * @brief  ��ʼ��Key1����
  * @retval ��
  */
void Key_Init(void)
{
	Key1_NVIC_Config();
	Key1_EXTI_Config();
}


 /**
  * @brief  ֹͣϵͳ���У��統�������º����ʹ��ͻ�е��ֹͣ����
  * @retval ��
  */
uint8_t Data_Stirng2[1];
void System_Stop(void)
{
	MOTOR_STOP;
	RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_EXECUTE_STOP, 0, Data_Stirng2, USART2_DEVICE);
	Clean_Screen(7);//���������������ַ�
	Display_Chinese_String( Chinese_Character_18  ,7  ,7 ,1 ,RED);//��ʾ��ϵͳֹͣ���У���
	Display_Rectangle();
}




 /**
  * @brief  KEY1_EXTI�жϷ�����
  * @retval ��
  */
void KEY1_EXTI_IRQHandler(void)
{
  if(EXTI_GetITStatus(KEY1_EXTI_LINE) != RESET)
	{
		EXTI_ClearITPendingBit(KEY1_EXTI_LINE);
		System_Stop();
	}
}
