#include "bsp_motor_control.h"

void TB6612_Pin_Set(void)
{
	/*初始化AIN端口时钟*/
	RCC_APB2PeriphClockCmd(TB6612_GPIO_PORT_CLOCK,ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	
	/*初始化AIN1引脚*/
	GPIO_InitStruct.GPIO_Pin = AIN1_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	/*初始化AIN1端口*/
	GPIO_Init(TB6612_GPIO_PORT, &GPIO_InitStruct);
	
	/*初始化AIN2引脚*/
	GPIO_InitStruct.GPIO_Pin = AIN2_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	/*初始化AIN2端口*/
	GPIO_Init(TB6612_GPIO_PORT, &GPIO_InitStruct);
	
	/*初始化PWMA_PIN引脚*/
	GPIO_InitStruct.GPIO_Pin = PWMA_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	/*初始化PWMA_PIN端口*/
	GPIO_Init(TB6612_GPIO_PORT, &GPIO_InitStruct);
	
}


 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
void MOTOR_TIM_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* 嵌套向量中断控制器组选择 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	/* 配置USART为中断源 */
	NVIC_InitStructure.NVIC_IRQChannel = MOTOR_TIM_IRQ;  
	/* 抢断优先级*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	/* 子优先级 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;  
	/* 使能中断 */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	/* 初始化配置NVIC */
	NVIC_Init(&NVIC_InitStructure);  
}

 /**
  * @brief  配置TIM2定时器
  * @param  无
  * @retval 无
  */
void MOTOR_TIM_Init(void) 
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/*时钟 TIM2 使能*/
	MOTOR_TIM_APBxClock_FUN(MOTOR_TIM_CLK, ENABLE); 	
	/*设置自动重装载寄存器周期的值*/
	TIM_TimeBaseStructure.TIM_Period = MOTOR_TIM_Period; 
	/*设置时钟频率除数的预分频值*/
	TIM_TimeBaseStructure.TIM_Prescaler = MOTOR_TIM_Prescaler; 
	/*时钟分频因子*/
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	/*TIM2 向上计数*/
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	/*初始化 TIM2*/
	TIM_TimeBaseInit(MOTOR_TIM, &TIM_TimeBaseStructure); 
	/*禁用ARR上的TIMX外围设备预加载寄存器*/
	TIM_ARRPreloadConfig(MOTOR_TIM, DISABLE);
	/*开启计数器中断*/
	TIM_ITConfig(MOTOR_TIM,TIM_IT_Update,ENABLE );  
	/*关闭TIM2*/
	MOTOR_TIM_DISABLE;  
}

 /**
  * @brief  初始MOTOR_TIM定时器，即TIM2定时器
  * @param  无
  * @retval 无
  */
void MOTOR_TIM_Config_Init(void)
{
	MOTOR_TIM_NVIC_Init();
	MOTOR_TIM_Init();
}


 /**
  * @brief  初始化电机
  * @param  无
  * @retval 无
  */
void Motor_Init(void)
{
	TB6612_Pin_Set();
	MOTOR_TIM_Config_Init();
}


/**
  * @brief  MOTOR_TIM(TIM2)定时中断服务函数
  * @param  无
  * @retval 无
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
  * @brief  控制引脚高低电平时间，模拟固件库输出PWM波，整个脉冲周期为10us
  * @param  无
  * @retval 无
  */

void TB6612_PWM_Pin_Control(void)
{
	if(!Flag) 
		{
			MOTOR_TIM_INTERRUPT_TIME = 4;//设定TIM2定时中断时间为4us，即高电平持续时间为4us
			PWMA_ON;		 
		}
		else 
		{
			MOTOR_TIM_INTERRUPT_TIME = 6;//设定TIM2定时中断时间为6us，即高电平持续时间为6us
			PWMA_OFF;
		}
}
