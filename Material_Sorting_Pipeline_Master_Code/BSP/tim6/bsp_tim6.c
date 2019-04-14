#include "bsp_tim6.h"

// �ж����ȼ�����
static void BASIC_TIM6_NVIC_Config(void)//��ֲʱ���Ը���ʵ������������޸�
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	//��ֲʱ���Ը���ʵ������������޸�	
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM6_IRQ ;	//��ֲʱ���Ը���ʵ������������޸�
		// ���������ȼ�Ϊ 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 //��ֲʱ���Ը���ʵ������������޸�
	  // ������ռ���ȼ�Ϊ3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;	//��ֲʱ���Ը���ʵ������������޸�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

//���û�����ʱ��TIM6
static void BASIC_TIM6_Mode_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		// ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M,�ڲ�ʱ�ӿɹ̶�
    BASIC_TIM6_APBxClock_FUN(BASIC_TIM6_CLK, ENABLE);//��ֲʱ���Ը���ʵ��������޸�
	
		// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
    TIM_TimeBaseStructure.TIM_Period = BASIC_TIM6_Period;//��ֲʱ���Ը���ʵ��������޸�(BASIC_TIM_Period = 1000-1)�ص���⣡��

	  // ʱ��Ԥ��Ƶ��= CK_INT /��BASIC_TIM_Prescaler+1�� = 72M / 71+1 = 1M�����ж����� T = BASIC_TIM_Period * (1/1000000) = 1000 * (1/1000000) = 1ms �ص���⣡��
    TIM_TimeBaseStructure.TIM_Prescaler= BASIC_TIM6_Prescaler;//��ֲʱ���Ը���ʵ��������޸�(BASIC_TIM_Prescaler= 71)
	
	  // ��ʼ����ʱ��
    TIM_TimeBaseInit(BASIC_TIM6, &TIM_TimeBaseStructure);//��ֲʱ���Ը���ʵ��������޸�
		
		// ����������жϱ�־λ
    TIM_ClearFlag(BASIC_TIM6, TIM_FLAG_Update);//��ֲʱ���Ը���ʵ��������޸�
	  
		// �����������ж�
    TIM_ITConfig(BASIC_TIM6,TIM_IT_Update,ENABLE);//��ֲʱ���Ը���ʵ��������޸�
		
		// ʹ�ܶ�ʱ��
    TIM6_DISABLE ;//�ر�TIM6��ʱ��
}

void BASIC_TIM6_Init(void)
{
	BASIC_TIM6_NVIC_Config();
	BASIC_TIM6_Mode_Config();
}


 /**
  * @brief  Tim6��ʱ�жϷ�������20ms�ж�һ��
  * @param  ��Ҫ���ͳ�ȥ���ַ�����ָ��
  * @retval ��
  */
volatile uint32_t TIM6_Count;
void  BASIC_TIM6_IRQHandler (void) 
{
	if ( TIM_GetITStatus( BASIC_TIM6, TIM_IT_Update) != RESET ) 
	{	
		TIM6_Count++;
		TIM_ClearITPendingBit(BASIC_TIM6, TIM_FLAG_Update);  		 
	}		 	
}
