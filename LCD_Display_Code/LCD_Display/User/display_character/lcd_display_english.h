#ifndef __LCD_DISPLAY_ENGLISH_H
#define __LCD_DISPLAY_ENGLISH_H

#include "stm32f10x.h"
#include "bsp_ili9341_lcd.h"

void Display_English(uint8_t * Character ,uint8_t Row_Num ,uint8_t Column_Num ,uint16_t Color);
void Display_Motto6666(uint8_t Row_Num ,uint8_t Column_Num ,uint16_t Color);

#endif /*__LCD_DISPLAY_ENGLISH_H*/
