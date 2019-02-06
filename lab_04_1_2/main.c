#include <stdio.h>

#define OK (0)
#define IO_ERROR (-1)
#define RANGE_ERROR (-2)
#define NO_NEGATIVE (-3)
#define N (10)

int input(int *a, int *n)
{
    char ch;
    //printf("Input number of elements in range from 1 to 10: ");
    if (scanf("%d%c", n, &ch) == 2 && ch == '\n')
    {
        if (*n > 0 && *n <= N)
        {
            //printf("Input the elements of array\n");
            for (int i = 0; i < *n; i++)
            {
                //printf("a[%d] = ", i);
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

int average(const int *a, int n, float *avr)
{
    int sum = 0;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] < 0)
        {
            sum += a[i];
            count += 1;
        }
    }
    if (count != 0)
    {
        *avr = sum / (float) count;
        return OK;
    }
    else
        return NO_NEGATIVE;
}

int main()
{
    int n;
    int rc = OK;
    int a[N];
    float avr;

    if ((rc = input(a, &n)) == OK)
    {
        rc = average(a, n, &avr);
        if (rc == OK)
            printf("%f", avr);
        /*else
            printf("There are no negative numbers in array\n");*/
    }
    /*else if (rc == IO_ERROR)
        printf("Incorrect input\n");
    else if (rc == RANGE_ERROR)
        printf("The wrong range of number of elements");*/

    return rc;
}
