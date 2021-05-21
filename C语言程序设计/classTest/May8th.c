#include <stdio.h>

/*------------------------------------------

5 月 8 日课堂练习 
章登宇 	

第一题程序入口：37行 taskOne()
第二题程序入口：97行 taskTwo()
第三题程序入口：137行 taskThree()

历次作业完整代码：
https://gitee.com/littlesunny2001/Cproject.git 

-------------------------------------------*/ 
static void taskOne();
static void taskTwo(); 
static void taskThree();

//程序入口 
int classTestMay8th(int argc, char** argv)
{
	puts("\n----------------------5月8日实验课---------------------\n");
	puts("\n-------------------------第一题-------------------------\n");
	taskOne();
	puts("\n-------------------------第二题-------------------------\n");
	taskTwo();
	puts("\n-------------------------第三题-------------------------\n");
	taskThree();
	return 0;
}

/* 第一题 
编写一个函数，输入 3 个整数，按由小到大的顺序输出（用指针的方法处理） 
*/
//定义输入数据个数 
static void taskOne()	//main
{
	//定义变量 
	int i=0,j=0; 		//计数变量 
	int input[3]; 		//输入数组
	int *p=input;		//数组指针 
	int *o1,*o2,*o3,*temp;	//输出 
	 
	//输入
	printf("请输入 3 个整数：");
	for(i=0; i<3; i++) 
	{
		scanf("%d",p++);
	}
	o1 = input;
	o2 = &input[1];
	o3 = &input[2];
	
	//比较 
	if(*o1>*o2)
	{
		temp = o1;
		o1 = o2;
		o2 = temp;
		
	}
	if(*o1>*o3)
	{
		temp = o1;
		o1 = o3;
		o3 = temp;
	}
	if(*o2>*o3)
	{
		temp = o2;
		o2 = o3;
		o3 = temp;
	}
	
	//输出
	printf("%d %d %d",*o1,*o2,*o3); 
	
}

/* 第二题 
有一个数组 a ，通过键盘输入数组 5 个元素。
定义一个指针变量 p，指向数组首地址，然后调用函数 void inv(int *x, int n)
将数组元素相反存放，然后在屏幕输出相反顺序存放的数组元素。 
*/
static void inv(int *x,int n)
{
	int temp,i;
	n--; 
	for(i=0; i<n/2; i++)
	{
		temp = *(x+i);
		*(x+i) = *(x+n-i);
		*(x+n-i) = temp;
	}
}
static void taskTwo()	//main
{ 
	//定义 
	int i;					//计数变量 
	int a[5] = {1,2,3,4,5};	//数组
	
	//输入
	printf("请输入5个数："); 
	for(i=0; i<5; i++)
	{
		scanf("%d", &a[i]);
	} 
	 
	//倒序 
	inv(a,5);
	
	//输出 
	for(i=0; i<5; i++)
	{
		printf("%d ",a[i]);
	}
}

/* 第三题 
从键盘输入 n（个数不限）个整型数字，放到数组 PArray 中，然后编写函数
int *Calc(int *PA, int Num); 计算出数组中所有元素的和返回给 main函数
并将其输出。（用到变长数组） 
*/
static int Calc(int *PA, int Num)
{
	int i;	//计数变量 
	int sum=0;
	
	for(i=0; i<Num; i++)
	{
		sum += *(PA+i);
	}
	
	return sum;
}
static void taskThree()	//main
{
	//定义
	int i,n = 1;
	
	//输入
	printf("请输入要输入的数字个数：");
	scanf("%d",&n);
	
	//变长数组
	int PArray[n];
	
	//输入
	printf("请输入%d个整数:",n);
	for(i=0; i<n; i++)
	{
		scanf("%d", &PArray[i]);
	} 
	
	//输出
	printf("和为：%d",Calc(PArray,n)); 
}
