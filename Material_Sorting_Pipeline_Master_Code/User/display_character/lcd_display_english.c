#include "lcd_display_english.h"

uint8_t Character_Motto6666[9][48] = 
{
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x1E,0x30,0x1C,0x38,0x1C,
 0x38,0x2C,0x28,0x2C,0x2C,0x2C,0x2C,0x4C,0x2C,0x4C,0x24,0x4C,0x26,0x8C,0x26,0x8C,
 0x22,0x8C,0x23,0x0C,0x23,0x0C,0x23,0x0C,0xF1,0x3F,0x00,0x00,0x00,0x00,0x00,0x00},//字符"M"字模
	
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x07,0xE0,0x18,0x18,0x10,0x0C,0x30,0x0C,0x30,0x0C,0x30,0x0C,
 0x30,0x0C,0x30,0x0C,0x10,0x08,0x08,0x10,0x07,0xE0,0x00,0x00,0x00,0x00,0x00,0x00},//字符"o"字模

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x00,
 0x03,0x00,0x07,0x00,0x3F,0xF8,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,
 0x03,0x00,0x03,0x00,0x03,0x04,0x03,0x18,0x00,0xE0,0x00,0x00,0x00,0x00,0x00,0x00},//字符"t"字模

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x00,
 0x03,0x00,0x07,0x00,0x3F,0xF8,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,
 0x03,0x00,0x03,0x00,0x03,0x04,0x03,0x18,0x00,0xE0,0x00,0x00,0x00,0x00,0x00,0x00},//字符"t"字模

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x00,0x00,0x07,0xE0,0x18,0x18,0x10,0x0C,0x30,0x0C,0x30,0x0C,0x30,0x0C,
 0x30,0x0C,0x30,0x0C,0x10,0x08,0x08,0x10,0x07,0xE0,0x00,0x00,0x00,0x00,0x00,0x00},//字符"o"字模

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xE0,0x06,0x18,0x08,0x18,0x18,0x18,
 0x30,0x00,0x30,0x00,0x30,0xC0,0x37,0x38,0x38,0x1C,0x30,0x0C,0x30,0x0C,0x30,0x0C,
 0x30,0x0C,0x30,0x0C,0x18,0x08,0x0C,0x10,0x03,0xE0,0x00,0x00,0x00,0x00,0x00,0x00},//字符"6"	字模

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xE0,0x06,0x18,0x08,0x18,0x18,0x18,
 0x30,0x00,0x30,0x00,0x30,0xC0,0x37,0x38,0x38,0x1C,0x30,0x0C,0x30,0x0C,0x30,0x0C,
 0x30,0x0C,0x30,0x0C,0x18,0x08,0x0C,0x10,0x03,0xE0,0x00,0x00,0x00,0x00,0x00,0x00},//字符"6"	字模

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xE0,0x06,0x18,0x08,0x18,0x18,0x18,
 0x30,0x00,0x30,0x00,0x30,0xC0,0x37,0x38,0x38,0x1C,0x30,0x0C,0x30,0x0C,0x30,0x0C,
 0x30,0x0C,0x30,0x0C,0x18,0x08,0x0C,0x10,0x03,0xE0,0x00,0x00,0x00,0x00,0x00,0x00},//字符"6"	字模

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xE0,0x06,0x18,0x08,0x18,0x18,0x18,
 0x30,0x00,0x30,0x00,0x30,0xC0,0x37,0x38,0x38,0x1C,0x30,0x0C,0x30,0x0C,0x30,0x0C,
 0x30,0x0C,0x30,0x0C,0x18,0x08,0x0C,0x10,0x03,0xE0,0x00,0x00,0x00,0x00,0x00,0x00}//字符"6"	字模
};


 

/**
	* @brief  显示单个英文字符，单个字符宽16个像素点。高24个像素点
	* @param	Character，要输入字模数据的指针
	* @param  Row_Num，字符的行数坐标，每行间隔24个像素点
	* @param  Column_Num，字符的列数坐标，每列间隔16个像素点
  * @param  Color，字符的颜色
	* @retval 无
	*/
void Display_English(uint8_t * Character ,uint8_t Row_Num ,uint8_t Column_Num ,uint16_t Color)
{
	uint16_t i,j;
	uint8_t ch;//存放字模中的十六进制数据
	
	for(i=0;i<24;i++)
	{
		for(j=0;j<8;j++)
		{
			ch = (Character[i*2]<<j);
			
			if ((ch & 0x80) == 0)
			{
				ILI9341_Draw_Point(i+1+((Row_Num-1)*24),j+1+((Column_Num-1)*16),BLACK);//显示一个黑色像素点
			}
			else
			{
				ILI9341_Draw_Point(i+1+((Row_Num-1)*24),j+1+((Column_Num-1)*16),Color);//显示一个对应颜色的像素点
			}
			
		}
		
		for(j=0;j<8;j++)
		{
			ch = (Character[i*2+1]<<j);
			
			if ((ch & 0x80) == 0)
			{
				ILI9341_Draw_Point(i+1+((Row_Num-1)*24),j+1+8+((Column_Num-1)*16),BLACK);//显示一个黑色像素点
			}
			else
			{
				ILI9341_Draw_Point(i+1+((Row_Num-1)*24),j+1+8+((Column_Num-1)*16),Color);//显示一个对应颜色的像素点
			}			
		}
		
	}	
}


/*显示Motto6666英文字符*/
/**
	* @brief  显示“Motto6666”英文字符串
	* @param  Row_Num，字符串的行数坐标
	* @param  Column_Num，字符串的列数坐标
  * @param  Color，字符串的颜色
	* @retval 无
	*/
void Display_Motto6666(uint8_t Row_Num ,uint8_t Column_Num ,uint16_t Color)
{
	uint8_t i;
	for(i=0;i<9;i++)
	{
		Display_English(Character_Motto6666[i], Row_Num, i+Column_Num,Color); 
	}
}

