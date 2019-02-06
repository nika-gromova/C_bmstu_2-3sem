#include "defines.h"
#include "io.h"

int input_array(FILE *f, int *pb, int *n)
{
    if(fscanf(f, "%d", n) == 1 && *n > 0 && *n <= 100)
    {
        for(int *pcur = pb; pcur < pb + (*n); pcur++)
        {
            if(fscanf(f, "%d", pcur) != 1)
                return INPUT_ERROR;
        }
        return OK;
    }
    else
        return INPUT_ERROR;
}

void output_array(const int *pb, const int *pe)
{
    printf("\n");
    while (pb < pe)
    {
        printf("%d ", *pb);
        pb++;
    }
    printf("\n");
}
