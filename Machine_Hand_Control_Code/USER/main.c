#include "stm32f10x.h"
#include "bsp_servo_gpio.h"
#include "servo_control.h"
#include "bsp_systick.h"
#include "bsp_usart1.h"
#include "bsp_tim2.h"
#include "analyze_action_group.h"
#include "execute_action_group.h"

int main(void) 
{	
	
	Servo_GPIO_Init();
	Servo_Pulse_Width_Init();
	USART1_Config();
	TIM2_Config_Init();
	
	SysTick_Delay_us(2000000);//����ʹ�ã��������ɾ��
	

	Curl_Up_Action();//��е��ִ����������
		
	Grab_Material_Action();//��е��ִ��ץȡ���϶���
	
	Left_Place_Action();//��е�������������
		
	Curl_Up_Action();//��е��ִ����������
		
	Grab_Material_Action();//��е��ִ��ץȡ���϶���

	Right_Place_Action();//��е�����ҷ�������
		
	Curl_Up_Action();//��е��ִ����������
	
	while(1);

}



