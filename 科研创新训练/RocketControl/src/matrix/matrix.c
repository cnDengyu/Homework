/*
*	Copyright© 2021 LittleSunny
*	All rights reserved
*
* charset : GBK
*
*	文件名称：matrix.c
*	文件标识：
*	摘要：矩阵基础库
*
*	当前版本：0.1
*	原作者：章登宇
*	完成日期：2021年1月3日
*
*	本文件包含矩阵函数的实现，需要使用时请 include matrix.h
*
* ------------------------------------------------------
*
* 矩阵基础库是数值计算方法课程的一部分内容，
* 现将其引入到科研创新训练课程的飞控程序中。
* 引入后进行了一些修改，这些修改不会被同步到数值计算方法的文件中。
* 引入时间：2022年3月5日
*
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef STM32F10X_LD

#include <stdio.h>

#endif

#include "matrix.h"
#include "matrix_err.h"

/*
*	函数名称：创建矩阵 MatrixCreate
*	输入参数：行数 lines，列数 cols
*	返回值：矩阵指针 Matrix*
*	说明：分配内存失败时，返回 NULL 并输出错误信息。
*/
Matrix* MatrixCreate(unsigned int rows, unsigned int cols)
{

	if (rows * cols < 1)
	{
		MatrixPrintError(err_rows_or_cols_less_than_1, oper_create_mat);
		return NULL;
	}

	Matrix* ret = (Matrix*)malloc(sizeof(Matrix));
	double* dataptr = (double*)malloc(sizeof(double) * rows * cols);
	if (dataptr == NULL || ret == NULL)
	{
		MatrixPrintError(err_fail_alloc_mem, oper_create_mat);
		return NULL;
	}

	ret->cols = cols;
	ret->rows = rows;
	ret->self = ret;
	ret->size = cols * rows;
	ret->data = dataptr;

	return ret;
}

/*
*	函数名称：删除矩阵 MatrixDelete
*	输入参数：需要删除的矩阵的地址 mat
*	返回值：空
*/
void MatrixDelete(Matrix** mat)
{
	if ((*mat) == NULL)
	{
		return;
	}
	if ((*mat)->data != NULL)
	{
		free((*mat)->data);
	}
	free((*mat));
	(*mat) = NULL;
}


/*
*	函数：从数组构建矩阵
*	输入参数：目标矩阵的地址 mat，数组指针 data, 行数 rows， 列数 cols
*	输出参数：目标矩阵 mat
*	返回值：0
*/
Matrix* MatrixBuildFromArray(double* data, unsigned int rows, unsigned int cols)
{
	Matrix* mat = MatrixCreate(rows, cols);
	double* ptr = mat->data;
	unsigned int n = rows * cols;
	while (n-- > 0)
	{
		*ptr++ = *data++;
	}
	return mat;
}

/*
*	函数名称：创建单位矩阵 MatrixCreate
*	输入参数：行数列数 size
*	返回值：矩阵指针 Matrix*
*	说明：分配内存失败时，返回 NULL 并输出错误信息。
*/
Matrix* MatrixCreateEye(unsigned int size)
{
	unsigned int i, j;
	if (size < 1)
	{
		MatrixPrintError(err_rows_or_cols_less_than_1, oper_create_mat);
		return NULL;
	}

	Matrix* ret = (Matrix*)malloc(sizeof(Matrix));
	double* dataptr = (double*)malloc(sizeof(double) * size * size);
	if (dataptr == NULL || ret == NULL)
	{
		MatrixPrintError(err_fail_alloc_mem, oper_create_mat);
		return NULL;
	}

	ret->cols = size;
	ret->rows = size;
	ret->self = ret;
	ret->size = size * size;
	ret->data = dataptr;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (i == j)
			{
				*(ret->data + i * size + j) = 1;
			}
			else {
				*(ret->data + i * size + j) = 0;
			}
		}
	}

	return ret;
}


/*
*	函数名称：矩阵清零 MatrixSetZeros
*	输入参数：矩阵 mat
*	输出参数：矩阵 mat
*	返回值：0
*/
int MatrixSetZeros(Matrix* mat)
{

	memset(mat->data, 0, mat->size * sizeof(double));
	return 0;
}


