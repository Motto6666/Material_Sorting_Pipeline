import sensor,image,time
from find_max_blob import find_max_blob
from camera_init import camera_init
from receive_data import data_receive
from send_rtu_data import send_rtu_data

red_threshold = (0, 100, 21, 101, -12, 74)#设置红色阈值
green_threshold =(0, 100, -65, -17, -2, 51)#设置绿色阈值
white_thresholds =(48, 100, -31, 2, -17, 48)#设置白色阈值
openmv_add = 0x31
check = 0x41
recognize = 0x42
none = 0
red_color = 0x52
green_color = 0x47

camera_init()#初始化摄像头

while(1):
    data = data_receive(openmv_add,check)
    if( data != none ):#若接收到openmv_add,check数据后，跳出循环
        break

data = []#清除data数组里的内容，避免数据出错

while(1):

    while(1):
        data = data_receive(openmv_add,recognize)
        if( data != none ):#若接收到openmv_add,recognize数据后，跳出循环
            break
    time.sleep(10)
    img = sensor.snapshot().binary([white_thresholds], invert=False, zero=True) #获取一帧图片，并将图片上的白色强光去除
    max_blob =find_max_blob( img.find_blobs([red_threshold,green_threshold],pixles_threshold = 200,area_threshold = 200,merge = 1) )

    if(max_blob):
        if max_blob.code() == 1:#判断是否为红色
            send_rtu_data(red_color)
            print("识别到红色")

        elif max_blob.code() == 2:#判断是否为绿色
            send_rtu_data(green_color)
            print("识别到绿色")


#第一次接收数据
'''
while(1):
    if( uart3.any() ):
        receive = uart3.read()
        print(len(receive))#调试使用，调试完毕后删除!!
        print(receive)#调试使用，调试完毕后删除!!
        if(receive[0] == openmv_add and receive[1] == check):
            print("正确接收到主机发送的信息")
            uart3.write( receive)
            receive = []#清除数组数据类容
            break
'''

#第二次接收数据
'''
while(1):
    if( uart3.any() ):
        receive = uart3.read()
        print(len(receive))#调试使用，调试完毕后删除!!
        print(receive)#调试使用，调试完毕后删除!!
        if(receive[0] == openmv_add and receive[1] == recognize):
            print("正确接收到主机发送的信息")
            uart3.write( receive)
            break
'''
