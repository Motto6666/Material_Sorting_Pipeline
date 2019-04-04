#include "bsp_systick.h"

/*第一种：采用读标志位值计时*/
void SysTick_Delay_us(uint32_t us)
{
	uint32_t i;
	
	SysTick_Config(72);//720000表示使用ms计时，改为72表示使用us计时（少用）
	
	for(i=0;i<us;i++)
	{
		while( !( SysTick->CTRL & (1<<16) ));
	}
	
	/*失能systick*/
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

