#include "bsp_usart1.h"

 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART1_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
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
void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* 打开串口GPIO的时钟*/
	DEBUG_USART1_GPIO_APBxClkCmd(DEBUG_USART1_GPIO_CLK, ENABLE);
	
	/* 打开串口外设的时钟*/
	DEBUG_USART1_APBxClkCmd(DEBUG_USART1_CLK, ENABLE);

	/* 将USART Tx的GPIO配置为推挽复用模式*/
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART1_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART1_TX_GPIO_PORT, &GPIO_InitStructure);

  /* 将USART Rx的GPIO配置为浮空输入模式*/
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART1_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART1_RX_GPIO_PORT, &GPIO_InitStructure);
	
	
	/* 配置串口波特率*/
	USART_InitStructure.USART_BaudRate = DEBUG_USART1_BAUDRATE;
	/* 配置 针数据字长*/
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* 配置停止位*/
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* 配置校验位，同步通信时才使用，所以配置为 USART_Parity_No*/
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	/* 配置硬件流控制，同步通信时才使用，所以配置为 USART_HardwareFlowControl_None*/
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	/* 配置工作模式，收发一起*/
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* 完成串口的初始化配置*/
	USART_Init(DEBUG_USART1, &USART_InitStructure);
	
	/* 串口中断优先级配置*/
	NVIC_Configuration();
	
	/* 使能串口接收中断*/
	USART_ITConfig(DEBUG_USART1, USART_IT_RXNE, ENABLE);	
	
	/* 使能串口*/
	USART_Cmd(DEBUG_USART1, ENABLE);	    
}


 /**
  * @brief  串口接收中断服务函数
  * @param  无
  * @retval 无
  */
void DEBUG_USART1_IRQHandler(void)
{
  uint8_t ucTemp;
	
	if(USART_GetITStatus(DEBUG_USART1,USART_IT_RXNE)!=RESET)
	{		
		ucTemp = USART_ReceiveData(DEBUG_USART1);
    USART_SendData(DEBUG_USART1,ucTemp);    
	}	 
}

/*模拟重定向后的printf函数*/
void USART1_Printf(uint8_t *String)
{
	uint16_t String_Num = 0;
	uint16_t i;
	
	while(String[String_Num] != '\0')
	{
		String_Num++;
	}
	
	for(i=0;i<String_Num;i++)
	{
		USART_SendData(DEBUG_USART1,String[i]);
		SysTick_Delay_us(100);
  }
}





