#pragma once

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

const char err_fail_alloc_mem[];
const char oper_create_mat[];
const char err_rows_or_cols_less_than_1[];
const char err_rows_and_cols_not_match[];
const char oper_multiply_matrix[];
const char err_rows_or_cols_out_of_range[];
const char oper_get_value[];
const char err_matrix_broken[];
const char oper_print_matrix[];
const char oper_set_value[];
const char oper_get_LUD[];
const char err_matrix_not_square[];
const char oper_matrix_minus[];
const char oper_matrix_add[];
const char oper_matrix_inverse_by_value[];
const char oper_matrix_set_zeros[];
const char oper_matrix_copy[];
const char oper_matrix_one_norm[];
void MatrixPrintError(const char* type, const char* operation);