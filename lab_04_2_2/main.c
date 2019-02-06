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
        if (*n > 0 && *n < 11)
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
    //printf("New array:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int is_num(int num)
{
    int flag = 0;
    num = abs(num);
    int tmp1 = num % 10;
    int tmp2 = num;

    while (tmp2 > 10)
    {
        tmp2 /= 10;
    }

    if (tmp1 == tmp2)
        flag = 1;
    else
        flag = 0;
    return flag;
}

int new_arr(const int *a, int *b, int n, int *n_b)
{
    int res;
    int j = 0;

    for (int i = 0; i < n; i++)
    {
        res = is_num(a[i]);
        if (res == 1)
        {
            b[j] = a[i];
            j++;
        }
    }
    *n_b = j;
    return OK;
}

int main()
{
    int n;
    int rc = OK;
    int a[N], b[N];
    int n_b;

    if ((rc = input(a, &n)) == OK)
    {
        rc = new_arr(a, b, n, &n_b);
        print(b, n_b);
        /*if (n_b != 0)
            print(b, n_b);
        else
            printf("There are 0 suitable numbers");*/
    }
    /*else if (rc == IO_ERROR)
        printf("Incorrect input\n");
    else if (rc == RANGE_ERROR)
        printf("The wrong range of number of elements\n");*/

    return rc;
}
