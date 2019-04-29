#include "bsp_tim2.h"
#include "servo_control.h"

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
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  
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
	TIM_TimeBaseStructure.TIM_Period = 	20000; 
	/*设置时钟频率除数的预分频值*/
	TIM_TimeBaseStructure.TIM_Prescaler =71; 
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
	/*使能 TIM2*/
	TIM2_ENABLE;  
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
		Servo_Pulse_Width_Control();
		Flag = !Flag;
	}
}


