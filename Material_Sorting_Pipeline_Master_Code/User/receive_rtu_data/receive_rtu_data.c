#include "receive_rtu_data.h"

extern volatile uint8_t USART1_Send_Count ;//USART1����RTU���ݰ�����
extern volatile uint8_t USART2_Send_Count ;//USART2����RTU���ݰ�����
uint8_t Data_Stirngs[1];


/**
  * @brief  USART1���ڵȴ�����Openmv���͵�RTU����֡
  * @param  Address 				��ַ��
	* @param  Funtion 				������
  * @retval ��
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
				break;//��������ѭ������
			}
			else
			{
				TIM6_ENABLE;
				USART_Buffer_Clean(USART1_RX_Pack);
			}			
		}
		
		if( (TIM6_Count == FIVE_SECONDS) && (USART1_Send_Count<=5) )//��ʱʱ��Ϊ5��
		{
			TIM6_Shut_Down();
			if(USART1_Send_Count == 5)
			{
				TIM6_Shut_Down();
				switch(Funtion)
				{
					case OPENMV_CHACK:
								Clean_Screen(7);//���������������ַ�
								Display_Chinese_String( Chinese_Character_4  ,12 ,7 ,1 ,RED);//��ʾ�����Ӿ�ģ���һ��ͨ�ų�ʱ��
								Display_Rectangle();
								break;
					
					case OPENMV_RECOGNIZE:
								Clean_Screen(7);//���������������ַ�
								Display_Chinese_String( Chinese_Character_8  ,12 ,7 ,1 ,RED);//��ʾ�����Ӿ�ģ��ڶ���ͨ�ų�ʱ��
								Display_Rectangle();
								break;
					
					default: break;
				}
				while(1);
			}
			
			RTU_Pack_Data(Address, Funtion, 0, Data_Stirngs, USART1_DEVICE);//���´��RTU���ݲ����͵�ָ���豸
			
			USART1_Send_Count++;
			
			TIM6_ENABLE;
		}
	}
	
	LCD_Display_State(Address,Funtion);//������ѭ��ʱ��ִ�и����
}


/**
  * @brief  USART2���ڵȴ����ջ�е�ֿ��ư巢�͵�RTU����֡
  * @param  Address 				��ַ��
	* @param  Funtion 				������
  * @retval ��
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
				break;//��������ѭ������
			}
			else
			{
				TIM6_ENABLE;
				USART_Buffer_Clean(USART2_RX_Pack);
			}			
		}
		
		if( (TIM6_Count == FIVE_SECONDS) && (USART2_Send_Count<=5) )//��ʱʱ��Ϊ10��
		{
			TIM6_Shut_Down();
			if(USART2_Send_Count == 5)
			{
				TIM6_Shut_Down();
				switch(Funtion)
				{
					case IRON_HAND_CHACK:
								Clean_Screen(7);//���������������ַ�
								Display_Chinese_String( Chinese_Character_6  ,15 ,7 ,1 ,RED);//��ʾ�����е�ֿ���ģ���һ��ͨ�ų�ʱ��
								Display_Rectangle();
								break;
					
					case IRON_HAND_EXECUTE:
								Clean_Screen(7);//���������������ַ�
								Display_Chinese_String( Chinese_Character_12 ,15 ,7 ,1 ,RED);//��ʾ�����е�ֿ���ģ��ڶ���ͨ�ų�ʱ��
								Display_Rectangle();
								break;
					
					case IRON_HAND_EXECUTE_END:
								Clean_Screen(7);//���������������ַ�
								Display_Chinese_String( Chinese_Character_14 ,15 ,7 ,1 ,RED);//��ʾ�����е�ֿ���ģ�������ͨ�ų�ʱ��
								Display_Rectangle();
								break;
					
					default: break;
				}
				while(1);
			}
			
			switch(Funtion)
			{
				case IRON_HAND_CHACK:
							RTU_Pack_Data(Address, Funtion, 0, Data_Stirngs, USART2_DEVICE);//���´��RTU���ݲ����͵�ָ���豸
							break;
				
				case IRON_HAND_EXECUTE:
							Data_Stirngs[0] = USART1_RX_Pack[3];////��ʶ�𵽵���ɫ���ݴ�ŵ�Data_Stirngs������
							RTU_Pack_Data(Address, Funtion, 1, Data_Stirngs, USART2_DEVICE);//���´��RTU���ݲ����͵�ָ���豸
							Data_Clean(Data_Stirngs);
							break;
				
				case IRON_HAND_EXECUTE_END://���뵽�ȴ���е�ַ���ִ��������ݻ���ʱ������ÿ��5S����RTU����֡
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
  * @brief  LCD��ʾ�������ַ�
	* @param  Address 				��ַ��
	* @param  Funtion 				������
  * @retval ��
  */
