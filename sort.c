#include "sort.h"


static void swap (void* a, void* b, int el_size);


static int search_refer_el (void* arr, int len_arr, int el_size, int (*cmp_int)(void* el_a, void* el_b)); 


static int search_refer_el (void* arr, int len_arr, int el_size, int (*cmp_int)(void* el_a, void* el_b)) 
{
    int first = 0;
    int last = len_arr - 1;
    int average = len_arr / 2;
    int last_min_on = last - 1;

    void* add_first  = (char*) arr + (first * el_size);
    void* add_average = (char*) arr + (average * el_size);
    void* add_last  = (char*) arr + (last * el_size);
    
    if ((cmp_int(add_first, add_average)) > 0)
    {
        swap(add_first, add_average, el_size);
    }

    if ((cmp_int(add_first, add_last)) > 0)
    {
        swap(add_first, add_last, el_size);
    }

    if ((cmp_int(add_average, add_last)) > 0)
    {
        swap(add_average, add_last, el_size);
    }

    void* add_last_min_on = (char*) arr + (last_min_on * el_size);
    swap(add_average, add_last_min_on, el_size);
    return last_min_on;
}


void quick_sort(void* arr, int len_arr, int el_size, int (*cmp_int)(void* el_a, void* el_b))
{
    if (len_arr <= 1) 
    {
        return;
    }

    if (len_arr == 2) // т.к. когда осталось два эл. медиану искать не нужно 
    {
        int zero_el = 0;
        int first_el = zero_el + 1;
        void* add_zero_el = (char*) arr + (zero_el * el_size);
        void* add_first_el = (char*) arr + (first_el * el_size);
        if (cmp_int(add_zero_el, add_first_el) > 0)
        {
            swap(add_zero_el, add_first_el, el_size);
        }
        return;
    }

    int refer_idx = search_refer_el (arr, len_arr, el_size, cmp_int);
    void* add_refer = (char*)arr + (refer_idx * el_size);
    int i = 0;
    int j = len_arr - 2; // что и будет опорным элементов, так как элемент впереди его будет больше него самого 

    while (1) // пользуемся схемой разделения Хоара 
    {
        while (cmp_int((char*) arr + (++i * el_size), add_refer) < 0);
        while (cmp_int((char*) arr + (--j * el_size), add_refer) > 0);

        if (i >= j)
        {
            break;
        }
        swap((char*) arr + (i * el_size), (char*) arr + (j * el_size), el_size);
    }
    int el_min_two = len_arr -2;
    swap ((char*) arr + (i * el_size), (char*) arr + (el_min_two * el_size), el_size); // опорный элемент теперь на месте i
    quick_sort(arr, i, el_size, cmp_int);
    quick_sort((char*) arr + ((i+1) * el_size), len_arr - i -1, el_size, cmp_int);
}


static void swap (void* a, void* b, int el_size)
{
    char* tmp_a = (char*) a;
    char* tmp_b = (char*) b;
    
    for (int i = 0; i < el_size; i++)
    {
        char tmp = tmp_a[i];
        tmp_a[i] = tmp_b[i];
        tmp_b[i] = tmp;
    }
}


void select_sort(void* arr, int len_arr, int el_size, int (*cmp_int)(void* el_a, void* el_b))
{
    int min_el, i, j;
    for(i = 0; i < len_arr - 1; i++) // сдвигаем границу неотсортированной части
    {
        min_el = i;
    
        for(j = i + 1; j < len_arr; j++) // ищем минимальный элемент
        {
            if (cmp_int((char*) arr + (j * el_size), (char*) arr + (min_el * el_size)) < 0)
            {
                min_el = j;
            }
        }
        if (min_el != i)
        {
            void* add_i = (char*) arr + (i * el_size);
            void* add_min_el = (char*) arr + (min_el * el_size); 
            swap(add_i, add_min_el, el_size);
        }
    }
}