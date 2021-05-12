#pragma once

/*
*	Copyright© 2021 LittleSunny
*	No rights reserved
* 
*	文件名称：matrix.h
*	文件标识：
*	摘要：矩阵基础库
* 
*	当前版本：0.1
*	原作者：章登宇
*	完成日期：2021年1月3日
*	
*	本文件包含矩阵函数的定义，具体实现在 matrix.c 中
*/

typedef struct matrix{
	int rows;
	int cols;
	double* data;
	int size;
	struct matrix* self;
} Matrix,MATRIX;

Matrix* MatrixCreate(int rows, int cols);
void MatrixDelete(Matrix** mat);
Matrix* MatrixBuildFromArray(double* data, int rows, int cols);
int MatrixCheck(Matrix* mat, const char* operation);
int MatrixGetValue(Matrix* mat, int row, int col, double* dst);
int MatrixSetValue(Matrix* mat, int row, int col, double value);
void MatrixPrint(Matrix* mat);
int MatrixMultiply(Matrix* mat1, Matrix* mat2, Matrix** dst);
void MatrixMultiplyCheck();
int MatrixGetLUD(Matrix* mat, Matrix** matL, Matrix** matU, Matrix** matD);
int MatrixMinus(Matrix* matMinute, Matrix* matMinus, Matrix** matResult);
int MatrixAdd(Matrix* matSrc, Matrix* matAdd, Matrix** matDst);
int MatrixInverseByValue(Matrix* mat, Matrix** dst);
int MatrixSetZeros(Matrix* mat);
int MatrixCopy(Matrix* src, Matrix** dst);
int MatrixOneNorm(Matrix* mat, double* norm);
