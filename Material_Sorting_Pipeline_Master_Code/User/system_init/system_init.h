#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H

#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_usart2.h"
#include "bsp_ili9341_lcd.h"
#include "lcd_display_english.h"
#include "lcd_display_chinese.h"
#include "bsp_tim6.h"
#include "bsp_motor_control.h"
#include "photoelectric_sensor.h"

void System_Init(void);

#endif /*__SYSTEM_INIT_H*/

