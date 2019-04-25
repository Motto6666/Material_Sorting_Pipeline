#include "bsp_motor_control.h"

void TB6612_AIN_Pin_Set(void)
{
	/*��ʼ��AIN�˿�ʱ��*/
	RCC_APB2PeriphClockCmd(AIN_GPIO_PORT_Clock,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	
	/*��ʼ��AIN1����*/
	GPIO_InitStruct.GPIO_Pin = AIN1_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	/*��ʼ��AIN1�˿�*/
	GPIO_Init(AIN_GPIO_PORT, &GPIO_InitStruct);

	
	/*��ʼ��AIN2����*/
	GPIO_InitStruct.GPIO_Pin = AIN2_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	/*��ʼ��AIN2�˿�*/
	GPIO_Init(AIN_GPIO_PORT, &GPIO_InitStruct);
}


void TB6612_PWMA_Pin_Set(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  /*��ʼ��ͨ��1�˿�ʱ��*/
	RCC_APB2PeriphClockCmd(GENERAL_TIM3_CH1_GPIO_CLK, ENABLE); 
	
	/*��ʼ��ͨ��1����*/
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM3_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	
	/*��ʼ��ͨ��1�˿�*/
  GPIO_Init(GENERAL_TIM3_CH1_PORT, &GPIO_InitStructure);
	
  /*������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M*/
	GENERAL_TIM3_APBxClock_FUN(GENERAL_TIM3_CLK,ENABLE);

	/*�������ڣ���������Ϊ100K*/	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	/*�Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�*/
	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM3_PERIOD;
	
	/* ����CNT��������ʱ�� = Fck_int/(psc+1)*/
	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM3_PRESCALER;
	
	/* ����������ģʽ������Ϊ���ϼ���*/
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;			
	
	/* ��ʼ����ʱ��*/
	TIM_TimeBaseInit(GENERAL_TIM3, &TIM_TimeBaseStructure);

	/*ռ�ձ�����*/	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	/*����ΪPWMģʽ1*/
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	
	/*���ʹ��*/
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	
	/*���ͨ����ƽ��������*/	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	/*���������*/
	TIM_OCInitStructure.TIM_Pulse = 3;//���������%30
	
	/*��ʼ�����ͨ��*/
	TIM_OC1Init(GENERAL_TIM3, &TIM_OCInitStructure);
	
	/*ʹ��TIM3�Զ���װ��*/
	TIM_OC1PreloadConfig(GENERAL_TIM3, TIM_OCPreload_Enable);//����ͨ��1
	
	/*�ر�TIM3��ʱ��*/
	GENERAL_TIM3_DISABLE;
	
}

void Motor_Init(void)
{
	TB6612_AIN_Pin_Set();
	TB6612_PWMA_Pin_Set();
}

void Motor_Speed_Change(uint16_t Motor_Speed)
{
	TIM_SetCompare1(GENERAL_TIM3,Motor_Speed);
}
