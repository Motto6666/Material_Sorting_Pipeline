#ifndef __RECEIVE_RTU_DATA_H
#define __RECEIVE_RTU_DATA_H

#define TURE 1

#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_usart2.h"
#include "bsp_tim6.h"
#include "modbus_agreement.h"
#include "bsp_ili9341_lcd.h"
#include "lcd_display_english.h"
#include "lcd_display_chinese.h"

void Receive_Openmv_Data(uint8_t Address, uint8_t Funtion);
void Receive_Iron_Hand_Data(uint8_t Address, uint8_t Funtion);
void Receive_Openmv_Recognize_Data(void);
void USART_Buffer_Clean(uint8_t *Buffer);
void LCD_Display_State(uint8_t Address, uint8_t Funtion);
#endif /*__RECEIVE_RTU_DATA_H*/