void LCD_Display_State(uint8_t Address, uint8_t Funtion)
{
	switch(Funtion)
	{
		case OPENMV_CHACK:
					Clean_Screen(7);//���������������ַ�
					Display_Chinese_String( Chinese_Character_3  ,8  ,7 ,1 ,GREEN);//��ʾ���Ӿ�ģ����Ӧ������
					break;
		
		case OPENMV_RECOGNIZE:
					Clean_Screen(7);//���������������ַ�
					Display_Chinese_String( Chinese_Character_7  ,8  ,7 ,1 ,GREEN);//��ʾ���Ӿ�ģ��ʶ��ʼ��
					break;
		
		case IRON_HAND_CHACK:
					Clean_Screen(7);//���������������ַ�
					Display_Chinese_String( Chinese_Character_5  ,11 ,7 ,1 ,GREEN);//��ʾ����е�ֿ���ģ����Ӧ������
					break;
		
		case IRON_HAND_EXECUTE:
					Clean_Screen(7);//���������������ַ�
					Display_Chinese_String( Chinese_Character_11 ,7  ,7 ,1 ,GREEN);//��ʾ����е��ִ�в�������ģ����
					break;
		
		case IRON_HAND_EXECUTE_END:
					Clean_Screen(7);//���������������ַ�
					Display_Chinese_String( Chinese_Character_13 ,7  ,7 ,1 ,GREEN);//��ʾ����е��ִ����ϡ���ģ����
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
  * @brief  USART1���ڵȴ�����Openmv���͵�ʶ�𵽵���ɫRTU����֡
  * @retval ��
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
				
				RTU_Pack_Data(OPENMV_ADD, OPENMV_RECOGNIZE, 1, Data_Stirngs, USART1_DEVICE);//����ok֡��Openmv
				
				Data_Clean(Data_Stirngs);
				
				switch(USART1_RX_Pack[3])//USART1_RX_Pack[3]Ϊ������
				{
					case DATA_RED :
								Clean_Screen(7);//���������������ַ�
								Display_Chinese_String( Chinese_Character_15  ,5  ,7 ,1 ,GREEN);//��ʾ��ʶ�𵽺�ɫ��
								break;
					
					case DATA_GREEN :
								Clean_Screen(7);//���������������ַ�
								Display_Chinese_String( Chinese_Character_16  ,5  ,7 ,1 ,GREEN);//��ʾ��ʶ����ɫ��
								break;
					
					case DATA_NONE :
								Clean_Screen(7);//���������������ַ�
								Display_Chinese_String( Chinese_Character_17  ,13  ,7 ,1 ,GREEN);//��ʾ�����������ɫ����ʶ��Χ�ڡ�
								break;
					
					default : break;
				}
				
				break;//��������ѭ������
				
			}
			else
			{
				TIM6_ENABLE;
				USART_Buffer_Clean(USART1_RX_Pack);
			}
		}
		
	if( (TIM6_Count == FIVE_SECONDS) && (USART1_Send_Count<=5) )//��ʱʱ��Ϊ5��
		{
			TIM6_Shut_Down();
			if(USART1_Send_Count == 5)
			{
				TIM6_Shut_Down();
				Clean_Screen(7);//���������������ַ�
				Display_Chinese_String( Chinese_Character_10 ,12 ,7 ,1 ,RED);//��ʾ�����Ӿ�ģ�������ͨ�ų�ʱ��
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
  * @brief  ���USART���ڽ��ջ���
  * @retval ��
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



