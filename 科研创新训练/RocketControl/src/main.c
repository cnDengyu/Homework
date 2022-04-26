
#include <stm32f10x.h>
#include "core/core.h"
#include "message/message.h"
#include "sensor/sensor.h"
#include "estimator/estimator.h"

/**
  * @brief  Main program ������
  * @param  None
  * @retval None
  */
int main(void)
{
	
	// Core Module Initlize ���ĳ����ʼ��
	Core_Init();
	
	while(1)
	{
		
		/*
		* Fake Thread Structure α�̼ܹ߳�
		*
		* scan specific update variables, and decide which Fake Thread to run.
		* ɨ���ض��ĸ��±���������Ӧ��ִ����Щα�̡߳�
		*
		* For example, when there is new information from Serial Port, run relative function.
		* For another example, when it's time to send a "Heart Beat" message, run relative function.
		* ���磬���������µ���Ϣ����ʱ��������صĴ������
		* �����磬������Ҫ��ʱ���͡�����������ʱ��������ش������
		* 
		* Under the Fake Thread Structure, 
		* interrupt functions can finish in a minimized controlable period, 
		* in case of interrupt irruption.
		* ��α�̼ܹ߳��£����е��жϷ�������ִ��ʱ�����������̣���ʱ��ɿأ��Է��жϳ�ͻ��
		*
		*	Exceptionally, it's better not to use Fake Thread when time precision acquared.
		* ����أ������ʱ�侫����Ҫ�󣬲�Ҫʹ��α�̡߳�
		*
		* Attention: All Fake Thread must be safe otherwise the whole program will crash.
		* ע�⣺���е�α�̱߳��밲ȫ������α�߳̿���ʱ���������򶼻Ῠ����
		*
		*/
		
		// Fake Thread: Core ����α�߳�
		Core_Run();
		
		// Fake Thread: Sensor ������α�߳�
		SensorManager_Run();
		
		// Fake Thread: Estimator ״̬����α�߳�
		Estimator_Run();
		
		// Fake Thread: Message ��Ϣα�߳�
		MessageManager_Run();
		
	}
}

