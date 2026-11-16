#include <stdio.h>
#include <time.h>
#include "sort.h"
#include "test.h"


int main ()
{
    srand (time(NULL));

    test_sort (quick_sort);
    test_sort (select_sort);

    printf ("Good work, all tests passed!\n");
    return 0;
}
