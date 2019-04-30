#ifndef __LCD_DISPLAY_CHINESE_H
#define __LCD_DISPLAY_CHINESE_H

#include "stm32f10x.h"
#include "bsp_ili9341_lcd.h"
#include "bsp_systick.h"
#include "bsp_buzzer.h"

extern uint8_t Chinese_Character_1[9][32];
extern uint8_t Chinese_Character_2[7][32];
extern uint8_t Chinese_Character_3[8][32];
extern uint8_t Chinese_Character_4[12][32];
extern uint8_t Chinese_Character_5[11][32];
extern uint8_t Chinese_Character_6[15][32];
extern uint8_t Chinese_Character_7[8][32];
extern uint8_t Chinese_Character_8[12][32];
extern uint8_t Chinese_Character_9[8][32];
extern uint8_t Chinese_Character_10[12][32];
extern uint8_t Chinese_Character_11[7][32];
extern uint8_t Chinese_Character_12[15][32];
extern uint8_t Chinese_Character_13[7][32];
extern uint8_t Chinese_Character_14[15][32];
extern uint8_t Chinese_Character_15[5][32];
extern uint8_t Chinese_Character_16[6][32];
extern uint8_t Chinese_Character_17[13][32];
extern uint8_t Chinese_Character_18[7][32];

void Display_Chinese(uint8_t * Character ,uint8_t Row_Num ,uint8_t Column_Num ,uint16_t Color);
void Clean_Screen(uint8_t Row_Num);
void Display_Chinese_String( uint8_t (*Chinese_String)[32] ,uint8_t Word_Num ,uint8_t Row_Num ,uint8_t Column_Num ,uint16_t Color);
void Display_Rectangle(void);

#endif /*__LCD_DISPLAY_CHINESE_H*/

