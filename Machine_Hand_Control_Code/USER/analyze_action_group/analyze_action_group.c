#include "analyze_action_group.h"

extern Servo  Servo_Action[SERVO_NUM];

//处理 #001P1500T1000! 类似的字符串
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
					Servo_Num = Servo_Num*10 + Action_Group[i][j]-'0';
					j++;
				}
			} 
			else if(Action_Group[i][j] == 'P') 
			{
				PWM = 0;
				j++;
				while(Action_Group[i][j] && Action_Group[i][j] != 'T') 
				{
					PWM = PWM*10 + Action_Group[i][j]-'0';
					j++;
				}
			} 
			else if(Action_Group[i][j] == 'T') 
			{
				Time = 0;
				j++;
				while(Action_Group[i][j] && Action_Group[i][j] != '!') 
				{
					Time = Time*10 + Action_Group[i][j]-'0';
					j++;
				}
				
				if(Servo_Num <= SERVO_NUM && (PWM<=2500) && (PWM>=500) && (Time<=10000)) 
				{
					if(Time < 20)
					{
						Time = 20;//舵机执行时间不能少于20ms
					}
					Servo_Action[Servo_Num].Pulse_Width_Aim = PWM;
					Servo_Action[Servo_Num].Time = Time;
					Servo_Action[Servo_Num].Pulse_Width_Increment = (Servo_Action[Servo_Num].Pulse_Width_Aim - Servo_Action[Servo_Num].Current_Pulse_Width) / (Servo_Action[Servo_Num].Time / 20.000);
					
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
