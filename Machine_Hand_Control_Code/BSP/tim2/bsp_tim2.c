#include "bsp_tim2.h"
#include "servo_control.h"

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
void TIM2_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Ƕ�������жϿ�������ѡ�� */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	/* ����USARTΪ�ж�Դ */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	/* �������ȼ�*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	/* �����ȼ� */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  
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
void TIM2_Init(void) 
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/*ʱ�� TIM2 ʹ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 	
	/*�����Զ���װ�ؼĴ������ڵ�ֵ*/
	TIM_TimeBaseStructure.TIM_Period = 	20000; 
	/*����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ*/
	TIM_TimeBaseStructure.TIM_Prescaler =71; 
	/*ʱ�ӷ�Ƶ����*/
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	/*TIM2 ���ϼ���*/
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	/*��ʼ�� TIM2*/
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	/*����ARR�ϵ�TIMX��Χ�豸Ԥ���ؼĴ���*/
	TIM_ARRPreloadConfig(TIM2, DISABLE);
	/*�����������ж�*/
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE );  
	/*ʹ�� TIM2*/
	TIM2_ENABLE;  
}

 /**
  * @brief  ��ʼ����ʱ��TIM2
  * @param  ��
  * @retval ��
  */
void TIM2_Config_Init(void)
{
	TIM2_NVIC_Init();
	TIM2_Init();
}


 /**
  * @brief  TIM2��ʱ�жϷ�����
  * @param  ��
  * @retval ��
  */
volatile uint8_t Flag = 0;
void TIM2_IRQHandler(void) 
{
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update ); 
		Servo_Pulse_Width_Control();
		Flag = !Flag;
	}
}


