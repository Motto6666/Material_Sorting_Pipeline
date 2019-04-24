#include "bsp_motor_control.h"

void TB6612_AIN_Pin_Set(void)
{
	/*初始化AIN端口时钟*/
	RCC_APB2PeriphClockCmd(AIN_GPIO_PORT_Clock,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	
	/*初始化AIN1引脚*/
	GPIO_InitStruct.GPIO_Pin = AIN1_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	/*初始化AIN1端口*/
	GPIO_Init(AIN_GPIO_PORT, &GPIO_InitStruct);

	
	/*初始化AIN2引脚*/
	GPIO_InitStruct.GPIO_Pin = AIN2_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	/*初始化AIN2端口*/
	GPIO_Init(AIN_GPIO_PORT, &GPIO_InitStruct);
}


void TB6612_PWMA_Pin_Set(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  /*初始化通道1端口时钟*/
	RCC_APB2PeriphClockCmd(GENERAL_TIM_CH1_GPIO_CLK, ENABLE); 
	
	/*初始化通道1引脚*/
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	
	/*初始化通道1端口*/
  GPIO_Init(GENERAL_TIM_CH1_PORT, &GPIO_InitStructure);
	

  /*开启定时器时钟,即内部时钟CK_INT=72M*/
	GENERAL_TIM_APBxClock_FUN(GENERAL_TIM_CLK,ENABLE);

/*--------------------时基结构体初始化-------------------------*/
	// 配置周期，这里配置为100K
	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;		
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;			
	// 初始化定时器
	TIM_TimeBaseInit(GENERAL_TIM, &TIM_TimeBaseStructure);

	/*--------------------输出比较结构体初始化-------------------*/	
	// 占空比配置	
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// 输出比较通道 1
	TIM_OCInitStructure.TIM_Pulse = 3;
	TIM_OC1Init(GENERAL_TIM, &TIM_OCInitStructure);//配置通道1
	//使能TIM3自动重装载
	TIM_OC1PreloadConfig(GENERAL_TIM, TIM_OCPreload_Enable);//配置通道1
	
	// 使能计数器
	TIM_Cmd(GENERAL_TIM, ENABLE);
	
}

void Motor_Init(void)
{
	TB6612_AIN_Pin_Set();
	TB6612_PWMA_Pin_Set();
	Clockwise_Rotation;//电机顺时针转动
}

void Motor_Speed_Change(uint16_t Motor_Speed)
{
	TIM_SetCompare1(GENERAL_TIM,Motor_Speed);
}
