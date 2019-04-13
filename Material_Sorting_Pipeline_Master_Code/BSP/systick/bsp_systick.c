#include "bsp_systick.h"

/**
	* @brief  ���ö���־λֵ��ʱ
	* @param  ��ʱʱ��ֵ
	* @retval ��
	*/
void SysTick_Delay_us(uint32_t us)
{
	uint32_t i;
	
	SysTick_Config(72);//720000��ʾʹ��ms��ʱ����Ϊ72��ʾʹ��us��ʱ
	
	for(i=0;i<us;i++)
	{
		while( !( SysTick->CTRL & (1<<16) ));
	}
	
	/*ʧ��systick*/
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

