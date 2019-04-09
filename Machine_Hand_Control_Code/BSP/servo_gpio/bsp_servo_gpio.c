#include "bsp_servo_gpio.h"

void Servo_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;		
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //使能禁止JTAG，此时PA15、PB3、PB4可作为普通I/O使用
	
	GPIO_InitStructure.GPIO_Pin =  SERVO_2_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SERVO_PORT_1, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  SERVO_1_PIN|SERVO_3_PIN|SERVO_4_PIN|SERVO_5_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(SERVO_PORT_2, &GPIO_InitStructure);
	
}

