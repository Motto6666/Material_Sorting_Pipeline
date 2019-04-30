#include "modbus_agreement.h"

/**
  * @brief  打包Modbus协议的RTU模式数据帧
  * @param  Address 				地址码
	* @param  Funtion 				功能码
	* @param  Data_Len				数据长度
	* @param  Data 						数据
  * @param  Send_Device			发送设备
  * @retval 无
  */

uint8_t Strings[50];
void RTU_Pack_Data(uint8_t Address, uint8_t Funtion, uint8_t Data_Len, uint8_t *Data )
{ 
	uint8_t i;
	Strings[0] = Address;
	Strings[1] = Funtion;
	
	if(Data_Len == 0)	//若Data_Len为0（0x00）时，不能直接将其放入到Strings数组里面，因为在
										//串口发送数据时遇到0时则停止发送，导致不能发送一个完整的数据帧，需注意！！
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
	CRC_16(Strings,Data_Len+3);//生成CRC码
	Strings[Data_Len+3] = Check_Code[1]; 
	Strings[Data_Len+4] = Check_Code[0];
	
	
	Send_Data_to_Master(Strings);

	
	Data_Clean(Strings);//清除String字符串中的数据，保证下一次执行时数据不出错
	Data_Clean(Check_Code);//清Check_Code字符串中的数据，保证下一次执行时数据不出错
}



/**
  * @brief  CRC生成函数，并将计算后的十六位CRC码存储在Check_Code[2]数组里
  * @param  *Str ：字符串数据的指针
  * @param  Len  ：需要校验的字符串数据长度
  * @retval 无
  */	
uint8_t Check_Code[2];//CRC校验码
void CRC_16(uint8_t *Str,uint8_t Len)
{
  uint16_t WCRC=0XFFFF; //预置16位CRC寄存器
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
  Check_Code[0] = WCRC;//CRC的低八位
  Check_Code[1] = WCRC>>8;//CRC的高八位
}



/**
  * @brief  将字符串输入的字符串数据
  * @param  *Str ：字符串数据的指针
  * @retval 无
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
  * @brief  RTU数据帧校验
  * @param  * RTU_Data：RTU数据帧指针
  * @retval 返回1或0
  */
uint8_t RTU_Data_Analysis(uint8_t * RTU_Data)
{
	uint8_t Temp_Array[2] = {'\0'};
	uint16_t Str_Num = 0;
	
	while(RTU_Data[Str_Num] != '\0')//计算数据帧长度
	{
		Str_Num++;
	}
	
	Temp_Array[0] = RTU_Data[Str_Num - 1];//获取CRC的低八位
	Temp_Array[1] = RTU_Data[Str_Num - 2];//获取CRC的高八位
	
	RTU_Data[Str_Num - 1] = '\0';
	RTU_Data[Str_Num - 2] = '\0';
	
	Data_Clean(Check_Code);//清Check_Code字符串中的数据，保证执行时数据不出错
	
	CRC_16(RTU_Data,Str_Num-2);
	
	if(Temp_Array[0] == Check_Code[0] && Temp_Array[1] == Check_Code[1])
	{
		Data_Clean(Check_Code);//清Check_Code字符串中的数据，保证下一次执行时数据不出错
		return CHECK_SUCCESS;
	}
	else
	{
		Data_Clean(Check_Code);//清Check_Code字符串中的数据，保证下一次执行时数据不出错
		return CHECK_FAILED;
	}
}

