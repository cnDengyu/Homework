#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*------------------------------------------

3月6日作业
章登宇 

-------------------------------------------*/ 

static void taskOne();//第一题 
static void taskTwo();//第二题 
static void taskThree();//第三题 
static void taskFour();//第四题 
static void taskFive();//第五题 
static void taskSix();//第六题 

//程序入口，移植时请将函数名改为 main 
int homeworkMar6th(int argc, char** argv)
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

//第一题
//假如我国国民生产总值的年增长率为9%，计算10年后我国国民生产总值与现在相比增长多少百分比。计算公式为
//p = (1+r)^n
//r为年增长率，n为年数，p为与现在相比的倍数

static void taskOne()
{
	const double r = 0.09;
	const int n = 10;
	int i = 0;
	double p = 1.0;
	for(i = 0; i < n; i ++){
		p = p * ( 1.0 + r ) ;
	}
	printf("%lf\n",p);
}

//第二题 
//设圆半径 r = 1.5，圆柱高 h = 3，求圆周长、圆面积、圆球表面积、圆球体积、圆柱体积。
//用scanf输入数据，输出计算结果，输出时要求有文字说明，取小数点后两位数字。 

static void taskTwo()
{
	const float pi = 3.1415926;
	float r = 1.5;
	float h = 3.0;
	float c,s,sr,vr,vh;//圆周长、圆面积、圆球表面积、圆球体积、圆柱体积
	c = s = sr = vr = vh = 0;
	printf("当圆半径 r = 1.5，圆柱高h = 3 时，\n");
	c = 2.0*pi*r ;
	s = pi*r*r ;
	sr = 4.0*pi*r*r ;
	vr = 4.0/3.0*pi*r*r*r ;
	vh = s*h ;
	printf("圆周长：%.2f\n圆面积：%.2f\n圆球表面积：%.2f\n圆球体积：%.2f\n圆柱体积：%.2f\n", c,s,sr,vr,vh);
	printf("请以空格分开，输入圆半径和圆柱高：");
	scanf("%f %f", &r, &h);
	c = 2.0*pi*r ;
	s = pi*r*r ;
	sr = 4.0*pi*r*r ;
	vr = 4.0/3.0*pi*r*r*r ;
	vh = s*h ;
	printf("圆周长：%.2f\n圆面积：%.2f\n圆球表面积：%.2f\n圆球体积：%.2f\n圆柱体积：%.2f\n", c,s,sr,vr,vh);
}

//第三题
//编写一个程序，要求提示输入一个 ASCII 码值（如，66），然后打印输入的字符

static void taskThree()
{
	char c;
	printf("请输入一个ASCII码值：");
	scanf("%d", &c);
	printf("输入的字符为%c\n", c);
} 

//第四题
//编写一个程序，提示用户输入一个整数，然后打印从该数到比该数大 10 的所有整数
//例如：用户输入 5，则打印 5~15 的所有整数，包括 5 和 15
//要求打印的各值之间用一个空格、制表符或换行符分开

static void taskFour()
{
	int d = 0;
	int n = 0;
	printf("请输入一个整数：");
	scanf("%d",&d); 
	n = d + 10;
	for(; d <= n; d++){
		printf("%d ",d);
	}
	putchar('\n'); 
} 
 
//第五题 
//编写一个程序，提示用户输入天数，然后将其转换成周数和天数。
//例如：用户输入 18，则转换成 2 周 4 天。以下面的格式显示结果：
//18 days are 2 weeks, 4 days.
//通过 while 循环让用户重复输入天数，当用户输入一个非正值时，循环结束。
 
static void taskFive()
{
	int days = 1;
	while(1){
		printf("请输入天数：");
		scanf("%d",&days);
		if(days <= 0) break;
		printf("%d days are %d weeks, %d days.\n",days,days/7,days%7);
	}
	getchar();
}

//第六题 
//编写一个程序，先提示用户输入用户名，然后提示用户输入姓。
//在一行打印用户输入的名和姓，下一行分别打印名和姓的字母数。字母数要与相应名和姓的结尾对齐，如下所示
//Melissa Honeybee
//      7        8
//接下来，再打印相同的信息，但是字母个数与相应名和姓的开头对齐，如下所示：
//Melissa Honeybee
//7       8

static void taskSix()
{
	int i = 0;
	char lastname[10],firstname[10];
	char format[24]; 
	printf("请输入用户名：");
	scanf("%s",firstname);
	printf("请输入姓：");
	scanf("%s",lastname);
	
	printf("%s %s\n", firstname, lastname);
	sprintf(format, "%%%dd %%%dd\n", strlen(firstname), strlen(lastname));
	printf(format, strlen(firstname), strlen(lastname));
	
	printf("%s %s\n", firstname, lastname);
	sprintf(format, "%%-%dd %%-%dd\n", strlen(firstname), strlen(lastname));
	printf(format, strlen(firstname), strlen(lastname));
} 
