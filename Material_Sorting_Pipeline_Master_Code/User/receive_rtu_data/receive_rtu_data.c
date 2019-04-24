#include "receive_rtu_data.h"

extern volatile uint8_t USART1_Send_Count ;//USART1发送RTU数据包次数
extern volatile uint8_t USART2_Send_Count ;//USART2发送RTU数据包次数
uint8_t Data_Stirngs[1];


/**
  * @brief  USART1串口等待接收Openmv发送的RTU数据帧
  * @param  Address 				地址码
	* @param  Funtion 				功能码
  * @retval 无
  */
void Receive_Openmv_Data(uint8_t Address, uint8_t Funtion)
{
	TIM6_ENABLE;
	while(1)
	{		
		if( USART_RX_Over == TURE)
		{		
			TIM6_Shut_Down();
			USART_RX_Over = 0;
			if( USART1_RX_Pack[0] == Address || USART1_RX_Pack[1] == Funtion )
			{				
				USART1_Send_Count = 0;
				break;//跳出接收循环函数
			}
			else
			{
				TIM6_ENABLE;
				USART_Buffer_Clean(USART1_RX_Pack);
			}			
		}
		
		if( (TIM6_Count == FIVE_SECONDS) && (USART1_Send_Count<=5) )//计时时间为5秒
		{
			TIM6_Shut_Down();
			if(USART1_Send_Count == 5)
			{
				TIM6_Shut_Down();
				switch(Funtion)
				{
					case OPENMV_CHACK:
								Clean_Screen(7);//清除第七行里面的字符
								Display_Chinese_String( Chinese_Character_4  ,12 ,7 ,1 ,RED);//显示“与视觉模块第一次通信超时”
								Display_Rectangle();
								break;
					
					case OPENMV_RECOGNIZE:
								Clean_Screen(7);//清除第七行里面的字符
								Display_Chinese_String( Chinese_Character_8  ,12 ,7 ,1 ,RED);//显示“与视觉模块第二次通信超时”
								Display_Rectangle();
								break;
					
					default: break;
				}
				while(1);
			}
			
			RTU_Pack_Data(Address, Funtion, 0, Data_Stirngs, USART1_DEVICE);//重新打包RTU数据并发送到指定设备
			
			USART1_Send_Count++;
			
			TIM6_ENABLE;
		}
	}
	
	LCD_Display_State(Address,Funtion);//当跳出循环时，执行该语句
}


/**
  * @brief  USART2串口等待接收机械手控制板发送的RTU数据帧
  * @param  Address 				地址码
	* @param  Funtion 				功能码
  * @retval 无
  */
void Receive_Iron_Hand_Data(uint8_t Address, uint8_t Funtion)
{
	TIM6_ENABLE;
	while(1)
	{
		if( USART_RX_Over == TURE)
		{		
			TIM6_Shut_Down();
			USART_RX_Over = 0;
			if( USART2_RX_Pack[0] == Address || USART2_RX_Pack[1] == Funtion )
			{				
				USART2_Send_Count = 0;
				break;//跳出接收循环函数
			}
			else
			{
				TIM6_ENABLE;
				USART_Buffer_Clean(USART2_RX_Pack);
			}			
		}
		
		if( (TIM6_Count == FIVE_SECONDS) && (USART2_Send_Count<=5) )//计时时间为10秒
		{
			TIM6_Shut_Down();
			if(USART2_Send_Count == 5)
			{
				TIM6_Shut_Down();
				switch(Funtion)
				{
					case IRON_HAND_CHACK:
								Clean_Screen(7);//清除第七行里面的字符
								Display_Chinese_String( Chinese_Character_6  ,15 ,7 ,1 ,RED);//显示“与机械手控制模块第一次通信超时”
								Display_Rectangle();
								break;
					
					case IRON_HAND_EXECUTE:
								Clean_Screen(7);//清除第七行里面的字符
								Display_Chinese_String( Chinese_Character_12 ,15 ,7 ,1 ,RED);//显示“与机械手控制模块第二次通信超时”
								Display_Rectangle();
								break;
					
					case IRON_HAND_EXECUTE_END:
								Clean_Screen(7);//清除第七行里面的字符
								Display_Chinese_String( Chinese_Character_14 ,15 ,7 ,1 ,RED);//显示“与机械手控制模块第三次通信超时”
								Display_Rectangle();
								break;
					
					default: break;
				}
				while(1);
			}
			
			switch(Funtion)
			{
				case IRON_HAND_CHACK:
							RTU_Pack_Data(Address, Funtion, 0, Data_Stirngs, USART2_DEVICE);//重新打包RTU数据并发送到指定设备
							break;
				
				case IRON_HAND_EXECUTE:
							Data_Stirngs[0] = USART1_RX_Pack[3];////将识别到的颜色数据存放到Data_Stirngs数组里
							RTU_Pack_Data(Address, Funtion, 1, Data_Stirngs, USART2_DEVICE);//重新打包RTU数据并发送到指定设备
							Data_Clean(Data_Stirngs);
							break;
				
				case IRON_HAND_EXECUTE_END://进入到等待机械手返回执行完毕数据环节时，无需每隔5S发送RTU数据帧
							break;
				
				default: break;
			}
						
			USART2_Send_Count++;
			
			TIM6_ENABLE;
		}
	}
	
	LCD_Display_State(Address,Funtion);
}


