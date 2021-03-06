#include "lcd_display_chinese.h"

/************************************************************************************************/
/*“物料分拣流水线”字模数据*/
uint8_t Chinese_Character_1[9][32] = 
{
{0x10,0x80,0x10,0x80,0x50,0x80,0x50,0xFC,0x7D,0x54,0x52,0x54,0x90,0x54,0x10,0x94,
 0x1C,0x94,0xF1,0x24,0x52,0x24,0x10,0x44,0x10,0x44,0x10,0x84,0x11,0x28,0x10,0x10},//字符"物"字模

{0x08,0x08,0x08,0x88,0x4A,0x48,0x2A,0x48,0x2C,0x08,0x08,0x88,0xFE,0x48,0x18,0x48,
 0x1C,0x08,0x2A,0x0E,0x2A,0xF8,0x48,0x08,0x88,0x08,0x08,0x08,0x08,0x08,0x08,0x08},//字符"料"字模

{0x00,0x40,0x04,0x40,0x04,0x20,0x08,0x20,0x10,0x10,0x20,0x08,0x40,0x04,0x9F,0xE2,
 0x04,0x20,0x04,0x20,0x04,0x20,0x08,0x20,0x08,0x20,0x10,0x20,0x21,0x40,0x40,0x80},//字符"分"字模

{0x10,0x40,0x10,0x40,0x17,0xFC,0x10,0x80,0xFC,0x80,0x13,0xE0,0x11,0x20,0x12,0x20,
 0x1B,0xFC,0x30,0x20,0xD1,0x28,0x11,0x24,0x12,0x22,0x14,0x22,0x50,0xA0,0x20,0x40},//字符"拣"字模

{0x00,0x80,0x20,0x40,0x17,0xFE,0x10,0x80,0x81,0x10,0x42,0x08,0x47,0xFC,0x10,0x04,
 0x10,0x00,0x22,0x48,0xE2,0x48,0x22,0x48,0x22,0x48,0x22,0x4A,0x24,0x4A,0x08,0x46},//字符"流"字模

{0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x08,0x01,0x08,0x7D,0x90,0x05,0xA0,0x09,0x40,
 0x09,0x40,0x11,0x20,0x11,0x10,0x21,0x08,0x41,0x06,0x81,0x00,0x05,0x00,0x02,0x00},//字符"水"字模

{0x10,0x50,0x10,0x48,0x20,0x40,0x24,0x5C,0x45,0xE0,0xF8,0x40,0x10,0x5E,0x23,0xE0,
 0x40,0x44,0xFC,0x48,0x40,0x30,0x00,0x22,0x1C,0x52,0xE0,0x8A,0x43,0x06,0x00,0x02},//字符"线"字模

{0x00,0xF8,0x3F,0x00,0x04,0x00,0x08,0x20,0x10,0x40,0x3F,0x80,0x01,0x00,0x06,0x10,
 0x18,0x08,0x7F,0xFC,0x01,0x04,0x09,0x20,0x11,0x10,0x21,0x08,0x45,0x04,0x02,0x00},//字符"系"字模

{0x10,0x40,0x10,0x20,0x20,0x20,0x23,0xFE,0x48,0x40,0xF8,0x88,0x11,0x04,0x23,0xFE,
 0x40,0x92,0xF8,0x90,0x40,0x90,0x00,0x90,0x19,0x12,0xE1,0x12,0x42,0x0E,0x04,0x00}//字符"统"字模
};

 
/************************************************************************************************/
/*“系统运行情况：”字模数据*/
uint8_t Chinese_Character_2[7][32] =
{
{0x00,0xF8,0x3F,0x00,0x04,0x00,0x08,0x20,0x10,0x40,0x3F,0x80,0x01,0x00,0x06,0x10,
 0x18,0x08,0x7F,0xFC,0x01,0x04,0x09,0x20,0x11,0x10,0x21,0x08,0x45,0x04,0x02,0x00},//字符"系"字模0

{0x10,0x40,0x10,0x20,0x20,0x20,0x23,0xFE,0x48,0x40,0xF8,0x88,0x11,0x04,0x23,0xFE,
 0x40,0x92,0xF8,0x90,0x40,0x90,0x00,0x90,0x19,0x12,0xE1,0x12,0x42,0x0E,0x04,0x00},//字符"统"字模1

{0x00,0x00,0x23,0xF8,0x10,0x00,0x10,0x00,0x00,0x00,0x07,0xFC,0xF0,0x40,0x10,0x80,
 0x11,0x10,0x12,0x08,0x17,0xFC,0x12,0x04,0x10,0x00,0x28,0x00,0x47,0xFE,0x00,0x00},//字符"运"字模2

{0x08,0x00,0x09,0xFC,0x10,0x00,0x20,0x00,0x48,0x00,0x08,0x00,0x13,0xFE,0x30,0x20,
 0x50,0x20,0x90,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0xA0,0x10,0x40},//字符"行"字模3

{0x10,0x40,0x10,0x40,0x17,0xFC,0x10,0x40,0x1B,0xF8,0x54,0x40,0x57,0xFE,0x50,0x00,
 0x93,0xF8,0x12,0x08,0x13,0xF8,0x12,0x08,0x13,0xF8,0x12,0x08,0x12,0x28,0x12,0x10},//字符"情"字模4

{0x00,0x00,0x47,0xF8,0x24,0x08,0x24,0x08,0x04,0x08,0x04,0x08,0x17,0xF8,0x11,0x20,
 0x21,0x20,0xE1,0x20,0x21,0x20,0x22,0x20,0x22,0x22,0x24,0x22,0x28,0x1E,0x10,0x00},//字符"况"字模5

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
 0x00,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00},//字符"："字模6
};

 
/************************************************************************************************/ 
/*“视觉模块响应正常”字模数据*/
uint8_t Chinese_Character_3[8][32] =
{
{0x20,0x00,0x11,0xFC,0x11,0x04,0xF9,0x04,0x09,0x24,0x11,0x24,0x11,0x24,0x39,0x24,
 0x55,0x24,0x95,0x54,0x10,0x50,0x10,0x90,0x10,0x90,0x11,0x12,0x12,0x12,0x14,0x0E},//字符"视"字模

{0x22,0x08,0x11,0x10,0x00,0x20,0x7F,0xFE,0x40,0x02,0x80,0x04,0x1F,0xF0,0x10,0x10,
 0x11,0x10,0x11,0x10,0x11,0x10,0x12,0x90,0x02,0x80,0x04,0x84,0x18,0x84,0x60,0x7C},//字符"觉"字模

{0x11,0x10,0x11,0x10,0x17,0xFC,0x11,0x10,0xFC,0x00,0x13,0xF8,0x32,0x08,0x3B,0xF8,
 0x56,0x08,0x53,0xF8,0x90,0x40,0x17,0xFC,0x10,0xA0,0x11,0x10,0x12,0x08,0x14,0x06},//字符"模"字模

{0x10,0x40,0x10,0x40,0x10,0x40,0x13,0xFC,0x10,0x44,0xFC,0x44,0x10,0x44,0x10,0x44,
 0x13,0xFE,0x10,0x40,0x10,0xA0,0x1C,0xA0,0xE1,0x10,0x42,0x08,0x04,0x04,0x08,0x02},//字符"块"字模

{0x00,0x40,0x00,0x40,0x78,0x80,0x4B,0xFC,0x4A,0x04,0x4A,0x04,0x4A,0xF4,0x4A,0x94,
 0x4A,0x94,0x4A,0x94,0x7A,0x94,0x4A,0xF4,0x02,0x04,0x02,0x04,0x02,0x14,0x02,0x08},//字符"响"字模

{0x01,0x00,0x00,0x80,0x3F,0xFE,0x20,0x00,0x20,0x00,0x21,0x04,0x28,0x84,0x24,0x84,
 0x24,0x48,0x22,0x48,0x22,0x10,0x22,0x10,0x40,0x20,0x40,0x40,0x9F,0xFE,0x00,0x00},//字符"应"字模

{0x00,0x00,0x7F,0xFC,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x11,0x00,0x11,0xF8,
 0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0xFF,0xFE,0x00,0x00},//字符"正"字模

{0x01,0x00,0x11,0x10,0x09,0x20,0x7F,0xFE,0x40,0x02,0x9F,0xF4,0x10,0x10,0x1F,0xF0,
 0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x21,0x28,0x21,0x10,0x01,0x00,0x01,0x00}//字符"常"字模 
};
 
 
/************************************************************************************************/
/*“向视觉模块发送检测指令超时”字模数据*/
uint8_t Chinese_Character_4[13][32] =
{
{0x02,0x00,0x04,0x00,0x08,0x00,0x7F,0xFC,0x40,0x04,0x40,0x04,0x47,0xC4,0x44,0x44,
 0x44,0x44,0x44,0x44,0x44,0x44,0x47,0xC4,0x44,0x44,0x40,0x04,0x40,0x14,0x40,0x08},//"向"字模0

{0x20,0x00,0x11,0xFC,0x11,0x04,0xF9,0x04,0x09,0x24,0x11,0x24,0x11,0x24,0x39,0x24,
 0x55,0x24,0x95,0x54,0x10,0x50,0x10,0x90,0x10,0x90,0x11,0x12,0x12,0x12,0x14,0x0E},//"视"字模1

{0x22,0x08,0x11,0x10,0x00,0x20,0x7F,0xFE,0x40,0x02,0x80,0x04,0x1F,0xF0,0x10,0x10,
 0x11,0x10,0x11,0x10,0x11,0x10,0x12,0x90,0x02,0x80,0x04,0x84,0x18,0x84,0x60,0x7C},//"觉"字模2

{0x11,0x10,0x11,0x10,0x17,0xFC,0x11,0x10,0xFC,0x00,0x13,0xF8,0x32,0x08,0x3B,0xF8,
 0x56,0x08,0x53,0xF8,0x90,0x40,0x17,0xFC,0x10,0xA0,0x11,0x10,0x12,0x08,0x14,0x06},//"模"字模3

{0x10,0x40,0x10,0x40,0x10,0x40,0x13,0xFC,0x10,0x44,0xFC,0x44,0x10,0x44,0x10,0x44,
 0x13,0xFE,0x10,0x40,0x10,0xA0,0x1C,0xA0,0xE1,0x10,0x42,0x08,0x04,0x04,0x08,0x02},//"块"字模4

{0x01,0x00,0x11,0x10,0x11,0x08,0x22,0x00,0x3F,0xFC,0x02,0x00,0x04,0x00,0x07,0xF8,
 0x0A,0x08,0x09,0x08,0x11,0x10,0x10,0xA0,0x20,0x40,0x40,0xA0,0x03,0x18,0x1C,0x06},//"发"字模5

{0x02,0x08,0x21,0x08,0x11,0x10,0x17,0xFC,0x00,0x40,0x00,0x40,0xF0,0x40,0x17,0xFE,
 0x10,0x40,0x10,0xA0,0x10,0x90,0x11,0x08,0x12,0x08,0x28,0x00,0x47,0xFE,0x00,0x00},//"送"字模6

{0x10,0x40,0x10,0x40,0x10,0xA0,0x10,0xA0,0xFD,0x10,0x12,0x08,0x35,0xF6,0x38,0x00,
 0x54,0x88,0x50,0x48,0x92,0x48,0x11,0x50,0x11,0x10,0x10,0x20,0x17,0xFE,0x10,0x00},//"检"字模7

{0x00,0x04,0x27,0xC4,0x14,0x44,0x14,0x54,0x85,0x54,0x45,0x54,0x45,0x54,0x15,0x54,
 0x15,0x54,0x25,0x54,0xE5,0x54,0x21,0x04,0x22,0x84,0x22,0x44,0x24,0x14,0x08,0x08},//"测"字模8

{0x11,0x00,0x11,0x04,0x11,0x38,0x11,0xC0,0xFD,0x02,0x11,0x02,0x10,0xFE,0x14,0x00,
 0x19,0xFC,0x31,0x04,0xD1,0x04,0x11,0xFC,0x11,0x04,0x11,0x04,0x51,0xFC,0x21,0x04},//"指"字模9

{0x01,0x00,0x01,0x00,0x02,0x80,0x04,0x40,0x0A,0x20,0x11,0x10,0x21,0x08,0xC0,0x06,
 0x1F,0xF0,0x00,0x10,0x00,0x20,0x04,0x40,0x02,0x80,0x01,0x00,0x00,0x80,0x00,0x80},//"令"字模10

{0x08,0x00,0x09,0xFC,0x08,0x44,0x7E,0x44,0x08,0x44,0x08,0x94,0xFF,0x08,0x08,0xFC,
 0x28,0x84,0x28,0x84,0x2E,0x84,0x28,0xFC,0x28,0x00,0x58,0x00,0x4F,0xFE,0x80,0x00},//"超"字模11

{0x00,0x08,0x00,0x08,0x7C,0x08,0x44,0x08,0x45,0xFE,0x44,0x08,0x44,0x08,0x7C,0x08,
 0x44,0x88,0x44,0x48,0x44,0x48,0x44,0x08,0x7C,0x08,0x44,0x08,0x00,0x28,0x00,0x10},//"时"字模12
};
 

