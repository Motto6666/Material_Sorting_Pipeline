import sensor,image,time
from pyb import UART
from find_max_blob import find_max_blob
from camera_init import camera_init

Red_threshold = (0, 100, 21, 101, -12, 74)#设置红色阈值
Green_threshold =(0, 100, -65, -17, -2, 51)#设置绿色阈值
white_thresholds =(48, 100, -31, 2, -17, 48)#设置白色阈值
uart3 = UART(3,115200) #设置通信串口P4、P5

camera_init()#初始化摄像头

while(1):
    if( uart3.any() ):
        receive = uart3.read()
        print(len(receive))#调试使用，调试完毕后删除!!
        print(receive)#调试使用，调试完毕后删除!!

        if(receive[0] == 0x31 and receive[1] == 0x41):
            print("正确接收到主机发送的信息")
            uart3.write( receive)
            break


print("接收数据完毕")

while(1):
    img = sensor.snapshot().binary([white_thresholds], invert=False, zero=True) #获取一帧图片，并将图片上的白色强光去除
    max_blob =find_max_blob( img.find_blobs([Red_threshold,Green_threshold],pixles_threshold = 200,area_threshold = 200,merge = 1) )

    if(max_blob):
        if max_blob.code() == 1:#判断是否为红色
            img.draw_string(max_blob.x(),max_blob.y()-10,"RED",color = (255,0,0))
            img.draw_rectangle( max_blob.rect() )
            img.draw_cross( max_blob.cx(),max_blob.cy() )

        elif max_blob.code() == 2:#判断是否为绿色
            img.draw_string( max_blob.x(),max_blob.y()-10,"GREEN",color = (0,255,0) )
            img.draw_rectangle( max_blob.rect() )
            img.draw_cross( max_blob.cx(),max_blob.cy() )
