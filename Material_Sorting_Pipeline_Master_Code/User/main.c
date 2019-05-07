#include "stm32f10x.h"
#include "system_init.h"
#include "bsp_systick.h"
#include "modbus_agreement.h"
#include "receive_rtu_data.h"

volatile uint8_t USART1_Send_Count = 0;//USART1����RTU���ݰ���������Ȼ�������ʣ�
volatile uint8_t USART2_Send_Count = 0;//USART2����RTU���ݰ���������Ȼ�������ʣ�
uint8_t Data_Stirng[1];//��ʶ����ɫ���ݣ����ʶ�𵽵����ݴ�ŵ���������

int main(void)
{ 		
	System_Init();
	
	Send_RTU_Data(OPENMV_ADD, OPENMV_CHACK, 0, Data_Stirng, USART1_DEVICE);
			
	Receive_Openmv_Data(OPENMV_ADD, OPENMV_CHACK);
	
	SysTick_Delay_ms(1000);
	
	Send_RTU_Data(IRON_HAND_ADD, IRON_HAND_CHACK, 0, Data_Stirng, USART2_DEVICE);
	
	Receive_Iron_Hand_Data(IRON_HAND_ADD, IRON_HAND_CHACK);
	
	SysTick_Delay_ms(1000);
	
	while(1)
	{
		PHOTOELECTRIC_SENSOR_ENABLE;
		
		MOTOR_ROTATION;
		
		while(Check_Object != TURE)
		{}//����⵽����ʱ������ѭ��
		
		PHOTOELECTRIC_SENSOR_DISABLE;
			
		SysTick_Delay_ms(320);//�ȴ�320ms�������ϵ�������Ӿ���ʶ��ķ�Χ
					
		MOTOR_STOP;
		
		Send_RTU_Data(OPENMV_ADD, OPENMV_RECOGNIZE, 0, Data_Stirng, USART1_DEVICE);
		
		Receive_Openmv_Data(OPENMV_ADD, OPENMV_RECOGNIZE);
		
		Receive_Openmv_Recognize_Data();
			
		if(USART1_RX_Pack[3] != DATA_NONE)//�ж��Ƿ�ʶ�𵽹涨��ɫ������
		{
			Data_Stirng[0] = USART1_RX_Pack[3];//��ʶ�𵽵���ɫ���ݴ�ŵ�Data_Stirng������
			
			Send_RTU_Data(IRON_HAND_ADD, IRON_HAND_EXECUTE, 1, Data_Stirng, USART2_DEVICE);
									
			Receive_Iron_Hand_Data(IRON_HAND_ADD,IRON_HAND_EXECUTE);
			
			Receive_Iron_Hand_Data(IRON_HAND_ADD,IRON_HAND_EXECUTE_END);
			
			Data_Clean(Data_Stirng);
			
			USART_Buffer_Clean(USART1_RX_Pack);	
		}
		
		else
		{
			SysTick_Delay_ms(350);//�ȴ�300ms����֤OpenMv���뵽�ȴ���������״̬
			
			USART_Buffer_Clean(USART1_RX_Pack);		
		}
		
	}
		
}


