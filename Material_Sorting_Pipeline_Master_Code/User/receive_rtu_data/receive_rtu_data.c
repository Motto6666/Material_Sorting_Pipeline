#include "receive_rtu_data.h"

extern volatile uint8_t USART1_Send_Count ;//USART1����RTU���ݰ�����
extern volatile uint8_t USART2_Send_Count ;//USART2����RTU���ݰ�����
uint8_t Data_Stirngs[1];


/**
  * @brief  USART1���ڽ���Openmv���͵�RTU����֡
  * @param  Address 				��ַ��
	* @param  Funtion 				������
  * @retval ��
  */
void USART1_Rtu_Data_Receive(uint8_t Address, uint8_t Funtion)
{
	TIM6_ENABLE;//������ʱ��TIM6
	while(1)
	{
		if( USART_RX_Over == 1)
		{
			TIM6_DISABLE;//�رն�ʱ��TIM6
			TIM6_Count = 0;//TIM6����ֵ��0
			USART1_Send_Count = 0;//����RTU���ݰ�������0
			USART_RX_Over = 0;//USART_RX_Over�ָ������ֵ����֤�´γ�ʱ��ⲻ����
			break;			
		}
		
		if( (TIM6_Count == 100) && (USART1_Send_Count<=5) )//��ʱʱ��Ϊ5��
		{
			TIM6_DISABLE;
			TIM6_Count = 0;
			if(USART1_Send_Count == 5)
			{
				TIM6_DISABLE;
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
			RTU_Pack_Data(Address, Funtion, 0, Data_Stirngs, USART1_DEVICE);//���RTU���ݲ����͵�ָ���豸
			
			USART1_Send_Count++;
			
			TIM6_ENABLE;
		}
	}
	
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
	Data_Clean(USART1_RX_Pack);//USART1_RX_Pack�ַ����е����ݣ���֤��һ��ִ��ʱ���ݲ�����
	USART1_RX_Count = 0;//����ֵ��0
}


/**
  * @brief  USART1���ڽ���Openmv���͵�ʶ����ɫ����֡
  * @retval ��
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
					
					default : Debug_USART2_Printf("ʶ�����ݴ�������\n");//����ʹ�ã�������Ϻ�ɾ��
								break;
				}
				break;//��������ѭ������
			}
			else
			{
				Debug_USART2_Printf("RTU����У��ʧ��\n");
				TIM6_ENABLE;
				Data_Clean(USART1_RX_Pack);
			}
		}
		
	if( (TIM6_Count == 100) && (USART1_Send_Count<=5) )//��ʱʱ��Ϊ5��
		{
			TIM6_DISABLE;
			TIM6_Count = 0;
			if(USART1_Send_Count == 5)
			{
				TIM6_DISABLE;
				Clean_Screen(7);//���������������ַ�
				Display_Chinese_String( Chinese_Character_10 ,12 ,7 ,1 ,RED);//��ʾ�����Ӿ�ģ�������ͨ�ų�ʱ��
				Debug_USART2_Printf("��OpenMvģ�������ͨ�ų�ʱ");//��ʱ����LCD��ʾ����ʾ
				Display_Rectangle();
				while(1);
			}
			RTU_Pack_Data(OPENMV_ADD, OPENMV_RECOGNIZE, 0, Data_Stirngs, USART1_DEVICE);//���RTU���ݲ����͵�ָ���豸
			
			USART1_Send_Count++;
			
			TIM6_ENABLE; 
		}	
	}
}

