#pragma once


void select_sort(void* arr, int len_arr, int el_size, int (*cmp_int)(void* el_a, void* el_b));


void quick_sort(void* arr, int len_arr, int el_size, int (*cmp_int)(void* el_a, void* el_b));