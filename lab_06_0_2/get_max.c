#include <stdio.h>
#include "get_max.h"
#include "defines.h"
int get_max(const int *pb, const int *pe, int *max)
{
    int cur_sum;
    if (pb == NULL || pe == NULL || max == NULL)
        return POINTER_ERROR;
    if (pb == pe)
        return NOT_ENOUGH_DATA;
    pe--;
    *max = *(pb) + *(pe);
    const int *pcur;
    for (pcur = (pb + 1); pcur < pe; pcur++)
    {
        pe--;
        cur_sum = *(pcur) + *(pe);
        if (*max < cur_sum)
            *max = cur_sum;
    }
    return OK;
}
