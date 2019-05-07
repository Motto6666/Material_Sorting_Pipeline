#include "stm32f10x.h"
#include "system_init.h"
#include "bsp_systick.h"
#include "modbus_agreement.h"
#include "receive_rtu_data.h"

volatile uint8_t USART1_Send_Count = 0;//USART1发送RTU数据包次数（仍然存在疑问）
volatile uint8_t USART2_Send_Count = 0;//USART2发送RTU数据包次数（仍然存在疑问）
uint8_t Data_Stirng[1];//若识别到颜色数据，则把识别到的数据存放到该数组里

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
		{}//当检测到物体时，跳出循环
		
		PHOTOELECTRIC_SENSOR_DISABLE;
			
		SysTick_Delay_ms(320);//等待320ms，让物料到达机器视觉可识别的范围
					
		MOTOR_STOP;
		
		Send_RTU_Data(OPENMV_ADD, OPENMV_RECOGNIZE, 0, Data_Stirng, USART1_DEVICE);
		
		Receive_Openmv_Data(OPENMV_ADD, OPENMV_RECOGNIZE);
		
		Receive_Openmv_Recognize_Data();
			
		if(USART1_RX_Pack[3] != DATA_NONE)//判断是否识别到规定颜色的物体
		{
			Data_Stirng[0] = USART1_RX_Pack[3];//将识别到的颜色数据存放到Data_Stirng数组里
			
			Send_RTU_Data(IRON_HAND_ADD, IRON_HAND_EXECUTE, 1, Data_Stirng, USART2_DEVICE);
									
			Receive_Iron_Hand_Data(IRON_HAND_ADD,IRON_HAND_EXECUTE);
			
			Receive_Iron_Hand_Data(IRON_HAND_ADD,IRON_HAND_EXECUTE_END);
			
			Data_Clean(Data_Stirng);
			
			USART_Buffer_Clean(USART1_RX_Pack);	
		}
		
		else
		{
			SysTick_Delay_ms(350);//等待300ms，保证OpenMv进入到等待接收数据状态
			
			USART_Buffer_Clean(USART1_RX_Pack);		
		}
		
	}
		
}


