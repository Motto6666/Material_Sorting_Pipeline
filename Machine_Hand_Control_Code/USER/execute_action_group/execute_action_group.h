#ifndef __EXECUTE_ACTION_GROUP_H
#define __EXECUTE_ACTION_GROUP_H

#include "stm32f10x.h"
#include "analyze_action_group.h"

extern uint8_t Curl_Up[7][15];
extern uint8_t Grab_Material_1[9][15];
extern uint8_t Grab_Material_2[11][15];
extern uint8_t Grab_Material_3[12][15];
extern uint8_t Left_Place_1[15][15];
extern uint8_t Left_Place_2[17][15];
extern uint8_t Right_Place_1[19][15];
extern uint8_t Right_Place_2[10][15];

void Curl_Up_Action(void);
void Grab_Material_Action(void);
void Left_Place_Action(void);
void Right_Place_Action(void);


#endif /*__EXECUTE_ACTION_GROUP_H*/
