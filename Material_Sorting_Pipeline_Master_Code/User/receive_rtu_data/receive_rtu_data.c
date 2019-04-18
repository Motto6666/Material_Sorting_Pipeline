#include "receive_rtu_data.h"

extern volatile uint8_t USART1_Send_Count ;//USART1����RTU���ݰ�����
extern volatile uint8_t USART2_Send_Count ;//USART2����RTU���ݰ�����
uint8_t Data_Stirngs[50];


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
								Debug_USART2_Printf("��OpenMvģ���һ��ͨ�ų�ʱ");//��ʱ����LCD��ʾ����ʾ
								break;
					
					case OPENMV_RECOGNIZE:
								Debug_USART2_Printf("��OpenMvģ��ڶ���ͨ�ų�ʱ");//��ʱ����LCD��ʾ����ʾ
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
						Debug_USART2_Printf("OpenMVģ����Ӧ����\n");//��ʱ����LCD��ʾ����ʾ
						break;
			
			case OPENMV_RECOGNIZE:
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
  * @param  Address 				��ַ��
	* @param  Funtion 				������
  * @retval ��
  */
void USART1_Receive_Recognize_Data(void)
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
			//�ڴ����RTU���ݽ�������			
		}
		
	if( (TIM6_Count == 100) && (USART1_Send_Count<=5) )//��ʱʱ��Ϊ5��
		{
			TIM6_DISABLE;
			TIM6_Count = 0;
			if(USART1_Send_Count == 5)
			{
				TIM6_DISABLE;
				Debug_USART2_Printf("��OpenMvģ�������ͨ�ų�ʱ");//��ʱ����LCD��ʾ����ʾ
				while(1);
			}
			RTU_Pack_Data(OPENMV_ADD, OPENMV_RECOGNIZE, 0, Data_Stirngs, USART1_DEVICE);//���RTU���ݲ����͵�ָ���豸
			
			USART1_Send_Count++;
			
			TIM6_ENABLE;
		}	
		
	}
}
