/*
*	Copyright© 2021 LittleSunny
*	No rights reserved
*
*	文件名称：matrix_err.c
*	文件标识：
*	摘要：矩阵基础库的相关报错文本
*
*	当前版本：0.1
*	原作者：章登宇
*	完成日期：2021年1月3日
*
*	本文件包含报错文本的定义，需要使用时请 include matrix_err.h
*/

#include <stdio.h>
#include "matrix_err.h"

#define DEBUG
#define LANGUAGE_ZH_CN

#ifdef LANGUAGE_ZH_CN
const char err_fail_alloc_mem[] = "分配内存失败";
const char oper_create_mat[] = "创建矩阵";
const char err_rows_or_cols_less_than_1[] = "行数或列数少于1";
const char err_rows_and_cols_not_match[] = "行数和列数不匹配";
const char oper_multiply_matrix[] = "矩阵相乘";
const char err_rows_or_cols_out_of_range[] = "行数或列数越界";
const char oper_get_value[] = "读取矩阵的值";
const char err_matrix_broken[] = "矩阵损坏";
const char oper_print_matrix[] = "输出矩阵";
const char oper_set_value[] = "修改矩阵的值";
const char oper_get_LUD[] = "提取方阵的LUD";
const char err_matrix_not_square[] = "矩阵不是方阵";
const char oper_matrix_minus[] = "矩阵减法";
const char oper_matrix_add[] = "矩阵加法";
const char oper_matrix_inverse_by_value[] = "矩阵求倒数";
const char oper_matrix_set_zeros[] = "矩阵清零";
const char oper_matrix_copy[] = "拷贝矩阵";
const char oper_matrix_one_norm[] = "计算矩阵的1-范数";
void MatrixPrintError(const char* type, const char* operation)
{
#ifdef DEBUG
	printf("在 <%s> 时，<%s>。\n", operation, type);
#endif
}
#endif

#ifdef LANGUAGE_EN
const char err_fail_alloc_mem[] = "Failed to allocate memory";
const char oper_create_mat[] = "Creating Matrix";
const char err_rows_or_cols_less_than_1[] = "Number of Rows or Columns is less than 1";
const char err_rows_and_cols_not_match[] = "Number of Rows and Columns dosn't Match";
const char oper_multiply_matrix[] = "Multiplying matrix";
const char err_rows_or_cols_out_of_range[] = "Rows or Columns out of Range";
const char oper_get_value[] = "Reading Value of Matrix";
const char err_matrix_broken[] = "Matrix Broken";
const char oper_set_value[] = "Setting a Value of Matrix";
const char oper_get_LUD[] = "Getting LUD of a Square Matrix";
const char err_matrix_not_square[] = "Matrix is not Square";
const char oper_matrix_minus[] = "Subtracting Matrix";
const char oper_matrix_inverse_by_value[] = "Inversing Matrix by Value";
const char oper_matrix_set_zeros[] = "Setting Zeros of a Matrix";
const char oper_matrix_copy[] = "Copying Matrix";
const char oper_matrix_one_norm[] = "Calculating 1-Norm of a Matrix";
void MatrixPrintError(const char* type, const char* operation)
{
#ifdef DEBUG
	printf("<%s> when <%s>.\n", type, operation);
#endif
}
#endif