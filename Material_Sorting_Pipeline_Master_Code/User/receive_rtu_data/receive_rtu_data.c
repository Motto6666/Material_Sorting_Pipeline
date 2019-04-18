#include "receive_rtu_data.h"

extern volatile uint8_t USART1_Send_Count ;//USART1发送RTU数据包次数
extern volatile uint8_t USART2_Send_Count ;//USART2发送RTU数据包次数
uint8_t Data_Stirngs[50];


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
								Debug_USART2_Printf("与OpenMv模块第一次通信超时");//到时候用LCD显示屏显示
								break;
					
					case OPENMV_RECOGNIZE:
								Debug_USART2_Printf("与OpenMv模块第二次通信超时");//到时候用LCD显示屏显示
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
						Debug_USART2_Printf("OpenMV模块响应正常\n");//到时候用LCD显示屏显示
						break;
			
			case OPENMV_RECOGNIZE:
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
  * @param  Address 				地址码
	* @param  Funtion 				功能码
  * @retval 无
  */
void USART1_Receive_Recognize_Data(void)
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
			//在此添加RTU数据解析函数			
		}
		
	if( (TIM6_Count == 100) && (USART1_Send_Count<=5) )//计时时间为5秒
		{
			TIM6_DISABLE;
			TIM6_Count = 0;
			if(USART1_Send_Count == 5)
			{
				TIM6_DISABLE;
				Debug_USART2_Printf("与OpenMv模块第三次通信超时");//到时候用LCD显示屏显示
				while(1);
			}
			RTU_Pack_Data(OPENMV_ADD, OPENMV_RECOGNIZE, 0, Data_Stirngs, USART1_DEVICE);//打包RTU数据并发送到指定设备
			
			USART1_Send_Count++;
			
			TIM6_ENABLE;
		}	
		
	}
}
