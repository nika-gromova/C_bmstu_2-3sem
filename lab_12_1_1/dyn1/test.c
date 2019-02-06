#include "defines.h"
#include "arr_lib.h"
#include <math.h>

/**
  Проверяет равенство целочисленного массива pb_ch - pe_ch массиву pb_ex - pe_ex.
 * @brief check_array
 * @param pb_ch [in] - указатель на начало одного массива
 * @param pe_ch [in] - указатель на конец одного массива
 * @param pb_ex [in] - указатель на начало второго массива
 * @param pe_ex [in] - указатель на конец второго массива
 * @return Возвращает CHECK_ARRAY_ERROR, если массивы не равны, либо OK, если массивы равны.
 */
int check_array(const int *pb_ch, const int *pe_ch, const int *pb_ex, const int *pe_ex)
{
    if ((pe_ch - pb_ch) != (pe_ex - pb_ex))
        return CHECK_ARRAY_ERROR;
    while (pb_ch < pe_ch)
    {
        if (*pb_ch != *pb_ex)
            return CHECK_ARRAY_ERROR;
        pb_ch++;
        pb_ex++;
    }
    return OK;
}

/**
  Проверяет равенство массива типа char pb_ch - pe_ch массиву pb_ex - pe_ex.
 * @brief check_array
 * @param pb_ch [in] - указатель на начало одного массива
 * @param pe_ch [in] - указатель на конец одного массива
 * @param pb_ex [in] - указатель на начало второго массива
 * @param pe_ex [in] - указатель на конец второго массива
 * @return Возвращает CHECK_ARRAY_ERROR, если массивы не равны, либо OK, если массивы равны.
 */
int check_array_char(const char *pb_ch, const char *pe_ch, const char *pb_ex, const char *pe_ex)
{
    if ((pe_ch - pb_ch) != (pe_ex - pb_ex))
        return CHECK_ARRAY_ERROR;
    while (pb_ch < pe_ch)
    {
        if (*pb_ch != *pb_ex)
            return CHECK_ARRAY_ERROR;
        pb_ch++;
        pb_ex++;
    }
    return OK;
}

/**
  Проверяет равенство массива вещественных чисел pb_ch - pe_ch массиву pb_ex - pe_ex.
 * @brief check_array
 * @param pb_ch [in] - указатель на начало одного массива
 * @param pe_ch [in] - указатель на конец одного массива
 * @param pb_ex [in] - указатель на начало второго массива
 * @param pe_ex [in] - указатель на конец второго массива
 * @return Возвращает CHECK_ARRAY_ERROR, если массивы не равны, либо OK, если массивы равны.
 */
int check_array_float(const float *pb_ch, const float *pe_ch, const float *pb_ex, const float *pe_ex)
{
    if ((pe_ch - pb_ch) != (pe_ex - pb_ex))
        return CHECK_ARRAY_ERROR;
    while (pb_ch < pe_ch)
    {
        if (fabs(*pb_ch - *pb_ex) > 0.000001)
            return CHECK_ARRAY_ERROR;
        pb_ch++;
        pb_ex++;
    }
    return OK;
}

/**
  Функция печати массива.
 * @brief print_array
 * @param pb [in] - указатель на начало массива
 * @param pe [in] - указатель на конец массива
 */
void print_array(const int *pb, const int *pe)
{
    while (pb < pe)
    {
        printf("%d ", *pb);
        pb++;
    }
    printf("\n");
}

/**
  Функция для тестирования ввода.
 * @brief test_input
 */
