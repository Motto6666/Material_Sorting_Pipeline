#include "servo_control.h"

Servo_Struct  Servo[SERVO_NUM];

/**
	* @brief  ���������ֵ��ʼ�� 
	* @retval ��
	*/
void Servo_Pulse_Width_Init(void)
{
	uint8_t i;
	for(i=1;i<=SERVO_NUM;i++)
	{
		Servo[i].Current_PWM = 1500;
		Servo[i].Increment_PWM = 0;
  }
}


/**
	* @brief  ���I/O���ŵ�ƽ���� 
	* @retval ��
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
		default:break;
	}
}



/**
	* @brief  ������ŵ�ƽ���� 
	* @retval ��
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
	* @brief  ��������ȿ��ƣ����ö�ʱ�����ƶ�����Ÿߵ͵�ƽ��ʱ�䣬
						�ö�����Ų������������ȵķ������ﵽ���ƶ��ת����Ŀ��
	* @retval ��
	*/
extern volatile uint8_t Flag;
volatile uint8_t Servo_Num = 1;
void Servo_Pulse_Width_Control(void)
{
	if(Servo_Num == 6) 
		{
			Servo_Num = 1;
		}
		
		if(!Flag) 
		{
			Servo_Pulse_Width_Increment_Apply(Servo_Num);
			TIM2_INTERRUPT_TIME = ( (uint32_t)Servo[Servo_Num].Current_PWM );//�趨TIM2��ʱ�ж�ʱ�䣬��λΪus
			Servo_IO_Set(Servo_Num, HIGH);//����TIM2_INTERRUPT_TIME�ߵ�ƽʱ��
		}
		else 
	  {
			TIM2_INTERRUPT_TIME = 2500 - ((uint32_t)Servo[Servo_Num].Current_PWM);//�趨TIM2��ʱ�ж�ʱ�䣬��λΪus
			Servo_IO_Set(Servo_Num, LOW);//����TIM2_INTERRUPT_TIME�͵�ƽʱ��
			Servo_Num ++;
		}
}


/**
	* @brief  �������������ֵ�����ã��ö���ڵ�λʱ����ת��һ����
						�Ƕȣ��ﵽ���ƶ��ת���ٶȵ�Ŀ�� 
	* @retval ��
	*/
void Servo_Pulse_Width_Increment_Apply(uint8_t Servo_Num) 
{	
	if(Servo[Servo_Num].Increment_PWM != 0) 
	{
		if(Abs_Float( Servo[Servo_Num].Aim_PWM - Servo[Servo_Num].Current_PWM) <= Abs_Float( 2*Servo[Servo_Num].Increment_PWM ))          
		{
			Servo[Servo_Num].Current_PWM   =  Servo[Servo_Num].Aim_PWM;
			Servo[Servo_Num].Increment_PWM =  0;
		} 
		else 
		{
			Servo[Servo_Num].Current_PWM += Servo[Servo_Num].Increment_PWM;
		}
	}
}


/**
	* @brief  ȡ����ֵ
	* @retval ��
	*/
float Abs_Float(float Value) 
{
	if(Value>0) 
	{
		return Value;
	}
	return (-Value);
}

