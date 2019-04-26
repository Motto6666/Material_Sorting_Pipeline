#include "photoelectric_sensor.h"

/**
  * @brief  配置NVIC
  * @retval 无
  */
static void Sensor_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	/*第一步：配置中断优先级的分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/*第二步：配置NVIC初始化结构体*/
	NVIC_InitStruct.NVIC_IRQChannel = SENSOR_EXTI_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 5;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	
	/*第三步：调用NVIC初始化函数把配置好的结构体写到寄存器里*/
	NVIC_Init(&NVIC_InitStruct);
}


/**
  * @brief  初始化要连接到EXTI的Sensor_GPIO
  * @retval 无
  */
void Sensor_EXTI_Config(void)
{ 
	GPIO_InitTypeDef GPIO_InitStruct;
  EXTI_InitTypeDef EXTI_InitStruct;	
	
	/*初始化Sensor端口时钟*/
	RCC_APB2PeriphClockCmd(SENSOR_PORT_CLOCK,ENABLE);
	/*初始化Sensor引脚*/
	GPIO_InitStruct.GPIO_Pin = SENSOR_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	/*初始化Sensor端口*/
	GPIO_Init(SENSOR_PORT, &GPIO_InitStruct);
	
	/*初始化复用功能的AFIO配置*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	/*将PAO连接到EXTI中*/
	GPIO_EXTILineConfig(SENSOR_PORTSOURCE,SENSOR_EXTI_GPIO_PINSOURCE);
	
	/*初始化EXTI外设结构体*/
	EXTI_InitStruct.EXTI_Line     = SENSOR_EXTI_LINE;
	EXTI_InitStruct.EXTI_Mode     = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger  = EXTI_Trigger_Falling;
	EXTI_InitStruct.EXTI_LineCmd  = ENABLE;
	
	/*初始化EXTI外设*/
	EXTI_Init(&EXTI_InitStruct);
}


/**
  * @brief  初始化光电传感器
  * @retval 无
  */
void Photoelectric_Sensor_Init(void)
{
	Sensor_NVIC_Config();
	Sensor_EXTI_Config();
}


/**
  * @brief  外部中断服务函数，当光电传感器检测到物体时，执行该函数
  * @retval 无
  */
volatile uint8_t Check_Object = 0;//用于判断是否检测到物体,其取值范围是0或1

void SENSOR_EXTI_IRQHandler(void)
{	
  if(EXTI_GetITStatus(SENSOR_EXTI_LINE) != RESET)
	{
		Check_Object = 1;//表示检测到物体
		EXTI_ClearITPendingBit(SENSOR_EXTI_LINE);
	}
}