void test_input(void)
{
    // пустой файл
    {
        FILE *f;
        int *pb = NULL, *pe = NULL;
        int rc = OK;
        f = fopen("../tests/in_1.txt", "r");
        if (f)
        {
            rc = input(f, &pb, &pe);
            printf("Correct work with empty file: %s\n", (rc == EMPTY_ARRAY) ? "YES" : "NO");
            fclose(f);
        }
    }

    // файл, содержащий некорректные данные
    {
        FILE *f;
        int *pb = NULL, *pe = NULL;
        int rc = OK;
        f = fopen("../tests/in_10.txt", "r");
        if (f)
        {
            rc = input(f, &pb, &pe);
            printf("Correct work with invalid data: %s\n", (rc == EMPTY_ARRAY) ? "YES" : "NO");
            fclose(f);
        }
    }

    // файлы, содержащие корректные данные
    {
        FILE *f;
        int *pb = NULL, *pe = NULL;
        int rc = OK;
        int a[] = { 3 };
        int *b = a, *e = a + sizeof(a) / sizeof(a[0]);
        f = fopen("../tests/in_2.txt", "r");
        if (f)
        {
            rc = input(f, &pb, &pe);
            printf("Correct work with valid data: %s\n", (rc == OK && check_array(pb, pe, b, e) == OK) ? "YES" : "NO");
            fclose(f);
        }
        free(pb);
    }

    {
        FILE *f;
        int *pb = NULL, *pe = NULL;
        int rc = OK;
        int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int *b = a, *e = a + sizeof(a) / sizeof(a[0]);
        f = fopen("../tests/in_3.txt", "r");
        if (f)
        {
            rc = input(f, &pb, &pe);
            printf("Correct work with valid data: %s\n", (rc == OK && check_array(pb, pe, b, e) == OK) ? "YES" : "NO");
            fclose(f);
        }
        free(pb);
    }

    {
        FILE *f;
        int *pb = NULL, *pe = NULL;
        int rc = OK;
        int a[] = { 10, 9, 7, 12, -7, 3, 0, -4 };
        int *b = a, *e = a + sizeof(a) / sizeof(a[0]);
        f = fopen("../tests/in_5.txt", "r");
        if (f)
        {
            rc = input(f, &pb, &pe);
            printf("Correct work with valid data: %s\n", (rc == OK && check_array(pb, pe, b, e) == OK) ? "YES" : "NO");
            fclose(f);
        }
        free(pb);
    }
}

/**
  Функция для тестирования работы фильтра.
 * @brief test_filter
 */

