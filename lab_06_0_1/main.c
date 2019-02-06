#include <stdio.h>
int get_max(int *pb, int *pe, int *max);
int input(FILE *f, int *pb, int **pe);
void print_array(const int *pb, const int *pe);
#define N (100)
#define OK (0)
#define IO_ERROR (-1)
#define MORE_THAN_N (-2)
#define OPEN_FILE_ERROR (-3)
#define USAGE_ERROR (-4)

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
