
#include <stm32f10x.h>
#include "core/core.h"
#include "message/message.h"
#include "sensor/sensor.h"
#include "estimator/estimator.h"

/**
  * @brief  Main program 主程序
  * @param  None
  * @retval None
  */
int main(void)
{
	
	// Core Module Initlize 核心程序初始化
	Core_Init();
	
	while(1)
	{
		
		/*
		* Fake Thread Structure 伪线程架构
		*
		* scan specific update variables, and decide which Fake Thread to run.
		* 扫描特定的更新变量，决定应该执行哪些伪线程。
		*
		* For example, when there is new information from Serial Port, run relative function.
		* For another example, when it's time to send a "Heart Beat" message, run relative function.
		* 例如，当串口有新的信息发来时，运行相关的处理程序。
		* 又例如，到了需要定时发送“心跳包”的时候，运行相关处理程序。
		* 
		* Under the Fake Thread Structure, 
		* interrupt functions can finish in a minimized controlable period, 
		* in case of interrupt irruption.
		* 在伪线程架构下，所有的中断服务函数的执行时间可以缩到最短，且时间可控，以防中断冲突。
		*
		*	Exceptionally, it's better not to use Fake Thread when time precision acquared.
		* 例外地，如果对时间精度有要求，不要使用伪线程。
		*
		* Attention: All Fake Thread must be safe otherwise the whole program will crash.
		* 注意：所有的伪线程必须安全。单个伪线程卡死时，整个程序都会卡死。
		*
		*/
		
		// Fake Thread: Core 核心伪线程
		Core_Run();
		
		// Fake Thread: Sensor 传感器伪线程
		SensorManager_Run();
		
		// Fake Thread: Estimator 状态估计伪线程
		Estimator_Run();
		
		// Fake Thread: Message 消息伪线程
		MessageManager_Run();
		
	}
}

