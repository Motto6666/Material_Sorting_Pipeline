#include "bsp_usart1.h"

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART1_IRQ;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  USART GPIO ����,������������
  * @param  ��
  * @retval ��
  */
void USART1_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* �򿪴���GPIO��ʱ��*/
	DEBUG_USART1_GPIO_APBxClkCmd(DEBUG_USART1_GPIO_CLK, ENABLE);
	
	/* �򿪴��������ʱ��*/
	DEBUG_USART1_APBxClkCmd(DEBUG_USART1_CLK, ENABLE);

	/* ��USART Tx��GPIO����Ϊ���츴��ģʽ*/
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART1_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART1_TX_GPIO_PORT, &GPIO_InitStructure);

  /* ��USART Rx��GPIO����Ϊ��������ģʽ*/
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART1_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART1_RX_GPIO_PORT, &GPIO_InitStructure);
	
	
	/* ���ô��ڲ�����*/
	USART_InitStructure.USART_BaudRate = DEBUG_USART1_BAUDRATE;
	/* ���� �������ֳ�*/
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* ����ֹͣλ*/
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* ����У��λ��ͬ��ͨ��ʱ��ʹ�ã���������Ϊ USART_Parity_No*/
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	/* ����Ӳ�������ƣ�ͬ��ͨ��ʱ��ʹ�ã���������Ϊ USART_HardwareFlowControl_None*/
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	/* ���ù���ģʽ���շ�һ��*/
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* ��ɴ��ڵĳ�ʼ������*/
	USART_Init(DEBUG_USART1, &USART_InitStructure);
	
	/* �����ж����ȼ�����*/
	NVIC_Configuration();
	
	/* ʹ�ܴ��ڽ����ж�*/
	USART_ITConfig(DEBUG_USART1, USART_IT_RXNE, ENABLE);	
	
	/* ʹ�ܴ���*/
	USART_Cmd(DEBUG_USART1, ENABLE);	    
}


 /**
  * @brief  ���ڽ����жϷ�����
  * @param  ��
  * @retval ��
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

/*ģ���ض�����printf����*/
void Printf(char *String)
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





