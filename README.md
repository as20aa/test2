# 基于QMC5883传感器的驱动
## 项目目录
* i2c
* move
* robot_driver
* uart
* main
## 功能说明
本项目代码能够实现一次性对八个QMC5883传感器的驱动和数据的交互。通过转换函数和偏差修正函数产生可以用直接发送给机器人的控制信号，实现动作实时跟随。		
用户可以在main函数中写入send(num)函数将接收到的数据通过串口发送到上位机
