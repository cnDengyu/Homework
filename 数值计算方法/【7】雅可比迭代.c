#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "matrix/matrix.h"

clock_t start, stop;
double duration;

#define SCALE 9

Matrix* SolveByJacobi(Matrix* matA, Matrix* matb, double accurancy);
Matrix* SolveByGS(Matrix* matA, Matrix* matb, double accurancy);


int main()
{
	start = clock();



	//***********************************
	//*这里写下程序实现*
	//***********************************
	// 题给数据
	double dataA[SCALE][SCALE] = {
		{ 31, -13, 0, 0, 0, -10, 0, 0, 0 },
		{ -13, 35, -9, 0, -11, 0, 0, 0, 0 },
		{ 0, -9, 31, -10, 0, 0, 0, 0, 0 },
		{ 0, 0, -10, 79, -30, 0, 0, 0, -9, },
		{ 0, 0, 0, -30, 57, -7, 0, -5, 0 },
		{ 0, 0, 0, 0, 7, 47, -30, 0, 0 },
		{ 0, 0, 0, 0, 0, -30, 41, 0, 0 },
		{ 0, 0, 0, 0, -5, 0, 0, 27, -2 },
		{ 0, 0, 0, -9, 0, 0, 0, -2, 29 },
	};
	double datab[SCALE] = {
		-15,
		27,
		-23,
		0,
		-20,
		12,
		-7,
		7,
		-10
	};
	// 加载矩阵
	Matrix* matA, * matb;
	Matrix* matResult = NULL;
	matA = MatrixBuildFromArray(dataA, SCALE, SCALE);
	matb = MatrixBuildFromArray(datab, SCALE, 1);
	// Jacobi 迭代计算
	matResult = SolveByJacobi(matA, matb, 0.000001);
	puts("Jacobi迭代结果为：");
	MatrixPrint(matResult);		// 输出G-S结果
	MatrixDelete(&matResult);	// 释放内存

	// G-S 迭代计算
	matResult = SolveByGS(matA, matb, 0.000001);
	puts("G-S迭代结果为：");
	MatrixPrint(matResult);		// 输出G-S结果
	MatrixDelete(&matResult);	// 释放内存

	// 释放内存
	MatrixDelete(&matA);
	MatrixDelete(&matb);

	// 用于写作业
	/*
	double dataA1[3][3] = {
		{5, 2, 1},
		{-1, 4, 2},
		{2, -3, 10} };
	double datab1[3] = { -12, 20, 3 };
	matA = MatrixBuildFromArray(dataA1, 3, 3);
	matb = MatrixBuildFromArray(datab1, 3, 1);
	matResult = SolveByJacobi(matA, matb, )
		*/

	stop = clock();
	duration = (double)(stop - start) / CLK_TCK;
	printf("程序运行所用时间：%f\n", duration);

	system("pause");
	return 0;
}

/*	Jacobi迭代计算函数
	返回值：计算结果
	输入参数：系数矩阵A、常数向量b，方程规模
*/
Matrix* SolveByJacobi(Matrix* matA, Matrix* matb, double accurancy)
{
	double result = 0;

	Matrix* matD = NULL;
	Matrix* matL = NULL;
	Matrix* matU = NULL;
	// 计算所需的矩阵 L、U、D
	MatrixGetLUD(matA, &matL, &matU, &matD);
	// puts("L矩阵");
	// MatrixPrint(matL);
	// puts("U矩阵");
	// MatrixPrint(matU);
	// puts("D矩阵");
	// MatrixPrint(matD);

	// 矩阵运算，暂存 L+U
	Matrix* matTemp = NULL;
	MatrixAdd(matL, matU, &matTemp);
	// puts("L+U矩阵");
	// MatrixPrint(matTemp);
	// 矩阵运算，暂存 D 的逆
	Matrix* matD_Inv = NULL;
	MatrixInverseByValue(matD, &matD_Inv);
	// puts("D的逆矩阵");
	// MatrixPrint(matD_Inv);

	// 释放掉不需要的内存
	MatrixDelete(&matD);
	MatrixDelete(&matL);
	MatrixDelete(&matU);

	// 矩阵乘法，得到迭代格式 M = D逆 * (L+U)
	Matrix* matM = NULL;
	MatrixMultiply(matD_Inv, matTemp, &matM);
	puts("迭代格式M");
	MatrixPrint(matM);

	// 计算迭代格式 M 的 1-范数
	double normM = 0;
	MatrixOneNorm(matM, &normM);
	printf("M的范数为%lf\n", normM);

	// 计算迭代格式 f = D逆 * b
	Matrix* matf = NULL;
	MatrixMultiply(matD_Inv, matb, &matf);
	// puts("迭代格式f");
	// MatrixPrint(matf);

	MatrixDelete(&matD_Inv);	// 释放掉 D逆

	// 创建并初始化迭代矩阵 x
	Matrix* x = MatrixCreate(matb->rows, matb->cols);
	MatrixSetZeros(x);	// x 清零
	// puts("初始x");
	// MatrixPrint(x);

	Matrix* x1 = NULL;
	Matrix* x1_x = NULL;
	double normX;	// 存放差值的1-范数||x(k+1)-x(k)||
	double eps = 0;
	int times = 0;

	do {
		// 计算 x(k+1) = M * x(k) + f
		MatrixMultiply(matM, x, &matTemp);	// matTemp = matM * x(k)
		MatrixAdd(matTemp, matf, &x1);		// x(k+1) = matTemp + matf
		
		// 计算 ||x(k+1) - x(k)||
		MatrixMinus(x1, x, &x1_x);			// x1_x = x1 - x
		MatrixOneNorm(x1_x, &normX);		// normX = ||x1_x||
		// printf("Xn+1-X 的范数为%lf\n", normX);

		// ε = ||x(k+1) - x(k)||
		eps = normX;
		// printf("精度为%lf\n", eps);

		// 将 x1 的值拷贝到 x 中去
		MatrixCopy(x1, &x);
		times++;	// 计次
	} while (eps >= accurancy);	//迭代精度

	printf("Jacobi 迭代了 %d 次，ε= %.10lf\n", times, eps);
	// MatrixPrint(x1);

	// 释放内存
	MatrixDelete(&matTemp);
	MatrixDelete(&matM);
	MatrixDelete(&matf);
	MatrixDelete(&x);
	MatrixDelete(&x1_x);
	return x1;
}

