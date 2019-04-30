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
	
	Display_Motto6666(1 ,1, YELLOW);//显示“Motto6666”英文字符串
	Display_Chinese_String( Chinese_Character_1  ,9  ,3 ,1 ,BLUE2);//显示“物料分拣流水线系统”中文字符串
	Display_Chinese_String( Chinese_Character_2  ,7  ,5 ,1 ,MAGENTA);//显示“系统运行情况：”
}
