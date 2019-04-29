#include "stm32f10x.h"
#include "system_init.h"

uint8_t Data[1];

int main(void) 
{	
	System_Init();
	
	while(1)
	{
		if(USART_RX_Over == TURE)//���������������
		{			
			USART_RX_Over = FALSE;//�ָ������ֵ
						
			switch(RTU_Data_Analysis(Receive_Master_Data))
			{
				case CHECK_SUCCESS:
							Execute_Action(Receive_Master_Data);
							break;
				
				case CHECK_FAILED:
							Clean_Data(Receive_Master_Data);
							break;
				
				default :
							break;
			}
		}
	}		
}



// 	RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_EXECUTE, 0, Data );//��������
// 	
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
// 	while(1);




