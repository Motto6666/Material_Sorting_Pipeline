#include "bsp_tim2.h"
#include "servo_control.h"

void TIM2_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Ƕ�������жϿ�������ѡ�� */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/* ����USARTΪ�ж�Դ */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	/* �������ȼ�*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
	/* �����ȼ� */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
	/* ʹ���ж� */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	/* ��ʼ������NVIC */
	NVIC_Init(&NVIC_InitStructure);  
}

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
	TIM_Cmd(TIM2, ENABLE);  
}

void TIM2_Config_Init(void)
{
	TIM2_NVIC_Init();
	TIM2_Init();
}


extern Servo  Servo_Action[SERVO_NUM];
/*TIM2��ʱ�жϷ�����*/
void TIM2_IRQHandler(void) 
{
	static uint8_t Flag = 0;
	static uint8_t Servo_Num = 1;//���޸�
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //��� TIM2 �����жϷ������
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update ); //��� TIM2 �����жϱ�־
				
		if(Servo_Num == 7) 
		{
			Servo_Num = 1;
		}
		
		if(!Flag) 
		{
			TIM2->ARR = ( (uint32_t)Servo_Action[Servo_Num].Current_Pulse_Width );
			Servo_IO_Set(Servo_Num, HIGH);
		}
		else 
	  {
			TIM2->ARR = 2500 - ((uint32_t)Servo_Action[Servo_Num].Current_Pulse_Width);
			Servo_IO_Set(Servo_Num, LOW);
			Servo_Num ++;
		}
		Flag = !Flag;
	}
} 
