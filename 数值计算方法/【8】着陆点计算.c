#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
// #include <stdlib.h>
#include <time.h>
#include <math.h>

clock_t start, stop;
double duration;

#define DEBUG
#define y0 y_0	// 这行不能删，因为 math.h 里已经定义了 y0 ，这里不改名的话会重名

static double a = 5319725.3894;
static double b = 5193654.3001;
static double y0 = 1151274.6106;
static double R = 6371000;

// 椭圆方程对应函数 f(y)
double fEllipse(double y)
{
	return (R*R - y*y) / b / b + (y - y0)*(y - y0) / a / a - 1;
}

// f(y) 的导函数 f'(y)
double dEllipse(double y)
{
	return -2 * y / b / b + 2 * (y - y0) / a / a;
}

// 地表圆上通过 y 求解 x
double GetXfromEllipse(double y)
{
	return sqrt(R*R - y*y);
}

/*	函数：牛顿迭代
输入参数：	方程所对应的函数 f(x)，以及该函数的导函数 f'(x)，
迭代起点 start，迭代精度 accuracy
返回值：迭代结果
*/
double NewtonIteration(double(*f)(double x), double(*df)(double x), double start, double accuracy)
{
	double x = start;
	double x1 = x - f(x) / df(x);
	double delta = fabs(x1 - x);
	int n = 1;

	while (delta > accuracy)
	{
		x = x1;
		x1 = x - f(x) / df(x);
		delta = fabs(x1 - x);
		n++;
	}

#ifdef DEBUG
	printf("迭代次数：%d\n\n", n);
#endif

	return x1;
}


int main()
{
	start = clock();


	//***********************************
	//*这里写下程序实现*
	//***********************************

	
	double pos[2] = { 0 };
	double y = NewtonIteration(fEllipse, dEllipse, 100, 0.00000001);
	printf("y的值为：%lf\n\n", y);
	pos[1] = y;
	pos[0] = GetXfromEllipse(y);
	printf("落点的坐标为：(%lf,%lf)\n\n", pos[0], pos[1]);


	stop = clock();
	duration = (double)(stop - start) / CLK_TCK;
	printf("程序运行所用时间：%f\n", duration);

	system("pause");
	return 0;
}

