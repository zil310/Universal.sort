#pragma once


typedef int (*cmp_skf)(void* el_a, void* el_b);
typedef void (*sort_stf)(void* arr, int len_arr, int el_size, cmp_skf cmp);

int cmp_int (void* el_a, void* el_b);


int cmp_char (void* el_a, void* el_b);


int cmp_float (void* el_a, void* el_b);


int cmp_double (void* el_a, void* el_b);


int check_order_arr (void* arr, int len_arr, int el_size, cmp_skf cmp);


int check_affil_arr (void* orig_arr, void* sort_arr, int len_arr, int el_size);


int check_sort_arr (void* orig_arr, void* sort_arr, int len_arr, int el_size, cmp_skf cmp);


void test_empt_arr (sort_stf sort);


void test_one_arr (sort_stf sort);


void test_two_arr (sort_stf sort);


void test_zero_arr (sort_stf sort);


void test_big_not_random_arr (sort_stf sort, const char* file_name, int len_arr);


void test_not_random_arr_char (sort_stf sort, const char* file_name, int len_arr);


void test_not_random_arr_double (sort_stf sort, const char* file_name, int len_arr);


void test_not_random_arr_float (sort_stf sort, const char* file_name, int len_arr);


void RUN_ALL_TESTS (sort_stf sort);