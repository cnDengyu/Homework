# 结课设计

### 介绍
本仓库存放c语言程序设计大作业。  
目前处在完善阶段。
可以在 issue 中反馈问题。   
  
### 发行版  
[beta1.0](https://gitee.com/group_classa_clang_19_saa_sysu/final_design/releases/beta1.0)

### 编译和运行

**用 Arduino IDE 打开 [arduino.ino](arduino/arduino.ino) 即可编译和真机运行。**  
[ArduinoIDE下载地址](https://gzc-download.weiyun.com/ftn_handler/dd5eb5e1aed788ffd8692d5c9b76314ff7474f1e51f231232c5cb0b241bd47d5bf13d50c5fa556bd1cea3b6f908e637ae7bc040309e1ff21af35463b8bfde7b0/arduino-1.8.12-windows.exe?fname=arduino-1.8.12-windows.exe&from=30113&version=3.3.3.3)  
**按照[仿真说明](doc/仿真说明.md)在 Proteus 中仿真**  
[获取Arduino仿真软件 Proteus](https://pan.baidu.com/s/1i5TgSW9)  
不鼓励使用破解版软件，本项目仅作业使用，不作商业用途。  

### 开发进度
- [x] 选题阶段
- [x] 分工阶段
- [x] 开发阶段
- [ ] 完善阶段 

### 项目架构  
[arduino](arduino/)存放 Arduino 源码  
由于 Arduino 不能跨文件夹编译，所以各个代码文件只能放在同一文件夹中  
[module](doc/module.md) 模块，包括[主模块](doc/主模块.md)和[计时器模块](doc/计时器模块.md)。  
[controller](doc/controller.md) 控制函数，主要是事件响应函数。  
[view](doc/view.md) 显示函数。   
[Keil文件夹](keil/)存放 Keil 工程文件  
Arduino 328 文件夹存放 Proteus 仿真文件。     

逻辑关系：module 调用（依赖） controller 和 view。controller 可以改变由 view 提供的全局状态变量，从而改变 view 的行为。

module controller view 有唯一的对应 .h 文件，供其他代码调用。  


#### 参与贡献
 
1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 码云特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  码云官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解码云上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是码云最有价值开源项目，是码云综合评定出的优秀开源项目
5.  码云官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  码云封面人物是一档用来展示码云会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
