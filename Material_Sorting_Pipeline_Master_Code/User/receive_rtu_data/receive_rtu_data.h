#ifndef __RECEIVE_RTU_DATA_H
#define __RECEIVE_RTU_DATA_H

#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_usart2.h"
#include "bsp_tim6.h"
#include "bsp_tim7.h"
#include "modbus_agreement.h"
#include "bsp_ili9341_lcd.h"
#include "lcd_display_english.h"
#include "lcd_display_chinese.h"

void USART1_Rtu_Data_Receive(uint8_t Address, uint8_t Funtion);
void USART1_Receive_Recognize_Data(void);
#endif /*__RECEIVE_RTU_DATA_H*/
