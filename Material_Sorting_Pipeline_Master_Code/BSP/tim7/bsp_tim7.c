#include "bsp_tim7.h"

 /**
  * @brief  ����TIM7�ж����ȼ�
  */
static void BASIC_TIM7_NVIC_Config(void)//��ֲʱ���Ը���ʵ������������޸�
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	//��ֲʱ���Ը���ʵ������������޸�	
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM7_IRQ ;	//��ֲʱ���Ը���ʵ������������޸�
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 //��ֲʱ���Ը���ʵ������������޸�
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	//��ֲʱ���Ը���ʵ������������޸�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


 /**
  * @brief  TIM7��������
  */
static void BASIC_TIM7_Mode_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M,�ڲ�ʱ�ӿɹ̶�
    BASIC_TIM7_APBxClock_FUN(BASIC_TIM7_CLK, ENABLE);
	
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period = BASIC_TIM7_Period;//��ֲʱ���Ը���ʵ��������޸�(BASIC_TIM_Period = 1000-1)�ص���⣡��

	  // ʱ��Ԥ��Ƶ��= CK_INT /��BASIC_TIM_Prescaler+1�� = 72M / 71+1 = 1M�����ж����� T = BASIC_TIM_Period * (1/1000000) = 1000 * (1/1000000) = 1ms �ص���⣡��
    TIM_TimeBaseStructure.TIM_Prescaler= BASIC_TIM7_Prescaler;
		
	  // ��ʼ����ʱ��
    TIM_TimeBaseInit(BASIC_TIM7, &TIM_TimeBaseStructure);
		
		// ����������жϱ�־λ
    TIM_ClearFlag(BASIC_TIM7, TIM_FLAG_Update);
	  
		// �����������ж�
    TIM_ITConfig(BASIC_TIM7,TIM_IT_Update,ENABLE);
		
		// ʹ�ܶ�ʱ��
    TIM7_DISABLE;
}


 /**
  * @brief  TIM7��ʼ��
  */
void BASIC_TIM7_Init(void)
{
	BASIC_TIM7_NVIC_Config();
	BASIC_TIM7_Mode_Config();
}


 /**
  * @brief  Tim7��ʱ�жϷ�������1ms�ж�һ��,�����ж�USART1���������Ƿ������ϣ�����ʱ���
  * @param  ��Ҫ���ͳ�ȥ���ַ�����ָ��
  * @retval ��
  */
volatile uint8_t TIM7_Count = 10;
volatile uint8_t USART_RX_Over = 0;

void  BASIC_TIM7_IRQHandler (void) 
{
	if ( TIM_GetITStatus( BASIC_TIM7, TIM_IT_Update) != RESET ) 
	{	
		TIM7_Count--;
		TIM_ClearITPendingBit(BASIC_TIM7, TIM_FLAG_Update);
		
		if(TIM7_Count == 0)//��TIM7_CountΪ0�������ж�USART�������ݽ������
		{
			USART_RX_Over = 1;//��ʾ���ݽ������
			TIM7_Count = 10;//TIM7_Countֵ�ָ������ֵ����֤�´γ�ʱ��ⲻ����
			TIM7_DISABLE;
		}
	}		 	
}
