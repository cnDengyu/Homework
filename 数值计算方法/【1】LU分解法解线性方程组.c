#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//clock_t为clock()函数返回的变量类型
clock_t start, stop;
double duration;

int myProgram();

int main()
{
	start = clock();

	//******************************
	//*这里写你的程序 * 
	myProgram();
	//******************************

	stop = clock();
	//CLK_TCK为clock()函数的时间单位，即时钟打点
	duration = (double)(stop - start) / CLK_TCK;
	printf("解方程所用时间：%f\n", duration);
	system("pause");
}

//说明：两次获得的时钟打点数之差(stop-start)就是程序运行所消耗的时钟打点数，再除以常数CLK_TCK，就得到了以秒为单位的运行时间。

// 所需函数的前向声明
int printMatrix(int lines, int rows, double* matrix);
int opScalarMultiplyLine(double* matrix, int lineMultiplicand, double multiplier, int lines, int rows);
int opLineSubLine(double* matrix, int lineMinute, int lineMinus, int lines, int rows);

#define MATRIX_N 5
#define DEBUG

int myProgram(){

	// 定义系数矩阵
	double points[5][2] = { \
	{-2.312, 0.5027}, \
	{2.061, -1.257}, \
	{-0.8545, -2.915}, \
	{-3.519, -1.156}, \
	{2.815, -2.815}		\
	};
	double matrixA[5][5];
	double b[MATRIX_N] = { 0,0,0,0,0 };

	// 初始化系数矩阵
	int i = 0;
	for (i = 0; i < MATRIX_N; i++){
		matrixA[i][0] = points[i][0] * points[i][1];
		matrixA[i][1] = points[i][1] * points[i][1];
		matrixA[i][2] = points[i][0];
		matrixA[i][3] = points[i][1];
		matrixA[i][4] = 1;
		b[i] = -points[i][0] * points[i][0];
	}
#ifdef DEBUG
	puts("系数矩阵A为：\n");
	printMatrix(MATRIX_N, MATRIX_N, matrixA);
	puts("常数矩阵b为：\n");
	printMatrix(MATRIX_N, 1, b);
#endif

	// 高斯消元得到上三角矩阵
	int j = 0;
	double m;
	for (j = 1; j < MATRIX_N; j++){
		// 消第j列
		for (i = j; i < MATRIX_N; i++){
			// 消第i+1行
			if (!matrixA[i][j-1]){
				continue;
			}
			m = matrixA[j - 1][j - 1] / matrixA[i][j - 1];
			opScalarMultiplyLine(matrixA, i + 1, m, MATRIX_N, MATRIX_N);
			b[i] *= m;
			opLineSubLine(matrixA, i + 1, j, MATRIX_N, MATRIX_N);
			b[i] -= b[j - 1];
		}
	}
#ifdef DEBUG
	puts("高斯消元后的上三角矩阵为：\n");
	printMatrix(MATRIX_N, MATRIX_N, matrixA);
#endif

	// 求解
	double x[MATRIX_N];
	double sum;
	for (i = MATRIX_N-1; i >= 0; i--){
		sum = 0;
		for (j = MATRIX_N - 1; j > i; j--) {
			sum += matrixA[i][j] * x[j];
		}
		x[i] = (b[i] - sum) / matrixA[i][i];
	}
#ifdef DEBUG
	puts("解得：x=");
	printMatrix(MATRIX_N, 1, x);

	printf("椭圆方程为：x*x + %10lf*x*y + %10lf*y*y + %10lf*x + %10lf*y + %10lf = 0 \n", x[0], x[1], x[2], x[3], x[4]);
#endif
	return 0;
}

/*
矩阵输出函数
lines			矩阵行数
rows			矩阵列数
matrix			操作矩阵
*/
int printMatrix(int lines, int rows, double* matrix){
	int i = 0;
	int j = 0;
	putchar('\n');
	for (i = 0; i < lines; i++){
		for (j = 0; j < rows; j++){
			printf(" %10lf ", *matrix++);
		}
		putchar('\n');
	}
	putchar('\n');
}

/*
矩阵操作——某行乘数
matrix			操作矩阵
lineMultiplicand	被乘的行
multiplier			乘数
lines			矩阵行数
rows			矩阵列数
*/
int opScalarMultiplyLine(double* matrix, int lineMultiplicand, double multiplier, int lines, int rows){
	// 越界检查
	if (lineMultiplicand > lines){
		return -1;
	}

	int i = 0;
	for (i = 0; i < rows; i++){
		*(matrix + rows * (lineMultiplicand - 1) + i) *= multiplier;
	}
	return 0;
}

/*
矩阵操作——某行减去某行
matrix			操作矩阵
lineMinute		被减的行
lineMinus		减去的行
lines			矩阵行数
rows			矩阵列数
*/
int opLineSubLine(double* matrix, int lineMinute, int lineMinus, int lines, int rows){
	// 越界检查
	if (max(lineMinus, lineMinute) > lines){
		return -1;
	}

	int i = 0;
	for (i = 0; i < rows; i++){
		*(matrix + rows * (lineMinute - 1) + i) -= *(matrix + rows * (lineMinus - 1) + i);
	}
	return 0;
}