#include "bsp_tim6.h"

// 中断优先级配置
static void BASIC_TIM6_NVIC_Config(void)//移植时可以根据实际情况作参数修改
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	//移植时可以根据实际情况作参数修改	
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM6_IRQ ;	//移植时可以根据实际情况作参数修改
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 //移植时可以根据实际情况作参数修改
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;	//移植时可以根据实际情况作参数修改
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

//配置基本定时器TIM6
static void BASIC_TIM6_Mode_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		// 开启定时器时钟,即内部时钟CK_INT=72M,内部时钟可固定
    BASIC_TIM6_APBxClock_FUN(BASIC_TIM6_CLK, ENABLE);//移植时可以根据实际情况作修改
	
		// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
    TIM_TimeBaseStructure.TIM_Period = BASIC_TIM6_Period;//移植时可以根据实际情况作修改(BASIC_TIM_Period = 1000-1)重点理解！！

	  // 时钟预分频数= CK_INT /（BASIC_TIM_Prescaler+1） = 72M / 71+1 = 1M，即中断周期 T = BASIC_TIM_Period * (1/1000000) = 1000 * (1/1000000) = 1ms 重点理解！！
    TIM_TimeBaseStructure.TIM_Prescaler= BASIC_TIM6_Prescaler;//移植时可以根据实际情况作修改(BASIC_TIM_Prescaler= 71)
	
	  // 初始化定时器
    TIM_TimeBaseInit(BASIC_TIM6, &TIM_TimeBaseStructure);//移植时可以根据实际情况作修改
		
		// 清除计数器中断标志位
    TIM_ClearFlag(BASIC_TIM6, TIM_FLAG_Update);//移植时可以根据实际情况作修改
	  
		// 开启计数器中断
    TIM_ITConfig(BASIC_TIM6,TIM_IT_Update,ENABLE);//移植时可以根据实际情况作修改
		
		// 使能定时器
    TIM6_DISABLE ;//关闭TIM6定时器
}

void BASIC_TIM6_Init(void)
{
	BASIC_TIM6_NVIC_Config();
	BASIC_TIM6_Mode_Config();
}


 /**
  * @brief  Tim6定时中断服务函数，20ms中断一次
  * @param  需要发送出去的字符串的指针
  * @retval 无
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
