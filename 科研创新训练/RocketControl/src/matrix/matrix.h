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
*
* ------------------------------------------------------
*
* 矩阵基础库是数值计算方法课程的一部分内容，
* 现将其引入到科研创新训练课程的飞控程序中。
* 引入后进行了一些修改，这些修改不会被同步到数值计算方法的文件中。
* 引入时间：2022年3月5日
*
*/

#pragma once

#ifndef __MATRIX_H
#define __MATRIX_H

#define NULL 0

typedef struct matrix {
	unsigned int rows;
	unsigned int cols;
	double* data;
	unsigned int size;
	struct matrix* self;
} Matrix, MATRIX;

Matrix* MatrixCreate(unsigned int rows, unsigned int cols);
void MatrixDelete(Matrix** mat);
Matrix* MatrixBuildFromArray(double* data, unsigned int rows, unsigned int cols);
Matrix* MatrixCreateEye(unsigned int size);
int MatrixCheck(Matrix* mat, const char* operation);
int MatrixGetValue(Matrix* mat, unsigned int row, unsigned int col, double* dst);
int MatrixSetValue(Matrix* mat, unsigned int row, unsigned int col, double value);
int MatrixMultiply(Matrix* mat1, Matrix* mat2, Matrix** dst);
// void MatrixMultiplyCheck(void);
int MatrixGetLUD(Matrix* mat, Matrix** matL, Matrix** matU, Matrix** matD);
int MatrixMinus(Matrix* matMinute, Matrix* matMinus, Matrix** matResult);
int MatrixAdd(Matrix* matSrc, Matrix* matAdd, Matrix** matDst);
int MatrixInverseByValue(Matrix* mat, Matrix** dst);
int MatrixSetZeros(Matrix* mat);
int MatrixCopy(Matrix* src, Matrix** dst);
int MatrixOneNorm(Matrix* mat, double* norm);
int MatrixTransfer(Matrix* mat, Matrix** dst);
int MatrixCofactor(Matrix* mat, unsigned row, unsigned col, Matrix** dst);
int MatrixDet(Matrix* mat, double* result);
int MatrixInv(Matrix* src, Matrix** dst);
int MatrixCrossProduct(Matrix* vec1, Matrix* vec2, Matrix** dst);

#ifndef STM32F10X_LD

void MatrixPrint(Matrix* mat);

#endif

#endif
