#include "stm32f10x.h"
#include "bsp_servo_gpio.h"
#include "servo_control.h"
#include "bsp_systick.h"
#include "bsp_usart1.h"
#include "bsp_usart2.h"
#include "bsp_tim2.h"
#include "bsp_tim3.h"
#include "analyze_action_group.h"
#include "execute_action_group.h"
#include "modbus_agreement.h"

uint8_t Data[1];

int main(void) 
{	
	
	Servo_GPIO_Init();
	Servo_Pulse_Width_Init();
	USART1_Config();
	USART2_Config();
	TIM2_Config_Init();
	TIM3_Config_Init();
	SysTick_Delay_us(2000000);//调试使用，调试完毕删除
	Curl_Up_Action();//机械手执行蜷缩动作
	
	while(1)
	{
		if(USART_RX_Over == TRUE)//接收STM32主控板发送的数据完毕
		{
			USART1_Printf("接收到数据");//数据发送到电脑，调试使用，调试完毕删除！！！
			
			USART_RX_Over = 0;//恢复到最初值
			
			if( RTU_Data_Analysis(USART2_RX_Pack) == CHECK_SUCCESS )
			{
				switch(USART2_RX_Pack[1])
				{
					case IRON_HAND_CHACK:
								RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_CHACK, 0, Data );
								USAER2_RX_Data_Clean(USART2_RX_Pack);			
								break;
					
					case IRON_HAND_EXECUTE:						
								RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_EXECUTE, 0, Data );
								if(USART2_RX_Pack[3] == DATA_RED)
								{
									USART1_Printf("抓取红色小球");//调试使用，调试完毕删除！！！
									Grab_Material_Action();//机械手执行抓取物料动作
									Left_Place_Action();//机械手往左放置物料	
									Curl_Up_Action();//机械手执行蜷缩动作
									RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_EXECUTE_END, 0, Data );
									USART1_Printf("抓取完毕，发送返回数据");//调试使用，调试完毕删除！！！
								}
								else if(USART2_RX_Pack[3] == DATA_GREEN)
								{
									Grab_Material_Action();//机械手执行抓取物料动作
									Right_Place_Action();//机械手往右放置物料
									Curl_Up_Action();//机械手执行蜷缩动作
									RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_EXECUTE_END, 0, Data );
								}
								USAER2_RX_Data_Clean(USART2_RX_Pack);
								break;
					
					default:break;									
				}
			}
			else
			{
				USAER2_RX_Data_Clean(USART2_RX_Pack);
			}
		}
		
	}
	
// 	SysTick_Delay_us(2000000);//调试使用，调试完毕删除
// 	

// 	Curl_Up_Action();//机械手执行蜷缩动作
// 		
// 	Grab_Material_Action();//机械手执行抓取物料动作
// 	
// 	Left_Place_Action();//机械手往左放置物料
// 		
// 	Curl_Up_Action();//机械手执行蜷缩动作
// 		
// 	Grab_Material_Action();//机械手执行抓取物料动作

// 	Right_Place_Action();//机械手往右放置物料
// 		
// 	Curl_Up_Action();//机械手执行蜷缩动作
// 	
// 	USART1_Printf("动作组执行完毕");//调试使用，调试完毕删除！！！
// 	
// 	while(1);

}



