#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_ili9341_lcd.h"
#include "lcd_display_english.h"
#include "lcd_display_chinese.h"
#include "modbus_agreement.h"
#include "bsp_systick.h"
#include "string.h"

//extern uint8_t Chinese_Character_1[9][32];
//extern uint8_t Chinese_Character_2[7][32];
//extern uint8_t Chinese_Character_3[8][32];
//extern uint8_t Chinese_Character_4[12][32];
//extern uint8_t Chinese_Character_5[11][32];
//extern uint8_t Chinese_Character_6[15][32];
//extern uint8_t Chinese_Character_7[8][32];
//extern uint8_t Chinese_Character_8[12][32];
//extern uint8_t Chinese_Character_9[8][32];
//extern uint8_t Chinese_Character_10[12][32];
//extern uint8_t Chinese_Character_11[7][32];
//extern uint8_t Chinese_Character_12[15][32];
//extern uint8_t Chinese_Character_13[7][32];
//extern uint8_t Chinese_Character_14[15][32];

//void Delay(__IO uint32_t nCount);// 延时函数声明

int main(void)
{ 	
	
	USART1_Config();//初始化USART1

	Pack_Data(OPENMV_ADD, OPENMV_CHACK, NONE, USART1_DEVICE);
	USART1_Printf(USART1_RX_Pack);
//	SysTick_Delay_us(5000000);
	while(strcmp(String,USART1_RX_Pack) != NULL);
	USART1_Printf("接收成功");
	
	Data_Clean(String);//清除String字符串中的数据，保证下一次执行时数据不出错
	Data_Clean(Check_Code);//清Check_Code字符串中的数据，保证下一次执行时数据不出错
	Data_Clean(USART1_RX_Pack);//USART1_RX_Pack字符串中的数据，保证下一次执行时数据不出错
	USART1_RX_Count = 0;//计数值清0
	
	while(1);
	
//	ILI9341_Init();//可以根据实际情况做参数的修改!!!

//	printf("\r\n读取到的ID =%x",ILI9341_Read_ID());
//	
//	Display_Motto6666(1 ,1, YELLOW);//显示“Motto6666”英文字符串
//	Display_Chinese_String( Chinese_Character_1  ,9  ,3 ,1 ,BLUE2);//显示“物料分拣流水线系统”中文字符串
//	Display_Chinese_String( Chinese_Character_2  ,7  ,5 ,1 ,MAGENTA);//显示“系统运行情况：”
//	Display_Chinese_String( Chinese_Character_3  ,8  ,7 ,1 ,GREEN);//显示“视觉模块响应正常”
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//清除第七行里面的字符
//	Display_Chinese_String( Chinese_Character_4  ,12 ,7 ,1 ,RED);//显示“与视觉模块第一次通信超时”
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_5  ,11 ,7 ,1 ,GREEN);//显示“机械手控制模块响应正常”
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_6  ,15 ,7 ,1 ,RED);//显示“与机械手控制模块第一次通信超时”
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_7  ,8  ,7 ,1 ,GREEN);//显示“视觉模块识别开始”
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_8  ,12 ,7 ,1 ,RED);//显示“与视觉模块第二次通信超时”
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_9  ,8  ,7 ,1 ,GREEN);//显示“视觉模块识别结束”
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_10 ,12 ,7 ,1 ,RED);//显示“与视觉模块第三次通信超时”
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_11 ,7  ,7 ,1 ,GREEN);//显示“机械手执行操作”字模数据
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_12 ,15 ,7 ,1 ,RED);//显示“与机械手控制模块第二次通信超时”
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_13 ,7  ,7 ,1 ,GREEN);//显示“机械手执行完毕”字模数据
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//清除第七行里面的字符
//	
//	Display_Chinese_String( Chinese_Character_14 ,15 ,7 ,1 ,RED);//显示“与机械手控制模块第三次通信超时”
//	
//  
//	/* 画矩形 */	
//	while(1)//当STM32主控板与模块间通信超时时，使用该函数
//	{
//		ILI9341_Draw_Rect(220,300,20, 20,RED);
//		Delay(0xFFFF0);//调试使用，调试完毕删除
//    ILI9341_Draw_Rect(220,300,20,20,BLACK);
//		Delay(0xFFFF0);//调试使用，调试完毕删除
//	} 

}


///*软件延时*/
//void Delay(__IO uint32_t nCount)
//{
//  for(; nCount != 0; nCount--);
//}



/*********************************************END OF FILE**********************/