/************************************************************************************************/
/*“机械手控制模块响应正常”字模数据*/ 
uint8_t Chinese_Character_5[11][32] =
{
 {0x10,0x00,0x11,0xF0,0x11,0x10,0x11,0x10,0xFD,0x10,0x11,0x10,0x31,0x10,0x39,0x10,
  0x55,0x10,0x55,0x10,0x91,0x10,0x11,0x12,0x11,0x12,0x12,0x12,0x12,0x0E,0x14,0x00},//字符"机"字模0

{0x10,0x10,0x10,0x14,0x10,0x12,0x10,0x10,0xFB,0xFE,0x10,0x10,0x31,0x50,0x39,0x54,
 0x57,0xF4,0x51,0x54,0x91,0x54,0x11,0x48,0x12,0x4A,0x12,0x5A,0x14,0x26,0x10,0x42},//字符"械"字模1

{0x00,0x10,0x00,0xF8,0x3F,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,
 0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x05,0x00,0x02,0x00},//字符"手"字模2

{0x10,0x40,0x10,0x20,0x10,0x20,0x13,0xFE,0xFA,0x02,0x14,0x94,0x11,0x08,0x1A,0x04,
 0x30,0x00,0xD1,0xFC,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x57,0xFE,0x20,0x00},//字符"控"字模3

{0x04,0x04,0x24,0x04,0x24,0x04,0x3F,0xA4,0x44,0x24,0x04,0x24,0xFF,0xE4,0x04,0x24,
 0x04,0x24,0x3F,0xA4,0x24,0xA4,0x24,0xA4,0x26,0x84,0x25,0x04,0x04,0x14,0x04,0x08},//字符"制"字模4

{0x11,0x10,0x11,0x10,0x17,0xFC,0x11,0x10,0xFC,0x00,0x13,0xF8,0x32,0x08,0x3B,0xF8,
 0x56,0x08,0x53,0xF8,0x90,0x40,0x17,0xFC,0x10,0xA0,0x11,0x10,0x12,0x08,0x14,0x06},//字符"模"字模5

{0x10,0x40,0x10,0x40,0x10,0x40,0x13,0xFC,0x10,0x44,0xFC,0x44,0x10,0x44,0x10,0x44,
 0x13,0xFE,0x10,0x40,0x10,0xA0,0x1C,0xA0,0xE1,0x10,0x42,0x08,0x04,0x04,0x08,0x02},//字符"块"字模6

{0x00,0x40,0x00,0x40,0x78,0x80,0x4B,0xFC,0x4A,0x04,0x4A,0x04,0x4A,0xF4,0x4A,0x94,
 0x4A,0x94,0x4A,0x94,0x7A,0x94,0x4A,0xF4,0x02,0x04,0x02,0x04,0x02,0x14,0x02,0x08},//字符"响"字模7

{0x01,0x00,0x00,0x80,0x3F,0xFE,0x20,0x00,0x20,0x00,0x21,0x04,0x28,0x84,0x24,0x84,
 0x24,0x48,0x22,0x48,0x22,0x10,0x22,0x10,0x40,0x20,0x40,0x40,0x9F,0xFE,0x00,0x00},//字符"应"字模8

{0x00,0x00,0x7F,0xFC,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x11,0x00,0x11,0xF8,
 0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0xFF,0xFE,0x00,0x00},//字符"正"字模9

{0x01,0x00,0x11,0x10,0x09,0x20,0x7F,0xFE,0x40,0x02,0x9F,0xF4,0x10,0x10,0x1F,0xF0,
 0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x21,0x28,0x21,0x10,0x01,0x00,0x01,0x00}//字符"常"字模10
};


