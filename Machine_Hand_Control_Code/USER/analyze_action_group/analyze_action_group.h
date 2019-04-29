#ifndef __ANALYZE_ACTION_GROUP_H
#define __ANALYZE_ACTION_GROUP_H

#include "stm32f10x.h"
#include "servo_control.h"

extern uint8_t Curl_Up[7][15];
extern uint8_t Grab_Material_1[9][15];
extern uint8_t Grab_Material_2[11][15];
extern uint8_t Grab_Material_3[12][15];
extern uint8_t Left_Place_1[15][15];
extern uint8_t Left_Place_2[17][15];
extern uint8_t Left_Place_3[8][15];
extern uint8_t Right_Place_1[19][15];
extern uint8_t Right_Place_2[10][15];
extern uint8_t Right_Place_3[5][15]; 


void Analyze_Action_Group(uint8_t (*Action_Group)[15]);

#endif /*__ANALYZE_ACTION_GROUP_H*/
