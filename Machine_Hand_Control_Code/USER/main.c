#include "stm32f10x.h"
#include "bsp_servo_gpio.h"
#include "servo_control.h"
#include "bsp_systick.h"
#include "bsp_usart1.h"
//#include <stdio.h>//调试使用，调试完毕删除
#include "bsp_tim2.h"
#include "analyze_action_group.h"


uint8_t Action_Group[SERVO_NUM][20] = 
{
	{"#001P1500T1000!"},
  {"#002P1500T1000!"},
	{"#003P1500T1000!"},
	{"#004P1500T1000!"},
	{"#005P1500T1000!"},
	{"#006P1500T1000!"},
};

// char s[] = {'0'};//调试使用，调试完毕删除

int main(void) 
{	
	//uint8_t i;//调试使用，调试完毕删除
	
	Servo_GPIO_Init();
	Servo_Pulse_Width_Init();
	USART1_Config();
	TIM2_Config_Init();
	
	SysTick_Delay_us(2000000);//调试使用，调试完毕删除
	
// 	for(i=1;i<=6;i++)//调试使用，调试完毕删除
// 	{
// 		Servo[i].Aim_PWM = 2400;
// 		Servo[i].Time =100;
// 		Servo[i].Increment_PWM = (Servo[i].Aim_PWM - Servo[i].Current_PWM) / (Servo[i].Time / 20.000);
//   }	
	
	
// 	sprintf(s,"%d\n",((uint32_t)Servo[1].Current_PWM)); //调试使用，调试完毕删除
// 	Printf(s);//调试使用，调试完毕删除
// 	Printf("123456\n");//调试使用，调试完毕删除

  Analyze_Action_Group(Action_Group);
	
	while(1);

}



