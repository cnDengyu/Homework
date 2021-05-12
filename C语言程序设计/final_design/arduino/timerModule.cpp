#include "framework.h"

#include "global.h"
#include "view.h"

// 定义全局时间变量
int nowtime = 0;

// 时间流速全局变量
int timeflow = 0;

//用于存放毫秒
int milliseconds=0;

void timerModule()
{
    
    nowtime += milliseconds / 1000; // 通过次数计算时间，增加到nowtime中
    milliseconds = milliseconds % 1000; // 减去已转化进 nowtime 的调用次数
    showTime(nowtime);              // 调用显示函数
    
    milliseconds += timeflow * refresh;//根据时间流速增加毫秒值
}
