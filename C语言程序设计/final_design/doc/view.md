# 显示函数

## 定位

唯一显示函数由计时器模块按照一定的帧率定期调用  

## 功能

根据全局变量 char toShow[4] 显示某一帧，当该变量为空时显示 nowtime  

## 基础显示函数  
在 showTime.cpp 中包含若干 static 函数，供显示函数调用，称为基础显示函数。  
```c
// 基础显示函数：清除所有显示内容
static void showClear();

// 基础显示函数，在dig位上按 abcdefg 显示内容
static void showOne(int dig, int a, int b, int c, int d, int e, int f, int g, int dp, int doubledot);

// 显示测试函数 显示 TEST 字样并使冒号闪烁
static void showTest();
```

## 注意事项

1. 由于显示函数是按照帧间隔定时调用的，所以**显示函数的执行时间不能超过帧间隔时间**  
2. 为了确保上一条得到执行，显示函数**禁止调用delay()**

## 参考

[view.h](../arduino/view.h)  