#include <stdio.h>
#include <time.h>
#include "sort.h"
#include "test.h"



int cmp_int (void* el_a, void* el_b)


int cmp_int (void* el_a, void* el_b)
{
    int a = *(int*) el_a;
    int b = *(int*) el_b;

    return (a > b) - (b > a);
}


int main ()
{
    srand (time(NULL));

    test_sort (quick_sort);
    test_sort (select_sort);

    printf ("Good work, all tests passed!\n");
    return 0;
}