void test_filter(void)
{
    printf("FILTER:\n");
    // неопределенные указатели
    {
        int rc;
        int *pb_dst = NULL;
        int *pe_dst = NULL;
        int *pb = NULL, *pe = NULL;
        rc = key(pb, pe, pb_dst, pe_dst, 0, 0);
        printf("Correct work with pointers: %s\n", (rc == POINTER_ERROR) ? "YES" : "NO");
    }

    {
        int rc;
        int *pb_dst = NULL;
        int *pe_dst = NULL;
        int a[5];
        int *pb = a, *pe = NULL;
        rc = key(pb, pe, pb_dst, pe_dst, 0, 0);
        printf("Correct work with pointers: %s\n", (rc == POINTER_ERROR) ? "YES" : "NO");
    }

    // пустой массив
    {
        int rc;
        int a[] = { 1 };
        int b[] = { 2 };
        int *pb_dst = b;
        int *pe_dst = b + 1;
        int *pb = a, *pe = pb;
        rc = key(pb, pe, pb_dst, pe_dst, a, a);
        printf("Correct work with empty array: %s\n", (rc == EMPTY_ARRAY) ? "YES" : "NO");
    }

    // корректные массивы
    {
        int rc;
        const int *i_max = NULL, *i_min = NULL;
        int m;
        int *pb_dst = NULL;
        int *pe_dst = NULL;
        int a[5] = { 1, 2, 3, 4, 5 };
        int res[] = { 2, 3, 4 };
        int *b = res, *e = res + sizeof(res) / sizeof(res[0]);
        int *pb = a, *pe = pb + 5;
        rc = find_max(pb, pe, &i_max);
        if (rc == OK)
        {
            rc =find_min(pb, pe, &i_min);
            if (rc == OK)
            {
                m = abs(i_min - i_max) - 1;
                if (m > 0)
                {
                    pb_dst = malloc(m * sizeof(int));
                    if (pb_dst)
                    {
                        pe_dst = pb_dst + m;
                        rc = key(pb, pe, pb_dst, pe_dst, i_max, i_min);
                        printf("Correct work with valid arrays: %s\n", (rc == OK && check_array(pb_dst, pe_dst, b, e) == OK) ? "YES" : "NO");
                        //print_array(pb_dst, pe_dst); // 2 3 4
                        free(pb_dst);
                    }
                    else
                        rc = MEMORY_ERROR;
                }
                else
                    rc = EMPTY_ARRAY;
            }
        }
    }

    {
        int rc;
        const int *i_max = NULL, *i_min = NULL;
        int m;
        int *pb_dst = NULL;
        int *pe_dst = NULL;
        int a[5] = { 5, 4, 3, 2, 1 };
        int res[] = { 4, 3, 2 };
        int *b = res, *e = res + sizeof(res) / sizeof(res[0]);
        int *pb = a, *pe = pb + 5;
        rc = find_max(pb, pe, &i_max);
        if (rc == OK)
        {
            rc =find_min(pb, pe, &i_min);
            if (rc == OK)
            {
                m = abs(i_min - i_max) - 1;
                if (m > 0)
                {
                    pb_dst = malloc(m * sizeof(int));
                    if (pb_dst)
                    {
                        pe_dst = pb_dst + m;
                        rc = key(pb, pe, pb_dst, pe_dst, i_max, i_min);
                        printf("Correct work with valid arrays: %s\n", (rc == OK && check_array(pb_dst, pe_dst, b, e) == OK) ? "YES" : "NO");
                        //print_array(pb_dst, pe_dst); // 4 3 2
                        free(pb_dst);
                    }
                    else
                        rc = MEMORY_ERROR;
                }
                else
                    rc = EMPTY_ARRAY;
            }
        }
    }

    {
        int rc;
        int *pb_dst = NULL;
        int *pe_dst = NULL;
        const int *i_max = NULL, *i_min = NULL;
        int m;
        int a[5] = { -6, 3, 100, 0, 1 };
        int res[] = { 3 };
        int *b = res, *e = res + sizeof(res) / sizeof(res[0]);
        int *pb = a, *pe = pb + 5;
        rc = find_max(pb, pe, &i_max);
        if (rc == OK)
        {
            rc =find_min(pb, pe, &i_min);
            if (rc == OK)
            {
                m = abs(i_min - i_max) - 1;
                if (m > 0)
                {
                    pb_dst = malloc(m * sizeof(int));
                    if (pb_dst)
                    {
                        pe_dst = pb_dst + m;
                        rc = key(pb, pe, pb_dst, pe_dst, i_max, i_min);
                        printf("Correct work with valid arrays: %s\n\n", (rc == OK && check_array(pb_dst, pe_dst, b, e) == OK) ? "YES" : "NO");
                        //print_array(pb_dst, pe_dst); // 3
                        free(pb_dst);
                    }
                    else
                        rc = MEMORY_ERROR;
                }
                else
                    rc = EMPTY_ARRAY;
            }
        }
    }
}


/**
  Функция для тестирования сортировки.
 * @brief test_sort
 */
