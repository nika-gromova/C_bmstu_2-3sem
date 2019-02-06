// Нахождение двух максимальных элементов

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define OK (0)
#define INPUT_TYPE_ERR (-1)
#define OPEN_FILE_ERR (-2)
#define USAGE_ERR (-3)

int process(FILE *f, int *first_max, int *second_max)
{
    int num;
    int tmp;

    if (fscanf(f, "%d", first_max) == 1)
    {
        if (fscanf(f, "%d", second_max) == 1)
        {
            if (*first_max < *second_max)
            {
                tmp = *first_max;
                *first_max = *second_max;
                *second_max = tmp;
            }

            while (fscanf(f, "%d", &num) == 1)
            {
                if ((num >= *first_max) && (num > *second_max))
                {
                    *second_max = *first_max;
                    *first_max = num;
                }
                else if ((num > *second_max) && (num < *first_max))
                    *second_max = num;
            }            
            return OK;
        }
        return INPUT_TYPE_ERR;
    }
    return INPUT_TYPE_ERR;
}

int main(void)
{
    int first_max, second_max;
    int rc;
    rc = process(stdin, &first_max, &second_max);
    if (rc == OK)
        fprintf(stdout, "first maximum = %d\nsecond maximum = %d", first_max, second_max);
    else
        fprintf(stdout, "The wrong input");

    return rc;
}
