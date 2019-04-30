#ifndef __LCD_DISPLAY_CHINESE_H
#define __LCD_DISPLAY_CHINESE_H

#include "stm32f10x.h"
#include "bsp_ili9341_lcd.h"

void Display_Chinese(uint8_t * Character ,uint8_t Row_Num ,uint8_t Column_Num ,uint16_t Color);
void Clean_Screen(uint8_t Row_Num);
void Display_Chinese_String( uint8_t (*Chinese_String)[32] ,uint8_t Word_Num ,uint8_t Row_Num ,uint8_t Column_Num ,uint16_t Color);


#endif /*__LCD_DISPLAY_CHINESE_H*/

