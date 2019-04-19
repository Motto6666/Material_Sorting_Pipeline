#include "receive_rtu_data.h"

extern volatile uint8_t USART1_Send_Count ;//USART1发送RTU数据包次数
extern volatile uint8_t USART2_Send_Count ;//USART2发送RTU数据包次数
uint8_t Data_Stirngs[1];


/**
  * @brief  USART1串口接收Openmv发送的RTU数据帧
  * @param  Address 				地址码
	* @param  Funtion 				功能码
  * @retval 无
  */
void USART1_Rtu_Data_Receive(uint8_t Address, uint8_t Funtion)
{
	TIM6_ENABLE;//开启定时器TIM6
	while(1)
	{
		if( USART_RX_Over == 1)
		{
			TIM6_DISABLE;//关闭定时器TIM6
			TIM6_Count = 0;//TIM6计数值清0
			USART1_Send_Count = 0;//发送RTU数据包次数清0
			USART_RX_Over = 0;//USART_RX_Over恢复到最初值，保证下次超时检测不出错
			break;			
		}
		
		if( (TIM6_Count == 100) && (USART1_Send_Count<=5) )//计时时间为5秒
		{
			TIM6_DISABLE;
			TIM6_Count = 0;
			if(USART1_Send_Count == 5)
			{
				TIM6_DISABLE;
				switch(Funtion)
				{
					case OPENMV_CHACK:
								Clean_Screen(7);//清除第七行里面的字符
								Display_Chinese_String( Chinese_Character_4  ,12 ,7 ,1 ,RED);//显示“与视觉模块第一次通信超时”
								Debug_USART2_Printf("与OpenMv模块第一次通信超时");//到时候用LCD显示屏显示
								Display_Rectangle();
								break;
					
					case OPENMV_RECOGNIZE:
								Clean_Screen(7);//清除第七行里面的字符
								Display_Chinese_String( Chinese_Character_8  ,12 ,7 ,1 ,RED);//显示“与视觉模块第二次通信超时”
								Debug_USART2_Printf("与OpenMv模块第二次通信超时");//到时候用LCD显示屏显示
								Display_Rectangle();
								break;
					
					default: break;
				}
				while(1);
			}
			RTU_Pack_Data(Address, Funtion, 0, Data_Stirngs, USART1_DEVICE);//打包RTU数据并发送到指定设备
			
			USART1_Send_Count++;
			
			TIM6_ENABLE;
		}
	}
	
	if(USART1_RX_Pack[0] == Address || USART1_RX_Pack[1] == Funtion)
	{
		switch(Funtion)
		{
			case OPENMV_CHACK:
						Clean_Screen(7);//清除第七行里面的字符
						Display_Chinese_String( Chinese_Character_3  ,8  ,7 ,1 ,GREEN);//显示“视觉模块响应正常”
						Debug_USART2_Printf("OpenMV模块响应正常\n");//到时候用LCD显示屏显示
						break;
			
			case OPENMV_RECOGNIZE:
						Clean_Screen(7);//清除第七行里面的字符
						Display_Chinese_String( Chinese_Character_7  ,8  ,7 ,1 ,GREEN);//显示“视觉模块识别开始”
						Debug_USART2_Printf("OpenMV识别开始\n");//到时候用LCD显示屏显示
						break;
			
			default: break;
		}
	}
	Data_Clean(USART1_RX_Pack);//USART1_RX_Pack字符串中的数据，保证下一次执行时数据不出错
	USART1_RX_Count = 0;//计数值清0
}


/**
  * @brief  USART1串口接收Openmv发送的识别颜色数据帧
  * @retval 无
  */
void USART1_Receive_Recognize_Data(void)
{	
	TIM6_ENABLE;
	while(1)
	{
		if( USART_RX_Over == 1)
		{
			TIM6_DISABLE;
			TIM6_Count = 0;
			USART_RX_Over = 0;
			printf("%s\n",USART1_RX_Pack);
			if( RTU_Data_Analysis(USART1_RX_Pack) == CHECK_SUCCESS )
			{
				switch(USART1_RX_Pack[3])//USART1_RX_Pack[3]为数据码
				{
					case DATA_RED :
								Clean_Screen(7);//清除第七行里面的字符
								Display_Chinese_String( Chinese_Character_15  ,5  ,7 ,1 ,GREEN);//显示“识别到红色”
								Debug_USART2_Printf("OpenMV识别到红色物体\n");//到时候用LCD显示屏显示
								break;
					
					case DATA_GREEN :
								Clean_Screen(7);//清除第七行里面的字符
								Display_Chinese_String( Chinese_Character_16  ,5  ,7 ,1 ,GREEN);//显示“识别到绿色”
								Debug_USART2_Printf("OpenMV识别到绿色物体\n");//到时候用LCD显示屏显示
								break;
					
					case DATA_NONE :
								Clean_Screen(7);//清除第七行里面的字符
								Display_Chinese_String( Chinese_Character_17  ,13  ,7 ,1 ,GREEN);//显示“该物体的颜色不在识别范围内”
								Debug_USART2_Printf("该物体的颜色不在识别范围内\n");//到时候用LCD显示屏显示
								break;
					
					default : Debug_USART2_Printf("识别数据存在问题\n");//调试使用，调试完毕后删除
								break;
				}
				break;//跳出接收循环函数
			}
			else
			{
				Debug_USART2_Printf("RTU数据校验失败\n");
				TIM6_ENABLE;
				Data_Clean(USART1_RX_Pack);
			}
		}
		
	if( (TIM6_Count == 100) && (USART1_Send_Count<=5) )//计时时间为5秒
		{
			TIM6_DISABLE;
			TIM6_Count = 0;
			if(USART1_Send_Count == 5)
			{
				TIM6_DISABLE;
				Clean_Screen(7);//清除第七行里面的字符
				Display_Chinese_String( Chinese_Character_10 ,12 ,7 ,1 ,RED);//显示“与视觉模块第三次通信超时”
				Debug_USART2_Printf("与OpenMv模块第三次通信超时");//到时候用LCD显示屏显示
				Display_Rectangle();
				while(1);
			}
			RTU_Pack_Data(OPENMV_ADD, OPENMV_RECOGNIZE, 0, Data_Stirngs, USART1_DEVICE);//打包RTU数据并发送到指定设备
			
			USART1_Send_Count++;
			
			TIM6_ENABLE; 
		}	
	}
}

