/*
 * This file defines display function
 * 本文件存放显示函数
 * 
 * Called per (int)refresh millisecond
 * 显示函数每 refresh 毫秒被调用一次
 */

#include "framework.h"
#include "pinSettings.h"
#include "global.h"

#ifdef TARGET_ARDUINO

#define DIG_ON HIGH
#define DIG_OFF LOW
#define LIGHT_ON LOW
#define LIGHT_OFF HIGH

#endif

#ifdef TARGET_51MCU

#define DIG_ON LOW
#define DIG_OFF HIGH
#define LIGHT_ON LOW
#define LIGHT_OFF HIGH

#endif

char toShow[4];

static void showTest();
// 基础显示函数：清除所有显示
static void showClear();  
// 基础显示函数：在某一位上显示内容（会清除其他位的显示）
static void showOne(int,int,int,int,int,int,int,int,int,int);
//基础显示函数；输入一个数字跟数码管位数，数码管对应位会显示该数字
static void showNum(int dig, int Num );
//计算十位数的函数
static int cal(int Num);

void showTime(int nowtime)
{
    int Min,Sec,Mil;
    Sec=nowtime%60;
    Min=(nowtime-nowtime%60)/60;
    Mil=(milliseconds%1000)/10;
    if(nowtime<60)
    {
      static int state = 1;
  switch(state)
  {
    case 1:showNum(PIN_DIG1,cal(Sec));state = 2; break;
    case 2:showNum(PIN_DIG2,Sec%10);state = 3;break;
    case 3:showNum(PIN_DIG3,cal(Mil));state = 4;break;
    case 4:showNum(PIN_DIG4,Mil%10);state = 1;break;
    }
     
    }
    else 
    {
     static int state = 1;
     switch(state)
    {
    case 1:showNum(PIN_DIG1,cal(Min));state = 2; break;
    case 2:showNum(PIN_DIG2,Min%10);state = 3;break;
    case 3:showNum(PIN_DIG3,cal(Sec));state = 4;break;
    case 4:showNum(PIN_DIG4,Sec%10);state = 1;break;
    }
    }
    
}

