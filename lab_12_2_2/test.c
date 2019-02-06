#include <stdio.h>
#include <math.h>
#include "array_lib.h"

int cmp_arrays(double *arr_1, int n_1, double *arr_2, int n_2)
{
    if (n_1 != n_2)
        return -1;
    for (int i = 0; i < n_1; i++)
    {
        if (fabs(arr_1[i] - arr_2[i]) >= 1e-7)
            return -1;
    }
    return 0;
}

int cmp_arrays_lu(unsigned long int *arr_1, int n_1, unsigned long int *arr_2, int n_2)
{
    if (n_1 != n_2)
        return -1;
    for (int i = 0; i < n_1; i++)
    {
        if (arr_1[i] != arr_2[i])
            return -1;
    }
    return 0;
}

void test_fill_fib(void)
{
    printf("Tests for filling array with Fibonacci numbeers:\n");
    {
        unsigned long int a[1];
        int rc = fill_fib(a, 0);
        printf("Correct work with empty array: %s\n", (rc == -1) ? ("YES") : ("NO"));
    }
    {
        unsigned long int a[1];
        int rc = fill_fib(a, -2);
        printf("Correct work with invalid size of array: %s\n", (rc == -1) ? ("YES") : ("NO"));
    }
    {
        unsigned long int a[1];
        int size_a = 1;
        int rc = fill_fib(a, size_a);
        unsigned long int res[] = { 0 };
        printf("Correct work with array size of 1: %s\n", (cmp_arrays_lu(a, size_a, res, 1) == 0 && rc == 0) ? ("YES") : ("NO"));
    }
    {
        unsigned long a[3];
        int size_a = 3;
        int rc = fill_fib(a, size_a);
        unsigned long int res[] = { 0, 1, 1 };
        int size_res = 3;
        printf("Correct work with array size of 3: %s\n", (cmp_arrays_lu(a, size_a, res, size_res) == 0 && rc == 0) ? ("YES") : ("NO"));
    }
    {
        unsigned long int a[5];
        int size_a = 5;
        int rc = fill_fib(a, size_a);
        unsigned long int res[] = { 0, 1, 1, 2, 3 };
        int size_res = 5;
        printf("Correct work with array size of 5: %s\n", (cmp_arrays_lu(a, size_a, res, size_res) == 0 && rc == 0) ? ("YES") : ("NO"));
    }
    {
        unsigned long int a[10];
        int size_a = 10;
        int rc = fill_fib(a, size_a);
        unsigned long int res[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
        int size_res = 10;
        printf("Correct work with array size of 10: %s\n\n", (cmp_arrays_lu(a, size_a, res, size_res) == 0 && rc == 0) ? ("YES") : ("NO"));
    }
}

void test_first_occurrence(void)
{
    printf("Tests for saving only first occurences of the numbers in array:\n");
    {
        double b[] = { 1.0 };
        int b_size = sizeof(b) / sizeof(b[0]);
        double res[1] = { 1.0 };
        int n_res = 0;
        int rc = first_occurrence(b, b_size, res, &n_res);
        printf("Correct work with empty array: %s\n", (rc == 1 && n_res == 1) ? "YES" : "NO");
    }
    {
        double b[] = { 1.0, 2.0 };
        int b_size = sizeof(b) / sizeof(b[0]);
        double res[1] = { 0 };
        int n_res = 1;
        int rc = first_occurrence(b, b_size, res, &n_res);
        printf("Correct work with not enough size of result array: %s\n", (rc == 1 && n_res == b_size) ? "YES" : "NO");
    }
    {
        double b[] = { 1.0, 2.0 };
        int b_size = sizeof(b) / sizeof(b[0]);
        double res[1] = { 0 };
        int n_res = -3;
        int rc = first_occurrence(b, b_size, res, &n_res);
        printf("Correct work with invalid size of result array: %s\n", (rc == 1 && n_res == b_size) ? "YES" : "NO");
    }
    {
        double b[] = { 1.0 };
        int b_size = sizeof(b) / sizeof(b[0]);
        double res[1] = { 0 };
        int res_size = 1;
        double check[] = { 1.0 };
        int check_size = sizeof(check) / sizeof(check[0]);
        int rc = first_occurrence(b, b_size, res, &res_size);
        printf("Correct work with 1 unique element and size of array is 1: %s\n", (rc == 0 && cmp_arrays(check, check_size, res, res_size) == 0) ? "YES" : "NO");
    }
    {
        double b[] = { 1.0, 1.0 };
        int b_size = sizeof(b) / sizeof(b[0]);
        double res[2] = { 0 };
        int res_size = 2;
        double check[] = { 1.0 };
        int check_size = sizeof(check) / sizeof(check[0]);
        int rc = first_occurrence(b, b_size, res, &res_size);
        printf("Correct work with 1 unique element and size of array is 2: %s\n", (rc == 0 && cmp_arrays(check, check_size, res, res_size) == 0) ? "YES" : "NO");
    }
    {
        double b[] = { 1.0, 1.0, 2.0 };
        int b_size = sizeof(b) / sizeof(b[0]);
        double res[3] = { 0 };
        int res_size = 3;
        double check[] = { 1.0, 2.0 };
        int check_size = sizeof(check) / sizeof(check[0]);
        int rc = first_occurrence(b, b_size, res, &res_size);
        printf("Correct work with 2 unique elements and size of array is 3: %s\n", (rc == 0 && cmp_arrays(check, check_size, res, res_size) == 0) ? "YES" : "NO");
    }
    {
        double b[] = { 2.0, 1.0, 1.0 };
        int b_size = sizeof(b) / sizeof(b[0]);
        double res[3] = { 0 };
        int res_size = 3;
        double check[] = { 2.0, 1.0 };
        int check_size = sizeof(check) / sizeof(check[0]);
        int rc = first_occurrence(b, b_size, res, &res_size);
        printf("Correct work with 2 unique element and size of array is 3 (another order): %s\n", (rc == 0 && cmp_arrays(check, check_size, res, res_size) == 0) ? "YES" : "NO");
    }
    {
        double b[] = { 2.0, 1.0, 2.0, 2.0, 1.0, 1.0 };
        int b_size = sizeof(b) / sizeof(b[0]);
        double res[6] = { 0 };
        int res_size = 6;
        double check[] = { 2.0, 1.0 };
        int check_size = sizeof(check) / sizeof(check[0]);
        int rc = first_occurrence(b, b_size, res, &res_size);
        printf("Correct work with 2 unique element and size of array is 6: %s\n", (rc == 0 && cmp_arrays(check, check_size, res, res_size) == 0) ? "YES" : "NO");
    }
    {
        double b[] = { 2.0, 1.0, 2.0, 2.0, 3.2, 1.0, 1.0 };
        int b_size = sizeof(b) / sizeof(b[0]);
        double res[7] = { 0 };
        int res_size = 7;
        double check[] = { 2.0, 1.0, 3.2 };
        int check_size = sizeof(check) / sizeof(check[0]);
        int rc = first_occurrence(b, b_size, res, &res_size);

        printf("Correct work with 3 unique element and size of array is 7: %s\n", (rc == 0 && cmp_arrays(check, check_size, res, res_size) == 0) ? "YES" : "NO");
    }
    {
        double b[] = { 2.0, 1.0, 1.0, 2.0};
        int b_size = sizeof(b) / sizeof(b[0]);
        double res[7] = { 0 };
        int res_size = 4;
        double check[] = { 2.0, 1.0};
        int check_size = sizeof(check) / sizeof(check[0]);
        int rc = first_occurrence(b, b_size, res, &res_size);

        printf("Correct work with 3 unique element and size of array is 4: %s\n\n", (rc == 0 && cmp_arrays(check, check_size, res, res_size) == 0) ? "YES" : "NO");
    }
}

int main(void)
{
    test_fill_fib();
    test_first_occurrence();
    return 0;
}
