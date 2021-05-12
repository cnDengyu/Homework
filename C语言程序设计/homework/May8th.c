#include <stdio.h>

/*------------------------------------------

5 月 8 日作业 
章登宇 	

第一题程序入口：61行 taskOne()
第二题程序入口：98行 taskTwo()
第三题程序入口：126行 taskThree()

历次作业完整代码：
https://gitee.com/littlesunny2001/Cproject.git 

-------------------------------------------*/ 
static void taskOne();
static void taskTwo(); 
static void taskThree();

//程序入口 
int homeworkMay8th(int argc, char** argv)
{
	puts("\n----------------------5月8日作业---------------------\n");
	puts("\n-------------------------第一题-------------------------\n");
	taskOne();
	puts("\n-------------------------第二题-------------------------\n");
	taskTwo();
	puts("\n-------------------------第三题-------------------------\n");
	taskThree();
	return 0;
}

/*第一题 -------------------------------------
有 n 个整数，使前面各数顺序向后移 m 个位置，
最后 m 个数变成最前面 m 个数，
写一函数实现以上功能，在主函数中输入 n 个整数和输出调整后的 n 个数 
*/ 
static void moveArr(int *p, int m, int n)
{
	//定义 
	int temp[m],i;
	
	//暂存 
	for(i=0; i<m; i++)
	{
		temp[i] = *(p+n-m+i);
	}
	
	//整体右移 
	for(i=n-1; i>=m; i--)
	{
		*(p+i) = *(p+i-m);
	}
	
	//取出暂存的数 
	for(i=0; i<m; i++)
	{
		*(p+i) = temp[i];
	}
}
static void taskOne()	//main
{
	//定义 
	int input[9],i;
	
	//输入 
	printf("请输入9个整数：");
	for(i=0; i<9; i++)
	{
		scanf("%d",&input[i]);
	}
	
	//变换 
	moveArr(input, 3, 9);
	
	//输出 
	for(i=0; i<9; i++)
	{
		printf("%d ",input[i]);
	}
}

/*第二题 -------------------------------------
编写一个函数，求一个字符串的长度。
字符串在 main 函数内输入（用指针实现） 
*/ 
static int myStrLen(char* buff, int maxLen)
{
	//定义 
	int len = 0;
	
	//计数 
	while(*buff++!='\0' && len++<maxLen);
	
	//返回 
	return len;
} 
static void taskTwo()	//main
{
	//定义 
	char buffer[30];
	int len;
	
	//输入 
	printf("请输入一个字符串：");
	scanf("%s",buffer);
	
	//计数
	len = myStrLen(buffer, 30);
	
	//输出
	printf("字符串的长度为：%d\n", len); 
}

/*第三题 -------------------------------------
有一字符串，包含 n 个字符。编写一个函数，
将此字符串从第 m 个字符开始的全部字符复制成为另一个字符串 
（用指针实现） 
*/ 
static void myStrCpy(char* inBuff, int n, int m, char* outBuff)
{
	inBuff = inBuff + m-1;
	n -= m-1;
	while((*outBuff++ = *inBuff++) != '\0' && n-->0);
}
static void taskThree()	//main
{
	//定义 
	char buffer[30],copy[30];
	int m;
	
	//输入
	printf("请输入一个字符串：");
	scanf("%s", buffer);
	printf("从第几个字符开始拷贝？") ;
	scanf("%d", &m);
	
	//拷贝 	此处用到了上一题的计数函数 
	myStrCpy(buffer, myStrLen(buffer,30), m, copy);
	
	//输出
	printf("%s",copy); 
}
