#include "execute_action_group.h"

/**
	* @brief  机械手执行蜷缩动作
	* @retval 无
	*/
void Curl_Up_Action(void)
{
	Analyze_Action_Group(Curl_Up);
}


/**
	* @brief  机械手执行抓取物料动作
	* @retval 无
	*/
void Grab_Material_Action(void)
{
	Analyze_Action_Group(Grab_Material_1);	
	Analyze_Action_Group(Grab_Material_2);
	Analyze_Action_Group(Grab_Material_3);
}


/**
	* @brief  机械手往左放置物料
	* @retval 无
	*/
void Left_Place_Action(void)
{
	Analyze_Action_Group(Left_Place_1);	
	Analyze_Action_Group(Left_Place_2);
}


/**
	* @brief  机械手往右放置物料
	* @retval 无
	*/

void Right_Place_Action(void)
{
	Analyze_Action_Group(Right_Place_1);	
	Analyze_Action_Group(Right_Place_2);
}


/**
	* @brief  根据接收到主机的数据执行对应的动作组并返回数据到主机
	* @param  接收到主机的数据
	* @retval 无
	*/
void Execute_Action(uint8_t *Receive__Master__Data)
{
	switch(Receive__Master__Data[1])
	{
		case IRON_HAND_CHACK:
					Send_Data_to_Master(Receive__Master__Data);
					Clean_Data(Receive__Master__Data);			
					break;
		
		case IRON_HAND_EXECUTE:						
					Send_Data_to_Master(Receive__Master__Data);
		
					if(Receive__Master__Data[3] == DATA_RED)
					{
						Grab_Material_Action();//机械手执行抓取物料动作
						Left_Place_Action();//机械手往左放置物料	
						Curl_Up_Action();//机械手执行蜷缩动作
						Receive__Master__Data[1] = IRON_HAND_EXECUTE_END;
						Send_Data_to_Master(Receive__Master__Data);
					}
					
					if(Receive__Master__Data[3] == DATA_GREEN)
					{
						Grab_Material_Action();//机械手执行抓取物料动作
						Right_Place_Action();//机械手往右放置物料
						Curl_Up_Action();//机械手执行蜷缩动作
						Receive__Master__Data[1] = IRON_HAND_EXECUTE_END;
						Send_Data_to_Master(Receive__Master__Data);
					}
					
					if(Receive__Master__Data[3] == DATA_NONE)
					{
						SysTick_Delay_ms(1000);//等待1000ms，保证主机进入接收数据状态
						Receive__Master__Data[1] = IRON_HAND_EXECUTE_END;
						Send_Data_to_Master(Receive__Master__Data);
					}
					
					Clean_Data(Receive__Master__Data);
					break;
		
		default:
					break;									
	}
}


