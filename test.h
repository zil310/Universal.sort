#pragma once


typedef int (*cmp_skf)(void* el_a, void* el_b);


typedef void (*sort_stf)(void* arr, int len_arr, int el_size, cmp_skf cmp);


void test_empt_arr(sort_stf sort);


void test_one_arr(sort_stf sort);


void test_two_arr(sort_stf sort);


void test_zero_arr(sort_stf sort);


void test_big_random_arr(sort_stf sort);


void test_random_arr_char(sort_stf sort);


void test_random_arr_double(sort_stf sort);


void test_random_arr_float(sort_stf sort);


void RUN_ALL_TESTS(sort_stf sort);