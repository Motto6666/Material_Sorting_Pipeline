#include "servo_control.h"

Servo  Servo_Action[SERVO_NUM];

void Servo_Init(void)
{
	uint8_t i;
	for(i=1;i<=SERVO_NUM;i++)
	{
		Servo_Action[i].Current_Pulse_Width = 1500;
		Servo_Action[i].Pulse_Width_Increment = 0;
  }
}


void Servo_IO_Set(uint8_t Index, uint8_t Level) 
{
	switch(Index) 
	{
		case 1:Servo_Pin_Set(SERVO_PORT_2, SERVO_1_PIN, Level);break;
		case 2:Servo_Pin_Set(SERVO_PORT_1, SERVO_2_PIN, Level);break;
		case 3:Servo_Pin_Set(SERVO_PORT_2, SERVO_3_PIN, Level);break;
		case 4:Servo_Pin_Set(SERVO_PORT_2, SERVO_4_PIN, Level);break;
		case 5:Servo_Pin_Set(SERVO_PORT_2, SERVO_5_PIN, Level);break;
		case 6:Servo_Pin_Set(SERVO_PORT_1, SERVO_6_PIN, Level);break;
		default:break;
	}
}


void Servo_Pin_Set(GPIO_TypeDef* GPIOx, uint16_t Pin, uint8_t Level) 
{
	if(Level) 
	{
		GPIO_SetBits(GPIOx,Pin);
	} 
	else 
	{
		GPIO_ResetBits(GPIOx,Pin);
	}
}

