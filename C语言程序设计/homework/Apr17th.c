#include <stdio.h>

/*------------------------------------------

4 月 17 日作业 
章登宇 	

第一题程序入口：51行 taskOne()
第二题程序入口：77行 taskTwo()
第三题程序入口：133行 taskThree()

历次作业完整代码：
https://gitee.com/littlesunny2001/Cproject.git 

-------------------------------------------*/ 
static void taskOne();
static void taskTwo(); 
static void taskThree();

//程序入口 
int homeworkApr17th(int argc, char** argv)
{
	puts("\n--------------------4月17日课后作业---------------------\n");
	puts("\n-------------------------第一题-------------------------\n");
	taskOne();
	puts("\n-------------------------第二题-------------------------\n");
	taskTwo();
	puts("\n-------------------------第三题-------------------------\n");
	taskThree();
	return 0;
}

/*第一题
编写一个函数，接受3个参数：一个字符和两个整数。
字符参数是待打印的字符，第一个整数指定一行中打印字符的次数，
第二个整数指定打印指定字符的行数。编写一个调用该函数的程序。 
*/
static void myPrint(char toPrint, int rows, int lines)
{
	int i,j;
	for(i=0; i<lines; i++)
	{
		for(j=0; j<rows; j++)
		{
			putchar(toPrint);
		}
		putchar('\n');
	}
}

static void taskOne()	//void main()
{
	myPrint('$',3,4);
} 

/*第二题
写一个函数，使给定的一个 3×3 的二维整型数组转置。 
*/
#define LINE 3
#define ROW 3 
static void transformMartix(int m[LINE][ROW])
{
	int temp,i,j;
	if(LINE == ROW)
	{
		for(i=0; i<LINE; i++)
		{
			for(j=0; j<i; j++)
			{
				temp = m[i][j];
				m[i][j] = m[j][i];
				m[j][i] = temp;
			}
		}
	}
}
static void taskTwo()	//void main()
{
	int m[LINE][ROW];
	int i,j;
	printf("请输入一个 3×3 的整数矩阵：\n");
	for(i=0; i<LINE; i++)
	{
		for(j=0; j<ROW; j++)
		{
			scanf("%d",&m[i][j]);
		}
	}
	
	transformMartix(m);
	
	printf("转置后的矩阵为：\n");
	for(i=0; i<LINE; i++)
	{
		for(j=0; j<ROW; j++)
		{
			printf("%3d",m[i][j]);
		}
		putchar('\n');
	}
} 

/*第三题
写两个函数，分别求两个整数的最大公约数和最小公倍数，
用主函数调用这两个函数，并输出结果。两个整数由键盘输入 
*/
static unsigned int fGCD(unsigned int a, unsigned int b)	//greatest common divisor
{
	unsigned int i,returnValue;
	for(returnValue=i=1; i<=(a<b?a:b); i++)
	{
		if(a%i == 0 && b%i == 0)
		{
			returnValue = i;
		} 
	}
	return returnValue;
} 

static int fLCM(int a, int b)	//least/lowest common multipe
{
	unsigned int i;
	for(i=(a>b?a:b); i<=a*b; i++)
	{
		if(i%a == 0 && i%b == 0)
		{
			return i;
		}
	}
	//return a*b;
}

static void taskThree()
{
	unsigned int a, b;
	do{
		printf("请输入两个数：");
		scanf("%u", &a);
		scanf("%u", &b);
	}while(a==0 || b==0);		//除去 0 
	
	printf("两数的最大公约数为：%d\n", fGCD(a,b));
	printf("两数的最小公倍数为：%d\n", fLCM(a,b));
} 
