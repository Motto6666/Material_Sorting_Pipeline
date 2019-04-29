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

	//��������2���߿����ж�
	USART_ITConfig(DEBUG_USART2, USART_IT_IDLE, ENABLE);
	
	// ʹ�ܴ���
	USART_Cmd(DEBUG_USART2, ENABLE);		
    
}


 /**
  * @brief  ģ���ض�����printf����
  * @param  ��Ҫ���ͳ�ȥ���ַ�����ָ��
  * @retval ��
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
  * @brief  USART2���ڽ����жϷ�����
  * @param  ��Ҫ���ͳ�ȥ���ַ�����ָ��
  * @retval ��
  */
uint8_t Receive_Master_Data[10];
volatile uint16_t USART2_RX_Count = 0;//��¼USART2���յ�8λ���ݵĸ���
uint8_t Free_Read_Rst = 0;//��DR��������ж�
volatile uint8_t USART_RX_Over = 0;//�����ж�����USART2�Ƿ��ս�����ϣ�ȡֵ��Χλ0��1

void DEBUG_USART2_IRQHandler(void)
{
	if(USART_GetITStatus(DEBUG_USART2,USART_IT_RXNE)!=RESET)
	{		
		USART_ClearITPendingBit(DEBUG_USART2, USART_FLAG_ORE); //����жϱ�־
		USART_ClearITPendingBit(DEBUG_USART2,USART_IT_ORE); //����жϱ�־
		Receive_Master_Data[USART2_RX_Count] = USART_ReceiveData(DEBUG_USART2);
    USART2_RX_Count++;
	}	
	else if(USART_GetITStatus(DEBUG_USART2,USART_IT_IDLE) !=RESET)//������һ�����������ݾͻ�������
	{
		Free_Read_Rst = DEBUG_USART2->DR; //��ȡUSART���ݼĴ������ﵽ��USART_IT_IDLE��־Ŀ��
		USART_RX_Over = 1;//���յ�һ������������
		USART2_RX_Count = 0;//������յĸ���
		Check_Stop_Data(Receive_Master_Data);//�����յ��������Ƿ�Ϊֹͣ����
  } 
}


/**
  * @brief  ���ַ���������ַ�������
  * @param  *Str ���ַ������ݵ�ָ��
  * @retval ��
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
  * @brief  �����յ��������Ƿ�Ϊֹͣ����
  * @param  *Str ���ַ������ݵ�ָ��
  * @retval ��
  */
void Check_Stop_Data(uint8_t *Str)
{
	if(Str[1] == IRON_HAND_EXECUTE_STOP)//�ж�RTU����֡�Ĺ������Ƿ�Ϊ��е��ֹͣ������
	{
		TIM2_DISABLE;//�رտ��ƶ�����еĶ�ʱ��TIM2����е��ֹͣ����
		while(1);
	}
}
