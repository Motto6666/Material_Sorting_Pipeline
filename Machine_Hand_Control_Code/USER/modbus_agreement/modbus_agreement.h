#ifndef __MODBUS_AGREEMENT_H
#define __MODBUS_AGREEMENT_H

#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "bsp_usart2.h"
#include "string.h"
  
#define IRON_HAND_ADD		 				0x32
#define IRON_HAND_CHACK  				0x43
#define IRON_HAND_EXECUTE 			0x44
#define IRON_HAND_EXECUTE_END 	0x45
#define IRON_HAND_EXECUTE_STOP	0x22

#define DATA_RED         				0x52 
#define DATA_GREEN       				0x47
#define DATA_LEN	         			0x01
#define DATA_NONE         			0x4E

#define OK											0x04

#define CHECK_SUCCESS 		 			1
#define CHECK_FAILED			 			0	


extern uint8_t Strings[50];
extern uint8_t Check_Code[2];

void RTU_Pack_Data(uint8_t Address, uint8_t Funtion, uint8_t Data_Len, uint8_t *Data );
void CRC_16(uint8_t *Str,uint8_t Len);
void Data_Clean(uint8_t *Str);
uint8_t RTU_Data_Analysis(uint8_t * RTU_Data);

#endif /*__MODBUS_AGREEMENT_H*/