/************************************************************************************************/
/*“向机械手发送检测指令超时”字模数据*/ 
uint8_t Chinese_Character_6[12][32] =
{
{0x02,0x00,0x04,0x00,0x08,0x00,0x7F,0xFC,0x40,0x04,0x40,0x04,0x47,0xC4,0x44,0x44,
 0x44,0x44,0x44,0x44,0x44,0x44,0x47,0xC4,0x44,0x44,0x40,0x04,0x40,0x14,0x40,0x08},//"向"字模0

{0x10,0x00,0x11,0xF0,0x11,0x10,0x11,0x10,0xFD,0x10,0x11,0x10,0x31,0x10,0x39,0x10,
 0x55,0x10,0x55,0x10,0x91,0x10,0x11,0x12,0x11,0x12,0x12,0x12,0x12,0x0E,0x14,0x00},//"机"字模1

{0x10,0x10,0x10,0x14,0x10,0x12,0x10,0x10,0xFB,0xFE,0x10,0x10,0x31,0x50,0x39,0x54,
 0x57,0xF4,0x51,0x54,0x91,0x54,0x11,0x48,0x12,0x4A,0x12,0x5A,0x14,0x26,0x10,0x42},//"械"字模2

{0x00,0x10,0x00,0xF8,0x3F,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,
 0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x05,0x00,0x02,0x00},//"手"字模3

{0x01,0x00,0x11,0x10,0x11,0x08,0x22,0x00,0x3F,0xFC,0x02,0x00,0x04,0x00,0x07,0xF8,
 0x0A,0x08,0x09,0x08,0x11,0x10,0x10,0xA0,0x20,0x40,0x40,0xA0,0x03,0x18,0x1C,0x06},//"发"字模4

{0x02,0x08,0x21,0x08,0x11,0x10,0x17,0xFC,0x00,0x40,0x00,0x40,0xF0,0x40,0x17,0xFE,
 0x10,0x40,0x10,0xA0,0x10,0x90,0x11,0x08,0x12,0x08,0x28,0x00,0x47,0xFE,0x00,0x00},//"送"字模5

{0x10,0x40,0x10,0x40,0x10,0xA0,0x10,0xA0,0xFD,0x10,0x12,0x08,0x35,0xF6,0x38,0x00,
 0x54,0x88,0x50,0x48,0x92,0x48,0x11,0x50,0x11,0x10,0x10,0x20,0x17,0xFE,0x10,0x00},//"检"字模6

{0x00,0x04,0x27,0xC4,0x14,0x44,0x14,0x54,0x85,0x54,0x45,0x54,0x45,0x54,0x15,0x54,
 0x15,0x54,0x25,0x54,0xE5,0x54,0x21,0x04,0x22,0x84,0x22,0x44,0x24,0x14,0x08,0x08},//"测"字模7

{0x11,0x00,0x11,0x04,0x11,0x38,0x11,0xC0,0xFD,0x02,0x11,0x02,0x10,0xFE,0x14,0x00,
 0x19,0xFC,0x31,0x04,0xD1,0x04,0x11,0xFC,0x11,0x04,0x11,0x04,0x51,0xFC,0x21,0x04},//"指"字模8

{0x01,0x00,0x01,0x00,0x02,0x80,0x04,0x40,0x0A,0x20,0x11,0x10,0x21,0x08,0xC0,0x06,
 0x1F,0xF0,0x00,0x10,0x00,0x20,0x04,0x40,0x02,0x80,0x01,0x00,0x00,0x80,0x00,0x80},//"令"字模9

{0x08,0x00,0x09,0xFC,0x08,0x44,0x7E,0x44,0x08,0x44,0x08,0x94,0xFF,0x08,0x08,0xFC,
 0x28,0x84,0x28,0x84,0x2E,0x84,0x28,0xFC,0x28,0x00,0x58,0x00,0x4F,0xFE,0x80,0x00},//"超"字模10

{0x00,0x08,0x00,0x08,0x7C,0x08,0x44,0x08,0x45,0xFE,0x44,0x08,0x44,0x08,0x7C,0x08,
 0x44,0x88,0x44,0x48,0x44,0x48,0x44,0x08,0x7C,0x08,0x44,0x08,0x00,0x28,0x00,0x10},//"时"字模11
};
 
 
/************************************************************************************************/
/*“视觉模块识别开始”字模数据*/ 
uint8_t Chinese_Character_7[8][32] = 
{
{0x20,0x00,0x11,0xFC,0x11,0x04,0xF9,0x04,0x09,0x24,0x11,0x24,0x11,0x24,0x39,0x24,
 0x55,0x24,0x95,0x54,0x10,0x50,0x10,0x90,0x10,0x90,0x11,0x12,0x12,0x12,0x14,0x0E},//"视"字模0

{0x22,0x08,0x11,0x10,0x00,0x20,0x7F,0xFE,0x40,0x02,0x80,0x04,0x1F,0xF0,0x10,0x10,
 0x11,0x10,0x11,0x10,0x11,0x10,0x12,0x90,0x02,0x80,0x04,0x84,0x18,0x84,0x60,0x7C},//"觉"字模1

{0x11,0x10,0x11,0x10,0x17,0xFC,0x11,0x10,0xFC,0x00,0x13,0xF8,0x32,0x08,0x3B,0xF8,
 0x56,0x08,0x53,0xF8,0x90,0x40,0x17,0xFC,0x10,0xA0,0x11,0x10,0x12,0x08,0x14,0x06},//"模"字模2

{0x10,0x40,0x10,0x40,0x10,0x40,0x13,0xFC,0x10,0x44,0xFC,0x44,0x10,0x44,0x10,0x44,
 0x13,0xFE,0x10,0x40,0x10,0xA0,0x1C,0xA0,0xE1,0x10,0x42,0x08,0x04,0x04,0x08,0x02},//"块"字模3

{0x00,0x00,0x20,0x00,0x11,0xFC,0x11,0x04,0x01,0x04,0x01,0x04,0xF1,0x04,0x11,0x04,
 0x11,0xFC,0x11,0x04,0x10,0x00,0x14,0x90,0x18,0x88,0x11,0x04,0x02,0x02,0x04,0x02},//"识"字模4

{0x00,0x04,0x7F,0x04,0x41,0x04,0x41,0x24,0x41,0x24,0x7F,0x24,0x10,0x24,0x10,0x24,
 0xFF,0x24,0x11,0x24,0x11,0x24,0x11,0x24,0x21,0x04,0x21,0x04,0x4A,0x14,0x84,0x08},//"别"字模5

{0x00,0x00,0x7F,0xFC,0x08,0x20,0x08,0x20,0x08,0x20,0x08,0x20,0x08,0x20,0xFF,0xFE,
 0x08,0x20,0x08,0x20,0x08,0x20,0x08,0x20,0x10,0x20,0x10,0x20,0x20,0x20,0x40,0x20},//"开"字模6

{0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x40,0xFC,0x48,0x24,0x84,0x25,0xFE,0x24,0x82,
 0x24,0x00,0x48,0xFC,0x28,0x84,0x10,0x84,0x28,0x84,0x44,0x84,0x80,0xFC,0x00,0x84}//"始"字模7
};

