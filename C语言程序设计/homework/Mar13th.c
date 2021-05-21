#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
/*------------------------------------------

3月13日作业
章登宇 

-------------------------------------------*/ 

static void taskOne();
static void taskTwo();
static void taskThree();
static void taskFour();
static void taskFive();
static void taskSix();

//程序入口，移植时请将函数名改为 main 
int homeworkMar13th(int argc, char** argv)
{
	puts("\n-------------------------第一题-------------------------\n");
	taskOne();
	puts("\n-------------------------第二题-------------------------\n");
	taskTwo();
	puts("\n-------------------------第三题-------------------------\n");
	taskThree();
	puts("\n-------------------------第四题-------------------------\n");
	taskFour();
	puts("\n-------------------------第五题-------------------------\n");
	taskFive();
	puts("\n-------------------------第六题-------------------------\n");
	taskSix();
	return 0; 
}

/*第一题
从键盘输入一个小于 1000 的正数，要求输出它的平方根
（如平方根不是整数，则输出其整数部分） 
要求在输入数据后先对其进行检查是否为小于 1000 的正数。
若不是，则要求重新输入 
*/ 

static void taskOne()
{
	int n = 0;
	int result = 0;
	do{
		printf("请输入一个小于 1000 的正数：");
		scanf("%d",&n); 
	}while(0 >= n || n >= 1000);
	
	result = (int)sqrt((double)n);
	printf("平方根为 %d \n",result);
} 

/*第二题
求 Σn! (1 ~ 20)
*/
static void taskTwo()
{
	int result = 0;
	int stage = 1;
	int i,n;
	for(n = 1; n <= 20; n++){
		for(i = 1; i <= n; i ++){
			stage = stage * i;
		}
		result = result + stage;
		stage = 1;
	}
	printf("%d", result);
} 

/*第三题
输入一些浮点数，计算负数的数目所占百分比，输出示例：
请输入数字：12 5 -2.5 1 0 5 -5 6 7 -10
总共 10 个数字，负数占比 30 % 
*/ 
static void taskThree()
{
	char numberBuff[20] = "";	//暂存 stdin 中截取的对应一个数字的字符串 
	char buff = ' ';
	int num = 0;			//统计总数字数量 
	int minusNum = 0;		//统计负数数量 
	float currentNumber;	//暂存 numberBuff 中解译的浮点数 
	char *pNumber;			//用于读写 numberBuffer的指针 
	bool ifLoop = true;
	
	fflush(stdin);		//清除缓冲区 
	
	pNumber = numberBuff;
	printf("请输入数字：");

	while(ifLoop){	//不断判断 stdin 中的字符，直到字符串结束 
		buff=getc(stdin);
		if(buff == '\0' || buff == '\n'){	//退出循环条件 
			ifLoop = false;
		}

		if(buff == ' ' || buff == '\n'){	//用空格分割各个数字 
			*pNumber++ = '\0';			//如果读到了空格，则给 numberBuffer 收尾 
			currentNumber = atof(numberBuff);	//解译暂存的包含单个数字的字符串 
			if(currentNumber < 0){
				minusNum++;			//如果小于零则记录 
			}
			num ++;					//如果读到数字则记录 
			pNumber = numberBuff;	//指针重置到起点 
		}else if(buff == '\b'){
			*pNumber--;				//如果读到退格则不写入，而且指针要回退 
		}else if(buff>31){			//略去所有控制字符 
			*pNumber++ = buff;		//如果没有读到空格，则写入 numberBuffer 
		}
	}

	printf("总共 %d 个数字，负数占比 %.0f%%",num,100.0*(float)minusNum/num);
	
	fflush(stdin);		//清除缓冲区 
} 

/*第四题
有三个正数 a, b, c，由键盘输入，输出其中最大的数 
*/ 
static void taskFour()
{
	int a,b,c;
	int max;

	printf("请以空格分开，输入三个整数：");
	scanf("%d %d %d",&a,&b,&c);

	max = a;
	if(b>max){
		max = b;
	}
	if(c>max){
		max = c;
	}
	printf("最大的数为 %d",max);
}

/*第五题
使用嵌套循环，按下面的格式打印字母 
F
FE
FED
FEDC
FEDCB
FEDCBA
*/

static void taskFive()
{
	char letter = 'F';
	int i,j;
	for(i = 1; i <= 6; i ++){
		for(j = 0; j < i; j++){
			putchar(letter - j);
		}
		putchar('\n');
	}
}

/*第六题
编写一个程序，提示用户输入大写字母。使用嵌套循环以下面的金字塔型的格式打印字母
    A
   ABA
  ABCBA
 ABCDCBA
ABCDEDCBA 
打印这样的图形，要根据用户输入的字母来决定。例如，上面的图形是在用户输入E后的打印结果 
*/ 

static void taskSix()
{
	char c;
	int i,j,n;
	do{
		printf("请输入一个大写字母：");
		scanf("%c", &c);
	}while(c < 'A' || c > 'Z');
	n = c - 'A' + 1;
	for(i = 0; i < n ; i ++) {
		for(j = 0; j < n - i - 1; j++){
			putchar(' ');
		}
		for(j = 0; j < i; j++){
			putchar('A'+j);
		}
		putchar('A'+i);
		for(j = i-1; j >= 0; j--){
			putchar('A'+j);
		}
		putchar('\n');
	}
}
