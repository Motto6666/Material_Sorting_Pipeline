#include "execute_action_group.h"

/**
	* @brief  ��е��ִ����������
	* @retval ��
	*/
void Curl_Up_Action(void)
{
	Analyze_Action_Group(Curl_Up);
}


/**
	* @brief  ��е��ִ��ץȡ���϶���
	* @retval ��
	*/
void Grab_Material_Action(void)
{
	Analyze_Action_Group(Grab_Material_1);	
	Analyze_Action_Group(Grab_Material_2);
	Analyze_Action_Group(Grab_Material_3);
}


/**
	* @brief  ��е�������������
	* @retval ��
	*/
void Left_Place_Action(void)
{
	Analyze_Action_Group(Left_Place_1);	
	Analyze_Action_Group(Left_Place_2);
}


/**
	* @brief  ��е�����ҷ�������
	* @retval ��
	*/

void Right_Place_Action(void)
{
	Analyze_Action_Group(Right_Place_1);	
	Analyze_Action_Group(Right_Place_2);
}


/**
	* @brief  ���ݽ��յ�����������ִ�ж�Ӧ�Ķ����鲢�������ݵ�����
	* @param  ���յ�����������
	* @retval ��
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
						Grab_Material_Action();//��е��ִ��ץȡ���϶���
						Left_Place_Action();//��е�������������	
						Curl_Up_Action();//��е��ִ����������
						Receive__Master__Data[1] = IRON_HAND_EXECUTE_END;
						Send_Data_to_Master(Receive__Master__Data);
					}
					
					if(Receive__Master__Data[3] == DATA_GREEN)
					{
						Grab_Material_Action();//��е��ִ��ץȡ���϶���
						Right_Place_Action();//��е�����ҷ�������
						Curl_Up_Action();//��е��ִ����������
						Receive__Master__Data[1] = IRON_HAND_EXECUTE_END;
						Send_Data_to_Master(Receive__Master__Data);
					}
					
					if(Receive__Master__Data[3] == DATA_NONE)
					{
						SysTick_Delay_ms(1000);//�ȴ�1000ms����֤���������������״̬
						Receive__Master__Data[1] = IRON_HAND_EXECUTE_END;
						Send_Data_to_Master(Receive__Master__Data);
					}
					
					Clean_Data(Receive__Master__Data);
					break;
		
		default:
					break;									
	}
}


