#include "bsp_motor_control.h"

void TB6612_Pin_Set(void)
{
	/*��ʼ��AIN�˿�ʱ��*/
	RCC_APB2PeriphClockCmd(TB6612_GPIO_PORT_CLOCK,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	
	/*��ʼ��AIN1����*/
	GPIO_InitStruct.GPIO_Pin = AIN1_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	/*��ʼ��AIN1�˿�*/
	GPIO_Init(TB6612_GPIO_PORT, &GPIO_InitStruct);
	
	/*��ʼ��AIN2����*/
	GPIO_InitStruct.GPIO_Pin = AIN2_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	/*��ʼ��AIN2�˿�*/
	GPIO_Init(TB6612_GPIO_PORT, &GPIO_InitStruct);
	
	/*��ʼ��PWMA_PIN����*/
	GPIO_InitStruct.GPIO_Pin = PWMA_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	/*��ʼ��PWMA_PIN�˿�*/
	GPIO_Init(TB6612_GPIO_PORT, &GPIO_InitStruct);
	
}


 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
void MOTOR_TIM_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Ƕ�������жϿ�������ѡ�� */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	/* ����USARTΪ�ж�Դ */
	NVIC_InitStructure.NVIC_IRQChannel = MOTOR_TIM_IRQ;  
	/* �������ȼ�*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	/* �����ȼ� */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;  
	/* ʹ���ж� */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	/* ��ʼ������NVIC */
	NVIC_Init(&NVIC_InitStructure);  
}

 /**
  * @brief  ����TIM2��ʱ��
  * @param  ��
  * @retval ��
  */
void MOTOR_TIM_Init(void) 
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/*ʱ�� TIM2 ʹ��*/
	MOTOR_TIM_APBxClock_FUN(MOTOR_TIM_CLK, ENABLE); 	
	/*�����Զ���װ�ؼĴ������ڵ�ֵ*/
	TIM_TimeBaseStructure.TIM_Period = MOTOR_TIM_Period; 
	/*����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ*/
	TIM_TimeBaseStructure.TIM_Prescaler = MOTOR_TIM_Prescaler; 
	/*ʱ�ӷ�Ƶ����*/
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	/*TIM2 ���ϼ���*/
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	/*��ʼ�� TIM2*/
	TIM_TimeBaseInit(MOTOR_TIM, &TIM_TimeBaseStructure); 
	/*����ARR�ϵ�TIMX��Χ�豸Ԥ���ؼĴ���*/
	TIM_ARRPreloadConfig(MOTOR_TIM, DISABLE);
	/*�����������ж�*/
	TIM_ITConfig(MOTOR_TIM,TIM_IT_Update,ENABLE );  
	/*�ر�TIM2*/
	MOTOR_TIM_DISABLE;  
}

 /**
  * @brief  ��ʼMOTOR_TIM��ʱ������TIM2��ʱ��
  * @param  ��
  * @retval ��
  */
void MOTOR_TIM_Config_Init(void)
{
	MOTOR_TIM_NVIC_Init();
	MOTOR_TIM_Init();
}


 /**
  * @brief  ��ʼ�����
  * @param  ��
  * @retval ��
  */
void Motor_Init(void)
{
	TB6612_Pin_Set();
	MOTOR_TIM_Config_Init();
}


/**
  * @brief  MOTOR_TIM(TIM2)��ʱ�жϷ�����
  * @param  ��
  * @retval ��
  */
volatile uint8_t Flag = 0;
void MOTOR_TIM_IRQHandler(void) 
{
	
	if (TIM_GetITStatus(MOTOR_TIM, TIM_IT_Update) != RESET) 
	{
		TIM_ClearITPendingBit(MOTOR_TIM, TIM_IT_Update ); 
		TB6612_PWM_Pin_Control();
		Flag = !Flag;
	}
}


/**
  * @brief  �������Ÿߵ͵�ƽʱ�䣬ģ��̼������PWM����������������Ϊ10us
  * @param  ��
  * @retval ��
  */

void TB6612_PWM_Pin_Control(void)
{
	if(!Flag) 
		{
			MOTOR_TIM_INTERRUPT_TIME = 4;//�趨TIM2��ʱ�ж�ʱ��Ϊ4us�����ߵ�ƽ����ʱ��Ϊ4us
			PWMA_ON;		 
		}
		else 
		{
			MOTOR_TIM_INTERRUPT_TIME = 6;//�趨TIM2��ʱ�ж�ʱ��Ϊ6us�����ߵ�ƽ����ʱ��Ϊ6us
			PWMA_OFF;
		}
}
