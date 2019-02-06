#include <stdio.h>
#include <math.h>

#define OK (0)
#define IO_ERROR (-1)
#define RANGE_ERROR (-2)

#define N (10)

int input(int *a, int *n)
{
    char ch;
    printf("Input number of elements in range from 1 to 10: ");
    if (scanf("%d%c", n, &ch) == 2 && ch == '\n')
    {
        if (*n > 0 && *n <= N)
        {
            printf("Input the elements of array\n");
            for (int i = 0; i < *n; i++)
            {
                printf("a[%d] = ", i);
                if (scanf("%d%c", &a[i], &ch) != 2 || ch != '\n')
                {
                    return IO_ERROR;
                }
            }
            return OK;
        }
        return RANGE_ERROR;
    }
    return IO_ERROR;
}

void print(const int *a, int n)
{
    //printf("New array: \n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int del_num(int *a, int *n, int pos)
{
    if (pos < 0 || pos >= *n)
        return RANGE_ERROR;
    for (int i = pos; i < *n - 1; i++)
    {
        a[i] = a[i + 1];
    }
    (*n) -= 1;
    return OK;
}

float is_square(int num)
{
    float sq;
    float ost;

    sq = sqrt(num);
    ost = sq - (int)sq;
    return ost;
}

int del_square(int *a, int *n)
{
    int i = 0;
    int rc = OK;
    float res;


    while (i < *n && rc == OK)
    {
        if (a[i] >= 0)
        {
            res = is_square(a[i]);
            if (res == 0)
            {
                rc = del_num(a, n, i);
            }
            else
                i++;
        }
        else
            i++;
    }
    return rc;
}

int main()
{
    int a[N];
    int n;
    int rc = OK;

    if ((rc = input(a, &n)) == OK)
    {
        rc = del_square(a, &n);
        if (rc == OK)
            print(a, n);
            /*if (n == 0)
                printf("All elements were full-square: 0");
            else
                print(a, n);
        else
            printf("Range error");*/
    }
    /*else if (rc == IO_ERROR)
        printf("Incorrect input\n");
    else if (rc == RANGE_ERROR)
        printf("The wrong range of number of elements\n");*/

    return rc;
}