/*
*	函数名称：G-S迭代求解函数
*	输入参数：矩阵matA，矩阵matb
*	输出参数：结果矩阵x1
*/
Matrix* SolveByGS(Matrix* matA, Matrix* matb, double accurancy)
{
	// 用于暂存计算值的变量
	double dx, aii, bi, aij, xj_k, xj_k1;
	double sum1, sum2, xi_k, xi_k1;
	int i, j;

	// 创建并初始化迭代值 x(0) = 0
	Matrix* x = MatrixCreate(matb->rows, matb->cols);
	MatrixSetZeros(x);
	// 创建迭代值 x(1)
	Matrix* x1 = MatrixCreate(matb->rows, matb->cols);
	Matrix* x1_x = NULL;

	// 暂存范数
	double normX;

	// 暂存精度和次数
	double eps = 0;
	int times = 0;

	do {
		for (i = 1; i <= matb->rows; i++)
		{
			// 从相应的矩阵中取出 aii, bi, xi(k) 的值
			MatrixGetValue(matA, i, i, &aii);
			MatrixGetValue(matb, i, 1, &bi);
			MatrixGetValue(x, i, 1, &xi_k);

			// 计算Σaij*x(k+1)
			sum1 = 0;
			for (j = 1; j <= i - 1; j++)
			{
				MatrixGetValue(matA, i, j, &aij);
				MatrixGetValue(x1, j, 1, &xj_k1);
				sum1 += aij * xj_k1;
			}

			// 计算Σaij*x(k)
			sum2 = 0;
			for (j = i; j <= matA->cols; j++)
			{
				MatrixGetValue(matA, i, j, &aij);
				MatrixGetValue(x, j, 1, &xj_k);
				sum2 += aij * xj_k;
			}
			// 计算 Δxi = 1/aii * (bi - Σaij*x(k+1) - Σaij*x(k))
			dx = 1.0 / aii * (bi - sum1 - sum2);
			// 计算 xi(k+1) = xi(k) + Δxi
			xi_k1 = xi_k + dx;
			// 将计算得到的 xi(k+1) 写入矩阵
			MatrixSetValue(x1, i, 1, xi_k1);
		}

		// 计算 || x(k + 1) - x(k) ||
		MatrixMinus(x1, x, &x1_x);		// x1_x = x1 - x
		MatrixOneNorm(x1_x, &normX);	// normX = ||x1_x||
		// 将 x1 的值拷贝到 x 中去
		MatrixCopy(x1, &x);
		// ε = ||x(k+1) - x(k)||
		eps = normX;
		times++;	// 计次

		// printf("G-S迭代了 %d 次，精度 ε= %.10lf\n", times, eps);

	} while (eps >= accurancy);

	printf("G-S迭代了 %d 次，精度 ε= %.10lf\n", times, eps);

	// 释放不需要的内存
	MatrixDelete(&x);
	MatrixDelete(&x1_x);
	return x1;
}
