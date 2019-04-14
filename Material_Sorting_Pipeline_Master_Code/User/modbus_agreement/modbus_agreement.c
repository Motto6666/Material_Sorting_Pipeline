#include "modbus_agreement.h"

/**
  * @brief  ���ModbusЭ���RTUģʽ����֡
  * @param  Address ����ַ��
	* @param  Funtion ��������
  * @param  Data    ��������
  * @retval ��
  */	
char String[] = {'\0'};
void Pack_Data(char Address, char Funtion, char Data, uint8_t Send_Device)
{ 
	sprintf(String,"%c%c%c",Address,Funtion,Data);
	CRC_16(String,STRING_LEN);//����CRC��
	Data_Clean(String);
	sprintf(String,"%c%c%c%s",Address,Funtion,Data,Check_Code);//���´��������RTUģʽ����֡
	switch(Send_Device)
	{
		case USART1_DEVICE: USART1_Printf(String); break; 
		case USART2_DEVICE: ; break;//��ʱ�����USART2_Printf(String)������ȥ�������������� 
		default: break;
	}
	Data_Clean(String);//���String�ַ����е����ݣ���֤��һ��ִ��ʱ���ݲ�����
	Data_Clean(Check_Code);//��Check_Code�ַ����е����ݣ���֤��һ��ִ��ʱ���ݲ�����
}




/**
  * @brief  CRC���ɺ���������������ʮ��λCRC��洢��Check_Code[2]������
  * @param  *Str ���ַ������ݵ�ָ��
  * @param  Len  ����ҪУ����ַ������ݳ���
  * @retval ��
  */	
char Check_Code[2];//CRCУ����
void CRC_16(char *Str,uint8_t Len)
{
  uint16_t WCRC=0XFFFF; //Ԥ��16λCRC�Ĵ���
  char Temp;
  uint8_t i=0,j=0;
  for(i=0;i<Len;i++)
  {
    Temp=*Str&0X00FF;
    Str++;
    WCRC^=Temp;
    for(j=0;j<8;j++)
    {
      if(WCRC&0X0001)
      {
        WCRC>>=1;
        WCRC^=0XA001;
      }
      else
      {
        WCRC>>=1;
      }
    }
  }
  Check_Code[0] = WCRC;//CRC�ĵͰ�λ
  Check_Code[1] = WCRC>>8;//CRC�ĸ߰�λ
}


/**
  * @brief  ���ַ���������ַ�������
  * @param  *Str ���ַ������ݵ�ָ��
  * @retval ��
  */
void Data_Clean(char *Str)
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