/************************************************************************************************/
/*“向视觉模块发送识别指令超时”字模数据*/ 
uint8_t Chinese_Character_8[13][32] =
{
{0x02,0x00,0x04,0x00,0x08,0x00,0x7F,0xFC,0x40,0x04,0x40,0x04,0x47,0xC4,0x44,0x44,
 0x44,0x44,0x44,0x44,0x44,0x44,0x47,0xC4,0x44,0x44,0x40,0x04,0x40,0x14,0x40,0x08},//"向"字模0

{0x20,0x00,0x11,0xFC,0x11,0x04,0xF9,0x04,0x09,0x24,0x11,0x24,0x11,0x24,0x39,0x24,
 0x55,0x24,0x95,0x54,0x10,0x50,0x10,0x90,0x10,0x90,0x11,0x12,0x12,0x12,0x14,0x0E},//"视"字模1

{0x22,0x08,0x11,0x10,0x00,0x20,0x7F,0xFE,0x40,0x02,0x80,0x04,0x1F,0xF0,0x10,0x10,
 0x11,0x10,0x11,0x10,0x11,0x10,0x12,0x90,0x02,0x80,0x04,0x84,0x18,0x84,0x60,0x7C},//"觉"字模2

{0x11,0x10,0x11,0x10,0x17,0xFC,0x11,0x10,0xFC,0x00,0x13,0xF8,0x32,0x08,0x3B,0xF8,
 0x56,0x08,0x53,0xF8,0x90,0x40,0x17,0xFC,0x10,0xA0,0x11,0x10,0x12,0x08,0x14,0x06},//"模"字模3

{0x10,0x40,0x10,0x40,0x10,0x40,0x13,0xFC,0x10,0x44,0xFC,0x44,0x10,0x44,0x10,0x44,
 0x13,0xFE,0x10,0x40,0x10,0xA0,0x1C,0xA0,0xE1,0x10,0x42,0x08,0x04,0x04,0x08,0x02},//"块"字模4

{0x01,0x00,0x11,0x10,0x11,0x08,0x22,0x00,0x3F,0xFC,0x02,0x00,0x04,0x00,0x07,0xF8,
 0x0A,0x08,0x09,0x08,0x11,0x10,0x10,0xA0,0x20,0x40,0x40,0xA0,0x03,0x18,0x1C,0x06},//"发"字模5

{0x02,0x08,0x21,0x08,0x11,0x10,0x17,0xFC,0x00,0x40,0x00,0x40,0xF0,0x40,0x17,0xFE,
 0x10,0x40,0x10,0xA0,0x10,0x90,0x11,0x08,0x12,0x08,0x28,0x00,0x47,0xFE,0x00,0x00},//"送"字模6

{0x00,0x00,0x20,0x00,0x11,0xFC,0x11,0x04,0x01,0x04,0x01,0x04,0xF1,0x04,0x11,0x04,
 0x11,0xFC,0x11,0x04,0x10,0x00,0x14,0x90,0x18,0x88,0x11,0x04,0x02,0x02,0x04,0x02},//"识"字模7

{0x00,0x04,0x7F,0x04,0x41,0x04,0x41,0x24,0x41,0x24,0x7F,0x24,0x10,0x24,0x10,0x24,
 0xFF,0x24,0x11,0x24,0x11,0x24,0x11,0x24,0x21,0x04,0x21,0x04,0x4A,0x14,0x84,0x08},//"别"字模8

{0x11,0x00,0x11,0x04,0x11,0x38,0x11,0xC0,0xFD,0x02,0x11,0x02,0x10,0xFE,0x14,0x00,
 0x19,0xFC,0x31,0x04,0xD1,0x04,0x11,0xFC,0x11,0x04,0x11,0x04,0x51,0xFC,0x21,0x04},//"指"字模9

{0x01,0x00,0x01,0x00,0x02,0x80,0x04,0x40,0x0A,0x20,0x11,0x10,0x21,0x08,0xC0,0x06,
 0x1F,0xF0,0x00,0x10,0x00,0x20,0x04,0x40,0x02,0x80,0x01,0x00,0x00,0x80,0x00,0x80},//"令"字模10

{0x08,0x00,0x09,0xFC,0x08,0x44,0x7E,0x44,0x08,0x44,0x08,0x94,0xFF,0x08,0x08,0xFC,
 0x28,0x84,0x28,0x84,0x2E,0x84,0x28,0xFC,0x28,0x00,0x58,0x00,0x4F,0xFE,0x80,0x00},//"超"字模11

{0x00,0x08,0x00,0x08,0x7C,0x08,0x44,0x08,0x45,0xFE,0x44,0x08,0x44,0x08,0x7C,0x08,
 0x44,0x88,0x44,0x48,0x44,0x48,0x44,0x08,0x7C,0x08,0x44,0x08,0x00,0x28,0x00,0x10},//"时"字模12 
};



/************************************************************************************************/
/*“视觉模块识别结束”字模数据*/ 
uint8_t Chinese_Character_9[8][32] = 
{
{0x20,0x00,0x11,0xFC,0x11,0x04,0xF9,0x04,0x09,0x24,0x11,0x24,0x11,0x24,0x39,0x24,
 0x55,0x24,0x95,0x54,0x10,0x50,0x10,0x90,0x10,0x90,0x11,0x12,0x12,0x12,0x14,0x0E},//"视"字模0

{0x22,0x08,0x11,0x10,0x00,0x20,0x7F,0xFE,0x40,0x02,0x80,0x04,0x1F,0xF0,0x10,0x10,
 0x11,0x10,0x11,0x10,0x11,0x10,0x12,0x90,0x02,0x80,0x04,0x84,0x18,0x84,0x60,0x7C},//"觉"字模1

{0x11,0x10,0x11,0x10,0x17,0xFC,0x11,0x10,0xFC,0x00,0x13,0xF8,0x32,0x08,0x3B,0xF8,
 0x56,0x08,0x53,0xF8,0x90,0x40,0x17,0xFC,0x10,0xA0,0x11,0x10,0x12,0x08,0x14,0x06},//"模"字模2

{0x10,0x40,0x10,0x40,0x10,0x40,0x13,0xFC,0x10,0x44,0xFC,0x44,0x10,0x44,0x10,0x44,
 0x13,0xFE,0x10,0x40,0x10,0xA0,0x1C,0xA0,0xE1,0x10,0x42,0x08,0x04,0x04,0x08,0x02},//"块"字模3

{0x00,0x00,0x20,0x00,0x11,0xFC,0x11,0x04,0x01,0x04,0x01,0x04,0xF1,0x04,0x11,0x04,
 0x11,0xFC,0x11,0x04,0x10,0x00,0x14,0x90,0x18,0x88,0x11,0x04,0x02,0x02,0x04,0x02},//"识"字模4

{0x00,0x04,0x7F,0x04,0x41,0x04,0x41,0x24,0x41,0x24,0x7F,0x24,0x10,0x24,0x10,0x24,
 0xFF,0x24,0x11,0x24,0x11,0x24,0x11,0x24,0x21,0x04,0x21,0x04,0x4A,0x14,0x84,0x08},//"别"字模5

{0x10,0x20,0x10,0x20,0x20,0x20,0x27,0xFE,0x44,0x20,0xF8,0x20,0x11,0xFC,0x20,0x00,
 0x40,0x00,0xFD,0xFC,0x41,0x04,0x01,0x04,0x1D,0x04,0xE1,0x04,0x41,0xFC,0x01,0x04},//"结"字模6

{0x01,0x00,0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,
 0x21,0x08,0x3F,0xF8,0x23,0x88,0x05,0x40,0x09,0x20,0x31,0x18,0xC1,0x06,0x01,0x00}//"束"字模7
};




