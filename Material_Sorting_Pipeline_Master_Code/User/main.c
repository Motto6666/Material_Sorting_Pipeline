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
	
	CLOCKWISE_ROTATION;
	
	SysTick_Delay_ms(60000);//调试使用，调试完毕删除!!!
	
	MOTOR_STOP;
	
	
	
	
	RTU_Pack_Data(OPENMV_ADD, OPENMV_CHACK, 0, Data_Stirng, USART1_DEVICE);//打包RTU数据并发送到指定设备
			
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

		Data_Stirng[0] = USART1_RX_Pack[3];//将识别到的颜色数据存放到Data_Stirng数组里
		
		
		
		
		SysTick_Delay_ms(1000);//等待1s，保证机械手控制模块已进入到接收数据的状态



		
		RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_EXECUTE, 1, Data_Stirng, USART2_DEVICE);
		            
		Receive_Iron_Hand_Data(IRON_HAND_ADD,IRON_HAND_EXECUTE);
		
		USART_Buffer_Clean(USART1_RX_Pack);
		Data_Clean(Data_Stirng);
		
		Receive_Iron_Hand_Data(IRON_HAND_ADD,IRON_HAND_EXECUTE_END);
		
		
		SysTick_Delay_ms(1000);//调试使用，调试完毕删除！！！！！
		
	}
		
}


