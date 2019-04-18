import sensor,image

def camera_init():
    sensor.reset() #初始化摄像头
    sensor.set_pixformat(sensor.RGB565) #设置RGB图像格式
    sensor.set_framesize(sensor.QQVGA) #设置图像分辨率
    sensor.skip_frames(10,1000) #跳过10帧
    sensor.set_contrast(1) #设置对比度
    sensor.set_auto_whitebal(False) #关闭白平衡