void test_sort(void)
{
    {
        char a[] = "12345";
        char b[] = "67890";
        char *pl = a, *pr = b;
        put_elem(pl, pr, sizeof(a));
        printf("Assignment test1: %s\n", a); //67890
    }

    {
        int a = 21;
        int b = 1;
        int *pl = &a, *pr = &b;
        put_elem(pl, pr, sizeof(int));
        printf("Assignment test2: %d\n", a); // 1
    }

    {
        double a = 45.6, b = 33.2;
        double *pl = &a, *pr = &b;
        put_elem(pl, pr, sizeof(double));
        printf("Assignment test3: %.2f\n", a); //33.20
    }
    printf("\n");
    {
        int a = -3, b = 20;
        printf("Correct work with int compare: %s\n", (cmp(&a, &b) < 0) ? "YES" : "NO");
        a = 12, b = 0;
        printf("Correct work with int compare: %s\n", (cmp(&a, &b) > 0) ? "YES" : "NO");
        a = 1, b = 1;
        printf("Correct work with int compare: %s\n", (cmp(&a, &b) == 0) ? "YES" : "NO");
    }

    {
        float a = -3.2, b = 20.33;
        printf("Correct work with float compare: %s\n", (cmp_float(&a, &b) < 0) ? "YES" : "NO");
        a = 2.1, b = -9.67;
        printf("Correct work with float compare: %s\n", (cmp_float(&a, &b) > 0) ? "YES" : "NO");
        a = -1.456, b = -2.456;
        printf("Correct work with float compare: %s\n", (cmp_float(&a, &b) > 0) ? "YES" : "NO");
        a = 1.456, b = 1.456;
        printf("Correct work with float compare: %s\n", (cmp_float(&a, &b) == 0) ? "YES" : "NO");
        a = 0.12, b = 0.91;
        printf("Correct work with float compare: %s\n", (cmp_float(&a, &b) < 0) ? "YES" : "NO");
    }

    {
        char a = 'a', b = 'b';
        printf("Correct work with char compare: %s\n", (cmp_char(&a, &b) < 0) ? "YES" : "NO");
        a = 'a', b = 'a';
        printf("Correct work with char compare: %s\n", (cmp_char(&a, &b) == 0) ? "YES" : "NO");
        a = 'c', b = 'b';
        printf("Correct work with char compare: %s\n", (cmp_char(&a, &b) > 0) ? "YES" : "NO");
    }

    printf("\n");

    {
        int a[] = { 1 };
        int size = sizeof(a) / sizeof(a[0]);
        int res[] = { 1 };
        int *b = res, *e = res + size;
        mysort(a, size, sizeof(int), cmp);
        printf("Correct work with sorting array in 1 element: %s\n", (check_array(a, a + size, b, e) == OK) ? "YES" : "NO");
        //print_array(a, a + size);
    }

    {
        int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int size = sizeof(a) / sizeof(a[0]);
        int res[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int *b = res, *e = res + size;
        mysort(a, size, sizeof(int), cmp);
        printf("Correct work with sorting increasing array: %s\n", (check_array(a, a + size, b, e) == OK) ? "YES" : "NO");
        //print_array(a, a + size);
    }

    {
        int a[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
        int size = sizeof(a) / sizeof(a[0]);
        int res[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int *b = res, *e = res + size;
        mysort(a, size, sizeof(int), cmp);
        printf("Correct work with sorting decreasing array: %s\n", (check_array(a, a + size, b, e) == OK) ? "YES" : "NO");
        //print_array(a, a + size);
    }

    {
        int a[] = { 2, 10 };
        int size = sizeof(a) / sizeof(a[0]);
        int res[] = { 2, 10 };
        int *b = res, *e = res + size;
        mysort(a, size, sizeof(int), cmp);
        printf("Correct work with sorting array in 2 sorted elements: %s\n", (check_array(a, a + size, b, e) == OK) ? "YES" : "NO");
        //print_array(a, a + size);
    }

    {
        int a[] = { 10, 2 };
        int size = sizeof(a) / sizeof(a[0]);
        int res[] = { 2, 10 };
        int *b = res, *e = res + size;
        mysort(a, size, sizeof(int), cmp);
        printf("Correct work with sorting array in 2 unsorted elements: %s\n", (check_array(a, a + size, b, e) == OK) ? "YES" : "NO");
        //print_array(a, a + size);
    }

    {
        int a[] = { 1, -7, 0, 6, 30, 9 };
        int size = sizeof(a) / sizeof(a[0]);
        int res[] = { -7, 0, 1, 6, 9, 30 };
        int *b = res, *e = res + size;
        mysort(a, size, sizeof(int), cmp);
        printf("Correct work with sorting random array: %s\n", (check_array(a, a + size, b, e) == OK) ? "YES" : "NO");
        //print_array(a, a + size);
    }

    {
        int a[] = { 12, 3, 4, 45, 5, 3, 2, -3, 0 };
        int size = sizeof(a) / sizeof(a[0]);
        int res[] = { -3, 0, 2, 3, 3, 4, 5, 12, 45 };
        int *b = res, *e = res + size;
        mysort(a, size, sizeof(int), cmp);
        printf("Correct work with sorting random array: %s\n", (check_array(a, a + size, b, e) == OK) ? "YES" : "NO");
        //print_array(a, a + size);
    }

    {
        int a[] = { 12 };
        int size = 0;
        int res[] = { 2 };
        int *b = res, *e = res;
        mysort(a, size, sizeof(int), cmp);
        printf("Correct work with sorting empty array: %s\n", (check_array(a, a + size, b, e) == OK) ? "YES" : "NO");
        //print_array(a, a + size);
    }

    {
        char a[] = "abcd";
        int size = sizeof(a) / sizeof(a[0]);
        char res[] = "abcd";
        char *b = res, *e = res + size;
        mysort(a, size - 1, sizeof(char), cmp_char);
        printf("Correct work with sorting char array: %s\n", (check_array_char(a, a + size, b, e) == OK) ? "YES" : "NO");
        //print_array(a, a + size);
    }

    {
        char a[] = "dcba";
        int size = sizeof(a) / sizeof(a[0]);
        char res[] = "abcd";
        char *b = res, *e = res + size;
        mysort(a, size - 1, sizeof(char), cmp_char);
        printf("Correct work with sorting char array: %s\n", (check_array_char(a, a + size, b, e) == OK) ? "YES" : "NO");
        //print_array(a, a + size);
    }

    {
        char a[] = "d";
        int size = sizeof(a) / sizeof(a[0]);
        char res[] = "d";
        char *b = res, *e = res + size;
        mysort(a, size - 1, sizeof(char), cmp_char);
        printf("Correct work with sorting char array: %s\n", (check_array_char(a, a + size, b, e) == OK) ? "YES" : "NO");
        //print_array(a, a + size);
    }
    {
        float a[] = { 12.3, 3.1, 0.4, 45.789, 5.3, 3.2, 0.002, -3.4, 0.09 };
        int size = sizeof(a) / sizeof(a[0]);
        float res[] = { -3.4, 0.002, 0.09, 0.4, 3.1, 3.2, 5.3, 12.3, 45.789 };
        float *b = res, *e = res + size;
        mysort(a, size, sizeof(int), cmp_float);
        printf("Correct work with sorting float array: %s\n", (check_array_float(a, a + size, b, e) == OK) ? "YES" : "NO");
        //print_array(a, a + size);
    }
    {
        float a[] = { 0.001, 0.002, 0.004, 0.0045 };
        int size = sizeof(a) / sizeof(a[0]);
        float res[] = { 0.001, 0.002, 0.004, 0.0045 };
        float *b = res, *e = res + size;
        mysort(a, size, sizeof(int), cmp_float);
        printf("Correct work with sorting float array: %s\n", (check_array_float(a, a + size, b, e) == OK) ? "YES" : "NO");
        //print_array(a, a + size);
    }

    {
        float a[] = { 0.0045, 0.004, 0.002, 0.001 };
        int size = sizeof(a) / sizeof(a[0]);
        float res[] = { 0.001, 0.002, 0.004, 0.0045 };
        float *b = res, *e = res + size;
        mysort(a, size, sizeof(int), cmp_float);
        printf("Correct work with sorting float array: %s\n", (check_array_float(a, a + size, b, e) == OK) ? "YES" : "NO");
        //print_array(a, a + size);
    }
}

int main(void)
{
    test_input();
    test_filter();
    test_sort();
    return 0;
}