/************************************************************************************************/
/*“接收视觉模块识别数据超时”字模数据*/ 
uint8_t Chinese_Character_10[12][32] =
{
{0x10,0x80,0x10,0x40,0x13,0xFC,0x10,0x00,0xFD,0x08,0x10,0x90,0x17,0xFE,0x10,0x40,
 0x18,0x40,0x37,0xFE,0xD0,0x88,0x11,0x08,0x10,0x90,0x10,0x60,0x51,0x98,0x26,0x04},//"接"字模0

{0x08,0x40,0x08,0x40,0x48,0x40,0x48,0x80,0x48,0xFE,0x49,0x08,0x4A,0x88,0x48,0x88,
 0x48,0x88,0x58,0x50,0x68,0x50,0x48,0x20,0x08,0x50,0x08,0x88,0x09,0x04,0x0A,0x02},//"收"字模1

{0x20,0x00,0x11,0xFC,0x11,0x04,0xF9,0x04,0x09,0x24,0x11,0x24,0x11,0x24,0x39,0x24,
 0x55,0x24,0x95,0x54,0x10,0x50,0x10,0x90,0x10,0x90,0x11,0x12,0x12,0x12,0x14,0x0E},//"视"字模2

{0x22,0x08,0x11,0x10,0x00,0x20,0x7F,0xFE,0x40,0x02,0x80,0x04,0x1F,0xF0,0x10,0x10,
 0x11,0x10,0x11,0x10,0x11,0x10,0x12,0x90,0x02,0x80,0x04,0x84,0x18,0x84,0x60,0x7C},//"觉"字模3

{0x11,0x10,0x11,0x10,0x17,0xFC,0x11,0x10,0xFC,0x00,0x13,0xF8,0x32,0x08,0x3B,0xF8,
 0x56,0x08,0x53,0xF8,0x90,0x40,0x17,0xFC,0x10,0xA0,0x11,0x10,0x12,0x08,0x14,0x06},//"模"字模4

{0x10,0x40,0x10,0x40,0x10,0x40,0x13,0xFC,0x10,0x44,0xFC,0x44,0x10,0x44,0x10,0x44,
 0x13,0xFE,0x10,0x40,0x10,0xA0,0x1C,0xA0,0xE1,0x10,0x42,0x08,0x04,0x04,0x08,0x02},//"块"字模5

{0x00,0x00,0x20,0x00,0x11,0xFC,0x11,0x04,0x01,0x04,0x01,0x04,0xF1,0x04,0x11,0x04,
 0x11,0xFC,0x11,0x04,0x10,0x00,0x14,0x90,0x18,0x88,0x11,0x04,0x02,0x02,0x04,0x02},//"识"字模6

{0x00,0x04,0x7F,0x04,0x41,0x04,0x41,0x24,0x41,0x24,0x7F,0x24,0x10,0x24,0x10,0x24,
 0xFF,0x24,0x11,0x24,0x11,0x24,0x11,0x24,0x21,0x04,0x21,0x04,0x4A,0x14,0x84,0x08},//"别"字模7

{0x08,0x20,0x49,0x20,0x2A,0x20,0x08,0x3E,0xFF,0x44,0x2A,0x44,0x49,0x44,0x88,0xA4,
 0x10,0x28,0xFE,0x28,0x22,0x10,0x42,0x10,0x64,0x28,0x18,0x28,0x34,0x44,0xC2,0x82},//"数"字模8

{0x20,0x00,0x23,0xFC,0x22,0x04,0x22,0x04,0xFB,0xFC,0x22,0x20,0x22,0x20,0x2B,0xFE,
 0x32,0x20,0xE2,0x20,0x22,0xFC,0x22,0x84,0x22,0x84,0x24,0x84,0xA4,0xFC,0x48,0x84},//"据"字模9

{0x08,0x00,0x09,0xFC,0x08,0x44,0x7E,0x44,0x08,0x44,0x08,0x94,0xFF,0x08,0x08,0xFC,
 0x28,0x84,0x28,0x84,0x2E,0x84,0x28,0xFC,0x28,0x00,0x58,0x00,0x4F,0xFE,0x80,0x00},//"超"字模10

{0x00,0x08,0x00,0x08,0x7C,0x08,0x44,0x08,0x45,0xFE,0x44,0x08,0x44,0x08,0x7C,0x08,
 0x44,0x88,0x44,0x48,0x44,0x48,0x44,0x08,0x7C,0x08,0x44,0x08,0x00,0x28,0x00,0x10},//"时"字模11 
};



/************************************************************************************************/
/*“机械手执行操作”字模数据*/ 
uint8_t Chinese_Character_11[7][32] =
{
{0x10,0x00,0x11,0xF0,0x11,0x10,0x11,0x10,0xFD,0x10,0x11,0x10,0x31,0x10,0x39,0x10,
 0x55,0x10,0x55,0x10,0x91,0x10,0x11,0x12,0x11,0x12,0x12,0x12,0x12,0x0E,0x14,0x00},//"机"字模0

{0x10,0x10,0x10,0x14,0x10,0x12,0x10,0x10,0xFB,0xFE,0x10,0x10,0x31,0x50,0x39,0x54,
 0x57,0xF4,0x51,0x54,0x91,0x54,0x11,0x48,0x12,0x4A,0x12,0x5A,0x14,0x26,0x10,0x42},//"械"字模1

{0x00,0x10,0x00,0xF8,0x3F,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,
 0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x05,0x00,0x02,0x00},//"手"字模2

{0x10,0x40,0x10,0x40,0x10,0x40,0x10,0x40,0xFD,0xF8,0x10,0x48,0x10,0x48,0x14,0x48,
 0x19,0x48,0x30,0xC8,0xD0,0x48,0x10,0xA8,0x10,0xAA,0x11,0x0A,0x52,0x06,0x24,0x02},//"执"字模3

{0x08,0x00,0x09,0xFC,0x10,0x00,0x20,0x00,0x48,0x00,0x08,0x00,0x13,0xFE,0x30,0x20,
 0x50,0x20,0x90,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0xA0,0x10,0x40},//"行"字模4

{0x23,0xF8,0x22,0x08,0x22,0x08,0x23,0xF8,0xF8,0x00,0x27,0xBC,0x24,0xA4,0x2C,0xA4,
 0x37,0xBC,0xE0,0x40,0x2F,0xFE,0x21,0x60,0x22,0x50,0x24,0x48,0xB8,0x46,0x40,0x40},//"操"字模5

{0x09,0x00,0x09,0x00,0x09,0x00,0x11,0xFE,0x12,0x80,0x32,0x80,0x34,0x80,0x50,0xF8,
 0x90,0x80,0x10,0x80,0x10,0x80,0x10,0xFC,0x10,0x80,0x10,0x80,0x10,0x80,0x10,0x80}//"作"字模6
};