/**
  * @brief  LCD显示的中文字符
	* @param  Address 				地址码
	* @param  Funtion 				功能码
  * @retval 无
  */
void LCD_Display_State(uint8_t Address, uint8_t Funtion)
{
	switch(Funtion)
	{
		case OPENMV_CHACK:
					Clean_Screen(7);//清除第七行里面的字符
					Display_Chinese_String( Chinese_Character_3  ,8  ,7 ,1 ,GREEN);//显示“视觉模块响应正常”
					break;
		
		case OPENMV_RECOGNIZE:
					Clean_Screen(7);//清除第七行里面的字符
					Display_Chinese_String( Chinese_Character_7  ,8  ,7 ,1 ,GREEN);//显示“视觉模块识别开始”
					break;
		
		case IRON_HAND_CHACK:
					Clean_Screen(7);//清除第七行里面的字符
					Display_Chinese_String( Chinese_Character_5  ,11 ,7 ,1 ,GREEN);//显示“机械手控制模块响应正常”
					break;
		
		case IRON_HAND_EXECUTE:
					Clean_Screen(7);//清除第七行里面的字符
					Display_Chinese_String( Chinese_Character_11 ,7  ,7 ,1 ,GREEN);//显示“机械手执行操作”字模数据
					break;
		
		case IRON_HAND_EXECUTE_END:
					Clean_Screen(7);//清除第七行里面的字符
					Display_Chinese_String( Chinese_Character_13 ,7  ,7 ,1 ,GREEN);//显示“机械手执行完毕”字模数据
					break;
		
		default: break;
	}

	
	switch(Address)
	{
		case OPENMV_ADD :
					USART_Buffer_Clean(USART1_RX_Pack);
					break;
		
		case IRON_HAND_ADD :
					USART_Buffer_Clean(USART2_RX_Pack);
					break;
		
		default : break;
	}
}


/**
  * @brief  USART1串口等待接收Openmv发送的识别到的颜色RTU数据帧
  * @retval 无
  */
void Receive_Openmv_Recognize_Data(void)
{	
	TIM6_ENABLE;
	while(1)
	{
		if( USART_RX_Over == TURE)
		{
			TIM6_Shut_Down();
			USART_RX_Over = 0;
			if( RTU_Data_Analysis(USART1_RX_Pack) == CHECK_SUCCESS )
			{
				USART1_Send_Count = 0;
				
				Data_Stirngs[0] = OK;
				
				RTU_Pack_Data(OPENMV_ADD, OPENMV_RECOGNIZE, 1, Data_Stirngs, USART1_DEVICE);//发送ok帧到Openmv
				
				Data_Clean(Data_Stirngs);
				
				switch(USART1_RX_Pack[3])//USART1_RX_Pack[3]为数据码
				{
					case DATA_RED :
								Clean_Screen(7);//清除第七行里面的字符
								Display_Chinese_String( Chinese_Character_15  ,5  ,7 ,1 ,GREEN);//显示“识别到红色”
								break;
					
					case DATA_GREEN :
								Clean_Screen(7);//清除第七行里面的字符
								Display_Chinese_String( Chinese_Character_16  ,5  ,7 ,1 ,GREEN);//显示“识别到绿色”
								break;
					
					case DATA_NONE :
								Clean_Screen(7);//清除第七行里面的字符
								Display_Chinese_String( Chinese_Character_17  ,13  ,7 ,1 ,GREEN);//显示“该物体的颜色不在识别范围内”
								break;
					
					default : break;
				}
				
				break;//跳出接收循环函数
				
			}
			else
			{
				TIM6_ENABLE;
				USART_Buffer_Clean(USART1_RX_Pack);
			}
		}
		
	if( (TIM6_Count == FIVE_SECONDS) && (USART1_Send_Count<=5) )//计时时间为5秒
		{
			TIM6_Shut_Down();
			if(USART1_Send_Count == 5)
			{
				TIM6_Shut_Down();
				Clean_Screen(7);//清除第七行里面的字符
				Display_Chinese_String( Chinese_Character_10 ,12 ,7 ,1 ,RED);//显示“与视觉模块第三次通信超时”
				Display_Rectangle();
				while(1);
			}
			RTU_Pack_Data(OPENMV_ADD, OPENMV_RECOGNIZE, 0, Data_Stirngs, USART1_DEVICE);
			
			USART1_Send_Count++;
			
			TIM6_ENABLE; 
		}	
	}
}


/**
  * @brief  清除USART串口接收缓存
  * @retval 无
  */
void USART_Buffer_Clean(uint8_t *Buffer)
{
	switch(Buffer[0])
	{
		case OPENMV_ADD :
					Data_Clean(Buffer);
					USART1_RX_Count = 0;
					break;
		
		case IRON_HAND_ADD :
					Data_Clean(Buffer);
					USART2_RX_Count = 0;
					break;
		
		default : break;
	}
}



