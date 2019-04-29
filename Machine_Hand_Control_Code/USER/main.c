#include "stm32f10x.h"
#include "system_init.h"

uint8_t Data[1];

int main(void) 
{	
	System_Init();
	
	while(1)
	{
		if(USART_RX_Over == TURE)//接收主机数据完毕
		{			
			USART_RX_Over = FALSE;//恢复到最初值
						
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



// 	RTU_Pack_Data(IRON_HAND_ADD, IRON_HAND_EXECUTE, 0, Data );//存在问题
// 	
// 	SysTick_Delay_us(2000000);//调试使用，调试完毕删除
// 	
// 	Curl_Up_Action();//机械手执行蜷缩动作
// 		
// 	Grab_Material_Action();//机械手执行抓取物料动作
// 	
// 	Left_Place_Action();//机械手往左放置物料
// 		
// 	Curl_Up_Action();//机械手执行蜷缩动作
// 		
// 	Grab_Material_Action();//机械手执行抓取物料动作

// 	Right_Place_Action();//机械手往右放置物料
// 		
// 	Curl_Up_Action();//机械手执行蜷缩动作
// 		
// 	while(1);




