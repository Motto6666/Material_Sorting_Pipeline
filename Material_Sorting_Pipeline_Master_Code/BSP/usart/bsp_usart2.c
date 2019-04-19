#include "bsp_usart2.h"

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void USART2_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART2_IRQ;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
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
void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	DEBUG_USART2_GPIO_APBxClkCmd(DEBUG_USART2_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	DEBUG_USART2_APBxClkCmd(DEBUG_USART2_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART2_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART2_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = DEBUG_USART2_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG_USART2, &USART_InitStructure);
	
	// �����ж����ȼ�����
	USART2_NVIC_Configuration();
	
	// ʹ�ܴ��ڽ����ж�
	USART_ITConfig(DEBUG_USART2, USART_IT_RXNE, ENABLE);	
	
	// ʹ�ܴ���
	USART_Cmd(DEBUG_USART2, ENABLE);		
    
}


 /**
  * @brief  ģ���ض�����printf����
  * @param  ��Ҫ���ͳ�ȥ���ַ�����ָ��
  * @retval ��
  */
void USART2_Printf(uint8_t *Str)
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
  * @brief  �ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
  * @param  ��
  * @retval ��
  */
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USART2, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_USART2, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}


 /**
  * @brief  ģ���ض�����printf����
  * @param  ��Ҫ���ͳ�ȥ���ַ�����ָ��
  * @retval ��
  */
void Debug_USART2_Printf(char *Str)//����ʹ�ã��������ɾ��
{
	uint16_t Str_Num=0;
	uint16_t i;
	
	while(Str[Str_Num] != '\0')
	{
		Str_Num++;
	}
	
	for(i=0;i<Str_Num+1;i++)
	{
		USART_SendData(DEBUG_USART2,Str[i]);
		SysTick_Delay_us(100);
  }
}

 /**
  * @brief  USART2���ڽ����жϷ�����
  * @param  ��Ҫ���ͳ�ȥ���ַ�����ָ��
  * @retval ��
  */
uint8_t USART2_RX_Pack[50];
volatile uint16_t USART2_RX_Count = 0;//USART2���յ����ַ�����
void DEBUG_USART2_IRQHandler(void)
{
	if(USART_GetITStatus(DEBUG_USART2,USART_IT_RXNE)!=RESET)
	{		
		TIM7_ENABLE;//����TIM7��ʱ���������ж�USART2�����Ƿ�������
		TIM7_Count = 10;
		USART2_RX_Pack[USART2_RX_Count] = USART_ReceiveData(DEBUG_USART2);
    USART2_RX_Count++;
	}	 
}
