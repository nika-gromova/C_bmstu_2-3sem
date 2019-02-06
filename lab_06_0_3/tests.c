#include "io.h"
#include "get_max.h"
#include "defines.h"

void test_input(void)
{
    FILE *f;
    int a[N];
    int *pb = a;
    int *pe = a;

    printf("Function 'input()' testing:\n");

    // файл, содержащий больше ста элементов
    f = fopen("test_2.txt", "r");
    printf("Correct work with more than 100 elements: %s\n", (input(f, pb, &pe) != MORE_THAN_N || pe != (pb + N)) ? "NO" : "YES");

    // файл, содержаший меньше ста элементов
    f = fopen("test_3.txt", "r");
    printf("Correct work with normal array [2 7 4 5 3 1 0 -5]: %s\n", (input(f, pb, &pe) != OK || *(pe - 1) != (-5)) ? "NO" : "YES");
    f = fopen("test_4.txt", "r");
    printf("Correct work with normal array [-1 -10 2 4 1]: %s\n\n\n", (input(f, pb, &pe) != OK || *(pe - 1) != (1)) ? "NO" : "YES");

}

void test_get_max(void)
{
    int max;
    int rc;

    int a[N];
    int *pb = NULL;
    int *pe = NULL;

    printf("Function 'get_max()' testing:\n");
    printf("'Correct work with' <test case> : 'YES/NO' (error code)\n\n");

    // неправильные параметры функции
    rc = get_max(pb, pe, &max);
    printf("Correct work with NULL pointers: %s (%d)\n", (rc != POINTER_ERROR) ? "NO" : "YES", rc);
    pe = a;
    rc = get_max(pb, pe, &max);
    printf("Correct work with NULL pointers: %s (%d)\n", (rc != POINTER_ERROR) ? "NO" : "YES", rc);
    pb = a;
    pe = NULL;
    rc = get_max(pb, pe, &max);
    printf("Correct work with NULL pointers: %s (%d)\n", (rc != POINTER_ERROR) ? "NO" : "YES", rc);

    // пустой массив
    pe = a;
    rc = get_max(pb, pe, &max);
    printf("Correct work with empty array: %s (%d)\n", (rc != NOT_ENOUGH_DATA) ? "NO" : "YES", rc);

    // массив из одного элемента
    int x[N] = {30};
    pb = x;
    pe = x + 1;
    rc = get_max(pb, pe, &max);
    printf("Correct work with normal array [30]: %s (%d)\n", (rc != OK || max != 60) ? "NO" : "YES", rc);

    // нормальный массив
    int b[N] = {30, 20, -8, 33, 45, -99, 0};
    pb = b;
    pe = b + 7;
    rc = get_max(pb, pe, &max);
    printf("Correct work with normal array [30, 20, -8, 33, 45, -99, 0]: %s (%d)\n", (rc != OK || max != 66) ? "NO" : "YES", rc);
    int c[N] = {2, -5, 0, 13, 4, -7, -6, 10};
    pb = c;
    pe = c + 8;
    rc = get_max(pb, pe, &max);
    printf("Correct work with normal array [2, -5, 0, 13, 4, -7, -6, 10]: %s (%d)\n", (rc != OK || max != 17) ? "NO" : "YES", rc);
    int d[N] = {3, 1, -5, 0, 7};
    pb = d;
    pe = d + 5;
    rc = get_max(pb, pe, &max);
    printf("Correct work with normal array [3, 1, -5, 0, 7]: %s (%d)\n\n", (rc != OK || max != 10) ? "NO" : "YES", rc);

}

int main(void)
{
    test_input();
    test_get_max();
    return 0;
}
