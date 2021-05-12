#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//clock_t为clock()函数返回的变量类型
clock_t start, stop;
double duration;

// 所需函数的前向声明
int calStarCalendar();

int main()
{
	start = clock();

	//******************************
	//*这里写你的程序 * 
	calStarCalendar();
	//******************************

	stop = clock();
	//CLK_TCK为clock()函数的时间单位，即时钟打点
	duration = (double)(stop - start) / CLK_TCK;
	printf("解方程所用时间：%f\n", duration);
	system("pause");
}

//说明：两次获得的时钟打点数之差(stop-start)就是程序运行所消耗的时钟打点数，再除以常数CLK_TCK，就得到了以秒为单位的运行时间。


#define NUM 9
#define SCALE 5
#define VARIBLES 4

// 所需函数的前向声明
int convertTime(double data[][4], int num);
int printMatrix(int lines, int rows, double* matrix);
double calChebyshev(int n, double x);
int calNormalEquationsA(double data[][VARIBLES], int num, double innerProduct[SCALE][SCALE]);
int calNormalEquationsB(double data[][VARIBLES], int num,
	double matrixBx[SCALE], double matrixBy[SCALE], double matrixBz[SCALE]);
int solveEquations(double matrixA[SCALE][SCALE], double matrixB[SCALE], double x[SCALE]);
int reCompare(double data[][VARIBLES], int num, double output[][VARIBLES], double coefficientX[SCALE], double coefficientY[SCALE], double coefficientZ[SCALE]);

int calStarCalendar()
{

	double data[NUM][VARIBLES] = { { 0, - 386976.786,	106369.212,	61240.44 } ,
	{ 12, - 397199.228,	70584.989,	41725.648 },
	{ 24, - 403002.333,	34008.818,	21741.252 },
	{ 36, - 404301.874, - 2946.251,	1512.866 },
	{ 48, - 401058.65, - 39859.487, - 18729.308 },
	{ 60, - 393279.751, - 76305.83, - 38752.308 },
	{ 72, - 381019.561, - 111859.429, - 58322.344 },
	{ 84, - 364380.489, - 146097.317, - 77206.812 },
	{ 96, - 343513.4, - 178603.222, - 95176.378 } };

	// 时间转换
	convertTime(data, NUM);

	// 验证时间转换函数的正确性
	// printMatrix(NUM, 4, data);

	double matrixA[SCALE][SCALE];
	calNormalEquationsA(data, NUM, matrixA);

	double matrixBx[SCALE], matrixBy[SCALE], matrixBz[SCALE];
	calNormalEquationsB(data, NUM, matrixBx, matrixBy, matrixBz);

	// 验证内积计算函数的正确性
	puts("系数矩阵A:");
	printMatrix(SCALE, SCALE, matrixA);
	puts("变量x的增广列：");
	printMatrix(SCALE, 1, matrixBx);
	puts("变量y的增广列：");
	printMatrix(SCALE, 1, matrixBy);
	puts("变量z的增广列：");
	printMatrix(SCALE, 1, matrixBz);

	double x[SCALE], y[SCALE], z[SCALE];
	solveEquations(matrixA, matrixBx, x);
	solveEquations(matrixA, matrixBy, y);
	solveEquations(matrixA, matrixBz, z);

	// 验证运算结果的正确性
	puts("x的拟合系数为：");
	printMatrix(SCALE, 1, x);
	puts("y的拟合系数为：");
	printMatrix(SCALE, 1, y);
	puts("z的拟合系数为：");
	printMatrix(SCALE, 1, z);

	
	double reCmp[NUM][VARIBLES];
	puts("拟合回代结果为：");
	reCompare(data, NUM, reCmp, x, y, z);
	printMatrix(NUM, VARIBLES, reCmp);
	

	return 0;
}


/*	时间转换函数
	返回值：0
	输入参数：data, num
	输出参数：data			*/
int convertTime(double data[][VARIBLES], int num)
{
	double tBegin = 0;
	double tEnd = 0;
	double t;
	int i;
	for (i = 0; i < num; i++)
	{
		if (data[i][0] > tEnd)
		{
			tEnd = data[i][0];
		}
		if (data[i][0] < tBegin)
		{
			tBegin = data[i][0];
		}
	}

	for (i = 0; i < num; i++)
	{
		t = data[i][0];
		data[i][0] = 2 * (t - tBegin) / (tEnd - tBegin) - 1;
	}

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
	return 0;
}

/*	切比雪夫求值函数
	返回值：切比雪夫值
	输入参数：阶数n，自变量值x
*/
double calChebyshev(int n, double x)
{
	return cos(n*acos(x));
}

/*	法方程组系数矩阵计算函数
	返回值：0
	输入参数：data,num
	输出参数：innerProduct
*/
int calNormalEquationsA(double data[][VARIBLES], int num, double matrixA[SCALE][SCALE])
{
	int i, j, k;
	for (i = 0; i < SCALE; i++)
	{
		for (j = 0; j < SCALE; j++)
		{
			matrixA[i][j] = 0;
			for (k = 0; k < num; k++)
			{
				matrixA[i][j] += calChebyshev(i, data[k][0]) * calChebyshev(j, data[k][0]);
			}
		}
	}
	return 0;
}

