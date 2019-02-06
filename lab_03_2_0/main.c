// Нахождение числа, наиболее близкого к среднему значению всех чисел

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#define OK (0)
#define INPUT_ERR (-1)
#define OPEN_FILE_ERR (-2)
#define USAGE_ERR (-3)

int find_num(FILE *fsrc, float *average, float *result)
{
    float num;
    float diff;

    if (fscanf(fsrc, "%f", &num) == 1)
    {
        diff = fabs(num - *average);

        while (fscanf(fsrc, "%f", &num) == 1)
        {
            if (fabs(num - *average) < diff)
            {
                diff = fabs(num - *average);
                *result = num;
            }
        }
        return OK;
    }
    return INPUT_ERR;
}


int find_average(FILE *fsrc, float *average)
{
    float num, sum = 0;
    int count = 0;

    while (fscanf(fsrc, "%f", &num) == 1)
    {
        sum += num;
        count++;
    }
    if (count == 0 || count == 1)
    {
        return INPUT_ERR;
    }
    else
    {
        *average = sum / count;
        return OK;
    }
}


int main(int argc, char **argv)
{
    FILE *fsrc;
    float average;
    float result;
    int rc;

    if (argc != 2)
    {
        fprintf(stdout, "main.exe <source file>\n");
        rc = USAGE_ERR;
    }
    else
    {
        fsrc = fopen(argv[1], "r");

        if (fsrc)
        {
            rc = find_average(fsrc, &average);
            if (rc == OK)
            {
                rewind(fsrc);
                rc = find_num(fsrc, &average, &result);
                fprintf(stdout, "result = %f", result);
            }
            else
                printf("Incorrect input\n");

            fclose(fsrc);
        }
        else
        {
            fprintf(stderr, "Could not open %s because of %s\n", argv[1], strerror(errno));
            rc = OPEN_FILE_ERR;
        }
    }
    return rc;
}
