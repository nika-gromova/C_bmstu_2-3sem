#include "array_lib.h"
#include <math.h>
#include <stdlib.h>
#define EPS 1e-7

/**
 * Функция генерирует число Фибоначчи (по его номеру n в ряде чисел Фибоначчи)
 * @param n [in] - номер числа
 * @return Возвращает полученное число Фибоначчи.
 */
unsigned long int create_fib(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return create_fib(n - 1) + create_fib(n - 2);
}

/**
 * Функция заполняет массив размера m числами Фибоначчи.
 * @param arr [in] - указатель на начало массива
 * @param n [in] - количество элементов массива
 * @return Возвращает -1, если количество элементов массива передано неверно (отрицательно), если массив пуст, либо возвращает 0, если массив был успешно заполнен.
 */
ARRAY_DLL int ARRAY_DECL fill_fib(unsigned long int *arr, int m)
{
    if (m <= 0)
        return -1;
    for (int i = 0; i < m; i++)
    {
        arr[i] = create_fib(i);
    }
    return 0;
}

int count_unique(double *array, int n)
{
    int count = 0;
    char flag = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n && flag == 0; j++)
            if (fabs(array[i] - array[j]) <= EPS)
                flag = 1;
        if (flag == 0)
            count++;
        flag = 0;
    }
    return count;
}


/*ARRAY_DLL int ARRAY_DECL first_occurrence(double *src, int n_src, double *dst, int *n_dst)
{
    int count = count_unique(src, n_src);
    if (*n_dst < count)
    {
        *n_dst = count;
        return 1;
    }
    char flag = 0;
    int k = 0;
    for (int i = 0; i < n_src; i++)
    {
        for (int j = i + 1; j < n_src && flag == 0; j++)
        {
            if (fabs(src[i] - src[j]) <= EPS)
                flag = 1;
        }
        if (flag == 0)
        {
            dst[k] = src[i];
            k++;
        }
        flag = 0;
    }
    *n_dst = count;
    if (k != count)
        return 1;
    return 0;
}*/


/**
 * Функция сохраняет в массив dst элементы массива src без повторений.
 * @param src [in] - указатель на начало массива, из которого будут сохраняться элементы
 * @param n_src [in] - количество элементов массива src
 * @param dst [in] - указатель на начало массива, в который будут сохраняться элементы
 * @param n_dst [in] - количество элементов массива dst
 * @return Возвращает 1, если количество элементов исходного массива передано неверно (отрицательно), если массив пуст, либо возвращает 0, или если количество элементов
 * результирующего массива меньше исходного, либо возвращает 0 если значения были успешно скопированы.
 */
ARRAY_DLL int ARRAY_DECL first_occurrence(double *src, int n_src, double *dst, int *n_dst)
{
    if (dst == NULL)
        return 1;
    int count = count_unique(src, n_src);
    if (*n_dst < count)
    {
        *n_dst = n_src;
        return 1;
    }
    int k = 1;
    int flag = 0;
    dst[0] = src[0];
    for (int i = 1; i < n_src; i++)
    {
        flag = 1;
        for (int j = 0; j < i; j++)
            if (fabs(src[i] - src[j]) <= EPS)
            {
                flag = 0;
                break;
            }
        if (flag)
        {
            dst[k] = src[i];
            k++;
        }
    }
    *n_dst = count;
    if (k != count)
        return 1;

    return 0;
}
