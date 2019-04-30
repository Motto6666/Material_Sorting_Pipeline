#include "stm32f10x.h"
#include "system_init.h"

int main(void) 
{	
	System_Init();
	
	while(1)
	{
		if(USART_RX_Over == TURE)//判断是否接收完主机发送的数据
		{			
			USART_RX_Over = FALSE;
						
			switch(RTU_Data_Analysis(Receive_Master_Data))//校验接收到主机的数据是否正确
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





