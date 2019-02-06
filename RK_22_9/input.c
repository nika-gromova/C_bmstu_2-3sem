#include <stdio.h>
#include "defines.h"

int input(FILE *f, int *a, int *n)
{
    if (fscanf(f, "%d", n) == 1)
    {
        if (n > 0)
        {
            for (int i = 0; i < *n; i++)
            {
                if (fscanf(f, "%d", &a[i]) != 1)
                    return IO_ERR;
            }
            return OK;
        }
        return RANGE_ERR;
    }
    return IO_ERR;
}
