#include "stm32f10x.h"
#include "bsp_servo_gpio.h"
#include "servo_control.h"
#include "bsp_systick.h"
#include "bsp_usart1.h"
#include "bsp_tim2.h"
#include "analyze_action_group.h"
#include "execute_action_group.h"

int main(void) 
{	
	
	Servo_GPIO_Init();
	Servo_Pulse_Width_Init();
	USART1_Config();
	TIM2_Config_Init();
	
	SysTick_Delay_us(2000000);//调试使用，调试完毕删除
	

	Curl_Up_Action();//机械手执行蜷缩动作
		
	Grab_Material_Action();//机械手执行抓取物料动作
	
	Left_Place_Action();//机械手往左放置物料
		
	Curl_Up_Action();//机械手执行蜷缩动作
		
	Grab_Material_Action();//机械手执行抓取物料动作

	Right_Place_Action();//机械手往右放置物料
		
	Curl_Up_Action();//机械手执行蜷缩动作
	
	while(1);

}



