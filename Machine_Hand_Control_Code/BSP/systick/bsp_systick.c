#include "bsp_systick.h"

/**
	* @brief  采用读标志位值计时
	* @param  定时时间值
	* @retval 无
	*/
void SysTick_Delay_us(uint32_t us)
{
	uint32_t i;
	
	SysTick_Config(72);//720000表示使用ms计时，改为72表示使用us计时
	
	for(i=0;i<us;i++)
	{
		while( !( SysTick->CTRL & (1<<16) ));
	}
	
	/*失能systick*/
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