/*
*	函数名称：矩阵检测 MatrixCheck
*	输入参数：矩阵 mat
*	返回值：0或-1
*	功能：校验矩阵是否正常。正常则返回0。
*/
int MatrixCheck(Matrix* mat, const char* operation)
{
	if (mat == NULL)
	{
		MatrixPrintError(err_matrix_broken, operation);
		return -1;
	}
	if (mat->self != mat)
	{
		MatrixPrintError(err_matrix_broken, operation);
		return -1;
	}
	return 0;
}


/*
*	函数名称：获取矩阵的值 MatrixGetValue
*	输入参数：矩阵 mat，行号 row，列号 col
*	返回值：矩阵的值
*	说明：行、列均从1开始计算。
*/
int MatrixGetValue(Matrix* mat, unsigned int row, unsigned int col, double* dst)
{

	if (row > mat->rows || col > mat->cols)
	{
		MatrixPrintError(err_rows_or_cols_out_of_range, oper_get_value);
		return -2;
	}
	*dst = *(mat->data + (row - 1) * mat->cols + col - 1);
	return 0;
}


/*
*	函数名称：修改矩阵的值
*	传入参数：矩阵mat，行号row，列号col，修改值value
*	返回值：0
*/
int MatrixSetValue(Matrix* mat, unsigned int row, unsigned int col, double value)
{

	if (row > mat->rows || col > mat->cols)
	{
		MatrixPrintError(err_rows_or_cols_out_of_range, oper_get_value);
		return -2;
	}
	*(mat->data + (row - 1) * mat->cols + col - 1) = value;
	return 0;
}


/*
*	函数名称：矩阵输出函数 MatrixPrint
*	输入参数：矩阵 mat
*	返回值：空
*/
#ifndef STM32F10X_LD
void MatrixPrint(Matrix* mat)
{
	if (MatrixCheck(mat, oper_print_matrix))
	{
		return;
	}
	unsigned int i = 0;
	unsigned int j = 0;
	double* tmp = mat->data;
	putchar('\n');
	for (i = 0; i < mat->rows; i++) {
		for (j = 0; j < mat->cols; j++) {
			printf(" %10lf ", *tmp++);
		}
		putchar('\n');
	}
	putchar('\n');
}
#endif

/*
*	函数名称：矩阵拷贝
*	输入参数：矩阵src
*	输出参数：矩阵dst
*	返回值：0
*/
int MatrixCopy(Matrix* src, Matrix** dst)
{
	if (MatrixCheck(src, oper_matrix_copy))
	{
		return -1;
	}
	MatrixDelete(dst);
	(*dst) = MatrixCreate(src->rows, src->cols);
	double* dataDst = (*dst)->data;
	double* dataSrc = src->data;
	unsigned int n = src->size;
	while (n-- > 0)
	{
		*dataDst++ = *dataSrc++;
	}
	return 0;
}


/*
	函数名称：矩阵乘法 MatrixMultiply
	传入参数：mat1, mat2
	输出参数：dst
	返回值：
		执行了矩阵运算则返回0。
		如果矩阵校验失败，则返回-1。
		传入矩阵必须符合乘法定义，即rows1 必须等于 lines2，否则函数不会执行，并返回-2。
		如果矩阵读值时发生越界，则返回-3（这种情况不应该发生）
*/
int MatrixMultiply(Matrix* mat1, Matrix* mat2, Matrix** dst)
{
	unsigned int i, j, k;
	if (MatrixCheck(mat1, oper_multiply_matrix) || MatrixCheck(mat2, oper_multiply_matrix))
	{
		return -1;
	}
	if (mat1->cols != mat2->rows) {
		MatrixPrintError(err_rows_and_cols_not_match, oper_multiply_matrix);
		return -2;
	}

	MatrixDelete(dst);
	(*dst) = MatrixCreate(mat1->rows, mat2->cols);
	double* result = (*dst)->data;
	double value1, value2;
	int flag1, flag2;

	for (i = 1; i <= mat1->rows; i++) {
		for (j = 1; j <= mat2->cols; j++) {
			*result = 0;
			for (k = 1; k <= mat1->cols; k++) {
				flag1 = MatrixGetValue(mat1, i, k, &value1);
				flag2 = MatrixGetValue(mat2, k, j, &value2);
				if (flag1 && flag2)
				{
					return -3;
				}
				else
				{
					*result += value1 * value2;
				}
			}
			result++;
		}
	}
	return 0;
}

