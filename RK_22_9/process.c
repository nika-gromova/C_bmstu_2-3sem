#include "defines.h"
#include "process.h"
#include "assert.h"

#define N (20)
int new_arr(const int *a, const int *b, int *c, int n1, int n2, int *n3)
{
    // на вход второй массив длиннее первого
    assert(n2 >= n1);
    int j;
    int k;
    int tmp;
    int flag = 0;
    j = n2 - 1;
    k = 0;
    for (int i = n1 - 1; i > -1; i--)
    {

        c[k] = a[i] + b[j];
        if (flag == 1)
        {
            c[k] += 1;
            flag = 0;
        }
        if (c[k] >= 10)
        {
           tmp = c[k] - 10;
           c[k] = tmp;
           flag = 1;
        }
        j--;
        k++;
    }

    if (flag == 1)
    {
        if (n2 == N)
            return FULL;
        if (j == -1)
        {
            c[n2] = 1;
            *n3 = n2 + 1;
        }
    }
    else
        *n3 = n2;

    if (j >= 0)
    {
        int iter = j;
        for (int i = n2 -1 - j; i < n2; i++)
        {
            if (flag == 1)
            {
                c[i] = b[iter] + 1;
                flag = 0;
                if (c[i] >= 10)
                {
                    tmp = c[i] - 10;
                    c[i] = tmp;
                    flag = 1;
                }
            }
            else
            {
                c[i] = b[iter];
            }
            iter--;
        }
    }
    if (flag == 1)
    {
        if (n2 == N)
            return FULL;
        c[n2] = 1;
        *n3 = n2 + 1;
    }
    else
        *n3 = n2;

    return OK;
}

void reverse(int *a, int n)
{
    int m = n / 2;
    int tmp;
    for (int i = 0; i < m; i++)
    {
        tmp = a[n - i - 1];
        a[n - i - 1] = a[i];
        a[i] = tmp;
    }
}
int sum_arr(int *a, int *b, int *c, int n1, int n2, int *n3)
{
    int rc;
    if (n1 >= n2)
    {
        rc = new_arr(b, a, c, n2, n1, n3);
    }
    if (n1 < n2)
    {
        rc = new_arr(a, b, c, n1, n2, n3);
    }
    if (rc == OK)
        reverse(c, *n3);
    return rc;
}
