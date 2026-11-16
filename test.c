#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "test.h"
#include "sort.h"


typedef int (*cmp_skf)(void* el_a, void* el_b);
typedef void (*sort_skf)(void* arr, int len_arr, int el_size, cmp_skf cmp);


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


void test_sort (sort_skf sort)
{
    sort (NULL, 0, sizeof(int), cmp_int);
    check_sort_arr (NULL, 0, sizeof(int), cmp_int);

    int one[] = {1};
    sort (one, 1, sizeof(int), cmp_int);
    check_sort_arr (one, 1, sizeof(int), cmp_int);

    int two[] = {4, 1};
    sort (two, 2, sizeof(int), cmp_int);
    check_sort_arr (two, 2, sizeof(int), cmp_int);

    int dubs[20] = {0};
    sort(dubs, 20, sizeof(int), cmp_int);
    check_sort_arr(dubs, 20, sizeof(int), cmp_int);

    int sizes[] = {15, 100, 10000};
    for (int i = 0; i < 3; ++i) 
    {
        int len = sizes[i];
    

        int* arr_int = generate_random_arr_int (len);
        sort (arr_int, len, sizeof(int), cmp_int);
        check_sort_arr (arr_int, len, sizeof(int), cmp_int);
        free (arr_int);

        char* arr_char = generate_random_arr_char (len);
        sort (arr_char, len, sizeof(char), cmp_char);
        check_sort_arr (arr_char, len, sizeof(char), cmp_char);
        free (arr_char);

        float* arr_float = generate_random_arr_float (len);
        sort (arr_float, len, sizeof(float), cmp_float);
        check_sort_arr (arr_float, len, sizeof(float), cmp_float);
        free (arr_float);

        double* arr_double = generate_random_arr_double (len);
        sort (arr_double, len, sizeof(double), cmp_double);
        check_sort_arr (arr_double, len, sizeof(double), cmp_double);
        free (arr_double);
    }    
}