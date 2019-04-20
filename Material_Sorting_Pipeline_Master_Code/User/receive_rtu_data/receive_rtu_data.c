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
void USART1_Receive_State_Data(uint8_t Address, uint8_t Funtion)
{
	TIM6_ENABLE;//������ʱ��TIM6
	while(1)
	{
		if( USART_RX_Over == TURE)
		{
			TIM6_Shut_Down();
			USART1_Send_Count = 0;//����RTU���ݰ�������0
			USART_RX_Over = 0;//USART_RX_Over�ָ������ֵ����֤�´γ�ʱ��ⲻ����
			break;			
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
								Debug_USART2_Printf("��OpenMvģ���һ��ͨ�ų�ʱ");//��ʱ����LCD��ʾ����ʾ
								Display_Rectangle();
								break;
					
					case OPENMV_RECOGNIZE:
								Clean_Screen(7);//���������������ַ�
								Display_Chinese_String( Chinese_Character_8  ,12 ,7 ,1 ,RED);//��ʾ�����Ӿ�ģ��ڶ���ͨ�ų�ʱ��
								Debug_USART2_Printf("��OpenMvģ��ڶ���ͨ�ų�ʱ");//��ʱ����LCD��ʾ����ʾ
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
	
	LCD_Display_State(Address,Funtion);
}


/**
  * @brief  
  * @retval ��
  */
void LCD_Display_State(uint8_t Address, uint8_t Funtion)
{
	if(USART1_RX_Pack[0] == Address || USART1_RX_Pack[1] == Funtion)
	{
		switch(Funtion)
		{
			case OPENMV_CHACK:
						Clean_Screen(7);//���������������ַ�
						Display_Chinese_String( Chinese_Character_3  ,8  ,7 ,1 ,GREEN);//��ʾ���Ӿ�ģ����Ӧ������
						Debug_USART2_Printf("OpenMVģ����Ӧ����\n");//��ʱ����LCD��ʾ����ʾ
						break;
			
			case OPENMV_RECOGNIZE:
						Clean_Screen(7);//���������������ַ�
						Display_Chinese_String( Chinese_Character_7  ,8  ,7 ,1 ,GREEN);//��ʾ���Ӿ�ģ��ʶ��ʼ��
						Debug_USART2_Printf("OpenMVʶ��ʼ\n");//��ʱ����LCD��ʾ����ʾ
						break;
			
			default: break;
		}
	}
	USART_Buffer_Clean(USART1_RX_Pack);
}


/**
  * @brief  USART1���ڵȴ�����Openmv���͵�ʶ�𵽵���ɫRTU����֡
  * @retval ��
  */
void USART1_Receive_Recognize_Data(void)
{	
	TIM6_ENABLE;
	while(1)
	{
		if( USART_RX_Over == TURE)
		{
			TIM6_Shut_Down();
			USART_RX_Over = 0;
			printf("%s\n",USART1_RX_Pack);
			if( RTU_Data_Analysis(USART1_RX_Pack) == CHECK_SUCCESS )
			{
				
				RTU_Pack_Data(OPENMV_ADD, OK, 0, Data_Stirngs, USART1_DEVICE);//����ok֡��openMV
				
				switch(USART1_RX_Pack[3])//USART1_RX_Pack[3]Ϊ������
				{
					case DATA_RED :
								Clean_Screen(7);//���������������ַ�
								Display_Chinese_String( Chinese_Character_15  ,5  ,7 ,1 ,GREEN);//��ʾ��ʶ�𵽺�ɫ��
								Debug_USART2_Printf("OpenMVʶ�𵽺�ɫ����\n");//��ʱ����LCD��ʾ����ʾ
								break;
					
					case DATA_GREEN :
								Clean_Screen(7);//���������������ַ�
								Display_Chinese_String( Chinese_Character_16  ,5  ,7 ,1 ,GREEN);//��ʾ��ʶ����ɫ��
								Debug_USART2_Printf("OpenMVʶ����ɫ����\n");//��ʱ����LCD��ʾ����ʾ
								break;
					
					case DATA_NONE :
								Clean_Screen(7);//���������������ַ�
								Display_Chinese_String( Chinese_Character_17  ,13  ,7 ,1 ,GREEN);//��ʾ�����������ɫ����ʶ��Χ�ڡ�
								Debug_USART2_Printf("���������ɫ����ʶ��Χ��\n");//��ʱ����LCD��ʾ����ʾ
								break;
					
					default : break;
				}
				
				break;//��������ѭ������
				
			}
			else
			{
				Debug_USART2_Printf("RTU����У��ʧ��\n");
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
				Debug_USART2_Printf("��OpenMvģ�������ͨ�ų�ʱ");//��ʱ����LCD��ʾ����ʾ
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
	Data_Clean(Buffer);
	USART1_RX_Count = 0;
	USART2_RX_Count = 0;
}