/*	验证乘法函数正确性
	返回值：空
*/
/*
void MatrixMultiplyCheck()
{
	double test1[2][2] = { { 1, 1 }, { 2, 2 } };
	double test2[2][2] = { { 1, 0 }, { 0, 1 } };
	// double testCheck[2][2] = { 0 };
	Matrix *mat1, *mat2, *mat3;
	mat1 = MatrixBuildFromArray(&test1[0][0], 2, 2);
	mat2 = MatrixBuildFromArray(&test2[0][0], 2, 2);
	MatrixPrint(mat1);
	MatrixPrint(mat2);
	MatrixMultiply(mat1, mat2, &mat3);
	MatrixPrint(mat3);
}
*/

/*	函数名称：矩阵分成L、U、D
	返回值：0
	输入参数：mat
	输出参数：matL, matU, matD
*/
int MatrixGetLUD(Matrix* mat, Matrix** matL, Matrix** matU, Matrix** matD)
{
	if (MatrixCheck(mat, oper_get_LUD))
	{
		return -1;
	}

	if (mat->rows != mat->cols)
	{
		MatrixPrintError(err_matrix_not_square, oper_get_LUD);
		return -2;
	}

	MatrixDelete(matL);
	MatrixDelete(matU);
	MatrixDelete(matD);
	(*matL) = MatrixCreate(mat->rows, mat->cols);
	(*matU) = MatrixCreate(mat->rows, mat->cols);
	(*matD) = MatrixCreate(mat->rows, mat->cols);

	unsigned int i = 0;
	unsigned int j = 0;
	double* dataA = mat->data;
	double* dataL = (*matL)->data;
	double* dataU = (*matU)->data;
	double* dataD = (*matD)->data;

	for (i = 0; i < mat->rows; i++)
	{
		for (j = 0; j < mat->cols; j++, dataA++)
		{
			if (j == i)
			{
				*dataL++ = 0;
				*dataU++ = 0;
				*dataD++ = *dataA;
			}
			else if (j > i)
			{
				*dataU++ = -*dataA;
				*dataL++ = 0;
				*dataD++ = 0;
			}
			else if (j < i)
			{
				*dataL++ = -*dataA;
				*dataU++ = 0;
				*dataD++ = 0;
			}
		}
	}
	return 0;
}


/*	矩阵减法
	返回值：0
	输入参数：matMinute, matMinus
	输出参数：matResult
*/
int MatrixMinus(Matrix* matMinute, Matrix* matMinus, Matrix** matResult)
{
	if (MatrixCheck(matMinute, oper_matrix_minus) || MatrixCheck(matMinus, oper_matrix_minus))
	{
		return -1;
	}
	if (matMinute->rows != matMinus->rows || matMinute->cols != matMinus->cols)
	{
		MatrixPrintError(err_rows_and_cols_not_match, oper_matrix_minus);
		return -2;
	}

	double* dataMinute = matMinute->data;
	double* dataMinus = matMinus->data;
	MatrixDelete(matResult);
	(*matResult) = MatrixCreate(matMinute->rows, matMinute->cols);
	double* dataResult = (*matResult)->data;

	unsigned int n = matMinute->cols * matMinute->rows;
	while (n-- > 0)
	{
		*dataResult++ = *dataMinute++ - *dataMinus++;
	}
	return 0;
}

/*	矩阵加法
	返回值：0
	输入参数：matSrc, matAdd
	输出参数：matDst
*/
int MatrixAdd(Matrix* matSrc, Matrix* matAdd, Matrix** matDst)
{
	if (MatrixCheck(matSrc, oper_matrix_add) || MatrixCheck(matAdd, oper_matrix_add))
	{
		return -1;
	}
	if (matSrc->rows != matAdd->rows || matSrc->cols != matAdd->cols)
	{
		MatrixPrintError(err_rows_and_cols_not_match, oper_matrix_add);
		return -2;
	}

	double* dataSrc = matSrc->data;
	double* dataAdd = matAdd->data;
	MatrixDelete(matDst);
	(*matDst) = MatrixCreate(matSrc->rows, matSrc->cols);
	double* dataResult = (*matDst)->data;

	unsigned int n = matSrc->cols * matSrc->rows;
	while (n-- > 0)
	{
		*dataResult++ = *dataSrc++ + *dataAdd++;
	}
	return 0;
}

