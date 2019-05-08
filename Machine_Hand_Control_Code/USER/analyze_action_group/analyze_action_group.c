#include "analyze_action_group.h"
#include "bsp_systick.h"

extern Servo_Struct  Servo[SERVO_NUM];

uint8_t Curl_Up[7][15] =  //机械手蜷缩动作组
{
	{"#001P1500T1000!"},
	{"#002P1000T1000!"},
	{"#003P0700T1000!"},
	{"#004P0950T1000!"},
	{"#005P1100T1000!"},
};

uint8_t Grab_Material_1[9][15] = //机械手抓取物料1
{
	{"#001P1500T0100!"},
	{"#002P1100T0700!"},
	{"#003P0550T0700!"},
	{"#004P1230T0600!"},
	{"#005P1100T0500!"},
};

uint8_t  Grab_Material_2[11][15] = //机械手抓取物料2
{
	{"#001P1500T0010!"},
	{"#002P1100T0010!"},
	{"#003P0550T0010!"},
	{"#004P1210T0800!"},
	{"#005P1900T0100!"},
};

uint8_t Grab_Material_3[12][15] = //机械手抓取物料3
{
	{"#001P1500T0010!"},
	{"#002P1050T0200!"},
	{"#003P0700T0200!"},
	{"#004P1220T0200!"},
	{"#005P1900T0100!"},
};


uint8_t Left_Place_1[15][15] = //机械手左放1:
{
	{"#001P2150T0600!"},
	{"#002P1050T0010!"},
	{"#003P0700T0010!"},
	{"#004P1220T0010!"},
	{"#005P1900T0010!"},

};

uint8_t Left_Place_2[17][15] = //机械手左放2:
{
	{"#001P2150T0010!"},
	{"#002P1460T0300!"},
	{"#003P0900T0300!"},
	{"#004P0900T0300!"},
	{"#005P1900T0010!"},
};

uint8_t Left_Place_3[8][15] = //机械手左放3:
{
	{"#001P2150T0010!"},
	{"#002P1460T0010!"},
	{"#003P0900T0010!"},
	{"#004P0900T0010!"},
	{"#005P1050T0050!"},
};

uint8_t Right_Place_1[19][15] = //机械手右放1:
{
	{"#001P0800T0600!"},
	{"#002P1050T0010!"},
	{"#003P0700T0010!"},
	{"#004P1220T0010!"},
	{"#005P1900T0010!"},
};

uint8_t Right_Place_2[10][15] = //机械手右放2:
{
	{"#001P0800T0010!"},
	{"#002P1460T0300!"},
	{"#003P0900T0300!"},
	{"#004P0900T0300!"},
	{"#005P1900T0010!"},
};

uint8_t Right_Place_3[5][15] = //机械手右放3:
{
	{"#001P0800T0010!"},
	{"#002P1460T0010!"},
	{"#003P0900T0010!"},
	{"#004P0900T0010!"},
	{"#005P1050T0100!"},
};


/**
	* @brief  解析动作组，类似处理 “#001P1500T1000!”的字符串。
						解析分为三步，第一步解析舵机标号（如001），第二步
						解析舵机的脉冲宽度目标值（如1500），第三步解析舵机
						执行时间（如1000）
	* @retval 无
	*/
void Analyze_Action_Group( uint8_t (*Action_Group)[15])
{
	uint8_t Servo_Num;
	uint16_t PWM, Time, i = 0, j = 0;
		
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
					Servo[Servo_Num].Increment_PWM = (Servo[Servo_Num].Aim_PWM - Servo[Servo_Num].Current_PWM)
					/ (Servo[Servo_Num].Time / 20.000);			
				}
			}
			
			else 
			{
				j++;
			}
		}
		
		i++;
		if(i%5 == 0)
		{
			SysTick_Delay_ms(400);
		}
		j = 0;
	}
}
