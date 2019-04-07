#include "servo_control.h"

Servo  Servo_Action[SERVO_NUM];

/**
	* @brief  舵机脉冲宽度值初始化 
	* @retval 无
	*/
void Servo_Pulse_Width_Init(void)
{
	uint8_t i;
	for(i=1;i<=SERVO_NUM;i++)
	{
		Servo_Action[i].Current_Pulse_Width = 2400;
		Servo_Action[i].Pulse_Width_Increment = 0;
  }
}


/**
	* @brief  舵机I/O引脚电平控制 
	* @retval 无
	*/
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



/**
	* @brief  舵机I/O引脚电平控制 
	* @retval 无
	*/
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


/**
	* @brief  舵机脉冲宽度控制 
	* @retval 无
	*/
extern volatile uint8_t Flag;
volatile uint8_t Servo_Num = 1;
void Servo_Pulse_Width_Control(void)
{
	if(Servo_Num == 7) 
		{
			Servo_Num = 1;
		}
		
		if(!Flag) 
		{
			Servo_Pulse_Width_Increment_Control(Servo_Num);
			TIM2_INTERRUPT_TIME = ( (uint32_t)Servo_Action[Servo_Num].Current_Pulse_Width );//设定TIM2定时中断时间，单位为us
			Servo_IO_Set(Servo_Num, HIGH);		 
		}
		else 
	  {
			TIM2_INTERRUPT_TIME = 2500 - ((uint32_t)Servo_Action[Servo_Num].Current_Pulse_Width);//设定TIM2定时中断时间，单位为us
			Servo_IO_Set(Servo_Num, LOW);
			Servo_Num ++;
		}
}


/**
	* @brief  舵机脉冲宽度增量值控制，达到控制舵机转动速度的目的 
	* @retval 无
	*/
void Servo_Pulse_Width_Increment_Control(uint8_t Servo_Num) 
{	
	if(Servo_Action[Servo_Num].Pulse_Width_Increment != 0) 
	{
		if(Abs_Float( Servo_Action[Servo_Num].Pulse_Width_Aim - Servo_Action[Servo_Num].Current_Pulse_Width) <= Abs_Float( 2*Servo_Action[Servo_Num].Pulse_Width_Increment ))          
		{
			Servo_Action[Servo_Num].Current_Pulse_Width   =  Servo_Action[Servo_Num].Pulse_Width_Aim;
			Servo_Action[Servo_Num].Pulse_Width_Increment =  0;
		} 
		else 
		{
			Servo_Action[Servo_Num].Current_Pulse_Width += Servo_Action[Servo_Num].Pulse_Width_Increment;
		}
	}
}


/**
	* @brief  取绝对值
	* @retval 无
	*/
float Abs_Float(float Value) 
{
	if(Value>0) 
	{
		return Value;
	}
	return (-Value);
}

