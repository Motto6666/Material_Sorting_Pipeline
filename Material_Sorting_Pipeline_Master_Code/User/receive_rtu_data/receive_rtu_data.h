#ifndef __receive_rtu_data_H
#define __receive_rtu_data_H

#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_usart2.h"
#include "bsp_tim6.h"
#include "bsp_tim7.h"
#include "modbus_agreement.h"

void USART1_Rtu_Data_Receive(uint8_t Address, uint8_t Funtion);
void USART1_Receive_Recognize_Data(void);
#endif /*__receive_rtu_data_H*/
