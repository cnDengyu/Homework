#include <string.h>
#include "core/usart.h"
#include "core/timer.h"
#include "mavlink/common/mavlink.h"
#include "./sensor.h"


static char ACCCALSW[5] = {0XFF,0XAA,0X01,0X01,0X00};//������ٶ�У׼ģʽ
static char SAVACALSW[5]= {0XFF,0XAA,0X00,0X00,0X00};//���浱ǰ����
 

void SensorManager(void)
{
	static unsigned char ucRxBuffer[16];
	static unsigned char ucRxCnt = 0;	
	
	SensorReaded();
	
	while(USARTs_Available())
	{
		
		ucRxBuffer[ucRxCnt++]=USARTs_ReadByte();	//���յ������ݴ��뻺������
		
		if (ucRxBuffer[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
		{
			ucRxCnt=0;
			return;
		}
		
		if (ucRxCnt<11) {return;}//���ݲ���11�����򷵻�
		
		else
		{
			
			SensorSetFromBuffer(ucRxBuffer);
			
			ucRxCnt=0;//��ջ�����
		}
	}
}



