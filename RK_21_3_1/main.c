#include <stdio.h>
#define OK (0)
#define IO_ERR (-1)
#define RANGE_ERR (-2)
#define A_B (1)
#define B_A (2)
#define NO_A (-3)
#define NO_B (-4)

int detect_a_b(int n, int a, int b)
{
    int pos_a = -1, pos_b = -1;
    int tmp;
    int i = 0;
    while (n > 0)
    {
        i++;
        tmp = n % 10;
        if (tmp == a)
        {
            if (pos_a != -1)
            {
                if (i < pos_a)
                    pos_a = i;
            }
            else
                pos_a = i;

        }
        if (tmp == b)
        {
            if (pos_b != -1)
            {
                if (i < pos_b )
                    pos_b = i;
            }
            else
                pos_b = i;

        }

        n /= 10;
    }

    if(pos_a == -1)
        return NO_A;
    if (pos_b == -1)
        return NO_B;
    else if (pos_a > pos_b)
        return A_B;
    else
        return B_A;


}

int main(void)
{
    int n;
    int a, b;
    int rc = OK;
    int res;

    printf("Input n: ");
    if (scanf("%d", &n) == 1)
    {
        if (n > 0)
        {
            printf("Input a and b: ");
            if (scanf("%d%d", &a, &b) == 2)
            {
                if ((a >= 0 && a <= 9) && (b >= 0 && b <= 9))
                {
                    res = detect_a_b(n, a, b);
                    if (res == A_B)
                        printf("b is right");
                    else if (res == B_A)
                        printf("a is right");
                    else if (res == NO_A)
                        printf("a not in a number");
                    else if (res == NO_B)
                        printf("b not in a number");
                }
                else
                    rc = RANGE_ERR;
            }
            else
                rc = IO_ERR;
        }
        else
            rc = RANGE_ERR;
    }
    else
        rc = IO_ERR;

    return rc;
}
