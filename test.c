#include "test.h"
#include "sort.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define LEN_ARR_INT 1000
#define LEN_ARR_DOUBLE 100
#define LEN_ARR_CHAR 100
#define LEN_ARR_FLOAT 100


#define FILE_NAME_INT "D:/C/Universal.sel.sort/int.txt"
#define FILE_NAME_CHAR "D:/C/Universal.sel.sort/char.txt"
#define FILE_NAME_FLOAT "D:/C/Universal.sel.sort/float.txt"
#define FILE_NAME_DOUBLE "D:/C/Universal.sel.sort/double.txt"



typedef int (*cmp_skf)(void* el_a, void* el_b);
typedef void (*sort_stf)(void* arr, int len_arr, int el_size, cmp_skf cmp);


int cmp_int (void* el_a, void* el_b);


int cmp_char (void* el_a, void* el_b);


int cmp_float (void* el_a, void* el_b);


int cmp_double (void* el_a, void* el_b);


int check_order_arr (void* arr, int len_arr, int el_size, cmp_skf cmp);


int check_affil_arr (void* orig_arr, void* sort_arr, int len_arr, int el_size);


int check_sort_arr (void* orig_arr, void* sort_arr, int len_arr, int el_size, cmp_skf cmp);



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


int check_order_arr (void* arr, int len_arr, int el_size, cmp_skf cmp)
{
    for (int i = 0; i < len_arr - 1; ++i)
    {
        void* add_el = (char*) arr + (i * el_size);
        void* add_next_el = (char*) arr + ((i + 1) * el_size);
        if ((cmp (add_el, add_next_el) > 0))
        {
            return 0;
        }
    }
    return 1;
}


int check_affil_arr (void* orig_arr, void* sort_arr, int len_arr, int el_size)
{
    for (int i = 0; i < len_arr; ++i)
    {
        void* check_el = (char*) orig_arr + (i * el_size);
        int count_orig_el = 0;
        int count_sort_el = 0;

        for (int j = 0; j < len_arr; ++j)
        {
            if (memcmp(check_el, (char*) orig_arr + (j * el_size), el_size) == 0)
            {
                count_orig_el++;
            }
            if (memcmp(check_el, (char*) sort_arr + (j * el_size), el_size) == 0)
            {
                count_sort_el++;
            }

        }
        if (count_orig_el != count_sort_el)
        {
            return 0;
        }
    }
    return 1;
}


int check_sort_arr (void* orig_arr, void* sort_arr, int len_arr, int el_size, cmp_skf cmp)
{
    return check_order_arr (sort_arr, len_arr, el_size, cmp) && check_affil_arr (orig_arr, sort_arr, len_arr, el_size);
}


void test_empt_arr (sort_stf sort) 
{
    sort (NULL, 0, sizeof(int), cmp_int);
    assert (check_sort_arr(NULL, NULL, 0, sizeof(int), cmp_int));
}

void test_one_arr (sort_stf sort) 
{
    int arr[] = {1};
    int orig[] = {1};
    sort (arr, 1, sizeof(int), cmp_int);
    assert (check_sort_arr(orig, arr, 1, sizeof(int), cmp_int));
}

void test_two_arr (sort_stf sort) 
{
    int arr[] = {7, 6};
    int orig[] = {7, 6};
    sort (arr, 2, sizeof(int), cmp_int);
    assert (check_sort_arr(orig, arr, 2, sizeof(int), cmp_int));
}

void test_zero_arr (sort_stf sort) 
{
    int arr = {0};
    int orig = {0};
    sort (arr, 20, sizeof(int), cmp_int);
    assert (check_sort_arr(orig, arr, 20, sizeof(int), cmp_int))
}

