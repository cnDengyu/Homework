#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

clock_t start, stop;
double duration;

#define SIZE 101
double calVolume(double surface[SIZE][SIZE]);
int getMatrixLine(double data[SIZE][SIZE], int index, double output[]);
double calSimpson(double f[], int n, double a, double b);

int main()
{
	start = clock();

	FILE *read = NULL;
	//打开曲面数据的文件
	fopen_s(&read, "surface_data.txt", "r");
	if (!read)
	{
		perror("fail to read !");
		exit(-1);
	}
	//读入.txt文件数据
	double surface[101][101];
	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			fscanf(read, "%lf", &surface[i][j]);
		}
	}
	fclose(read);

	//提示：曲面数据为surface[101][101]；
	//***********************************
	//*这里写下程序实现Simpson求积*

	double volume = calVolume(surface);
	printf("体积为：%lf\n", volume);

	//***********************************


	stop = clock();
	duration = (double)(stop - start) / CLK_TCK;
	printf("程序运行所用时间：%f\n", duration);

	system("pause");
	return 0;
}

/*	函数：计算曲面围成的体积
	返回值：体积 volume
	输入参数：曲面的点 surface[SIZE][SIZE]
*/
double calVolume(double surface[SIZE][SIZE])
{
	double volume = 0;
	double area[SIZE] = {0};
	double f[SIZE];
	int i = 0;

	for (i = 0; i < SIZE; i++)
	{
		getMatrixLine(surface, i, f);
		area[i] = calSimpson(f, 50, 2, -2);
	}

	volume = calSimpson(area, 50, 2, -2);
	
	return volume;
}


/*	函数：计算Simpson积分
	返回值：Simpson积分值
	输入参数：f[],n,a,b
*/
double calSimpson(double f[], int n, double a, double b)
{
	if (n < 2){
		return 0;
	}

	double result = 0;

	// 计算首末项
	result = f[0] + f[2*n];

	// 计算4*f(2k-1)求和项
	double temp2k_1 = 0;
	int k;
	for (k = 1; k <= n; k++)
	{
		temp2k_1 += f[2 * k - 1];
	}
	temp2k_1 = temp2k_1 * 4;
	result += temp2k_1;

	// 计算2*f(2k)求和项
	double temp2k = 0;
	for (k = 1; k <= n-1; k++)
	{
		temp2k += f[2 * k];
	}
	temp2k = temp2k * 2;
	result += temp2k;

	// 乘上系数
	result *= (b - a) / 6 / n;

	return result;
}


/*	函数：提取矩阵一行
	返回值：0为成功
	输入参数：data[][], index
	输出参数：output[]
*/
int getMatrixLine(double data[SIZE][SIZE], int index, double output[])
{
	if (index >= SIZE || index < 0)
	{
		puts("提取行异常\n");
		return -1;
	}

	int i = 0;
	for (i = 0; i < SIZE; i++)
	{
		output[i] = data[index][i];
	}
}