/**
  * @brief  矩阵的每一个值取倒数（可用于计算对角矩阵的逆矩阵）
  * @param  对角矩阵diag 和 目标矩阵 dst
  * @retval error flag
  */
int MatrixInverseByValue(Matrix* mat, Matrix** dst)
{
	if (MatrixCheck(mat, oper_matrix_inverse_by_value))
	{
		return -1;
	}
	unsigned int i, j;
	double* data = mat->data;
	MatrixDelete(dst);
	(*dst) = MatrixCreate(mat->rows, mat->cols);
	double* dataDst = (*dst)->data;
	for (i = 0; i < mat->rows; i++)
	{
		for (j = 0; j < mat->cols; j++)
		{
			if (i == j && (*data != 0))
			{
				*dataDst++ = 1.0 / *data;
			}
			else
			{
				*dataDst++ = 0;
			}
			data++;
		}
	}
	return 0;
}

/*
*	函数名称：矩阵的1-范数（列范数） MatrixOneNorm
*	输入参数：矩阵 mat
*	输出参数：范数 norm
*	返回值：0
*/
int MatrixOneNorm(Matrix* mat, double* norm)
{
	if (MatrixCheck(mat, oper_matrix_one_norm))
	{
		return -1;
	}

	double max = 0;
	double sum = 0;
	double value;
	unsigned int i, j;

	for (j = 1; j <= mat->cols; j++)
	{
		sum = 0;
		for (i = 1; i <= mat->cols; i++)
		{
			if (MatrixGetValue(mat, i, j, &value))
			{
				return -3;
			}
			else
			{
				sum += fabs(value);
			}
		}
		if (sum > max)
		{
			max = sum;
		}
	}
	*norm = max;
	return 0;
}

/**
  * @brief  Matrix Transfer 矩阵转置
  * @param  mat to transfer and dst transfered
  * @retval error flag
  */
int MatrixTransfer(Matrix* mat, Matrix** dst)
{
	unsigned int i, j;

	MatrixDelete(dst);
	*dst = MatrixCreate(mat->cols, mat->rows);

	for (i = 0; i < mat->cols; i++)
	{
		for (j = 0; j < mat->rows; j++)
		{
			*((*dst)->data + i * mat->rows + j) = *(mat->data + j * mat->cols + i);
		}
	}
	return 0;
}

/**
  * @brief  Matrix cofactor 矩阵余子式
  * @param  mat to get cofactor and position and dst
  * @retval error flag
  */

int MatrixCofactor(Matrix* mat, unsigned row, unsigned col, Matrix** dst)
{
	unsigned int i, j;
	unsigned int ofi, ofj;
	if (mat == NULL)
	{
		return -1;
	}

	if (row > mat->rows || col > mat->cols)
	{
		return -2;
	}
	
	if (mat->rows <= 1 )
	{
		return -3;
	}

	MatrixDelete(dst);
	*dst = MatrixCreate(mat->rows - 1, mat->cols - 1);

	for (i = 0; i < (*dst)->rows; i++)
	{
		for (j = 0; j < (*dst)->cols; j++)
		{
			if (i < row - 1)
			{
				ofi = 0;
			}
			else
			{
				ofi = 1;
			}
			if (j < col - 1)
			{
				ofj = 0;
			}
			else
			{
				ofj = 1;
			}

			*((*dst)->data + i * (*dst)->cols + j) = *(mat->data + (i + ofi) * mat->cols + j + ofj);

		}
	}

	// MatrixPrint(*dst);

	return 0;
}

/**
  * @brief  Matrix determinant 矩阵行列式
  * @param  mat to get determinant and the determinant
  * @retval error flag
  */
