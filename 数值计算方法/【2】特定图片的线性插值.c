#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start, stop, linear_bg, linear_ed, cubic_ed;
double duration, duration_linear, duration_cubic;

int main()
{
	start = clock();

	FILE *read = NULL;
	FILE *write1 = NULL;
	FILE *write2 = NULL;
	//打开.txt文件
	//打开原始数据的文件
	fopen_s(&read, "image_data/1.txt", "r");
	if (!read)
	{
		perror("fail to read !");
		exit(-1);
	}
	//创建保存线性插值结果的文件
	fopen_s(&write1, "image_data/1_linear.txt", "w");
	if (!write1)
	{
		perror("fail to write1 !");
		exit(-2);
	}
	//创建保存三次插值结果的文件
	fopen_s(&write2, "image_data/1_cubic.txt", "w");
	if (!write2)
	{
		perror("fail to write1 !");
		exit(-3);
	}
	//读入.txt文件数据
	int img[50][50];
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			fscanf(read, "%d", &img[i][j]);
		}
	}
	fclose(read);
	linear_bg = clock();
	// ==========================线性插值==========================
	//提示：待处理图像数据为img[50][50]；
	int linear[491][491] = { 0 }; //线性插值最终结果保存到这个数组

	//***********************************
	//*这里写下程序实现拉格朗日线性插值*

	// 临时变量
	int x0, x1, x2, x3,i,j;
	double l0, l1, l2, l3;
	
	// 横向插值
	for (i = 0; i < 50; i++)
	{
		for (j = 0; j < 491 - 1; j++)
		{
			x0 = j - j % 10;
			x1 = x0 + 10;
			l0 = (double)(j - x1) / (x0 - x1);
			l1 = (double)(j - x0) / (x1 - x0);

			linear[i*10][j] = img[i][x0/10] * l0 + l1 * img[i][x1/10];
		}
		linear[i*10][490] = img[i][49];
	}
	// 纵向插值
	for (j = 0; j < 491; j++)
	{
		
		for (i = 0; i < 491 - 1; i++)
		{
			x0 = i - i % 10;
			x1 = x0 + 10;
			l0 = (double)(i - x1) / (x0 - x1);
			l1 = (double)(i - x0) / (x1 - x0);
			
			linear[i][j] = linear[x0][j]*l0 + l1 * linear[x1][j];
		}
	}

	//***********************************

	//线性插值结果写入.txt
	for (int i = 0; i < 491; i++)
	{
		for (int j = 0; j < 491; j++)
		{
			fprintf(write1, "%3d  ", linear[i][j]);
		}
		fprintf(write1, "\n");
	}
	linear_ed = clock();


	// ==========================三次插值==========================
	//提示：待处理图像数据为img[50][50]
	int cubic[491][491] = { 0 }; //三次插值最终结果保存到这个数组

	//***********************************
	//*这里写下程序实现拉格朗日三次插值*

	// 横向插值
	for (i = 0; i < 50; i++)
	{
		for (j = 0; j < 491 - 1; j++)
		{
			if (0<=j && j<10)
			{
				x0 = j - j % 10;
			}
			else if (480<=j && j<490)
			{
				x0 = j - j % 10 - 20;
			}
			else
			{
				x0 = j - j % 10 - 10;
			}
			x1 = x0 + 10;
			x2 = x0 + 20;
			x3 = x0 + 30;
			l0 = (double)(j - x1)*(j - x2)*(j - x3) / (x0 - x1) / (x0 - x2) / (x0 - x3);
			l1 = (double)(j - x0)*(j - x2)*(j - x3) / (x1 - x0) / (x1 - x2) / (x1 - x3);
			l2 = (double)(j - x0)*(j - x1)*(j - x3) / (x2 - x0) / (x2 - x1) / (x2 - x3);
			l3 = (double)(j - x0)*(j - x1)*(j - x2) / (x3 - x0) / (x3 - x1) / (x3 - x2);
			cubic[i * 10][j] = l0 * img[i][x0 / 10] + l1 * img[i][x1 / 10] + l2 * img[i][x2 / 10] + l3 * img[i][x3 / 10];
		}
		cubic[i * 10][490] = img[i][49];
	}
	// 纵向插值
	for (j = 0; j < 491; j++)
	{

		for (i = 0; i < 491 - 1; i++)
		{
			if (0 <= i && i < 10)
			{
				x0 = i - i % 10;
			}
			else if (480 <= i && i < 490)
			{
				x0 = i - i % 10 - 20;
			}
			else
			{
				x0 = i - i % 10 - 10;
			}
			x1 = x0 + 10;
			x2 = x0 + 20;
			x3 = x0 + 30;
			l0 = (double)(i - x1) * (i - x2) * (i - x3) / (x0 - x1) / (x0 - x2) / (x0 - x3);
			l1 = (double)(i - x0) * (i - x2) * (i - x3) / (x1 - x0) / (x1 - x2) / (x1 - x3);
			l2 = (double)(i - x0) * (i - x1) * (i - x3) / (x2 - x0) / (x2 - x1) / (x2 - x3);
			l3 = (double)(i - x0) * (i - x1) * (i - x2) / (x3 - x0) / (x3 - x1) / (x3 - x2);
			cubic[i][j] = l0 * cubic[x0][j] + l1 * cubic[x1][j] + l2 * cubic[x2][j] + l3 * cubic[x3][j];
		}
	}

	//***********************************


	//三次插值结果写入.txt
	for (int i = 0; i < 491; i++)
	{
		for (int j = 0; j < 491; j++)
		{
			fprintf(write2, "%3d  ", cubic[i][j]);
		}
		fprintf(write2, "\n");
	}
	cubic_ed = clock();
	//关闭插值结果文件
	fclose(write1);
	fclose(write2);

	stop = clock();
	duration_linear = (double)(linear_ed - linear_bg) / CLK_TCK;
	duration_cubic = (double)(cubic_ed - linear_ed) / CLK_TCK;
	duration = (double)(stop - start) / CLK_TCK;
	printf("拉格朗日线性插值所用时间：%f\n", duration_linear);
	printf("拉格朗日三次插值所用时间：%f\n", duration_cubic);
	printf("程序运行所用时间：%f\n", duration);

	system("pause");
	return 0;
}

