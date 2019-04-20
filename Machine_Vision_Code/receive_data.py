from pyb import UART
uart3 = UART(3,115200) #设置通信串口P4、P5
ok = 0x04

def data_receive(add,function):
    if( uart3.any() ):
        data = uart3.read()
        #print(len(data))#调试使用，调试完毕后删除!!
        #print(data)#调试使用，调试完毕后删除!!
        if( (data[0] == add and data[1] == function)  or  data[1] == ok ):
            #print("正确接收到主机发送的信息")#调试使用，调试完毕后删除!!
            return data
    return 0

def data_send(data):
     uart3.write( data)
