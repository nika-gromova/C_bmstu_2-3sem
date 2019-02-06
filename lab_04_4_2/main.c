#include <stdio.h>

#define OK (0)
#define OPEN_FILE_ERROR (-1)
#define IO_ERROR (-2)
#define RANGE_ERROR (-3)

#define N 10

int input(int *a, int *n)
{
    char ch;

    printf("Input n in range from 1 to 10: ");
    if (scanf("%d", n) == 1)
    {
        if (*n > 0 && *n < 11)
        {
            for (int i = 0; i < *n; i++)
            {
                printf("a[%d] = ", i);
                if (scanf("%d%c", &a[i], &ch) != 2 || ch != '\n')
                    return IO_ERROR;
            }
            return OK;
        }
        return RANGE_ERROR;
    }
    return IO_ERROR;
}

void sort(int *a, int n)
{
    int tmp;
    int index_min;

    for (int i = 0; i < n; i++)
    {
        index_min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[index_min])
                index_min = j;
        }
        tmp = a[index_min];
        a[index_min] = a[i];
        a[i] = tmp;
    }
}

void print(const int *a, int n)
{
    //printf("sorted array:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main()
{
    int n;
    int a [N];
    int rc = OK;

    if ((rc = input(a, &n)) == OK)
    {
        sort(a, n);
        print(a, n);
    }
    /*else if (rc == IO_ERROR)
        printf("Incorrect input");
    else
        printf("n should be > 0 and <= 10");*/

    return rc;
}
