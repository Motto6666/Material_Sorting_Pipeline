#include "modbus_agreement.h"

/**
  * @brief  打包Modbus协议的RTU模式数据帧
  * @param  Address ：地址码
	* @param  Funtion ：功能码
  * @param  Data    ：数据码
  * @retval 无
  */	
char String[] = {'\0'};
void Pack_Data(char Address, char Funtion, char Data, uint8_t Send_Device)
{ 
	sprintf(String,"%c%c%c",Address,Funtion,Data);
	CRC_16(String,STRING_LEN);//生成CRC码
	Data_Clean(String);
	sprintf(String,"%c%c%c%s",Address,Funtion,Data,Check_Code);//重新打包完整的RTU模式数据帧
	switch(Send_Device)
	{
		case USART1_DEVICE: USART1_Printf(String); break; 
		case USART2_DEVICE: ; break;//到时候添加USART2_Printf(String)函数上去！！！！！！！ 
		default: break;
	}
	Data_Clean(String);//清除String字符串中的数据，保证下一次执行时数据不出错
	Data_Clean(Check_Code);//清Check_Code字符串中的数据，保证下一次执行时数据不出错
}




/**
  * @brief  CRC生成函数，并将计算后的十六位CRC码存储在Check_Code[2]数组里
  * @param  *Str ：字符串数据的指针
  * @param  Len  ：需要校验的字符串数据长度
  * @retval 无
  */	
char Check_Code[2];//CRC校验码
void CRC_16(char *Str,uint8_t Len)
{
  uint16_t WCRC=0XFFFF; //预置16位CRC寄存器
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
  Check_Code[0] = WCRC;//CRC的低八位
  Check_Code[1] = WCRC>>8;//CRC的高八位
}


/**
  * @brief  将字符串输入的字符串数据
  * @param  *Str ：字符串数据的指针
  * @retval 无
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