/************************************************************************************************/
/*“向机械手发送执行指令超时”字模数据*/ 
uint8_t Chinese_Character_12[12][32] =
{
{0x02,0x00,0x04,0x00,0x08,0x00,0x7F,0xFC,0x40,0x04,0x40,0x04,0x47,0xC4,0x44,0x44,
 0x44,0x44,0x44,0x44,0x44,0x44,0x47,0xC4,0x44,0x44,0x40,0x04,0x40,0x14,0x40,0x08},//"向"字模0

{0x10,0x00,0x11,0xF0,0x11,0x10,0x11,0x10,0xFD,0x10,0x11,0x10,0x31,0x10,0x39,0x10,
 0x55,0x10,0x55,0x10,0x91,0x10,0x11,0x12,0x11,0x12,0x12,0x12,0x12,0x0E,0x14,0x00},//"机"字模1

{0x10,0x10,0x10,0x14,0x10,0x12,0x10,0x10,0xFB,0xFE,0x10,0x10,0x31,0x50,0x39,0x54,
 0x57,0xF4,0x51,0x54,0x91,0x54,0x11,0x48,0x12,0x4A,0x12,0x5A,0x14,0x26,0x10,0x42},//"械"字模2

{0x00,0x10,0x00,0xF8,0x3F,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,
 0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x05,0x00,0x02,0x00},//"手"字模3

{0x01,0x00,0x11,0x10,0x11,0x08,0x22,0x00,0x3F,0xFC,0x02,0x00,0x04,0x00,0x07,0xF8,
 0x0A,0x08,0x09,0x08,0x11,0x10,0x10,0xA0,0x20,0x40,0x40,0xA0,0x03,0x18,0x1C,0x06},//"发"字模4

{0x02,0x08,0x21,0x08,0x11,0x10,0x17,0xFC,0x00,0x40,0x00,0x40,0xF0,0x40,0x17,0xFE,
 0x10,0x40,0x10,0xA0,0x10,0x90,0x11,0x08,0x12,0x08,0x28,0x00,0x47,0xFE,0x00,0x00},//"送"字模5

{0x10,0x40,0x10,0x40,0x10,0x40,0x10,0x40,0xFD,0xF8,0x10,0x48,0x10,0x48,0x14,0x48,
 0x19,0x48,0x30,0xC8,0xD0,0x48,0x10,0xA8,0x10,0xAA,0x11,0x0A,0x52,0x06,0x24,0x02},//"执"字模6

{0x08,0x00,0x09,0xFC,0x10,0x00,0x20,0x00,0x48,0x00,0x08,0x00,0x13,0xFE,0x30,0x20,
 0x50,0x20,0x90,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0xA0,0x10,0x40},//"行"字模7

{0x11,0x00,0x11,0x04,0x11,0x38,0x11,0xC0,0xFD,0x02,0x11,0x02,0x10,0xFE,0x14,0x00,
 0x19,0xFC,0x31,0x04,0xD1,0x04,0x11,0xFC,0x11,0x04,0x11,0x04,0x51,0xFC,0x21,0x04},//"指"字模8

{0x01,0x00,0x01,0x00,0x02,0x80,0x04,0x40,0x0A,0x20,0x11,0x10,0x21,0x08,0xC0,0x06,
 0x1F,0xF0,0x00,0x10,0x00,0x20,0x04,0x40,0x02,0x80,0x01,0x00,0x00,0x80,0x00,0x80},//"令"字模9

{0x08,0x00,0x09,0xFC,0x08,0x44,0x7E,0x44,0x08,0x44,0x08,0x94,0xFF,0x08,0x08,0xFC,
 0x28,0x84,0x28,0x84,0x2E,0x84,0x28,0xFC,0x28,0x00,0x58,0x00,0x4F,0xFE,0x80,0x00},//"超"字模10

{0x00,0x08,0x00,0x08,0x7C,0x08,0x44,0x08,0x45,0xFE,0x44,0x08,0x44,0x08,0x7C,0x08,
 0x44,0x88,0x44,0x48,0x44,0x48,0x44,0x08,0x7C,0x08,0x44,0x08,0x00,0x28,0x00,0x10},//"时"字模11
};




/************************************************************************************************/
/*“机械手执行完毕”字模数据*/ 
uint8_t Chinese_Character_13[7][32] =
{
{0x10,0x00,0x11,0xF0,0x11,0x10,0x11,0x10,0xFD,0x10,0x11,0x10,0x31,0x10,0x39,0x10,
 0x55,0x10,0x55,0x10,0x91,0x10,0x11,0x12,0x11,0x12,0x12,0x12,0x12,0x0E,0x14,0x00},//"机"字模0

{0x10,0x10,0x10,0x14,0x10,0x12,0x10,0x10,0xFB,0xFE,0x10,0x10,0x31,0x50,0x39,0x54,
 0x57,0xF4,0x51,0x54,0x91,0x54,0x11,0x48,0x12,0x4A,0x12,0x5A,0x14,0x26,0x10,0x42},//"械"字模1

{0x00,0x10,0x00,0xF8,0x3F,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,
 0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x05,0x00,0x02,0x00},//"手"字模2

{0x10,0x40,0x10,0x40,0x10,0x40,0x10,0x40,0xFD,0xF8,0x10,0x48,0x10,0x48,0x14,0x48,
 0x19,0x48,0x30,0xC8,0xD0,0x48,0x10,0xA8,0x10,0xAA,0x11,0x0A,0x52,0x06,0x24,0x02},//"执"字模3

{0x08,0x00,0x09,0xFC,0x10,0x00,0x20,0x00,0x48,0x00,0x08,0x00,0x13,0xFE,0x30,0x20,
 0x50,0x20,0x90,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0xA0,0x10,0x40},//"行"字模4

{0x02,0x00,0x01,0x00,0x7F,0xFE,0x40,0x02,0x80,0x04,0x1F,0xF0,0x00,0x00,0x00,0x00,
 0x7F,0xFC,0x04,0x40,0x04,0x40,0x04,0x40,0x08,0x44,0x08,0x44,0x10,0x44,0x60,0x3C},//"完"字模5

{0x20,0x80,0x20,0x88,0x20,0xB0,0x3E,0xC0,0x20,0x80,0x20,0x84,0x26,0x84,0x38,0x7C,
 0x21,0x00,0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00}//"毕"字模6
};




/************************************************************************************************/
/*“接收机械手执行数据超时”字模数据*/ 
uint8_t Chinese_Character_14[11][32] =
{
{0x10,0x80,0x10,0x40,0x13,0xFC,0x10,0x00,0xFD,0x08,0x10,0x90,0x17,0xFE,0x10,0x40,
 0x18,0x40,0x37,0xFE,0xD0,0x88,0x11,0x08,0x10,0x90,0x10,0x60,0x51,0x98,0x26,0x04},//"接"字模0

{0x08,0x40,0x08,0x40,0x48,0x40,0x48,0x80,0x48,0xFE,0x49,0x08,0x4A,0x88,0x48,0x88,
 0x48,0x88,0x58,0x50,0x68,0x50,0x48,0x20,0x08,0x50,0x08,0x88,0x09,0x04,0x0A,0x02},//"收"字模1

{0x10,0x00,0x11,0xF0,0x11,0x10,0x11,0x10,0xFD,0x10,0x11,0x10,0x31,0x10,0x39,0x10,
 0x55,0x10,0x55,0x10,0x91,0x10,0x11,0x12,0x11,0x12,0x12,0x12,0x12,0x0E,0x14,0x00},//"机"字模2

{0x10,0x10,0x10,0x14,0x10,0x12,0x10,0x10,0xFB,0xFE,0x10,0x10,0x31,0x50,0x39,0x54,
 0x57,0xF4,0x51,0x54,0x91,0x54,0x11,0x48,0x12,0x4A,0x12,0x5A,0x14,0x26,0x10,0x42},//"械"字模3

{0x00,0x10,0x00,0xF8,0x3F,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,
 0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x05,0x00,0x02,0x00},//"手"字模4

{0x10,0x40,0x10,0x40,0x10,0x40,0x10,0x40,0xFD,0xF8,0x10,0x48,0x10,0x48,0x14,0x48,
 0x19,0x48,0x30,0xC8,0xD0,0x48,0x10,0xA8,0x10,0xAA,0x11,0x0A,0x52,0x06,0x24,0x02},//"执"字模5

{0x08,0x00,0x09,0xFC,0x10,0x00,0x20,0x00,0x48,0x00,0x08,0x00,0x13,0xFE,0x30,0x20,
 0x50,0x20,0x90,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0xA0,0x10,0x40},//"行"字模6

{0x08,0x20,0x49,0x20,0x2A,0x20,0x08,0x3E,0xFF,0x44,0x2A,0x44,0x49,0x44,0x88,0xA4,
 0x10,0x28,0xFE,0x28,0x22,0x10,0x42,0x10,0x64,0x28,0x18,0x28,0x34,0x44,0xC2,0x82},//"数"字模7

{0x20,0x00,0x23,0xFC,0x22,0x04,0x22,0x04,0xFB,0xFC,0x22,0x20,0x22,0x20,0x2B,0xFE,
 0x32,0x20,0xE2,0x20,0x22,0xFC,0x22,0x84,0x22,0x84,0x24,0x84,0xA4,0xFC,0x48,0x84},//"据"字模8

{0x08,0x00,0x09,0xFC,0x08,0x44,0x7E,0x44,0x08,0x44,0x08,0x94,0xFF,0x08,0x08,0xFC,
 0x28,0x84,0x28,0x84,0x2E,0x84,0x28,0xFC,0x28,0x00,0x58,0x00,0x4F,0xFE,0x80,0x00},//"超"字模9

{0x00,0x08,0x00,0x08,0x7C,0x08,0x44,0x08,0x45,0xFE,0x44,0x08,0x44,0x08,0x7C,0x08,
 0x44,0x88,0x44,0x48,0x44,0x48,0x44,0x08,0x7C,0x08,0x44,0x08,0x00,0x28,0x00,0x10},//"时"字模10
};




