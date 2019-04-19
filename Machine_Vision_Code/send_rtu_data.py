import struct
from pyb import UART
uart3 = UART(3,115200) #设置通信串口P4、P5

address = 0x31
funtion = 0x42
data_len = 0x01
red_color = 0x52
red_crc_high = 0xA1
red_crc_low = 0x2E
green_color = 0x47
green_crc_high = 0x6E
green_crc_low = 0xEF
no_color = 0x4E
no_color_crc_high = 0x68
no_color_crc_low = 0x2F


def send_rtu_data(color):

    if(color == red_color):
        data = [address, funtion, data_len, red_color, red_crc_high, red_crc_low]
        rtu_data=struct.pack("%dB"%(len(data)),*data)#生成RTU数据帧

    elif(color == green_color):
        data = [address, funtion, data_len, green_color, green_crc_high, green_crc_low]
        rtu_data=struct.pack("%dB"%(len(data)),*data)#生成RTU数据帧

    else:
        data = [address, funtion, data_len, no_color, no_color_crc_high, no_color_crc_low]
        rtu_data=struct.pack("%dB"%(len(data)),*data)#生成RTU数据帧

    #print(rtu_data)
    uart3.write(rtu_data)
    data = []#清除data数组里的内容，避免数据出错
    rtu_data = []#清除rtu_data数组里的内容，避免数据出错


