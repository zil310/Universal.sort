#include "test.h"
#include "sort.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef int (*cmp_skf)(void* el_a, void* el_b);
typedef void (*sort_stf)(void* arr, int len_arr, int el_size, cmp_skf cmp);


int cmp_int(void* el_a, void* el_b) 
{
    int a = *(int*) el_a;
    int b = *(int*) el_b;
    return (a > b) - (b > a);
}


int cmp_char(void* el_a, void* el_b) 
{
    char a = *(char*) el_a;
    char b = *(char*) el_b;
    return (a > b) - (b > a);
}


int cmp_float(void* el_a, void* el_b) 
{
    float a = *(float*) el_a;
    float b = *(float*) el_b;
    return (a > b) - (b > a);
}


int cmp_double(void* el_a, void* el_b) 
{
    double a = *(double*) el_a;
    double b = *(double*) el_b;
    return (a > b) - (b > a);
}


int* generate_random_arr_int (int len_arr)
{
    int* arr = malloc(len_arr * sizeof(int));

    for (int i = 0; i < len_arr; ++i)
    {
        arr[i] = rand() % 2298 - 1000;
    }

    return arr;
}


char* generate_random_arr_char (int len_arr)
{
    char* arr = malloc(len_arr * sizeof(char));

    for (int i = 0; i < len_arr; ++i)
    {
        arr[i] = 32 + (rand() % 95); // таким образом мы попадаем в диапозон символов печатных по таблице ASCII
    }
    return arr;
}


double* generate_random_arr_double (int len_arr)
{
    double* arr = malloc(len_arr * sizeof(double));

    for (int i = 0; i < len_arr; ++i)
    {
        arr[i] = ((double)rand() / RAND_MAX) * 2000.0 - 1000.0;
    }
    return arr;
}


float* generate_random_arr_float (int len_arr)
{
    float* arr = malloc(len_arr * sizeof(float));

    for (int i = 0; i < len_arr; ++i)
    {
        arr[i] = ((float)rand() / RAND_MAX) * 2000.0f - 1000.0f; // да бы комп понимал что именно float
    }
    return arr;
}


void check_sort_arr (void* arr, int len_arr, int el_size, cmp_skf cmp)
{
    for (int i = 0; i < len_arr - 1; ++i)
    {
        void* add_el = (char*) arr + (i * el_size);
        void* add_next_el = (char*) arr + ((i + 1) * el_size);
        assert (cmp (add_el, add_next_el) <=0);
    }
}


void test_empt_arr (sort_stf sort)
{
    sort (NULL, 0, sizeof(int), cmp_int);
    check_sort_arr (NULL, 0, sizeof(int), cmp_int);
}


void test_one_arr (sort_stf sort)
{
    int arr[] = {1};
    sort (arr, 1, sizeof(int), cmp_int);
    check_sort_arr (arr, 1, sizeof(int), cmp_int);
}


void test_two_arr (sort_stf sort)
{
    int arr[] = {6,7};
    sort (arr, 2, sizeof(int), cmp_int);
    check_sort_arr (arr, 2, sizeof(int), cmp_int);
}


void test_zero_arr (sort_stf sort)
{   
    int arr[20] = {0}; 
    sort (arr, 20, sizeof(int), cmp_int);
    check_sort_arr (arr, 20, sizeof(int), cmp_int);
}


void test_big_random_arr (sort_stf sort)
{
    int len_arr = 1000;
    int* arr = generate_random_arr_int (len_arr);
    sort (arr, len_arr, sizeof(int), cmp_int);
    free (arr);
}


void test_random_arr_char (sort_stf sort)
{
    int len_arr = 100;
    char* arr = generate_random_arr_char (len_arr);
    sort (arr, len_arr, sizeof(char), cmp_char);
    free (arr);
}


void test_random_arr_double (sort_stf sort)
{
    int len_arr = 100;
    double* arr = generate_random_arr_double (len_arr);
    sort (arr, len_arr, sizeof(double), cmp_double);
    free (arr);
}


void test_random_arr_float (sort_stf sort)
{
    int len_arr = 100;
    float* arr = generate_random_arr_float (len_arr);
    sort (arr, len_arr, sizeof(float), cmp_float);
    free (arr);
}


void RUN_ALL_TESTS (sort_skf sort)
{
    test_empt_arr(sort);
    test_one_arr(sort);
    test_two_arr(sort);
    test_zero_arr(sort);
    test_big_random_arr(sort);
    test_random_arr_char(sort);
    test_random_arr_double(sort);
    test_random_arr_float(sort);

    printf("Good work, all tests passed!\n");
}