/************************************************************************************************/
/*“识别到红色”字模数据*/ 
uint8_t Chinese_Character_15[5][32] =
{
{0x00,0x00,0x20,0x00,0x11,0xFC,0x11,0x04,0x01,0x04,0x01,0x04,0xF1,0x04,0x11,0x04,
 0x11,0xFC,0x11,0x04,0x10,0x00,0x14,0x90,0x18,0x88,0x11,0x04,0x02,0x02,0x04,0x02},//"识"字模0

{0x00,0x04,0x7F,0x04,0x41,0x04,0x41,0x24,0x41,0x24,0x7F,0x24,0x10,0x24,0x10,0x24,
 0xFF,0x24,0x11,0x24,0x11,0x24,0x11,0x24,0x21,0x04,0x21,0x04,0x4A,0x14,0x84,0x08},//"别"字模1

{0x00,0x04,0xFF,0x84,0x08,0x04,0x10,0x24,0x22,0x24,0x41,0x24,0xFF,0xA4,0x08,0xA4,
 0x08,0x24,0x08,0x24,0x7F,0x24,0x08,0x24,0x08,0x04,0x0F,0x84,0xF8,0x14,0x40,0x08},//"到"字模2

{0x10,0x00,0x10,0x00,0x21,0xFC,0x24,0x20,0x44,0x20,0xF8,0x20,0x10,0x20,0x20,0x20,
 0x40,0x20,0xFC,0x20,0x40,0x20,0x00,0x20,0x1C,0x20,0xE0,0x20,0x43,0xFE,0x00,0x00},//"红"字模3

{0x08,0x00,0x08,0x00,0x1F,0xE0,0x20,0x20,0x40,0x40,0xBF,0xF8,0x21,0x08,0x21,0x08,
 0x21,0x08,0x3F,0xF8,0x20,0x00,0x20,0x02,0x20,0x02,0x20,0x02,0x1F,0xFE,0x00,0x00},//"色"字模4
};




/************************************************************************************************/
/*“识别到绿色”字模数据*/ 
uint8_t Chinese_Character_16[6][32] =
{
{0x00,0x00,0x20,0x00,0x11,0xFC,0x11,0x04,0x01,0x04,0x01,0x04,0xF1,0x04,0x11,0x04,
 0x11,0xFC,0x11,0x04,0x10,0x00,0x14,0x90,0x18,0x88,0x11,0x04,0x02,0x02,0x04,0x02},//"识"字模0

{0x00,0x04,0x7F,0x04,0x41,0x04,0x41,0x24,0x41,0x24,0x7F,0x24,0x10,0x24,0x10,0x24,
 0xFF,0x24,0x11,0x24,0x11,0x24,0x11,0x24,0x21,0x04,0x21,0x04,0x4A,0x14,0x84,0x08},//"别"字模1

{0x00,0x04,0xFF,0x84,0x08,0x04,0x10,0x24,0x22,0x24,0x41,0x24,0xFF,0xA4,0x08,0xA4,
 0x08,0x24,0x08,0x24,0x7F,0x24,0x08,0x24,0x08,0x04,0x0F,0x84,0xF8,0x14,0x40,0x08},//"到"字模2

{0x10,0x00,0x11,0xF8,0x20,0x08,0x20,0x08,0x49,0xF8,0xF8,0x08,0x10,0x08,0x23,0xFE,
 0x40,0x20,0xFA,0x22,0x41,0x74,0x00,0xA8,0x19,0x24,0xE2,0x22,0x40,0xA0,0x00,0x40},//"绿"字模3

{0x08,0x00,0x08,0x00,0x1F,0xE0,0x20,0x20,0x40,0x40,0xBF,0xF8,0x21,0x08,0x21,0x08,
 0x21,0x08,0x3F,0xF8,0x20,0x00,0x20,0x02,0x20,0x02,0x20,0x02,0x1F,0xFE,0x00,0x00},//"色"字模4
};




/************************************************************************************************/
/*“该物体的颜色不在识别范围内”字模数据*/ 
uint8_t Chinese_Character_17[13][32] =
{
{0x00,0x80,0x40,0x40,0x2F,0xFE,0x20,0x80,0x01,0x10,0x01,0x10,0xE2,0x24,0x27,0xE4,
 0x20,0x48,0x20,0x88,0x21,0x10,0x2A,0x20,0x34,0x50,0x20,0x88,0x03,0x04,0x0C,0x04},//"该"字模0

{0x10,0x80,0x10,0x80,0x50,0x80,0x50,0xFC,0x7D,0x54,0x52,0x54,0x90,0x54,0x10,0x94,
 0x1C,0x94,0xF1,0x24,0x52,0x24,0x10,0x44,0x10,0x44,0x10,0x84,0x11,0x28,0x10,0x10},//"物"字模1

{0x08,0x40,0x08,0x40,0x08,0x40,0x10,0x40,0x17,0xFC,0x30,0x40,0x30,0xE0,0x50,0xE0,
 0x91,0x50,0x11,0x50,0x12,0x48,0x15,0xF4,0x18,0x42,0x10,0x40,0x10,0x40,0x10,0x40},//"体"字模2

{0x10,0x40,0x10,0x40,0x20,0x40,0x7E,0x7C,0x42,0x84,0x42,0x84,0x43,0x04,0x42,0x44,
 0x7E,0x24,0x42,0x24,0x42,0x04,0x42,0x04,0x42,0x04,0x7E,0x04,0x42,0x28,0x00,0x10},//"的"字模3

{0x10,0x00,0x08,0xFE,0x7F,0x10,0x22,0x20,0x14,0x7C,0x7F,0x44,0x44,0x54,0x48,0x54,
 0x52,0x54,0x44,0x54,0x48,0x54,0x51,0x54,0x42,0x28,0x44,0x24,0x88,0x42,0x30,0x82},//"颜"字模4

{0x08,0x00,0x08,0x00,0x1F,0xE0,0x20,0x20,0x40,0x40,0xBF,0xF8,0x21,0x08,0x21,0x08,
 0x21,0x08,0x3F,0xF8,0x20,0x00,0x20,0x02,0x20,0x02,0x20,0x02,0x1F,0xFE,0x00,0x00},//"色"字模5

{0x00,0x00,0x7F,0xFC,0x00,0x80,0x00,0x80,0x01,0x00,0x01,0x00,0x03,0x40,0x05,0x20,
 0x09,0x10,0x11,0x08,0x21,0x04,0x41,0x04,0x81,0x00,0x01,0x00,0x01,0x00,0x01,0x00},//"不"字模6

{0x02,0x00,0x02,0x00,0x04,0x00,0xFF,0xFE,0x08,0x00,0x08,0x40,0x10,0x40,0x30,0x40,
 0x57,0xFC,0x90,0x40,0x10,0x40,0x10,0x40,0x10,0x40,0x10,0x40,0x1F,0xFE,0x10,0x00},//"在"字模7

{0x00,0x00,0x20,0x00,0x11,0xFC,0x11,0x04,0x01,0x04,0x01,0x04,0xF1,0x04,0x11,0x04,
 0x11,0xFC,0x11,0x04,0x10,0x00,0x14,0x90,0x18,0x88,0x11,0x04,0x02,0x02,0x04,0x02},//"识"字模8

{0x00,0x04,0x7F,0x04,0x41,0x04,0x41,0x24,0x41,0x24,0x7F,0x24,0x10,0x24,0x10,0x24,
 0xFF,0x24,0x11,0x24,0x11,0x24,0x11,0x24,0x21,0x04,0x21,0x04,0x4A,0x14,0x84,0x08},//"别"字模9

{0x04,0x40,0x04,0x40,0xFF,0xFE,0x04,0x40,0x10,0x00,0x09,0xF8,0x49,0x08,0x21,0x08,
 0x25,0x08,0x05,0x28,0x09,0x10,0x71,0x02,0x11,0x02,0x11,0x02,0x10,0xFE,0x00,0x00},//"范"字模10

{0x00,0x00,0x7F,0xFC,0x41,0x04,0x41,0x04,0x5F,0xF4,0x41,0x04,0x4F,0xE4,0x41,0x04,
 0x5F,0xF4,0x41,0x14,0x41,0x14,0x41,0x54,0x41,0x24,0x41,0x04,0x7F,0xFC,0x40,0x04},//"围"字模11

{0x01,0x00,0x01,0x00,0x01,0x00,0x7F,0xFC,0x41,0x04,0x41,0x04,0x41,0x04,0x42,0x84,
 0x42,0x44,0x44,0x24,0x48,0x14,0x50,0x14,0x40,0x04,0x40,0x04,0x40,0x14,0x40,0x08},//"内"字模12
};




