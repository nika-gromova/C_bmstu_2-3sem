#include "io.h"
#include "get_max.h"
#include "defines.h"

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
