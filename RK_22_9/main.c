#include <stdio.h>
#include "defines.h"
#include "input.h"
#include "print.h"
#include "process.h"
#define N (20)
int main(int argc, char *argv[])
{
    FILE *f1, *f2;
    int rc = OK;
    int a[N], b[N], c[N];
    int n1, n2, n3;
    if (argc != 3)
    {
        printf("<main.exe> <file1.txt> <file2.txt>");
        return USAGE;
    }
    f1 = fopen(argv[1], "r");
    f2 = fopen(argv[2], "r");
    if (f1)
    {
        if (f2)
        {
            rc = input(f1, a, &n1);
            if (rc == OK)
            {
                rc = input(f2, b, &n2);
                if (rc == OK)
                {
                    print(a, n1);
                    printf("\n");
                    print(b, n2);
                    printf("\n");
                    rc = sum_arr(a, b, c, n1, n2, &n3);
                    if (rc == OK)
                        print(c, n3);
                    else
                        return FULL;
                }
                else
                    return IO_ERR;
            }
            else
                return IO_ERR;
            fclose(f2);
        }
        else
            return OPEN_FILE_ERR;
        fclose(f1);
    }
    else
        return OPEN_FILE_ERR;
    return OK;
}
