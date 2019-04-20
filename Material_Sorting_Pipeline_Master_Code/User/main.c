#include "stm32f10x.h"
#include "system_init.h"
#include "bsp_systick.h"
#include "modbus_agreement.h"
#include "receive_rtu_data.h"


volatile uint8_t USART1_Send_Count = 0;//USART1发送RTU数据包次数（仍然存在疑问）
volatile uint8_t USART2_Send_Count = 0;//USART2发送RTU数据包次数（仍然存在疑问）

uint8_t Data_Stirng[1];

int main(void)
{ 		
	System_Init();
	
	RTU_Pack_Data(OPENMV_ADD, OPENMV_CHACK, 0, Data_Stirng, USART1_DEVICE);//打包RTU数据并发送到指定设备
			
	USART1_Receive_State_Data(OPENMV_ADD, OPENMV_CHACK);
	
	while(1)
	{
		SysTick_Delay_us(1000);//等待1ms，保证OpenMV模块已进入到接收数据的状态
	
		RTU_Pack_Data(OPENMV_ADD, OPENMV_RECOGNIZE, 0, Data_Stirng, USART1_DEVICE);
		
		USART1_Receive_State_Data(OPENMV_ADD, OPENMV_RECOGNIZE);
		
		USART1_Receive_Recognize_Data();
		
		USART_Buffer_Clean(USART1_RX_Pack);
	}
	
	
	
		
	
	
	
	
		
//	TIM6_ENABLE;//开启定时器TIM6
		 
//	while(1)
//	{
//		if( USART_RX_Over == 1)
//		{
//			TIM6_DISABLE;//关闭定时器TIM6
//			TIM6_Count = 0;//TIM6计数值清0
//			USART1_Send_Count = 0;//发送RTU数据包次数清0
//			USART_RX_Over = 0;//USART_RX_Over恢复到最初值，保证下次超时检测不出错 
//			break;
//		}
//		
//		if( (TIM6_Count == 100) && (USART1_Send_Count<=5) )//计时时间为5秒
//		{
//			TIM6_DISABLE;
//			TIM6_Count = 0;
//			if(USART1_Send_Count == 5)
//			{
//				TIM6_DISABLE;
//				Debug_USART2_Printf("与OpenMv模块第一次通信超时");//到时候用LCD显示屏显示
//				while(1);
//			}
//			RTU_Pack_Data(OPENMV_ADD, OPENMV_CHACK, 0, Data_Stirng, USART1_DEVICE);//打包RTU数据并发送到指定设备
//			USART1_Send_Count++;
//			TIM6_ENABLE;
//		}
//		
//	}
//			
//	if(USART1_RX_Pack[0] == OPENMV_ADD || USART1_RX_Pack[1] == OPENMV_CHACK)
//	{
//		Debug_USART2_Printf("OpenMV模块响应正常\n");//到时候用LCD显示屏显示
//	}
//	Data_Clean(USART1_RX_Pack);//USART1_RX_Pack字符串中的数据，保证下一次执行时数据不出错
//	USART1_RX_Count = 0;//计数值清0
	
	
	
//	SysTick_Delay_us(1000);
//	
//	
//	
//	RTU_Pack_Data(OPENMV_ADD, OPENMV_RECOGNIZE, 0, Data_Stirng, USART1_DEVICE);//打包RTU数据并发送到指定设备
//	
//	Debug_USART2_Printf("USART1第二次数据发送成功");
//	//	
//	TIM6_ENABLE;//开启定时器TIM6
//	
//	while(1)
//	{
//		if( USART_RX_Over == 1)
//		{
//			TIM6_DISABLE;//关闭定时器TIM6
//			TIM6_Count = 0;//TIM6计数值清0
//			USART1_Send_Count = 0;//发送RTU数据包次数清0
//			USART_RX_Over = 0;//USART_RX_Over恢复到最初值，保证下次超时检测不出错 
//			break;
//		}
//		
//		if( (TIM6_Count == 100) && (USART1_Send_Count<=5) )//计时时间为5秒
//		{
//			TIM6_DISABLE;
//			TIM6_Count = 0;
//			if(USART1_Send_Count == 5)
//			{
//				TIM6_DISABLE;
//				Debug_USART2_Printf("与OpenMv模块第二次通信超时");//到时候用LCD显示屏显示
//				while(1);
//			}
//			RTU_Pack_Data(OPENMV_ADD, OPENMV_CHACK, 0, Data_Stirng, USART1_DEVICE);//打包RTU数据并发送到指定设备
//			USART1_Send_Count++;
//			TIM6_ENABLE;
//		}
//		
//	}
//				
//	if(USART1_RX_Pack[0] == OPENMV_ADD || USART1_RX_Pack[1] == OPENMV_RECOGNIZE)
//	{
//		Debug_USART2_Printf("OpenMV模块识别开始\n");//到时候用LCD显示屏显示
//	}
//	Data_Clean(USART1_RX_Pack);//USART1_RX_Pack字符串中的数据，保证下一次执行时数据不出错
//	USART1_RX_Count = 0;//计数值清0
//	
//	
//	
//	TIM6_ENABLE;//开启定时器TIM6
//	
//	while(1)
//	{
//		if( USART_RX_Over == 1)
//		{
//			TIM6_DISABLE;//关闭定时器TIM6
//			TIM6_Count = 0;//TIM6计数值清0
//			USART1_Send_Count = 0;//发送RTU数据包次数清0
//			USART_RX_Over = 0;//USART_RX_Over恢复到最初值，保证下次超时检测不出错 
//			break;
//		}
//		
//		if( (TIM6_Count == 100) && (USART1_Send_Count<=5) )//计时时间为5秒
//		{
//			TIM6_DISABLE;
//			TIM6_Count = 0;
//			if(USART1_Send_Count == 5)
//			{
//				TIM6_DISABLE;
//				Debug_USART2_Printf("与OpenMv模块第三次通信超时");//到时候用LCD显示屏显示
//				while(1);
//			}
//			USART1_Send_Count++;
//			TIM6_ENABLE;
//		}
//		
//	}
//	
//	if(USART1_RX_Pack[3] == DATA_GREEN)
//	{
//		Debug_USART2_Printf("识别到绿色物体\n");//到时候用LCD显示屏显示
//	}
//	if(USART1_RX_Pack[3] == DATA_RED)
//	{
//		Debug_USART2_Printf("识别到红色物体\n");//到时候用LCD显示屏显示
//	}
//	if(USART1_RX_Pack[3] == DATA_NONE)
//	{
//		Debug_USART2_Printf("该物体不在识别范围内\n");//到时候用LCD显示屏显示
//	}
//	
//	Data_Clean(USART1_RX_Pack);//USART1_RX_Pack字符串中的数据，保证下一次执行时数据不出错
//	USART1_RX_Count = 0;//计数值清0
	

	
	while(1);//调试使用，调试完毕删除！！！
	
	
	
	

//	RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_CHACK, 0, Data_Stirng, USART2_DEVICE);//打包RTU数据并发送到指定设备
//	
//	TIM6_ENABLE;//开启定时器TIM6
//	
//	while(1)
//	{
//		if( USART_RX_Over == 1)
//		{
//			TIM6_DISABLE;//关闭定时器TIM6
//			TIM6_Count = 0;//TIM6计数值清0
//			USART2_Send_Count = 0;//USART2发送RTU数据包次数清0
//			USART_RX_Over = 0;//USART_RX_Over恢复到最初值，保证下次超时检测不出错 
//			break;
//		}
//		
//		if( (TIM6_Count == 100) && (USART2_Send_Count<=5) )//计时时间为5秒
//		{
//			TIM6_DISABLE;
//			TIM6_Count = 0;
//			if(USART2_Send_Count == 5)
//			{
//				Debug_USART2_Printf("与机械手模块第一次通信超时");
//				while(1);
//			}
//			RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_CHACK, 0, Data_Stirng, USART2_DEVICE);//打包RTU数据并发送到指定设备
//			USART2_Send_Count++;
//			TIM6_ENABLE;
//		}
//		
//	}
//				
//	Debug_USART2_Printf("完成USART2超时检测");//到时候用LCD显示屏显示
//	USART2_Printf(USART2_RX_Pack);
//	if(USART2_RX_Pack[0] == IRON_HAND_ADD && USART2_RX_Pack[1] == IRON_HAND_CHACK)
//	{
//		Debug_USART2_Printf("机械手模块响应正常");//到时候用LCD显示屏显示
//	}	
//	Data_Clean(USART2_RX_Pack);//USART1_RX_Pack字符串中的数据，保证下一次执行时数据不出错
//	USART2_RX_Count = 0;//计数值清0
//	
//	while(1);



	
//	ILI9341_Init();//可以根据实际情况做参数的修改!!!

//	printf("\r\n读取到的ID =%x",ILI9341_Read_ID());
//	
//	Display_Motto6666(1 ,1, YELLOW);//显示“Motto6666”英文字符串
//	Display_Chinese_String( Chinese_Character_1  ,9  ,3 ,1 ,BLUE2);//显示“物料分拣流水线系统”中文字符串
//	Display_Chinese_String( Chinese_Character_2  ,7  ,5 ,1 ,MAGENTA);//显示“系统运行情况：”
//	Display_Chinese_String( Chinese_Character_3  ,8  ,7 ,1 ,GREEN);//显示“视觉模块响应正常”
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//清除第七行里面的字符
//	Display_Chinese_String( Chinese_Character_4  ,12 ,7 ,1 ,RED);//显示“与视觉模块第一次通信超时”
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_5  ,11 ,7 ,1 ,GREEN);//显示“机械手控制模块响应正常”
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_6  ,15 ,7 ,1 ,RED);//显示“与机械手控制模块第一次通信超时”
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_7  ,8  ,7 ,1 ,GREEN);//显示“视觉模块识别开始”
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_8  ,12 ,7 ,1 ,RED);//显示“与视觉模块第二次通信超时”
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_9  ,8  ,7 ,1 ,GREEN);//显示“视觉模块识别结束”
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_10 ,12 ,7 ,1 ,RED);//显示“与视觉模块第三次通信超时”
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_11 ,7  ,7 ,1 ,GREEN);//显示“机械手执行操作”字模数据
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_12 ,15 ,7 ,1 ,RED);//显示“与机械手控制模块第二次通信超时”
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_13 ,7  ,7 ,1 ,GREEN);//显示“机械手执行完毕”字模数据
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_14 ,15 ,7 ,1 ,RED);//显示“与机械手控制模块第三次通信超时”
//	
//  
//	/* 画矩形 */	
//	while(1)//当STM32主控板与模块间通信超时时，使用该函数
//	{
//		ILI9341_Draw_Rect(220,300,20, 20,RED);
//		Delay(0xFFFF0);//调试使用，调试完毕删除
//    ILI9341_Draw_Rect(220,300,20,20,BLACK);
//		Delay(0xFFFF0);//调试使用，调试完毕删除
//	} 

}





/*********************************************END OF FILE**********************/
