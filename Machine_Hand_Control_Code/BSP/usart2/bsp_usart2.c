#include "bsp_usart2.h"

 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void USART2_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART2_IRQ;
	
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  USART GPIO 配置,工作参数配置
  * @param  无
  * @retval 无
  */
void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// 打开串口GPIO的时钟
	DEBUG_USART2_GPIO_APBxClkCmd(DEBUG_USART2_GPIO_CLK, ENABLE);
	
	// 打开串口外设的时钟
	DEBUG_USART2_APBxClkCmd(DEBUG_USART2_CLK, ENABLE);

	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART2_TX_GPIO_PORT, &GPIO_InitStructure);

  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART2_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// 配置串口的工作参数
	// 配置波特率
	USART_InitStructure.USART_BaudRate = DEBUG_USART2_BAUDRATE;
	
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	// 完成串口的初始化配置
	USART_Init(DEBUG_USART2, &USART_InitStructure);
	
	// 串口中断优先级配置
	USART2_NVIC_Configuration();
	
	// 使能串口接收中断
	USART_ITConfig(DEBUG_USART2, USART_IT_RXNE, ENABLE);

	//开启串口2总线空闲中断
	USART_ITConfig(DEBUG_USART2, USART_IT_IDLE, ENABLE);
	
	// 使能串口
	USART_Cmd(DEBUG_USART2, ENABLE);		
    
}


 /**
  * @brief  模拟重定向后的printf函数
  * @param  需要发送出去的字符串的指针
  * @retval 无
  */
void Send_Data_to_Master(uint8_t *Str)
{
	uint16_t Str_Num=0;
	uint16_t i;
	
	while(Str[Str_Num] != '\0')
	{
		Str_Num++;
	}
	
	for(i=0;i<Str_Num;i++)
	{
		USART_SendData(DEBUG_USART2,Str[i]);
		SysTick_Delay_us(100);
  }
}


 /**
  * @brief  USART2串口接收中断服务函数
  * @param  需要发送出去的字符串的指针
  * @retval 无
  */
uint8_t Receive_Master_Data[10];
volatile uint16_t USART2_RX_Count = 0;//记录USART2接收到8位数据的个数
uint8_t Free_Read_Rst = 0;//读DR清除空闲中断
volatile uint8_t USART_RX_Over = 0;//用于判断数据USART2是否收接收完毕，取值范围位0或1

void DEBUG_USART2_IRQHandler(void)
{
	if(USART_GetITStatus(DEBUG_USART2,USART_IT_RXNE)!=RESET)
	{		
		USART_ClearITPendingBit(DEBUG_USART2, USART_FLAG_ORE); //清除中断标志
		USART_ClearITPendingBit(DEBUG_USART2,USART_IT_ORE); //清除中断标志
		Receive_Master_Data[USART2_RX_Count] = USART_ReceiveData(DEBUG_USART2);
    USART2_RX_Count++;
	}	
	else if(USART_GetITStatus(DEBUG_USART2,USART_IT_IDLE) !=RESET)//传输完一条完整的数据就会进入这个
	{
		Free_Read_Rst = DEBUG_USART2->DR; //读取USART数据寄存器，达到清USART_IT_IDLE标志目的
		USART_RX_Over = 1;//接收到一条完整的数据
		USART2_RX_Count = 0;//清零接收的个数
		Check_Stop_Data(Receive_Master_Data);//检查接收到的数据是否为停止数据
  } 
}


/**
  * @brief  将字符串输入的字符串数据
  * @param  *Str ：字符串数据的指针
  * @retval 无
  */
void Clean_Data(uint8_t *Str) 
{
	uint16_t Str_Num=0;
	uint16_t i;
	
	while(Str[Str_Num] != '\0')
	{
		Str_Num++;
	}
	
	for(i=0;i<Str_Num;i++)
	{
		Str[i] = '\0';
  }
}


/**
  * @brief  检查接收到的数据是否为停止数据
  * @param  *Str ：字符串数据的指针
  * @retval 无
  */
void Check_Stop_Data(uint8_t *Str)
{
	if(Str[1] == IRON_HAND_EXECUTE_STOP)//判断RTU数据帧的功能码是否为机械手停止运行码
	{
		TIM2_DISABLE;//关闭控制舵机运行的定时器TIM2，机械手停止运作
		while(1);
	}
}
