#include "stm32f10x.h"
#include "system_init.h"

int main(void) 
{	
	System_Init();
	
	while(1)
	{
		if(USART_RX_Over == TURE)//�ж��Ƿ�������������͵�����
		{			
			USART_RX_Over = FALSE;
						
			switch(RTU_Data_Analysis(Receive_Master_Data))//У����յ������������Ƿ���ȷ
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





