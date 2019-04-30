#include "system_init.h"

void System_Init(void)
{
	USART1_Config();
	USART2_Config();
	BASIC_TIM6_Init();
	LCD_Init();
	Motor_Init();
	Photoelectric_Sensor_Init();
	Key_Init();
	Buzzer_Init();
	
	Display_Motto6666(1 ,1, YELLOW);//��ʾ��Motto6666��Ӣ���ַ���
	Display_Chinese_String( Chinese_Character_1  ,9  ,3 ,1 ,BLUE2);//��ʾ�����Ϸּ���ˮ��ϵͳ�������ַ���
	Display_Chinese_String( Chinese_Character_2  ,7  ,5 ,1 ,MAGENTA);//��ʾ��ϵͳ�����������
}