void test_big_not_random_arr (sort_stf sort)
{   
    int len_arr = LEN_ARR_INT;
    const char* file_name = FILE_NAME_INT

    FILE* file = fopen (file_name, "r");

    if (file == NULL)
    {
        return;
    }
    
    int* orig_arr = malloc (len_arr * sizeof(int));
    int* arr = malloc (len_arr * sizeof(int));

    if (orig_arr == NULL || arr == NULL)
    {
        free (orig_arr);
        free (arr);
        fclose (file);
        
        return;
    }
    
    for (int i = 0; i < len_arr; ++i)
    {
        fscanf (file, "%d", &arr[i]);
    }
    memcpy (orig_arr, arr, len_arr * sizeof(int));

    sort (arr, len_arr, sizeof(int), cmp_int);
    fclose (file);
    assert (check_sort_arr (orig_arr, arr, len_arr, sizeof(int), cmp_int));

    free (arr);
    free (orig_arr);
}


void test_not_random_arr_char (sort_stf sort)
{   
    int len_arr = LEN_ARR_CHAR
    const char* file_name = FILE_NAME_CHAR
    
    FILE* file = fopen (file_name, "r");

    if (file == NULL)
    {
        return;
    }
    
    char* orig_arr = malloc (len_arr * sizeof(char));
    char* arr = malloc (len_arr * sizeof(char));

        if (orig_arr == NULL || arr == NULL)
    {
        free (orig_arr);
        free (arr);
        fclose (file);
        
        return;
    }
    
    for (int i = 0; i < len_arr; ++i)
    {
        fscanf (file, " %c", &arr[i]);
    }
    memcpy (orig_arr, arr, len_arr * sizeof(char));

    sort (arr, len_arr, sizeof(char), cmp_char);
    fclose (file);
    assert (check_sort_arr (orig_arr, arr, len_arr, sizeof(char), cmp_char));

    free (arr);
    free (orig_arr);  
}


void test_not_random_arr_double (sort_stf sort)
{   
    int len_arr = LEN_ARR_DOUBLE
    const char* file_name = FILE_NAME_DOUBLE

    FILE* file = fopen (file_name, "r");

        if (file == NULL)
    {
        return;
    }

    double* orig_arr = malloc (len_arr * sizeof(double));
    double* arr = malloc (len_arr * sizeof(double));

        if (orig_arr == NULL || arr == NULL)
    {
        free (orig_arr);
        free (arr);
        fclose (file);
        
        return;
    }
    
    for (int i = 0; i < len_arr; ++i)
    {
        fscanf (file, "%lf", &arr[i]);
    }
    memcpy (orig_arr, arr, len_arr * sizeof(double));

    sort (arr, len_arr, sizeof(double), cmp_double);
    fclose (file);
    assert (check_sort_arr (orig_arr, arr, len_arr, sizeof(double), cmp_double));

    free (arr);
    free (orig_arr);
}


void test_not_random_arr_float (sort_stf sort)
{   
    int len_arr = LEN_ARR_FLOAT
    const char* file_name = FILE_NAME_FLOAT

    FILE* file = fopen (file_name, "r");

        if (file == NULL)
    {
        return;
    }

    float* orig_arr = malloc (len_arr * sizeof(float));
    float* arr = malloc (len_arr * sizeof(float));

        if (orig_arr == NULL || arr == NULL)
    {
        free (orig_arr);
        free (arr);
        fclose (file);
        
        return;
    }
    
    for (int i = 0; i < len_arr; ++i)
    {
        fscanf (file, "%f", &arr[i]);
    }
    memcpy (orig_arr, arr, len_arr * sizeof(float));

    sort (arr, len_arr, sizeof(float), cmp_float);
    fclose (file);
    assert (check_sort_arr (orig_arr, arr, len_arr, sizeof(float), cmp_float));

    free (arr);
    free (orig_arr);
}


void RUN_ALL_TESTS () 
{
    test_empt_arr (select_sort);
    test_one_arr (select_sort);
    test_two_arr (select_sort);
    test_zero_arr (select_sort);

    test_big_not_random_arr (select_sort);
    test_not_random_arr_char (select_sort);
    test_not_random_arr_double (select_sort);
    test_not_random_arr_float (select_sort);

    test_empt_arr (quick_sort);
    test_one_arr (quick_sort);
    test_two_arr (quick_sort);
    test_zero_arr (quick_sort);

    test_big_not_random_arr (quick_sort);
    test_not_random_arr_char (quick_sort);
    test_not_random_arr_double (quick_sort);
    test_not_random_arr_float (quick_sort);
}