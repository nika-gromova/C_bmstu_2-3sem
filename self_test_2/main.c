#include "io.h"
#include "defines.h"
#include "process.h"
#include <assert.h>

int main(int argc, char *argv[])
{
    FILE *f;
    int rc = OK;
    int a[N];
    int *pb = a;
    int *pe;
    int n;
    int max_i;

    if (argc != 2)
        return USAGE_ERROR;

    f = fopen(argv[1], "r");
    if (f)
    {
        rc = input_array(f, pb, &n);
        if (rc == OK)
        {
            pe = pb + n;
            assert(n > 0 && n <= 100);
            printf("Array:");
            output_array(pb, pe);
            rc = find_max(pb, pe, &max_i);
            if (rc == OK)
            {
                rc = add_num(pb, &pe, max_i);
                if (rc == OK)
                {
                    printf("New array:");
                    output_array(pb, pe);
                }
            }
        }
        else
            printf("Incorrect input");
        fclose(f);
    }
    else
        rc = OPEN_FILE_ERROR;
    return rc;
}
