#include "sort.h"
#include "test.h"
#include <stdio.h>
#include <time.h>



int main ()
{
    srand ((unsigned int)time(NULL))

    RUN_ALL_TESTS(select_sort);
    RUN_ALL_TESTS(quick_sort);
    
    return 0;
}
