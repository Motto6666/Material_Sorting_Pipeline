#ifndef __MODBUS_AGREEMENT_H
#define __MODBUS_AGREEMENT_H

#include "stm32f10x.h"
#include <stdio.h>
#include "bsp_usart1.h"

#define OPENMV_ADD       	'1'
#define OPENMV_CHACK     	'A'
#define OPENMV_RECOGNIZE 	'B'    

#define IRON_HAND_ADD		 	'2'
#define IRON_HAND_CHACK  	'C'
#define IRON_HAND_EXECUTE 'D'

#define DATA_RED         	'R' 
#define DATA_GREEN       	'G'
#define NONE             	'N'

#define STRING_LEN         3

#define USART1_DEVICE      1
#define USART2_DEVICE      2


extern char String[];
extern char Check_Code[2];

void Pack_Data(char Address, char Funtion, char Data, uint8_t Send_Device);
void CRC_16(char *Str,uint8_t len);
void Data_Clean(char *Str);

#endif /*__MODBUS_AGREEMENT_H*/
