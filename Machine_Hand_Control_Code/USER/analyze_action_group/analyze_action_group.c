#include "analyze_action_group.h"
#include "bsp_systick.h"
#include "bsp_usart1.h"//����ʹ�ã��������ɾ��

extern Servo_Struct  Servo[SERVO_NUM];

uint8_t Curl_Up[7][15] =  //��е������������
{
	{"#001P1500T1500!"},
	{"#002P1050T1500!"},
	{"#003P0700T1500!"},
	{"#004P0850T1500!"},
	{"#005P1100T1500!"},
};

uint8_t Grab_Material_1[9][15] = //��е��ץȡ����1
{
	{"#001P1500T1500!"},
	{"#002P1580T1500!"},
	{"#003P0980T1500!"},
	{"#004P0900T0800!"},
	{"#005P1100T1500!"},

};

uint8_t  Grab_Material_2[11][15] = //��е��ץȡ����2
{
	{"#001P1500T1500!"},
	{"#002P1580T1500!"},
	{"#003P0980T1500!"},
	{"#004P0900T0800!"},
	{"#005P1600T0500!"},
};

uint8_t Grab_Material_3[12][15] = //��е��ץȡ����3
{
	{"#001P1500T1200!"},
	{"#002P1050T1200!"},
	{"#003P0700T1200!"},
	{"#004P1220T1200!"},
	{"#005P1600T1200!"},
};


uint8_t Left_Place_1[15][15] = //��е�����1:
{
	{"#001P2150T1000!"},
	{"#002P1460T1500!"},
	{"#003P0900T1500!"},
	{"#004P0900T1500!"},
	{"#005P1600T1500!"},

};

uint8_t Left_Place_2[17][15] = //��е�����2:
{
	{"#001P2150T1500!"},
	{"#002P1460T1500!"},
	{"#003P0900T1500!"},
	{"#004P0900T1500!"},
	{"#005P1050T0100!"},
};

uint8_t Right_Place_1[19][15] = //��е���ҷ�1:
{
	{"#001P0800T1000!"},
	{"#002P1460T1500!"},
	{"#003P0900T1500!"},
	{"#004P0900T1500!"},
	{"#005P1600T1500!"},
};

uint8_t Right_Place_2[10][15] = //��е���ҷ�2:
{
	{"#001P0800T1000!"},
	{"#002P1460T1500!"},
	{"#003P0900T1500!"},
	{"#004P0900T1500!"},
	{"#005P1050T0100!"},
};

/**
	* @brief  ���������飬���ƴ��� ��#001P1500T1000!�����ַ���
	* @retval ��
	*/
void Analyze_Action_Group( uint8_t (*Action_Group)[15])
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
					Servo_Num = Servo_Num*10 + Action_Group[i][j]-'0';//���������
					j++;
				}
			} 
			else if(Action_Group[i][j] == 'P') 
			{
				PWM = 0;
				j++;
				while(Action_Group[i][j] && Action_Group[i][j] != 'T') 
				{
					PWM = PWM*10 + Action_Group[i][j]-'0';//����PWMֵ
					j++;
				}
			} 
			else if(Action_Group[i][j] == 'T') 
			{
				Time = 0;
				j++;
				while(Action_Group[i][j] && Action_Group[i][j] != '!') 
				{
					Time = Time*10 + Action_Group[i][j]-'0';//������ת��ʱ��
					j++;
				}
				
				if(Servo_Num <= SERVO_NUM && (PWM<=2500) && (PWM>=500) && (Time<=10000)) 
				{
					if(Time < 20)
					{
						Time = 20;//���ִ��ʱ�䲻������20ms
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
		if(i%5 == 0)
		{
			SysTick_Delay_ms(1000);
		}
		j = 0;
	}
}
