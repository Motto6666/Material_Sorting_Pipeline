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
	
	CLOCKWISE_ROTATION;
	
	SysTick_Delay_ms(60000);//����ʹ�ã��������ɾ��!!!
	
	MOTOR_STOP;
	
	
	
	
	RTU_Pack_Data(OPENMV_ADD, OPENMV_CHACK, 0, Data_Stirng, USART1_DEVICE);//���RTU���ݲ����͵�ָ���豸
			
	Receive_Openmv_Data(OPENMV_ADD, OPENMV_CHACK);
	
	SysTick_Delay_ms(2000);
	
	RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_CHACK, 0, Data_Stirng, USART2_DEVICE);
	
	Receive_Iron_Hand_Data(IRON_HAND_ADD, IRON_HAND_CHACK);
	
	SysTick_Delay_ms(2000);
	
	while(1)
	{
		
		
		RTU_Pack_Data(OPENMV_ADD, OPENMV_RECOGNIZE, 0, Data_Stirng, USART1_DEVICE);
		
		Receive_Openmv_Data(OPENMV_ADD, OPENMV_RECOGNIZE);
		
		Receive_Openmv_Recognize_Data();

		Data_Stirng[0] = USART1_RX_Pack[3];//��ʶ�𵽵���ɫ���ݴ�ŵ�Data_Stirng������
		
		
		
		
		SysTick_Delay_ms(1000);//�ȴ�1s����֤��е�ֿ���ģ���ѽ��뵽�������ݵ�״̬



		
		RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_EXECUTE, 1, Data_Stirng, USART2_DEVICE);
		            
		Receive_Iron_Hand_Data(IRON_HAND_ADD,IRON_HAND_EXECUTE);
		
		USART_Buffer_Clean(USART1_RX_Pack);
		Data_Clean(Data_Stirng);
		
		Receive_Iron_Hand_Data(IRON_HAND_ADD,IRON_HAND_EXECUTE_END);
		
		
		SysTick_Delay_ms(1000);//����ʹ�ã��������ɾ������������
		
	}
		
}


