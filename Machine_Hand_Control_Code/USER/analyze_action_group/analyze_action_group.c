#include "analyze_action_group.h"

extern Servo_Struct  Servo[SERVO_NUM];

/**
	* @brief  解析动作组，类似处理 “#001P1500T1000!”的字符串
	* @retval 无
	*/
void Analyze_Action_Group(uint8_t (*Action_Group)[20])
{
	uint8_t Servo_Num;
	uint16_t PWM, Time,i = 0,j = 0;
	
	while(Action_Group[i][j])
	{
		while(Action_Group[i][j]) 
		{
			if(Action_Group[i][j] == '#') 
			{
				Servo_Num = 0;
				j++;
				while(Action_Group[i][j] && Action_Group[i][j] != 'P') 
				{
					Servo_Num = Servo_Num*10 + Action_Group[i][j]-'0';//计算舵机标号
					j++;
				}
			} 
			else if(Action_Group[i][j] == 'P') 
			{
				PWM = 0;
				j++;
				while(Action_Group[i][j] && Action_Group[i][j] != 'T') 
				{
					PWM = PWM*10 + Action_Group[i][j]-'0';//计算PWM值
					j++;
				}
			} 
			else if(Action_Group[i][j] == 'T') 
			{
				Time = 0;
				j++;
				while(Action_Group[i][j] && Action_Group[i][j] != '!') 
				{
					Time = Time*10 + Action_Group[i][j]-'0';//计算舵机转动时间
					j++;
				}
				
				if(Servo_Num <= SERVO_NUM && (PWM<=2500) && (PWM>=500) && (Time<=10000)) 
				{
					if(Time < 20)
					{
						Time = 20;//舵机执行时间不能少于20ms
					}
					Servo[Servo_Num].Aim_PWM = PWM;
					Servo[Servo_Num].Time = Time;
					Servo[Servo_Num].Increment_PWM = (Servo[Servo_Num].Aim_PWM - Servo[Servo_Num].Current_PWM) / (Servo[Servo_Num].Time / 20.000);
					
				}
			} 
			else 
			{
				j++;
			}
		}
		
		i++;
		j = 0;
	}
}
