# 机器人动作跟随项目
## 文件目录结构
* 51单片机端
* STM32端
* 电脑端
## 文件目录介绍
* 51单片机端，同时驱动8个陀螺仪，并且获取行对于陀螺仪X轴的倾斜角度，并将数据打包发送到STM32端
* STM32端，接收51单片机所发送的数据，接收电脑发送过来数据，并整合处理数据，最后发送到机器人控制动作
* 电脑端，因为传感器检测的缺陷，电脑使用了摄像头作为人体动作跟踪的最后一个维度，并且将数据发送到STM32上
## bug
* 目前还没有实现我们的摄像头跟踪目标的算法，最终的路都指向了基于机器学习的特征工程，时间浪费比较多
* STM32的数据处理还需要等待电脑数据完成提取后才能调试，目前未上机

## 关于计算机视觉的一些问题
计算机视觉应用于物体时，主要有两种，一种是物体检测，一种是物体跟踪。两种有不同点，物体识别是主要是将图片中的物体识别并表示出来，类似于一个分类问题。物体追踪下面也分了两个部分，一个是纯粹地跟踪整个运动物体(Tracking)，一种是先经过识别是我们需要追踪的物体，然后再进行定位的方式(Detecting)，总的来说，tracking的算法比较容易，速度较快。detecting的算法往往包含了tracking的部分，但是实现的效果有些类似，算法比较复杂，而且运行起来也比较慢。		
目前有很多的算法可以用于跟踪目标物体，并且每年也会有比赛关于这些算法的优劣。		
anyway，如果想要实现对人手的追踪，有两种途径：一种是给手添加特殊的特征，即带上颜色鲜艳的手套，一种则是通过机器学习对手的特征进行提取，用于识别跟踪的程序中。目前识别跟踪的程序框架已经存在，只是训练数据没有获得，目前是比较几种机器学习的算法差别和优劣，用于我们的识别跟踪中。知乎上有一篇非常好的集合回答[知乎](https://www.zhihu.com/question/26493945)		
目前尝试过的有：		
* 背景消除法追踪，通过将静态的背景消除，判断运动中的物体，然后跟踪，这里的特征应该是像素的移动
* 