/*	法方程组增广向量计算函数
	返回值：0
	输入参数：data, num
	输出参数：matrixBx, matrixBy, matrixBz
*/
int calNormalEquationsB(double data[][VARIBLES], int num, 
	double matrixBx[SCALE], double matrixBy[SCALE], double matrixBz[SCALE])
{
	int i,k;
	for (i = 0; i < SCALE; i++)
	{
		matrixBx[i] = 0;
		matrixBy[i] = 0;
		matrixBz[i] = 0;
		for (k = 0; k < num; k++)
		{
			matrixBx[i] += data[k][1] * calChebyshev(i, data[k][0]);
			matrixBy[i] += data[k][2] * calChebyshev(i, data[k][0]);
			matrixBz[i] += data[k][3] * calChebyshev(i, data[k][0]);
		}
	}
	return 0;
}

/*	解方程函数
	返回值：0
	输入参数：matrixA, matrixB
	输出参数：x
*/
#define MATRIX_N SCALE
int solveEquations(double matrixA[SCALE][SCALE], double matrixB[SCALE], double x[SCALE])
{
	// 求解 L U
	int i;
	int j = 0;
	double matrixU[MATRIX_N][MATRIX_N] = { 0 };
	double matrixL[MATRIX_N][MATRIX_N] = { 0 };
	int k = 0;
	double sumtmp = 0;

	for (i = 0; i < MATRIX_N; i++){
		for (j = i; j < MATRIX_N; j++){
			// U 第 i+1 行
			matrixU[i][j] = matrixA[i][j];
			for (k = 0; k < i; k++){
				matrixU[i][j] -= matrixL[i][k] * matrixU[k][j];
			}
		}
		for (j = i; j < MATRIX_N; j++){
			// L 第 i+1 列
			if (j == i){
				matrixL[j][i] = 1;
			}
			else{
				matrixL[j][i] = matrixA[j][i];
				for (k = 0; k < i; k++){
					matrixL[j][i] -= matrixL[j][k] * matrixU[k][i];
				}
				matrixL[j][i] /= matrixU[i][i];
			}
		}
	}
	/*
	// 已弃用代码，用于验证 multiplyMatrix() 函数的正确性
	double test1[2][2] = { { 1, 1 }, { 2, 2 } };
	double test2[2][2] = { { 1, 0 }, { 0, 1 } };
	double testCheck[2][2] = { 0 };
	multiplyMatrix(2, 2, test1, 2, 2, test2, testCheck);
	printMatrix(2, 2, testCheck);
	*/

#ifdef DEBUG
	puts("求得下三角矩阵L为：\n");
	printMatrix(MATRIX_N, MATRIX_N, matrixL);
	puts("求得上三角矩阵U为：\n");
	printMatrix(MATRIX_N, MATRIX_N, matrixU);
	double matrixCheck[MATRIX_N][MATRIX_N] = { 0 };
	multiplyMatrix(MATRIX_N, MATRIX_N, matrixL, MATRIX_N, MATRIX_N, matrixU, matrixCheck);
	puts("将LU回乘后得：\n");
	printMatrix(MATRIX_N, MATRIX_N, matrixCheck);
#endif

	// 求解 y
	double y[MATRIX_N];
	for (i = 0; i < MATRIX_N; i++){
		y[i] = matrixB[i];
		for (k = 0; k < i; k++){
			y[i] -= matrixL[i][k] * y[k];
		}
	}
#ifdef DEBUG
	puts("算得y为：");
	printMatrix(MATRIX_N, 1, y);
#endif

	// 求解 x
	// double x[MATRIX_N];
	double sum;
	for (i = MATRIX_N - 1; i >= 0; i--){
		x[i] = y[i];
		for (j = MATRIX_N - 1; j > i; j--) {
			x[i] -= matrixU[i][j] * x[j];
		}
		x[i] /= matrixU[i][i];
	}
#ifdef DEBUG
	puts("解得：x=");
	printMatrix(MATRIX_N, 1, x);
#endif
	return 0;
}

/*	回代比较函数
	返回值：0
	输入参数：data, num, coefficientX, coefficientY, coefficientZ
	输出参数：output
*/
int reCompare(double data[][VARIBLES], int num, double output[][VARIBLES], double coefficientX[SCALE], double coefficientY[SCALE], double coefficientZ[SCALE])
{
	int i,k;
	for (i = 0; i < num; i++)
	{
		output[i][0] = data[i][0];
		output[i][1] = 0;
		output[i][2] = 0;
		output[i][3] = 0;
		for (k = 0; k < SCALE; k++)
		{
			output[i][1] += coefficientX[i] * calChebyshev(k, output[i][0]);
			output[i][2] += coefficientY[i] * calChebyshev(k, output[i][0]);
			output[i][3] += coefficientZ[i] * calChebyshev(k, output[i][0]);
		}
		//output[i][1] -= data[i][1];
		//output[i][2] -= data[i][2];
		//output[i][3] -= data[i][3];
	}
}