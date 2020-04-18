#pragma once
//设置语言,必须且只能设置一个语言 
#define LANGUAGE_ZH_CN 
//#define LANGUAGE_EN 
//#define LANGUAGE_ZH_HK
//#define LANGUAGE_ZH_TW 

//字符串统一处理，如果文本过多，这一部分应当单独放置在 string.h 中 
//简体中文 
#ifdef LANGUAGE_ZH_CN
const char str_main1[] = "这是登宇的作业程序\n请输入需要执行的作业号,输入0退出\n";
const char str_main2[] = "没找到这个作业\n";
const char str_main3[] = "已退出\n";
const char str_one1[] = "这是一号作业\n点阵\n输入wasd以控制 @ 上下左右移动\n输入0退出\n\n";
const char str_two1[] = "分子";
const char str_two2[] = "分母";
#endif
//ENGLISH
#ifdef LANGUAGE_EN 
const char* str_main1[] = "This is the program written by Dengyu\nPlease enter the number of homework, enter 0 to exit\n";
const char* str_main2[] = "Homework not found\n";
const char* str_main3[] = "Program terminated\n";
const char* str_one1[] = "This is the first task\nLATTICE\nenter wasd to let @ up/left/right/down\nenter 0 to exit\n\n";
#endif
//繁體中文
#ifdef LANGUAGE_ZH_HK
const char* str_main1[] = "這是登宇的作業程序\n請輸入需要執行的作業號,輸入0退出\n";
const char* str_main2[] = "沒找到這個作業\n";
const char* str_main3[] = "已退出\n";
const char* str_one1[] = "這是一号作业\n点阵\n输入wasd以控制 @ 上下左右移动\n输入0退出\n\n";
#endif
#ifdef LANGUAGE_ZH_TW
const char* str_main1[] = "這是登宇的作業程序\n請輸入需要執行的作業號,輸入0退出\n";
const char* str_main2[] = "沒找到這個作業\n";
const char* str_main3[] = "已退出\n";
const char* str_one1[] = "這是一號作業\n点阵\n输入wasd以控制 @ 上下左右移动\n输入0退出\n\n";
#endif
