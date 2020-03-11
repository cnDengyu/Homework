#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#include "strings.h"

//设置默认执行的作业。取消定义以在执行中选择 。 
#define TARGET 3 
//设置是否需要循环
//#define LOOP 

//声明各项作业。 
//第一号程序 
extern int programOne(int argc, char** argv);
extern int programTwo(int argc, char** argv);
extern int programThree(int argc, char** argv);
extern int homeworkMar6th(int argc, char** argv);

int main(int argc, char** argv) {
	int homework = 0;
	int returnValue = 0;
	
	#ifdef LOOP 
	do{
	#endif
	
	#ifdef TARGET
		homework = TARGET;
	#else
		system("cls");
		puts(str_main1);
		scanf("%d",&homework);
	#endif
	
		system("cls");
		switch(homework){
			
			case 0:break;
			
			case 1:
				returnValue = programOne(argc, argv);
			break;
			
			case 2:
				returnValue = programTwo(argc, argv);
			break;
			
			case 3:
				returnValue = programThree(argc, argv);
			break; 
			
			case 4:
				returnValue = homeworkMar6th(argc, argv);
			break;
			
			default:
				puts(str_main2); 
			break; 
		} 
		
	#ifdef LOOP
	}while(homework);
	#endif

	//puts(str_main3);
	return returnValue;
}
