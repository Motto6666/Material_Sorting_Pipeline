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

//void Delay(__IO uint32_t nCount);// ��ʱ��������

int main(void)
{ 	
	
	USART1_Config();//��ʼ��USART1

	Pack_Data(OPENMV_ADD, OPENMV_CHACK, NONE, USART1_DEVICE);
	USART1_Printf(USART1_RX_Pack);
//	SysTick_Delay_us(5000000);
	while(strcmp(String,USART1_RX_Pack) != NULL);
	USART1_Printf("���ճɹ�");
	
	Data_Clean(String);//���String�ַ����е����ݣ���֤��һ��ִ��ʱ���ݲ�����
	Data_Clean(Check_Code);//��Check_Code�ַ����е����ݣ���֤��һ��ִ��ʱ���ݲ�����
	Data_Clean(USART1_RX_Pack);//USART1_RX_Pack�ַ����е����ݣ���֤��һ��ִ��ʱ���ݲ�����
	USART1_RX_Count = 0;//����ֵ��0
	
	while(1);
	
//	ILI9341_Init();//���Ը���ʵ��������������޸�!!!

//	printf("\r\n��ȡ����ID =%x",ILI9341_Read_ID());
//	
//	Display_Motto6666(1 ,1, YELLOW);//��ʾ��Motto6666��Ӣ���ַ���
//	Display_Chinese_String( Chinese_Character_1  ,9  ,3 ,1 ,BLUE2);//��ʾ�����Ϸּ���ˮ��ϵͳ�������ַ���
//	Display_Chinese_String( Chinese_Character_2  ,7  ,5 ,1 ,MAGENTA);//��ʾ��ϵͳ�����������
//	Display_Chinese_String( Chinese_Character_3  ,8  ,7 ,1 ,GREEN);//��ʾ���Ӿ�ģ����Ӧ������
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//���������������ַ�
//	Display_Chinese_String( Chinese_Character_4  ,12 ,7 ,1 ,RED);//��ʾ�����Ӿ�ģ���һ��ͨ�ų�ʱ��
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_5  ,11 ,7 ,1 ,GREEN);//��ʾ����е�ֿ���ģ����Ӧ������
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_6  ,15 ,7 ,1 ,RED);//��ʾ�����е�ֿ���ģ���һ��ͨ�ų�ʱ��
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_7  ,8  ,7 ,1 ,GREEN);//��ʾ���Ӿ�ģ��ʶ��ʼ��
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_8  ,12 ,7 ,1 ,RED);//��ʾ�����Ӿ�ģ��ڶ���ͨ�ų�ʱ��
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_9  ,8  ,7 ,1 ,GREEN);//��ʾ���Ӿ�ģ��ʶ�������
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_10 ,12 ,7 ,1 ,RED);//��ʾ�����Ӿ�ģ�������ͨ�ų�ʱ��
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_11 ,7  ,7 ,1 ,GREEN);//��ʾ����е��ִ�в�������ģ����
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_12 ,15 ,7 ,1 ,RED);//��ʾ�����е�ֿ���ģ��ڶ���ͨ�ų�ʱ��
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_13 ,7  ,7 ,1 ,GREEN);//��ʾ����е��ִ����ϡ���ģ����
//	Delay(0xFFFFF0);
//	Clean_Screen(7);//���������������ַ�
//	
//	Display_Chinese_String( Chinese_Character_14 ,15 ,7 ,1 ,RED);//��ʾ�����е�ֿ���ģ�������ͨ�ų�ʱ��
//	
//  
//	/* ������ */	
//	while(1)//��STM32���ذ���ģ���ͨ�ų�ʱʱ��ʹ�øú���
//	{
//		ILI9341_Draw_Rect(220,300,20, 20,RED);
//		Delay(0xFFFF0);//����ʹ�ã��������ɾ��
//    ILI9341_Draw_Rect(220,300,20,20,BLACK);
//		Delay(0xFFFF0);//����ʹ�ã��������ɾ��
//	} 

}


///*�����ʱ*/
//void Delay(__IO uint32_t nCount)
//{
//  for(; nCount != 0; nCount--);
//}



/*********************************************END OF FILE**********************/
