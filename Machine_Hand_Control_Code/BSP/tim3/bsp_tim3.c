#include "bsp_tim3.h"

 /**
  * @brief  配置TIM3中断优先级
  */
static void GENERAL_TIM3_NVIC_Config(void)//移植时可以根据实际情况作参数修改
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	//移植时可以根据实际情况作参数修改	
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = GENERAL_TIM3_IRQ ;	//移植时可以根据实际情况作参数修改
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 //移植时可以根据实际情况作参数修改
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	//移植时可以根据实际情况作参数修改
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


 /**
  * @brief  TIM3外设配置
  */
static void GENERAL_TIM3_Mode_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		// 开启定时器时钟,即内部时钟CK_INT=72M,内部时钟可固定
    GENERAL_TIM3_APBxClock_FUN(GENERAL_TIM3_CLK, ENABLE);
	
		// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM3_Period;//移植时可以根据实际情况作修改(BASIC_TIM_Period = 1000-1)重点理解！！

	  // 时钟预分频数= CK_INT /（BASIC_TIM_Prescaler+1） = 72M / 71+1 = 1M，即中断周期 T = BASIC_TIM_Period * (1/1000000) = 1000 * (1/1000000) = 1ms 重点理解！！
    TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM3_Prescaler;
		
	  // 初始化定时器
    TIM_TimeBaseInit(GENERAL_TIM3, &TIM_TimeBaseStructure);
		
		// 清除计数器中断标志位
    TIM_ClearFlag(GENERAL_TIM3, TIM_FLAG_Update);
	  
		// 开启计数器中断
    TIM_ITConfig(GENERAL_TIM3,TIM_IT_Update,ENABLE);
		
		// 使能定时器
    TIM3_DISABLE;
}


 /**
  * @brief  TIM3初始化
  */
void TIM3_Config_Init(void)
{
	GENERAL_TIM3_NVIC_Config();
	GENERAL_TIM3_Mode_Config();
}


 /**
  * @brief  Tim7定时中断服务函数，1ms中断一次,用作判断USART串
	*					口数据是否接收完毕，作接收数据超时检测
  * @retval 无
  */
volatile uint8_t TIM3_Count = 10;
volatile uint8_t USART_RX_Over = 0;
void  GENERAL_TIM3_IRQHandler (void) 
{
	if ( TIM_GetITStatus( GENERAL_TIM3, TIM_IT_Update) != RESET ) 
	{	
		TIM3_Count--;
		TIM_ClearITPendingBit(GENERAL_TIM3, TIM_FLAG_Update);
		
		if(TIM3_Count == 0)//若TIM3_Count为0，即可判断USART串口数据接收完毕
		{
			USART_RX_Over = TRUE;//表示数据接收完毕
			TIM3_Count = 10;//TIM3_Count值恢复到最初值，保证下次超时检测不出错
			TIM3_DISABLE;
		}
	}		 	
}
