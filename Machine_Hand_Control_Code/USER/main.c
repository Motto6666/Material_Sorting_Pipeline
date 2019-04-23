#include "stm32f10x.h"
#include "bsp_servo_gpio.h"
#include "servo_control.h"
#include "bsp_systick.h"
#include "bsp_usart1.h"
#include "bsp_usart2.h"
#include "bsp_tim2.h"
#include "bsp_tim3.h"
#include "analyze_action_group.h"
#include "execute_action_group.h"
#include "modbus_agreement.h"

uint8_t Data[1];

int main(void) 
{	
	
	Servo_GPIO_Init();
	Servo_Pulse_Width_Init();
	USART1_Config();
	USART2_Config();
	TIM2_Config_Init();
	TIM3_Config_Init();
	SysTick_Delay_us(2000000);//����ʹ�ã��������ɾ��
	Curl_Up_Action();//��е��ִ����������
	
	while(1)
	{
		if(USART_RX_Over == TRUE)//����STM32���ذ巢�͵��������
		{
			USART1_Printf("���յ�����");//���ݷ��͵����ԣ�����ʹ�ã��������ɾ��������
			
			USART_RX_Over = 0;//�ָ������ֵ
			
			if( RTU_Data_Analysis(USART2_RX_Pack) == CHECK_SUCCESS )
			{
				switch(USART2_RX_Pack[1])
				{
					case IRON_HAND_CHACK:
								RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_CHACK, 0, Data );
								USAER2_RX_Data_Clean(USART2_RX_Pack);			
								break;
					
					case IRON_HAND_EXECUTE:						
								RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_EXECUTE, 0, Data );
								if(USART2_RX_Pack[3] == DATA_RED)
								{
									USART1_Printf("ץȡ��ɫС��");//����ʹ�ã��������ɾ��������
									Grab_Material_Action();//��е��ִ��ץȡ���϶���
									Left_Place_Action();//��е�������������	
									Curl_Up_Action();//��е��ִ����������
									RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_EXECUTE_END, 0, Data );
									USART1_Printf("ץȡ��ϣ����ͷ�������");//����ʹ�ã��������ɾ��������
								}
								else if(USART2_RX_Pack[3] == DATA_GREEN)
								{
									Grab_Material_Action();//��е��ִ��ץȡ���϶���
									Right_Place_Action();//��е�����ҷ�������
									Curl_Up_Action();//��е��ִ����������
									RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_EXECUTE_END, 0, Data );
								}
								USAER2_RX_Data_Clean(USART2_RX_Pack);
								break;
					
					default:break;									
				}
			}
			else
			{
				USAER2_RX_Data_Clean(USART2_RX_Pack);
			}
		}
		
	}
	
// 	SysTick_Delay_us(2000000);//����ʹ�ã��������ɾ��
// 	

// 	Curl_Up_Action();//��е��ִ����������
// 		
// 	Grab_Material_Action();//��е��ִ��ץȡ���϶���
// 	
// 	Left_Place_Action();//��е�������������
// 		
// 	Curl_Up_Action();//��е��ִ����������
// 		
// 	Grab_Material_Action();//��е��ִ��ץȡ���϶���

// 	Right_Place_Action();//��е�����ҷ�������
// 		
// 	Curl_Up_Action();//��е��ִ����������
// 	
// 	USART1_Printf("������ִ�����");//����ʹ�ã��������ɾ��������
// 	
// 	while(1);

}



