/*
 * This file declares all global variables
 * 本文件声明所有全局变量
 */

// 全局时间变量，用于存放当前时间
extern int nowtime,milliseconds;

// 全局按键状态变量，确保按键时只执行一次按键控制
extern int isButtonDown;
#define TRUE 1
#define FALSE 0

// 刷新率时间常量，控制显示器刷新的时间间隔
extern const int refresh;

// 时间流速全局变量，控制 nowtime 增加的速度。建议值为 0 1
extern int timeflow;

// 显示内容变量,显示函数根据这里的内容显示。如果第1位为'\0'，则根据 nowtime 显示
extern char toShow[4];

// 程序状态变量，由主模块维护
extern int programState;
#define STATE_STOP 0
#define STATE_RUN 1
#define STATE_PAUSE 2
extern int time_1,time_2,time_3,time_4,time_5,time_6;//建立三个用来存放时间的变量量并初始化(在onSave函数中使用)//

// EEPROM 地址
extern int addr;
