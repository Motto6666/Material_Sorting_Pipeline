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
