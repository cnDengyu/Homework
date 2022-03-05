#include <string.h>
#include "core/usart.h"
#include "core/timer.h"
#include "mavlink/common/mavlink.h"
#include "./sensor.h"


static char ACCCALSW[5] = {0XFF,0XAA,0X01,0X01,0X00};//进入加速度校准模式
static char SAVACALSW[5]= {0XFF,0XAA,0X00,0X00,0X00};//保存当前配置
 

void SensorManager(void)
{
	static unsigned char ucRxBuffer[16];
	static unsigned char ucRxCnt = 0;	
	
	SensorReaded();
	
	while(USARTs_Available())
	{
		
		ucRxBuffer[ucRxCnt++]=USARTs_ReadByte();	//将收到的数据存入缓冲区中
		
		if (ucRxBuffer[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
		{
			ucRxCnt=0;
			return;
		}
		
		if (ucRxCnt<11) {return;}//数据不满11个，则返回
		
		else
		{
			
			SensorSetFromBuffer(ucRxBuffer);
			
			ucRxCnt=0;//清空缓存区
		}
	}
}



