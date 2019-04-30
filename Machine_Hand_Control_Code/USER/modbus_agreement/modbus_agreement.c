#include "modbus_agreement.h"

/**
  * @brief  ���ModbusЭ���RTUģʽ����֡
  * @param  Address 				��ַ��
	* @param  Funtion 				������
	* @param  Data_Len				���ݳ���
	* @param  Data 						����
  * @param  Send_Device			�����豸
  * @retval ��
  */

uint8_t Strings[50];
void RTU_Pack_Data(uint8_t Address, uint8_t Funtion, uint8_t Data_Len, uint8_t *Data )
{ 
	uint8_t i;
	Strings[0] = Address;
	Strings[1] = Funtion;
	
	if(Data_Len == 0)	//��Data_LenΪ0��0x00��ʱ������ֱ�ӽ�����뵽Strings�������棬��Ϊ��
										//���ڷ�������ʱ����0ʱ��ֹͣ���ͣ����²��ܷ���һ������������֡����ע�⣡��
	{
		Strings[2] = DATA_NONE;
	}
	else
	{
		Strings[2] = Data_Len;
	}
	
	for(i = 0;i<Data_Len;i++)
	{
		Strings[i+3] = Data[i];
	}
	CRC_16(Strings,Data_Len+3);//����CRC��
	Strings[Data_Len+3] = Check_Code[1]; 
	Strings[Data_Len+4] = Check_Code[0];
	
	
	Send_Data_to_Master(Strings);

	
	Data_Clean(Strings);//���String�ַ����е����ݣ���֤��һ��ִ��ʱ���ݲ�����
	Data_Clean(Check_Code);//��Check_Code�ַ����е����ݣ���֤��һ��ִ��ʱ���ݲ�����
}



/**
  * @brief  CRC���ɺ���������������ʮ��λCRC��洢��Check_Code[2]������
  * @param  *Str ���ַ������ݵ�ָ��
  * @param  Len  ����ҪУ����ַ������ݳ���
  * @retval ��
  */	
uint8_t Check_Code[2];//CRCУ����
void CRC_16(uint8_t *Str,uint8_t Len)
{
  uint16_t WCRC=0XFFFF; //Ԥ��16λCRC�Ĵ���
  uint8_t Temp;
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
void Data_Clean(uint8_t *Str)
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
  * @brief  RTU����֡У��
  * @param  * RTU_Data��RTU����ָ֡��
  * @retval ����1��0
  */
uint8_t RTU_Data_Analysis(uint8_t * RTU_Data)
{
	uint8_t Temp_Array[2] = {'\0'};
	uint16_t Str_Num = 0;
	
	while(RTU_Data[Str_Num] != '\0')//��������֡����
	{
		Str_Num++;
	}
	
	Temp_Array[0] = RTU_Data[Str_Num - 1];//��ȡCRC�ĵͰ�λ
	Temp_Array[1] = RTU_Data[Str_Num - 2];//��ȡCRC�ĸ߰�λ
	
	RTU_Data[Str_Num - 1] = '\0';
	RTU_Data[Str_Num - 2] = '\0';
	
	Data_Clean(Check_Code);//��Check_Code�ַ����е����ݣ���ִ֤��ʱ���ݲ�����
	
	CRC_16(RTU_Data,Str_Num-2);
	
	if(Temp_Array[0] == Check_Code[0] && Temp_Array[1] == Check_Code[1])
	{
		Data_Clean(Check_Code);//��Check_Code�ַ����е����ݣ���֤��һ��ִ��ʱ���ݲ�����
		return CHECK_SUCCESS;
	}
	else
	{
		Data_Clean(Check_Code);//��Check_Code�ַ����е����ݣ���֤��һ��ִ��ʱ���ݲ�����
		return CHECK_FAILED;
	}
}

