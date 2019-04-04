#include "stm32f10x.h"
#include "bsp_servo_gpio.h"
#include "servo_control.h"
#include "bsp_systick.h"
#include "bsp_usart1.h"
// #include <stdio.h>//调试使用，调试完毕删除
#include "bsp_tim2.h"

// extern Servo  Servo_Action[SERVO_NUM];//调试使用，调试完毕删除

// char s[] = {'0'};//调试使用，调试完毕删除

int main(void) 
{	
	Servo_GPIO_Init();
	Servo_Init();
	USART1_Config();
	TIM2_Config_Init();
		
// 	sprintf(s,"%d\n",((uint32_t)Servo_Action[1].Current_Pulse_Width)); //调试使用，调试完毕删除
// 	Printf(s);//调试使用，调试完毕删除
// 	Printf("123456\n");//调试使用，调试完毕删除

// 	
// 	Servo_IO_Set(6, LOW);//调试使用，调试完毕删除
// 	SysTick_Delay_us(18500);//调试使用，调试完毕删除
// 	Servo_IO_Set(6, HIGH);//调试使用，调试完毕删除
// 	SysTick_Delay_us(1500);//调试使用，调试完毕删除
// 	Servo_IO_Set(6, LOW);//调试使用，调试完毕删除
// 	SysTick_Delay_us(18500);//调试使用，调试完毕删除
	
	while(1)
	{
	}
}



