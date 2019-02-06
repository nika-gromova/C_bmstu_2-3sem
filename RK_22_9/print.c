#include <stdio.h>
#include "print.h"
void print(const int *a,int n)
{
    printf("Array: \n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
}
