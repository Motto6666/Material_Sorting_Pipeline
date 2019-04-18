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
red_code = 1
green_code = 2
red_color = 0x52
green_color = 0x47
no_color = 0x4E

camera_init()#初始化摄像头

while(1):
    data = data_receive(openmv_add,check)
    if( data != none ):#判断是否接收到openmv_add,check指令
        break

data = []#清除data数组里的内容，避免数据出错

while(1):

    while(1):
        data = data_receive(openmv_add,recognize)
        if( data != none ):#判断是否接收到openmv_add,recognize指令
            break

    time.sleep(10)#等待10ms，保证STM32主控板已进入到接收数据的状态

    img = sensor.snapshot().binary([white_thresholds], invert=False, zero=True) #获取一帧图片，并将图片上的白色强光去除
    target_blob =find_max_blob( img.find_blobs([red_threshold,green_threshold],pixles_threshold = 200,area_threshold = 200,merge = 1) )#寻找目标色块

    if(target_blob):
        if target_blob.code() == red_code:
            send_rtu_data(red_color)
            print("识别到红色")

        elif target_blob.code() == green_code:
            send_rtu_data(green_color)
            print("识别到绿色")

    else:
        send_rtu_data(no_color)
        print("该物体不在识别范围内")
