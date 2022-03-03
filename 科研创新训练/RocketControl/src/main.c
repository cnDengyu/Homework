
#include <stm32f10x.h>
#include "core/core.h"
#include "message/message.h"

/**
  * @brief  Main program 主程序
  * @param  None
  * @retval None
  */
int main(void)
{
	
	// Core Ability Initlize 核心程序初始化
	CORE_Configuration();
	
	while(1)
	{
		
		/*
		* Fake Thread Structure 伪线程架构
		*
		* scan specific variables, and decide which Fake Thread to run.
		* 扫描特定的全局变量，决定应该执行哪些伪线程。
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
		*/
		
		// Fake Thread:Core 核心伪线程
		CORE_Loop();
		
		// Fake Thread:Message 消息伪线程
		MessageManager();
		
	}
}

