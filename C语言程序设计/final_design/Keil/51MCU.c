/************************************/
/*程序名:秒表		        */
//要实现10ms精度
/************************************/

#define uchar unsigned char
#define uint unsigned int

#include "framework.h"

/* ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓----主模块----↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ */

#include "../arduino/arduino.ino"

/* ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑----主模块----↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ */

/* ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓----兼容Arduino函数----↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ */

sbit S_PIN_PAUSE = P3^4;
sbit S_PIN_RESUME = P3^4;
sbit S_PIN_STOP = P3^5;
sbit S_PIN_START = P3^5;
sbit S_PIN_CLEAR = P3^6;
sbit S_PIN_SAVE = P3^7;
sbit S_PIN_LOAD = P3^7;

sbit S_PIN_DIG1=P2^0;    		//段码位1
sbit S_PIN_DIG2=P2^1;    		//段码位2  
sbit S_PIN_DIG3=P2^2;    		//段码位3
sbit S_PIN_DIG4=P2^3;    		//段码位4  

sbit S_PIN_A = P0^0;
sbit S_PIN_B = P0^1;
sbit S_PIN_C = P0^2;
sbit S_PIN_D = P0^3;
sbit S_PIN_E = P0^4;
sbit S_PIN_F = P0^5;
sbit S_PIN_G = P0^6;
sbit S_PIN_DP = P0^7;
sbit S_PIN_DOUBLE_DOT = P0^7;

#define translateW(PIN,u) case PIN: S_##PIN = u; break;

void digitalWrite(int pin, int u)
{
	switch(pin)
	{
		translateW(PIN_PAUSE,u)
		translateW(PIN_RESUME,u)
		translateW(PIN_STOP,u)
		translateW(PIN_START,u)
		translateW(PIN_CLEAR,u)
		translateW(PIN_SAVE,u)
		translateW(PIN_LOAD,u)
		translateW(PIN_DIG1,u)
		translateW(PIN_DIG2,u)
		translateW(PIN_DIG3,u)
		translateW(PIN_DIG4,u)
		translateW(PIN_A,u)
		translateW(PIN_B,u)
		translateW(PIN_C,u)
		translateW(PIN_D,u)
		translateW(PIN_E,u)
		translateW(PIN_F,u)
		translateW(PIN_G,u)
		translateW(PIN_DP,u)
		translateW(PIN_DOUBLE_DOT,u)
		default:break;
	}
}

void delay(uint z)//延时函数
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

#define translateM(PIN) case PIN: S_##PIN = 1; break;

void pinMode(int pin, int mode)
{
	if(mode == INPUT || mode == INPUT_PULLUP)
	{
		switch (pin)
		{
		translateM(PIN_PAUSE)
		translateM(PIN_RESUME)
		translateM(PIN_SAVE)
		translateM(PIN_START)
		translateM(PIN_STOP)
		translateM(PIN_LOAD)
		translateM(PIN_CLEAR)
		default:
			break;
		}
	}
}

#define translateR(PIN) case PIN: v = S_##PIN ;break;

int digitalRead(pin)
{
	int v;
	switch (pin)
	{
	translateR(PIN_PAUSE)
	translateR(PIN_RESUME)
	translateR(PIN_SAVE)
	translateR(PIN_START)
	translateR(PIN_STOP)
	translateR(PIN_LOAD)
	translateR(PIN_CLEAR)
	default:
		break;
	}
	return v;
}

void timer_start_51()
{
	int x = refresh*QUARTZ/12000;
	EA=1;
	TMOD=01;//定时器0,,16位定时方式
	TH0=(65536-x)/256;	//5ms
	TL0=(65536-x)%256;	//5ms
	//TH0=(65535-500)/256;//50MS
	//TL0=(65535-500)%256;//50MS
	ET0=1;
	TR0=1;
}

sfr ISP_DATA = 0xe2;   
sfr ISP_ADDRH = 0xe3;     
sfr ISP_ADDRL = 0xe4;   
sfr ISP_CMD = 0xe5;   
sfr ISP_TRIG = 0xe6;      
sfr ISP_CONTR = 0xe7;
//关IAP/ISP
static void Q0()
{
    ISP_CONTR = 0;            // 关闭IAP功能
    ISP_CMD   = 0;            // 待机模式，无ISP操作
    ISP_TRIG  = 0;            // 关闭IAP功能, 清与ISP有关的特殊功能寄存器
}

void EEPROM_write(int addr,int dat)
{
	addr += 0x2000;
    ISP_CONTR = 0x81;                  
    ISP_CMD   = 0x02;              // 用户可以对"Data Flash/EEPROM区"进行字节编程
    ISP_ADDRL = (int)addr;        
    ISP_ADDRH = (int)addr>>8;      
    ISP_DATA  = (int)dat;          // 数据进ISP_DATA
    EA = 0;
    ISP_TRIG = 0x46;         
    ISP_TRIG = 0xB9;         
	
    _nop_();
    Q0();                                          // 关闭ISP/IAP
}

int EEPROM_read(int addr)
{   
    uchar dat;
	addr += 0x2000;
      
    ISP_CONTR = 0x81;                  
    ISP_CMD   = 0x01;         // 用户可以对"Data Flash/EEPROM区"进行字节读
    ISP_ADDRL = (uchar)addr;         
    ISP_ADDRH = (uchar)addr>>8;      
    EA = 0;
    ISP_TRIG = 0x46;         
    ISP_TRIG = 0xB9;         
	
    _nop_();
    dat = ISP_DATA;                          // 取出数据
        Q0();                                          // 关闭ISP/IAP                  
        return (int)dat;
}

void main()
{
	setup();

	while(1)
	{
		loop();
	}
}

/* ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑----兼容Arduino函数----↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ */

/* ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓----定时器模块----↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ */

void timer0_INT() interrupt 1
{  
	int x = refresh*QUARTZ/12000;
	TH0=(65536-x)/256;	//5ms
	TL0=(65536-x)%256;	//5ms
	timerModule();
}

/* ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑----定时器模块----↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑ */

