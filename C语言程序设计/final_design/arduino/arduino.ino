#include "framework.h"

#ifdef TARGET_ARDUINO
#include <MsTimer2.h>
#endif

#include "global.h"
#include "pinSettings.h"
#include "view.h"
#include "controller.h"
#include "module.h"

// 刷新率时间常量，控制显示器刷新的时间间隔
const int refresh = 10; // 200 fps

// 全局按键状态变量，确保按键时只执行一次按键控制
int isButtonDown = FALSE;

// 程序状态变量，用于判断按键的功能
int programState = STATE_STOP;

void setup() {
  // put your setup code here, to run once:
  // set button pins to Input mode
  pinMode(PIN_PAUSE,INPUT_PULLUP);
  pinMode(PIN_RESUME,INPUT_PULLUP);
  pinMode(PIN_CLEAR,INPUT_PULLUP);
  pinMode(PIN_SAVE,INPUT_PULLUP);
  pinMode(PIN_STOP,INPUT_PULLUP);
  pinMode(PIN_DIG1,OUTPUT);
  pinMode(PIN_DIG2,OUTPUT);
  pinMode(PIN_DIG3,OUTPUT);
  pinMode(PIN_DIG4,OUTPUT);
  pinMode(PIN_A,OUTPUT);
  pinMode(PIN_B,OUTPUT);
  pinMode(PIN_C,OUTPUT);
  pinMode(PIN_D,OUTPUT);
  pinMode(PIN_E,OUTPUT);
  pinMode(PIN_F,OUTPUT);
  pinMode(PIN_G,OUTPUT);
  pinMode(PIN_DP,OUTPUT);
  pinMode(PIN_DOUBLE_DOT,OUTPUT);

  #ifdef TARGET_ARDUINO
  // set up timer
  MsTimer2::set(refresh,timerModule);
  MsTimer2::start();
  #endif

  #ifdef TARGET_51MCU
  timer_start_51();
  #endif
}

#define SOFTPRESS 100

void loop() {
  
  // put your main code here, to run repeatedly:
  if((!isButtonDown) && digitalRead(PIN_PAUSE) == BUTTON_DOWN \
  && programState == STATE_RUN)
  // 计时状态下才能触发暂停
  {
    delay(SOFTPRESS);
    if(digitalRead(PIN_PAUSE) == BUTTON_DOWN) // 按键前消抖
    {
    isButtonDown = TRUE;
    programState = STATE_PAUSE;
    onPause();
    }
  }
  else if((!isButtonDown) && digitalRead(PIN_RESUME) == BUTTON_DOWN \
  && programState == STATE_PAUSE)
  // 暂停状态下才能触发继续
  {
    delay(SOFTPRESS);
    if(digitalRead(PIN_RESUME) == BUTTON_DOWN) // 按键前消抖
    {
    isButtonDown = TRUE;
    programState = STATE_RUN;
    onResume();
    }
  }
  else if((!isButtonDown) && digitalRead(PIN_CLEAR) == BUTTON_DOWN \
  && (programState == STATE_STOP || programState == STATE_PAUSE))
  // 暂停或停止状态下才能触发清零
  {
    delay(SOFTPRESS);
    if(digitalRead(PIN_CLEAR) == BUTTON_DOWN) // 按键前消抖
    {
    isButtonDown = TRUE;
    programState = STATE_STOP;
    onClear();
    }
  }
  else if((!isButtonDown) && digitalRead(PIN_SAVE) == BUTTON_DOWN \
  && programState == STATE_RUN)
  // 计时状态下才能触发保存
  {
    delay(SOFTPRESS);
    if(digitalRead(PIN_SAVE) == BUTTON_DOWN) // 按键前消抖
    {
    isButtonDown = TRUE;
    onSave();
    }
  }
  else if((!isButtonDown) && digitalRead(PIN_LOAD) == BUTTON_DOWN \
  && (programState == STATE_STOP))
  // 停止状态下可以读取已保存的内容
  {
    delay(SOFTPRESS);
    if(digitalRead(PIN_LOAD) == BUTTON_DOWN) // 按键前消抖
    {
    isButtonDown = TRUE;
    onLoad();
    }
  }
  else if((!isButtonDown) && digitalRead(PIN_STOP) == BUTTON_DOWN \
  && (programState == STATE_RUN || programState == STATE_PAUSE))
  // 计时或暂停状态下才能触发停止
  {
    delay(SOFTPRESS);
    if(digitalRead(PIN_STOP) == BUTTON_DOWN) // 按键前消抖
    {
    isButtonDown = TRUE;
    programState = STATE_STOP;
    onStop();
    }
  }
  else if((!isButtonDown) && digitalRead(PIN_START) == BUTTON_DOWN \
  && programState == STATE_STOP)
  // 停止状态下才能触发开始
  {
    delay(SOFTPRESS);
    if(digitalRead(PIN_START) == BUTTON_DOWN) // 按键前消抖
    {
    isButtonDown = TRUE;
    programState = STATE_RUN;
    onStart();
    }
  }
  else if(isButtonDown) // 按键后消抖
  {
    isButtonDown = FALSE;
    delay(SOFTPRESS);
  }
}
