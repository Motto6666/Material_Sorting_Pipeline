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
