#include "defines.h"
#include "process.h"
#include <stdio.h>

int find_max(int *pb, int *pe, int *max_ind)
{
    if (pe - pb == 0)
        return EMPTY_ARRAY_ERROR;
    if (max_ind == NULL || pb == NULL || pe == NULL)
        return POINTER_ERROR;

    int max_num = *pb;
    *max_ind = 0;
    for (int *pcur = pb + 1; pcur < pe; pcur++)
    {
        if (*pcur > max_num)
        {
            max_num = *pcur;
            *max_ind = pcur - pb;
        }
    }
    return OK;
}

int add_num(int *pb, int **pe, int max_ind)
{
    for (int *pcur = (*pe - max_ind); pcur >= pb + max_ind + 1; pcur--)
    {
        *pcur = *(pcur - 1);
    }
    *(pb + max_ind + 1) = 100;
    *pe += 1;
    return OK;
}


