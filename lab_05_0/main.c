#include <stdio.h>

#define N (100)

#define OK (0)
#define IO_ERROR (-1)
#define MORE_THAN_N (-2)
#define OPEN_FILE_ERROR (-3)
#define USAGE_ERROR (-4)
#define POINTER_ERROR (-5)
#define NOT_ENOUGH_DATA (-6)

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

/*int main(int argc, char *argv[])
{
    FILE *f;
    int rc = OK;
    int a [N];
    int *pb = a;
    int *pe = a;
    int max;

    if (argc != 2)
    {
        printf("<main.exe> <file.txt>");
        return USAGE_ERROR;
    }

    f = fopen(argv[1], "r");
    if (f)
    {
        rc = input(f, pb, &pe);
        if (rc == OK)
        {
            print_array(pb, pe);
            rc = get_max(pb, pe, &max);
            if (rc == OK)
                printf("max_sum = %d", max);
            else
                printf("Some errors with pointers");
        }
        else if (rc == MORE_THAN_N)
        {
            pb = a;
            printf("File has more than %d numbers\n", N);
            print_array(pb, pe);
            rc = get_max(pb, pe, &max);
            if (rc == OK)
                printf("\nmax sum for the first %d numbers = %d", N, max);
            else
                printf("Some errors with pointers");
        }
        else if (rc == IO_ERROR)
            printf("There are no numbers");
        //fclose(f);
    }
    else
    {
        printf("Can not open a file");
        rc = OPEN_FILE_ERROR;
    }
    return rc;
}*/

int main(int argc, char *argv[])
{
    FILE *f;
    int rc = OK;
    int a [N];
    int *pb = a;
    int *pe = a;
    int max;

    if (argc != 2)
        return USAGE_ERROR;

    f = fopen(argv[1], "r");
    if (f)
    {
        rc = input(f, pb, &pe);
        pb = a;
        if (pb != pe)
        {
            if (rc == MORE_THAN_N)
            {
                printf("There are more then 100 numbers in file\n");
            }
            rc = get_max(pb, pe, &max);
            if (rc == OK)
                printf("%d", max);
        }
        else
            rc = IO_ERROR;
        fclose(f);
    }
    else
    {
        rc = OPEN_FILE_ERROR;
    }
    return rc;
}