int MatrixDet(Matrix* mat, double* result)
{
	Matrix* D = NULL;
	unsigned int k;
	double d;
	double res = 0;
	int sign = 1;

	if (mat == NULL)
	{
		return -1;
	}

	if (mat->cols != mat->rows)
	{
		return -2;
	}

	if (mat->rows == 0)
	{
		return -3;
	}

	if (mat->cols == 1)
	{
		*result = *(mat->data);
		return 0;
	}

	// D = MatrixCreate(mat->rows - 1, mat->cols - 1);

	for (k = 0; k < mat->rows; k++)
	{
		/*
		// 按第一列展开，求余子式
		for (i = 0; i < D->rows; i++)
		{
			if (i < k)
			{
				for (j = 0; j < D->cols; j++)
				{
					*(D->data + i * D->cols + j) = *(mat->data + (i)*mat->cols + j + 1);		//D[i][j] = A[i][j+1]
				}
			}
			else if (i >= k)
			{
				for (j = 0; j < D->cols; j++)
				{
					*(D->data + (i) * D->cols + j) = *(mat->data + (i + 1) * mat->cols + j + 1);	//D[i][j] = A[i+1][j+1]
				}
			}
		}
		*/

		MatrixCofactor(mat, k + 1, 1, &D);
		// MatrixPrint(D);
		MatrixDet(D, &d);
		// printf("\n%lf\n", d);
		MatrixDelete(&D);

		res += sign * *(mat->data + k * mat->cols) * d;		// ΣA[i][1]*det(D)	

		sign = sign * (-1);
	}

	*result = res;

	MatrixDelete(&D);
	return 0;
}

/**
  * @brief  Matrix invert 矩阵求逆
  * @param  mat to invert and dst inverted
  * @retval error flag
  */

int MatrixInv(Matrix* mat, Matrix** dst)
{
	unsigned int i, j;
	Matrix* D = NULL;
	double det = 0;
	double temp = 0;
	int sign = 1;

	if (mat == NULL)
	{
		return -1;
	}

	if (mat->rows != mat->cols)
	{
		return -2;
	}

	MatrixDet(mat, &det);
	if (det == 0)
	{
		return -3;
	}

	MatrixDelete(dst);
	*dst = MatrixCreate(mat->rows, mat->cols);
	
	if(mat->rows == 1)
	{
		MatrixSetValue(*dst, 1, 1, 1.0/det);
		return 0;
	}

	for (i = 0; i < mat->rows; i++)
	{
		for (j = 0; j < mat->cols; j++)
		{
			MatrixCofactor(mat, i+1, j+1, &D);
			MatrixDet(D, &temp);
			if ((i+j)%2 != 0)
			{
				sign = -1;
			}
			else 
			{
				sign = 1;
			}
			MatrixSetValue(*dst, i+1, j+1, sign * temp / det);
			// *((*dst)->data + i * (*dst)->cols + j) = sign * temp / det;
		}
	}

	MatrixDelete(&D);
	return 0;
}

/**
  * @brief  Matrix Cross Product 3×1向量叉乘
  * @param  two oper vector and a dst vector
  * @retval error flag
  */
int MatrixCrossProduct(Matrix* vec1, Matrix* vec2, Matrix** dst)
{
	unsigned int i = 0;
	double temp1[3], temp2[3], temp3[3];

	if (vec1->rows != 3 || vec1->cols != 1 || vec2->rows != 3 || vec2->cols != 1) {
		return -1;
	}

	MatrixDelete(dst);

	*dst = MatrixCreate(3, 1);

	for (i = 0; i < 3; i++)
	{
		MatrixGetValue(vec1, i + 1, 1, &temp1[i]);
		MatrixGetValue(vec2, i + 1, 1, &temp2[i]);
	}

	// (l,m,n)×(o,p,q) = (mq-np,no-lq,lp-mo)
	temp3[0] = temp1[1] * temp2[2] - temp1[2] * temp2[1];
	temp3[1] = temp1[2] * temp2[0] - temp1[0] * temp2[2];
	temp3[2] = temp1[0] * temp2[1] - temp1[1] * temp2[0];

	for (i = 0; i < 3; i++)
	{
		MatrixSetValue(*dst, i + 1, 1, temp3[i]);
	}
	return 0;
}
