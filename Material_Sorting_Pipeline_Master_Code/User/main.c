#include "stm32f10x.h"
#include "system_init.h"
#include "bsp_systick.h"
#include "modbus_agreement.h"
#include "receive_rtu_data.h"


volatile uint8_t USART1_Send_Count = 0;//USART1����RTU���ݰ���������Ȼ�������ʣ�
volatile uint8_t USART2_Send_Count = 0;//USART2����RTU���ݰ���������Ȼ�������ʣ�

uint8_t Data_Stirng[1];

int main(void)
{ 		
	System_Init();
	
	RTU_Pack_Data(OPENMV_ADD, OPENMV_CHACK, 0, Data_Stirng, USART1_DEVICE);//���RTU���ݲ����͵�ָ���豸
			
	USART1_Receive_State_Data(OPENMV_ADD, OPENMV_CHACK);
	
	while(1)
	{
		SysTick_Delay_us(1000);//�ȴ�1ms����֤OpenMVģ���ѽ��뵽�������ݵ�״̬
	
		RTU_Pack_Data(OPENMV_ADD, OPENMV_RECOGNIZE, 0, Data_Stirng, USART1_DEVICE);
		
		USART1_Receive_State_Data(OPENMV_ADD, OPENMV_RECOGNIZE);
		
		USART1_Receive_Recognize_Data();
		
		USART_Buffer_Clean(USART1_RX_Pack);
	}
	
	
	
		
	
	
	
	
		
//	TIM6_ENABLE;//������ʱ��TIM6
		 
//	while(1)
//	{
//		if( USART_RX_Over == 1)
//		{
//			TIM6_DISABLE;//�رն�ʱ��TIM6
//			TIM6_Count = 0;//TIM6����ֵ��0
//			USART1_Send_Count = 0;//����RTU���ݰ�������0
//			USART_RX_Over = 0;//USART_RX_Over�ָ������ֵ����֤�´γ�ʱ��ⲻ���� 
//			break;
//		}
//		
//		if( (TIM6_Count == 100) && (USART1_Send_Count<=5) )//��ʱʱ��Ϊ5��
//		{
//			TIM6_DISABLE;
//			TIM6_Count = 0;
//			if(USART1_Send_Count == 5)
//			{
//				TIM6_DISABLE;
//				Debug_USART2_Printf("��OpenMvģ���һ��ͨ�ų�ʱ");//��ʱ����LCD��ʾ����ʾ
//				while(1);
//			}
//			RTU_Pack_Data(OPENMV_ADD, OPENMV_CHACK, 0, Data_Stirng, USART1_DEVICE);//���RTU���ݲ����͵�ָ���豸
//			USART1_Send_Count++;
//			TIM6_ENABLE;
//		}
//		
//	}
//			
//	if(USART1_RX_Pack[0] == OPENMV_ADD || USART1_RX_Pack[1] == OPENMV_CHACK)
//	{
//		Debug_USART2_Printf("OpenMVģ����Ӧ����\n");//��ʱ����LCD��ʾ����ʾ
//	}
//	Data_Clean(USART1_RX_Pack);//USART1_RX_Pack�ַ����е����ݣ���֤��һ��ִ��ʱ���ݲ�����
//	USART1_RX_Count = 0;//����ֵ��0
	
	
	
//	SysTick_Delay_us(1000);
//	
//	
//	
//	RTU_Pack_Data(OPENMV_ADD, OPENMV_RECOGNIZE, 0, Data_Stirng, USART1_DEVICE);//���RTU���ݲ����͵�ָ���豸
//	
//	Debug_USART2_Printf("USART1�ڶ������ݷ��ͳɹ�");
//	//	
//	TIM6_ENABLE;//������ʱ��TIM6
//	
//	while(1)
//	{
//		if( USART_RX_Over == 1)
//		{
//			TIM6_DISABLE;//�رն�ʱ��TIM6
//			TIM6_Count = 0;//TIM6����ֵ��0
//			USART1_Send_Count = 0;//����RTU���ݰ�������0
//			USART_RX_Over = 0;//USART_RX_Over�ָ������ֵ����֤�´γ�ʱ��ⲻ���� 
//			break;
//		}
//		
//		if( (TIM6_Count == 100) && (USART1_Send_Count<=5) )//��ʱʱ��Ϊ5��
//		{
//			TIM6_DISABLE;
//			TIM6_Count = 0;
//			if(USART1_Send_Count == 5)
//			{
//				TIM6_DISABLE;
//				Debug_USART2_Printf("��OpenMvģ��ڶ���ͨ�ų�ʱ");//��ʱ����LCD��ʾ����ʾ
//				while(1);
//			}
//			RTU_Pack_Data(OPENMV_ADD, OPENMV_CHACK, 0, Data_Stirng, USART1_DEVICE);//���RTU���ݲ����͵�ָ���豸
//			USART1_Send_Count++;
//			TIM6_ENABLE;
//		}
//		
//	}
//				
//	if(USART1_RX_Pack[0] == OPENMV_ADD || USART1_RX_Pack[1] == OPENMV_RECOGNIZE)
//	{
//		Debug_USART2_Printf("OpenMVģ��ʶ��ʼ\n");//��ʱ����LCD��ʾ����ʾ
//	}
//	Data_Clean(USART1_RX_Pack);//USART1_RX_Pack�ַ����е����ݣ���֤��һ��ִ��ʱ���ݲ�����
//	USART1_RX_Count = 0;//����ֵ��0
//	
//	
//	
//	TIM6_ENABLE;//������ʱ��TIM6
//	
//	while(1)
//	{
//		if( USART_RX_Over == 1)
//		{
//			TIM6_DISABLE;//�رն�ʱ��TIM6
//			TIM6_Count = 0;//TIM6����ֵ��0
//			USART1_Send_Count = 0;//����RTU���ݰ�������0
//			USART_RX_Over = 0;//USART_RX_Over�ָ������ֵ����֤�´γ�ʱ��ⲻ���� 
//			break;
//		}
//		
//		if( (TIM6_Count == 100) && (USART1_Send_Count<=5) )//��ʱʱ��Ϊ5��
//		{
//			TIM6_DISABLE;
//			TIM6_Count = 0;
//			if(USART1_Send_Count == 5)
//			{
//				TIM6_DISABLE;
//				Debug_USART2_Printf("��OpenMvģ�������ͨ�ų�ʱ");//��ʱ����LCD��ʾ����ʾ
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
//		Debug_USART2_Printf("ʶ����ɫ����\n");//��ʱ����LCD��ʾ����ʾ
//	}
//	if(USART1_RX_Pack[3] == DATA_RED)
//	{
//		Debug_USART2_Printf("ʶ�𵽺�ɫ����\n");//��ʱ����LCD��ʾ����ʾ
//	}
//	if(USART1_RX_Pack[3] == DATA_NONE)
//	{
//		Debug_USART2_Printf("�����岻��ʶ��Χ��\n");//��ʱ����LCD��ʾ����ʾ
//	}
//	
//	Data_Clean(USART1_RX_Pack);//USART1_RX_Pack�ַ����е����ݣ���֤��һ��ִ��ʱ���ݲ�����
//	USART1_RX_Count = 0;//����ֵ��0
	

	
	while(1);//����ʹ�ã��������ɾ��������
	
	
	
	

//	RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_CHACK, 0, Data_Stirng, USART2_DEVICE);//���RTU���ݲ����͵�ָ���豸
//	
//	TIM6_ENABLE;//������ʱ��TIM6
//	
//	while(1)
//	{
//		if( USART_RX_Over == 1)
//		{
//			TIM6_DISABLE;//�رն�ʱ��TIM6
//			TIM6_Count = 0;//TIM6����ֵ��0
//			USART2_Send_Count = 0;//USART2����RTU���ݰ�������0
//			USART_RX_Over = 0;//USART_RX_Over�ָ������ֵ����֤�´γ�ʱ��ⲻ���� 
//			break;
//		}
//		
//		if( (TIM6_Count == 100) && (USART2_Send_Count<=5) )//��ʱʱ��Ϊ5��
//		{
//			TIM6_DISABLE;
//			TIM6_Count = 0;
//			if(USART2_Send_Count == 5)
//			{
//				Debug_USART2_Printf("���е��ģ���һ��ͨ�ų�ʱ");
//				while(1);
//			}
//			RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_CHACK, 0, Data_Stirng, USART2_DEVICE);//���RTU���ݲ����͵�ָ���豸
//			USART2_Send_Count++;
//			TIM6_ENABLE;
//		}
//		
//	}
//				
//	Debug_USART2_Printf("���USART2��ʱ���");//��ʱ����LCD��ʾ����ʾ
//	USART2_Printf(USART2_RX_Pack);
//	if(USART2_RX_Pack[0] == IRON_HAND_ADD && USART2_RX_Pack[1] == IRON_HAND_CHACK)
//	{
//		Debug_USART2_Printf("��е��ģ����Ӧ����");//��ʱ����LCD��ʾ����ʾ
//	}	
//	Data_Clean(USART2_RX_Pack);//USART1_RX_Pack�ַ����е����ݣ���֤��һ��ִ��ʱ���ݲ�����
//	USART2_RX_Count = 0;//����ֵ��0
//	
//	while(1);



	
//	ILI9341_Init();//���Ը���ʵ��������������޸�!!!

//	printf("\r\n��ȡ����ID =%x",ILI9341_Read_ID());
//	
//	Display_Motto6666(1 ,1, YELLOW);//��ʾ��Motto6666��Ӣ���ַ���
//	Display_Chinese_String( Chinese_Character_1  ,9  ,3 ,1 ,BLUE2);//��ʾ�����Ϸּ���ˮ��ϵͳ�������ַ���
//	Display_Chinese_String( Chinese_Character_2  ,7  ,5 ,1 ,MAGENTA);//��ʾ��ϵͳ�����������
//	Display_Chinese_String( Chinese_Character_3  ,8  ,7 ,1 ,GREEN);//��ʾ���Ӿ�ģ����Ӧ������
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//���������������ַ�
//	Display_Chinese_String( Chinese_Character_4  ,12 ,7 ,1 ,RED);//��ʾ�����Ӿ�ģ���һ��ͨ�ų�ʱ��
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_5  ,11 ,7 ,1 ,GREEN);//��ʾ����е�ֿ���ģ����Ӧ������
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_6  ,15 ,7 ,1 ,RED);//��ʾ�����е�ֿ���ģ���һ��ͨ�ų�ʱ��
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_7  ,8  ,7 ,1 ,GREEN);//��ʾ���Ӿ�ģ��ʶ��ʼ��
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_8  ,12 ,7 ,1 ,RED);//��ʾ�����Ӿ�ģ��ڶ���ͨ�ų�ʱ��
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_9  ,8  ,7 ,1 ,GREEN);//��ʾ���Ӿ�ģ��ʶ�������
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_10 ,12 ,7 ,1 ,RED);//��ʾ�����Ӿ�ģ�������ͨ�ų�ʱ��
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_11 ,7  ,7 ,1 ,GREEN);//��ʾ����е��ִ�в�������ģ����
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_12 ,15 ,7 ,1 ,RED);//��ʾ�����е�ֿ���ģ��ڶ���ͨ�ų�ʱ��
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_13 ,7  ,7 ,1 ,GREEN);//��ʾ����е��ִ����ϡ���ģ����
//	SysTick_Delay_us(5000000);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_14 ,15 ,7 ,1 ,RED);//��ʾ�����е�ֿ���ģ�������ͨ�ų�ʱ��
//	
//  
//	/* ������ */	
//	while(1)//��STM32���ذ���ģ���ͨ�ų�ʱʱ��ʹ�øú���
//	{
//		ILI9341_Draw_Rect(220,300,20, 20,RED);
//		Delay(0xFFFF0);//����ʹ�ã��������ɾ��
//    ILI9341_Draw_Rect(220,300,20,20,BLACK);
//		Delay(0xFFFF0);//����ʹ�ã��������ɾ��
//	} 

}





/*********************************************END OF FILE**********************/
