#ifndef __SYSTEM_INIT_H
#define __SYSTEM_INIT_H

#include "stm32f10x.h"
#include "bsp_servo_gpio.h"
#include "servo_control.h"
#include "bsp_systick.h"
#include "bsp_usart1.h"
#include "bsp_usart2.h"
#include "bsp_tim2.h"
#include "analyze_action_group.h"
#include "execute_action_group.h"
#include "modbus_agreement.h"

void System_Init(void);

#endif /*__SYSTEM_INIT_H*/
