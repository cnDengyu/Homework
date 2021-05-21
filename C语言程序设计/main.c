#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#include "strings.h"

//设置默认执行的作业。取消定义以在执行中选择 。 
// #define TARGET 22
//设置是否需要循环
//#define LOOP 

//声明各项作业。 
#include "homework/date.h"
#include "classTest/date.h"
#include "others/program.h"

//程序入口 
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
		printf("已进入第%d号作业\n",homework);
		getchar();
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
			
			case 5:
				returnValue = homeworkMar13th(argc, argv);
			break;
			
			case 6:
				returnValue = homeworkMar20th(argc, argv);
			break;
			
			case 7:
				returnValue = homeworkMar27th(argc, argv);
			break;
			
			case 8:
				returnValue = classTestApr3rd(argc, argv);
			break;
			
			case 9:
				returnValue = homeworkApr4th(argc, argv); 
			break;
			
			case 10:
				returnValue = classTestApr10th(argc, argv);
			break;
			
			case 11:
				returnValue = homeworkApr10th(argc, argv);
			break;
			
			case 12:
				returnValue = classTestApr17th(argc, argv);
			break; 
			
			case 13:
				returnValue = homeworkApr17th(argc, argv);
			break;
			
			case 14:
				returnValue = classTestMay8th(argc, argv);
			break;
			
			case 15:
				returnValue = homeworkMay8th(argc, argv);
			break;
			
			case 16:
				returnValue = findSaddlePoint();
			break;
			
			case 17:
				returnValue = classTestMay15th(argc, argv);
			break;
			
			case 18:
				returnValue = homeworkMay15th(argc, argv);
			break;
			
			case 19:
				returnValue = classTestMay22nd(argc, argv);
			break;
			
			case 20:
				returnValue = homeworkMay22nd(argc, argv);
			break;
			
			case 21:
				returnValue = sortTest(argc, argv);
			break;
			
			case 22:
				returnValue = findASpecialCollection();
			break;
			
			default:
				puts(str_main2); 
			break; 
		} 
		
	#ifdef LOOP
	}while(homework);
	#endif

	puts(str_main3);
	getchar();
	return returnValue;
}
