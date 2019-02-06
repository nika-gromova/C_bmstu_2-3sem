#include <stdio.h>
#include "process.h"
#include "print.h"
#include "defines.h"
#include <stdbool.h>
#define N (20)

bool is_equal(const int *array_1, const int *array_2, int n1, int n2)
{
    if (n1 != n2)
        return false;
    for (int i = 0; i < n1; i++)
    {
        if (array_1[i] != array_2[i])
            return false;
    }
    return true;
}
void test_new_arr(void)
{
    printf("Tests for function 'new_arr()': \n\n");
    {
    int n1 = 4;
    int n2 = 5;
    int n3;
    int a[] = {1, 0, 2, 4};
    int b[] = {5, 0, 3, 2, 1};
    int c[N];
    int result[N] = {5, 4, 3, 1, 5};
    int rc;
    rc = new_arr(a, b, c, n1, n2, &n3);
    printf("Test #1: %s (%d)\n", (is_equal(c, result, n3, 5)) ? "OK" : "FAIL", rc);
    }
    {
        int n1 = 1;
        int n2 = 3;
        int n3;
        int a[] = {5};
        int b[] = {2, 8, 5};
        int c[N];
        int result[N] = {0, 9, 2};
        int rc;
        rc = new_arr(a, b, c, n1, n2, &n3);
        printf("Test #2: %s (%d)\n", (is_equal(c, result, n3, 3)) ? "OK" : "FAIL", rc);
    }
    {
        int n1 = 3;
        int n2 = 3;
        int n3;
        int a[] = {9, 8, 7};
        int b[] = {1, 2, 3};
        int c[N];
        int result[N] = {0, 1, 1, 1};
        int rc;
        rc = new_arr(a, b, c, n1, n2, &n3);
        printf("Test #3: %s (%d)\n", (is_equal(c, result, n3, 4)) ? "OK" : "FAIL", rc);
    }
    {
        int n1 = 2;
        int n2 = 20;
        int n3;
        int b[] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4};
        int a[] = {1, 5};
        int c[N];
        int rc;
        rc = new_arr(a, b, c, n1, n2, &n3);
        printf("Test #4: %s (%d)\n", (rc == FULL) ? "OK" : "FAIL", rc);
    }
}
void test_reverse(void)
{
    printf("\nTests fot function 'reverse()':\n\n");
    {
        int a[] = {1, 2, 3, 4};
        int n = 4;
        int result[] = {4, 3, 2, 1};
        reverse(a, n);
        printf("Test #1: %s\n", (is_equal(a, result, n, 4)) ? "OK" : "FAIL");
    }
    {
        int a[] = {5};
        int n = 1;
        int result[] = {5};
        reverse(a, n);
        printf("Test #2: %s\n", (is_equal(a, result, n, 1)) ? "OK" : "FAIL");
    }
    {
        int a[] = {12, 3, 0, -8, 2};
        int n = 5;
        int result[] = {2, -8, 0, 3, 12};
        reverse(a, n);
        printf("Test #3: %s\n", (is_equal(a, result, n, 5)) ? "OK" : "FAIL");
    }
}
void test_sum_arr(void)
{
    printf("\nTests for function 'sum_arr()':\n\n");
    {
        int n1 = 5;
        int n2 = 3;
        int n3;
        int a[] = {2, 1, 4, 3, 5};
        int b[] = {1, 3, 8};
        int c[N];
        int result[] = {2, 1, 5, 7, 3};
        int rc;
        rc = sum_arr(a, b, c, n1, n2, &n3);
        printf("Test #1: %s (%d)\n", (is_equal(c, result, n3, 5)) ? "OK" : "FAIL", rc);
    }
    {
        int n1 = 5;
        int n2 = 3;
        int n3;
        int a[] = {9, 9, 9, 2, 3};
        int b[] = {9, 2, 1};
        int c[N];
        int result[] = {1, 0, 0, 8, 4, 4};
        int rc;
        rc = sum_arr(a, b, c, n1, n2, &n3);
        printf("Test #2: %s (%d)\n", (is_equal(c, result, n3, 6)) ? "OK" : "FAIL", rc);
    }
    {
        int n1 = 2;
        int n2 = 6;
        int n3;
        int a[] = {1, 9};
        int b[] = {9, 3, 5, 4, 9, 7};
        int c[N];
        int result[] = {9, 3, 5, 5, 1, 6};
        int rc;
        rc = sum_arr(a, b, c, n1, n2, &n3);
        printf("Test #3: %s (%d)\n", (is_equal(c, result, n3, 6)) ? "OK" : "FAIL", rc);
    }
    {
        int n1 = 20;
        int n2 = 1;
        int n3;
        int a[] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
        int b[] = {5};
        int c[N];
        int rc;
        rc = sum_arr(a, b, c, n1, n2, &n3);
        printf("Test #3: %s (%d)\n", (rc == FULL) ? "OK" : "FAIL", rc);
    }

}

int main(void)
{
    test_new_arr();
    test_reverse();
    test_sum_arr();
    return 0;
}
