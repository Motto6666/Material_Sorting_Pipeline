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
void TIM2_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* 嵌套向量中断控制器组选择 */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	/* 配置USART为中断源 */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
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
void TIM2_Init(void) 
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/*时钟 TIM2 使能*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 	
	/*设置自动重装载寄存器周期的值*/
	TIM_TimeBaseStructure.TIM_Period = 10; 
	/*设置时钟频率除数的预分频值*/
	TIM_TimeBaseStructure.TIM_Prescaler = 71; 
	/*时钟分频因子*/
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	/*TIM2 向上计数*/
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	/*初始化 TIM2*/
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
	/*禁用ARR上的TIMX外围设备预加载寄存器*/
	TIM_ARRPreloadConfig(TIM2, DISABLE);
	/*开启计数器中断*/
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE );  
	/*关闭TIM2*/
	MOTOR_TIM_DISABLE;  
}

 /**
  * @brief  初始化定时器TIM2
  * @param  无
  * @retval 无
  */
void TIM2_Config_Init(void)
{
	TIM2_NVIC_Init();
	TIM2_Init();
}


 /**
  * @brief  初始化电机
  * @param  无
  * @retval 无
  */
void Motor_Init(void)
{
	TB6612_Pin_Set();
	TIM2_Config_Init();
}


/**
  * @brief  TIM2定时中断服务函数
  * @param  无
  * @retval 无
  */
volatile uint8_t Flag = 0;
void TIM2_IRQHandler(void) 
{
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update ); 
		TB6612_PWM_Pin_Control();
		Flag = !Flag;
	}
}


void TB6612_PWM_Pin_Control(void)
{
	if(!Flag) 
		{
			MOTOR_TIM_INTERRUPT_TIME = 2;//设定TIM2定时中断时间，单位为us
			PWMA_ON;		 
		}
		else 
		{
			MOTOR_TIM_INTERRUPT_TIME = 8;//设定TIM2定时中断时间，单位为us
			PWMA_OFF;
		}
}