// 基础显示函数，在dig位上按 abcdefg 显示内容
static void showOne(int dig, int a, int b, int c, int d, int e, int f, int g, int dp, int doubledot)
{
  digitalWrite(PIN_DIG1,DIG_OFF);
  digitalWrite(PIN_DIG2,DIG_OFF);
  digitalWrite(PIN_DIG3,DIG_OFF);
  digitalWrite(PIN_DIG4,DIG_OFF);

  digitalWrite(PIN_A,a);
  digitalWrite(PIN_B,b);
  digitalWrite(PIN_C,c);
  digitalWrite(PIN_D,d);
  digitalWrite(PIN_E,e);
  digitalWrite(PIN_F,f);
  digitalWrite(PIN_G,g);
  digitalWrite(PIN_DP,dp);
  digitalWrite(PIN_DOUBLE_DOT,doubledot);

  digitalWrite(dig,DIG_ON);
}
// 基础显示函数：清除所有显示内容
static void showClear()
{
  digitalWrite(PIN_DIG1,DIG_OFF);
  digitalWrite(PIN_DIG2,DIG_OFF);
  digitalWrite(PIN_DIG3,DIG_OFF);
  digitalWrite(PIN_DIG4,DIG_OFF);
  digitalWrite(PIN_A,LIGHT_OFF);
  digitalWrite(PIN_B,LIGHT_OFF);
  digitalWrite(PIN_C,LIGHT_OFF);
  digitalWrite(PIN_D,LIGHT_OFF);
  digitalWrite(PIN_E,LIGHT_OFF);
  digitalWrite(PIN_F,LIGHT_OFF);
  digitalWrite(PIN_G,LIGHT_OFF);
  digitalWrite(PIN_DP,LIGHT_OFF);
}
//基础显示函数；输入一个数字跟数码管位数，数码管对应位会显示该数字
static void showNum(int dig, int Num )
{
   int showDoubleDot;
   if(dig == PIN_DIG2 && (timeflow == 0 || nowtime%2 == 0))
   {
     showDoubleDot = LIGHT_ON;    
   }
   else
   {
     showDoubleDot = LIGHT_OFF;
   }
   switch(Num)
   {
    case 1:showOne(dig,LIGHT_OFF,LIGHT_ON,LIGHT_ON,\
      LIGHT_OFF,LIGHT_OFF,LIGHT_OFF,LIGHT_OFF,showDoubleDot,showDoubleDot);break;
    case 2:showOne(dig,LIGHT_ON,LIGHT_ON,LIGHT_OFF,\
      LIGHT_ON,LIGHT_ON,LIGHT_OFF,LIGHT_ON,showDoubleDot,showDoubleDot);break;
    case 3:showOne(dig,LIGHT_ON,LIGHT_ON,LIGHT_ON,\
      LIGHT_ON,LIGHT_OFF,LIGHT_OFF,LIGHT_ON,showDoubleDot,showDoubleDot);break;
    case 4:showOne(dig,LIGHT_OFF,LIGHT_ON,LIGHT_ON,\
      LIGHT_OFF,LIGHT_OFF,LIGHT_ON,LIGHT_ON,showDoubleDot,showDoubleDot);break;
    case 5:showOne(dig,LIGHT_ON,LIGHT_OFF,LIGHT_ON,\
      LIGHT_ON,LIGHT_OFF,LIGHT_ON,LIGHT_ON,showDoubleDot,showDoubleDot);break;
    case 6:showOne(dig,LIGHT_ON,LIGHT_OFF,LIGHT_ON,\
      LIGHT_ON,LIGHT_ON,LIGHT_ON,LIGHT_ON,showDoubleDot,showDoubleDot);break;
    case 7 :showOne(dig,LIGHT_ON,LIGHT_ON,LIGHT_ON,\
      LIGHT_OFF,LIGHT_OFF,LIGHT_OFF,LIGHT_OFF,showDoubleDot,showDoubleDot);break;
    case 8:showOne(dig,LIGHT_ON,LIGHT_ON,LIGHT_ON,\
      LIGHT_ON,LIGHT_ON,LIGHT_ON,LIGHT_ON,showDoubleDot,showDoubleDot);break;
    case 9:showOne(dig,LIGHT_ON,LIGHT_ON,LIGHT_ON,\
      LIGHT_ON,LIGHT_OFF,LIGHT_ON,LIGHT_ON,showDoubleDot,showDoubleDot);break;
     case 0:showOne(dig,LIGHT_ON,LIGHT_ON,LIGHT_ON,\
      LIGHT_ON,LIGHT_ON,LIGHT_ON,LIGHT_OFF,showDoubleDot,showDoubleDot);break;
    default : break;
   }
}


// 显示测试函数
static void showTest()
{
  static int state = 1;
  switch(state)
  {
    case 1:
      showOne(PIN_DIG1,LIGHT_ON,LIGHT_ON,LIGHT_ON,\
      LIGHT_OFF,LIGHT_OFF,LIGHT_OFF,LIGHT_OFF,LIGHT_OFF,LIGHT_OFF);
      state = 2;
    break;
    case 2:
      if(nowtime%2 == 0)
      {
        showOne(PIN_DIG2,LIGHT_ON,LIGHT_OFF,LIGHT_OFF,\
        LIGHT_ON,LIGHT_ON,LIGHT_ON,LIGHT_ON,LIGHT_ON,LIGHT_ON);
      }
      else
      {
        showOne(PIN_DIG2,LIGHT_ON,LIGHT_OFF,LIGHT_OFF,\
        LIGHT_ON,LIGHT_ON,LIGHT_ON,LIGHT_ON,LIGHT_OFF,LIGHT_OFF);
      }
      state = 3;
    break;
    case 3:
      showOne(PIN_DIG3,LIGHT_ON,LIGHT_OFF,LIGHT_ON,\
      LIGHT_ON,LIGHT_OFF,LIGHT_ON,LIGHT_ON,LIGHT_OFF,LIGHT_OFF);
      state = 4;
    break;
    case 4:
      showOne(PIN_DIG4,LIGHT_ON,LIGHT_ON,LIGHT_ON,\
      LIGHT_OFF,LIGHT_OFF,LIGHT_OFF,LIGHT_OFF,LIGHT_OFF,LIGHT_OFF);
      state = 1;
    break;
  }
}
//计算十位数的函数
static int cal(int Num)
{
  int tens;
  tens=(Num-Num%10)/10;
  return tens;
 }