/************************************************************************************************/
/*“系统停止运行！”字模数据*/ 
uint8_t Chinese_Character_18[7][32] =
{
{0x00,0xF8,0x3F,0x00,0x04,0x00,0x08,0x20,0x10,0x40,0x3F,0x80,0x01,0x00,0x06,0x10,
 0x18,0x08,0x7F,0xFC,0x01,0x04,0x09,0x20,0x11,0x10,0x21,0x08,0x45,0x04,0x02,0x00},//"系"字模0

{0x10,0x40,0x10,0x20,0x20,0x20,0x23,0xFE,0x48,0x40,0xF8,0x88,0x11,0x04,0x23,0xFE,
 0x40,0x92,0xF8,0x90,0x40,0x90,0x00,0x90,0x19,0x12,0xE1,0x12,0x42,0x0E,0x04,0x00},//"统"字模1

{0x10,0x80,0x10,0x40,0x17,0xFC,0x20,0x00,0x23,0xF8,0x62,0x08,0x63,0xF8,0xA0,0x00,
 0x2F,0xFE,0x28,0x02,0x23,0xF8,0x20,0x40,0x20,0x40,0x20,0x40,0x21,0x40,0x20,0x80},//"停"字模2

{0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x11,0x00,0x11,0x00,0x11,0xF8,0x11,0x00,
 0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0xFF,0xFE,0x00,0x00},//"止"字模3

{0x00,0x00,0x23,0xF8,0x10,0x00,0x10,0x00,0x00,0x00,0x07,0xFC,0xF0,0x40,0x10,0x80,
 0x11,0x10,0x12,0x08,0x17,0xFC,0x12,0x04,0x10,0x00,0x28,0x00,0x47,0xFE,0x00,0x00},//"运"字模4

{0x08,0x00,0x09,0xFC,0x10,0x00,0x20,0x00,0x48,0x00,0x08,0x00,0x13,0xFE,0x30,0x20,
 0x50,0x20,0x90,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0xA0,0x10,0x40},//"行"字模5

{0x00,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,
 0x10,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x10,0x00,0x00,0x00,0x00,0x00},//"！"字模6
};




/**
	* @brief  显示单个中文字符，单个字符宽16个像素点。高16个像素点 
	* @param	Character，要输入字模数据的指针
	* @param  Row_Num，字符的行坐标，每行间隔16个像素点
	* @param  Column_Num，字符的列坐标，每列间隔16个像素点
  * @param  Color，字符的颜色
	* @retval 无
	*/
void Display_Chinese(uint8_t * Character ,uint8_t Row_Num ,uint8_t Column_Num ,uint16_t Color)
{
	uint16_t i,j;
	uint8_t ch;//存放字模中的十六进制数据
	
	for(i=0;i<16;i++)
	{
		for(j=0;j<8;j++)
		{
			ch = (Character[i*2]<<j);
			
			if ((ch & 0x80) == 0)
			{
				ILI9341_Draw_Point(i+1+((Row_Num-1)*16),j+1+((Column_Num-1)*16),BLACK);//显示一个黑色像素点
			}
			else
			{
				ILI9341_Draw_Point(i+1+((Row_Num-1)*16),j+1+((Column_Num-1)*16),Color);//显示一个对应颜色的像素点
			}
			
		}
		
		for(j=0;j<8;j++)
		{
			ch = (Character[i*2+1]<<j);
			
			if ((ch & 0x80) == 0)
			{
				ILI9341_Draw_Point(i+1+((Row_Num-1)*16),j+1+8+((Column_Num-1)*16),BLACK);//显示一个黑色像素点
			}
			else
			{
				ILI9341_Draw_Point(i+1+((Row_Num-1)*16),j+1+8+((Column_Num-1)*16),Color);//显示一个对应颜色的像素点
			}			
		}
		
	}	
}


/**
	* @brief  清除LCD液晶显示屏上指定行数里面的字符
	* @param  Row_Num，行坐标，每行间隔16个像素点
	* @retval 无
	*/
void Clean_Screen(uint8_t Row_Num)
{
	uint16_t i,j;
	uint8_t Column_Num = 1;//列坐标，初始值为1
	
	while(Column_Num < 21)//当列数为21时（即超出屏幕尺寸），则停止清屏
	{
		for(i=0;i<16;i++)
	  {
			for(j=0;j<8;j++)
			{
				ILI9341_Draw_Point(i+1+((Row_Num-1)*16),j+1+((Column_Num-1)*16),BLACK);//显示一个黑色像素点
			}
			
			for(j=0;j<8;j++)
			{		
				ILI9341_Draw_Point(i+1+((Row_Num-1)*16),j+1+8+((Column_Num-1)*16),BLACK);//显示一个黑色像素点			
			}	
	  }
		Column_Num++;
	}
}


/**
	* @brief  显示指定的中文字符
  * @param  (*Chinese_String)[32]，指定中文字模数据指针
	* @param  Word_Num，指定中文字符串个数
  * @param  Row_Num，指定中文字符串显示的行坐标
  * @param  Column_Num，指定中文字符串显示的列坐标
	* @param  Color，指定中文字符串显示颜色
	* @retval 无
	*/
void Display_Chinese_String( uint8_t (*Chinese_String)[32] ,uint8_t Word_Num ,uint8_t Row_Num ,uint8_t Column_Num ,uint16_t Color)
{
	uint8_t i;
	for(i=0;i<Word_Num;i++)
	{
		Display_Chinese(Chinese_String[i], Row_Num, i+Column_Num,Color); 
	}
}


/**
	* @brief  显示闪烁的矩形，蜂鸣器响起，起到警示作用
						当STM32主控板与模块间通信超时或按下急停按
						钮K1时，使用该函数
	* @retval 无
	*/

void Display_Rectangle(void)
{
	while(1)
	{
		ILI9341_Draw_Rect(220,300,20, 20,RED);
		BUZZER_NO;
		SysTick_Delay_ms(100);
    ILI9341_Draw_Rect(220,300,20,20,BLACK);
		BUZZER_OFF;
		SysTick_Delay_ms(100);
	} 
}

