#include <stdio.h>

/*------------------------------------------

4 月 17 日课堂练习 
章登宇 	

第一题程序入口：41行 taskOne()
第二题程序入口：70行 taskTwo()
第三题程序入口：95行 taskThree()

历次作业完整代码：
https://gitee.com/littlesunny2001/Cproject.git 

-------------------------------------------*/ 
static void taskOne();
static void taskTwo(); 
static void taskThree();

//程序入口 
int classTestApr17th(int argc, char** argv)
{
	puts("\n----------------------4月17日实验课---------------------\n");
	puts("\n-------------------------第一题-------------------------\n");
	taskOne();
	puts("\n-------------------------第二题-------------------------\n");
	taskTwo();
	puts("\n-------------------------第三题-------------------------\n");
	taskThree();
	return 0;
}

/*第一题 
设计一个函数 min(x,y)，返回两个 float 类型变量中的较小值。并在 main 函数中测试。 
*/
static float min(float x, float y)
{
	return x>y?x:y;
}

static void taskOne()	//void main() 
{
	float x,y;
	printf("请输入两个数；");
	scanf("%f", &x);
	scanf("%f", &y); 
	printf("较小的数为：%f", min(x,y));
}

/*第二题 
用函数递归的方法计算阶乘 
*/
static int factorial(int n)
{
	if(n < 0)
	{
		printf("输入的值不正确");
		return -1;
	}
	else if(n == 0)
	{
		return 1;
	}
	else
	{
		return n*factorial(n-1);
	}
}

static void taskTwo()	//void main()
{
	int n = 0;
	printf("请输入一个非负整数：");
	scanf("%d", &n);
	printf("%d 的阶乘为：%d", n, factorial(n));
}

/*第三题 
有两个班级，分别有 20 名和 15 名学生，设计并调用 average 函数，
分别求这两个班级的平均成绩 
99 98 97 96 95 94 93 92 91 90 89 88 87 86 85 84 83 82 81 80
99 98 97 95 93 92 91 88 87 86 85 84 82 81 80
*/
static double average(double grades[], int num)
{
	double sum = 0;
	int i = 0;
	for(i=0; i<num; i++)
	{
		sum += grades[i];
	}
	return sum/(double)num;
}

static void taskThree()	//void main()
{
	int i=0;
	double grades[20];
	printf("请输入第一个班级的20人的成绩：\n");
	for(i=0; i<20; i++)
	{
		scanf("%lf", &grades[i]);
	}
	printf("第一个班级的平均分为：%lf\n", average(grades, 20));
	printf("请输入第二个班级的15人的成绩：\n");
	for(i=0; i<15; i++)
	{
		scanf("%lf", &grades[i]);
	}
	printf("第一个班级的平均分为：%lf\n", average(grades, 15));
}
