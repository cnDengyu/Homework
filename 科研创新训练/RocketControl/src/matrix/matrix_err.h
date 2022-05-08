#pragma once

#ifndef __MATRIX_ERR_H
#define __MATRIX_ERR_H

/*
*	Copyright© 2021 LittleSunny
*	No rights reserved
*
*	文件名称：matrix_err.h
*	文件标识：
*	摘要：矩阵基础库的报错文本声明
*
*	当前版本：0.1
*	原作者：章登宇
*	完成日期：2021年1月3日
*
*	本文件包含矩阵相关的报错文本的声明，具体实现在 matrix_err.c 中
*/

extern const char err_fail_alloc_mem[];
extern const char oper_create_mat[];
extern const char err_rows_or_cols_less_than_1[];
extern const char err_rows_and_cols_not_match[];
extern const char oper_multiply_matrix[];
extern const char err_rows_or_cols_out_of_range[];
extern const char oper_get_value[];
extern const char err_matrix_broken[];
extern const char oper_print_matrix[];
extern const char oper_set_value[];
extern const char oper_get_LUD[];
extern const char err_matrix_not_square[];
extern const char oper_matrix_minus[];
extern const char oper_matrix_add[];
extern const char oper_matrix_inverse_by_value[];
extern const char oper_matrix_set_zeros[];
extern const char oper_matrix_copy[];
extern const char oper_matrix_one_norm[];
void MatrixPrintError(const char* type, const char* operation);

#endif
