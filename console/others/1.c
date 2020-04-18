#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>

/*---------------------------------- 

	输出点阵，代号 1
	
----------------------------------*/

//定义点阵的行数、列数 
#define LINE 15
#define ROW 15
 
 //全局变量，用于存储点阵信息 
static int show[LINE][ROW];

//函数声明 
void setShow();
void showMap();
void showInfo();
void refreshShow();

//字符串声明
#include "..\\strings.h"

//程序入口 
int programOne(int argc, char** argv){
	char move = 'w';
	int temp[2] = {0,0};			//暂存当前所在位置 

	setShow();						//点阵数组全置为 0
	show[temp[0]][temp[1]] = 1;		//当前位置置 1 
	refreshShow();
	
	while(move != '0'){
		move = getchar();
		show[temp[0]][temp[1]] = 0;	//当前（上一个循环所设置的）位置置 0 
		switch(move){				//检测输入，修改当前位置 
			case 'w':
				if(temp[0]>0)
					temp[0] -= 1;
			break;
			case 'a':
				if(temp[1]>0)
					temp[1] -= 1;
			break;
			case 's':
				if(temp[0]<LINE-1)
					temp[0] += 1;
			break;
			case 'd':
				if(temp[1]<ROW-1)
					temp[1] +=1;
			break;
			default:break; 
		}
		show[temp[0]][temp[1]] = 1;	//当前位置置 1 
		refreshShow();
		//Sleep(1000); 
	}
	
}

//初始化点阵数组，全部值为 0
void setShow(){
	int i,j;
	for(i = 0; i < LINE; i ++){
		for(j = 0; j < ROW; j ++){
			show[i][j] = 0;
		}
	}
}

//显示点阵 ，不要在主函数中使用 
void showMap(){
	int i,j;
	for(i = 0; i < LINE; i++){
		for(j = 0; j < ROW; j++){
			if(show[i][j])
				putchar('@');	//非零为 @
			else
				putchar('O');	//零为 O
			putchar(' ');
		}
		putchar('\n');
	}
}

//输出提示 ，不要在主函数中使用 
void showInfo(){
	puts(str_one1);
}

//刷新整个页面 
void refreshShow(){
	system("cls");
	showInfo();
	showMap(); 
}
