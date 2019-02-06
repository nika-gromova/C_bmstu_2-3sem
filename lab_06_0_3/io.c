#include "io.h"
#include "defines.h"

int input(FILE *f, int *pb, int **pe)
{
    int *pcur = pb;
    while ((pcur - pb) < N && fscanf(f, "%d", pcur) == 1)
    {
        pcur++;
    }
    *pe = pcur;
    if (feof(f) == 0)
        return MORE_THAN_N;
    return OK;
}

void print_array(const int *pb, const int *pe)
{
    printf("Array: \n");
    while (pb < pe)
    {
        printf("%d ", *pb);
        pb++;
    }
    printf("\n");
}
