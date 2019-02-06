#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io.h"
#include "operations.h"
#include "defines.h"
#include "reverse.h"
#include "allocate.h"

#define CHECK_MATRIX_ERROR -8
#define N 3
#define M 3
#define T 2
#define O 1

/**
 * @brief check_matrix Функция проверяет равенство двух матриц
 * @param mtr_1 - указатель на массив указателей на строки первой матрицы
 * @param n_1 - количество строк первой матрицы
 * @param m_1 - количество столбцов первой матрицы
 * @param mtr_2 - указатель на массив указателей на строки второй матрицы
 * @param n_2 - количество строк второй матрицы
 * @param m_2 - количество столбцов второй матрицы
 * @return возвращает CHECK_MATRIX_ERROR, если матрицы не равны либо OK - если матрицы равны.
 */
int check_matrix(double **mtr_1, int n_1, int m_1, double **mtr_2, int n_2, int m_2)
{
    if (n_1 != n_2 || m_1 != m_2)
        return CHECK_MATRIX_ERROR;
    for (int i = 0; i < n_1; i++)
        for (int j = 0; j < m_1; j++)
            if (fabs(mtr_1[i][j] - mtr_2[i][j]) > EPS)
                return CHECK_MATRIX_ERROR;
    return OK;
}

/**
 * @brief test_input Тестирование ввода
 */
void test_input(void)
{
    {
        int rc = OK;
        double **buf = NULL;
        int n, m;

        rc = read_matrix("functional tests\\in_0.txt", &buf, &n, &m);
        printf("Correct work with error file: %s\n", (rc == FILE_OPEN_ERROR) ? "YES" : "NO");

        rc = read_matrix("functional tests\\in_1.txt", &buf, &n, &m);
        printf("Correct work with empty file: %s\n", (rc == INPUT_ERROR) ? "YES" : "NO");

        rc = read_matrix("functional tests\\in_3.txt", &buf, &n, &m);
        printf("Correct work with ivalid n m parameters: %s\n", (rc == N_M_ERROR) ? "YES" : "NO");
        rc = read_matrix("functional tests\\in_6.txt", &buf, &n, &m);
        printf("Correct work with ivalid n m parameters: %s\n", (rc == N_M_ERROR) ? "YES" : "NO");
        rc = read_matrix("functional tests\\in_11.txt", &buf, &n, &m);
        printf("Correct work with ivalid n m parameters: %s\n", (rc == N_M_ERROR) ? "YES" : "NO");
        rc = read_matrix("functional tests\\in_13.txt", &buf, &n, &m);
        printf("Correct work with ivalid n m parameters: %s\n", (rc == N_M_ERROR) ? "YES" : "NO");
        rc = read_matrix("functional tests\\in_14.txt", &buf, &n, &m);
        printf("Correct work with ivalid n m parameters: %s\n", (rc == N_M_ERROR) ? "YES" : "NO");

        rc = read_matrix("functional tests\\in_2.txt", &buf, &n, &m);
        printf("Correct work with ivalid n m parameters: %s\n", (rc == INPUT_ERROR) ? "YES" : "NO");
        rc = read_matrix("functional tests\\in_5.txt", &buf, &n, &m);
        printf("Correct work with ivalid n m parameters: %s\n", (rc == INPUT_ERROR) ? "YES" : "NO");
        rc = read_matrix("functional tests\\in_8.txt", &buf, &n, &m);
        printf("Correct work with ivalid n m parameters: %s\n", (rc == INPUT_ERROR) ? "YES" : "NO");
        rc = read_matrix("functional tests\\in_10.txt", &buf, &n, &m);
        printf("Correct work with ivalid n m parameters: %s\n", (rc == INPUT_ERROR) ? "YES" : "NO");
        rc = read_matrix("functional tests\\in_12.txt", &buf, &n, &m);
        printf("Correct work with ivalid n m parameters: %s\n", (rc == INPUT_ERROR) ? "YES" : "NO");

        rc = read_matrix("functional tests\\in_4.txt", &buf, &n, &m);
        printf("Correct work with ivalid \"i j a[i][j]\": %s\n", (rc == INPUT_ERROR) ? "YES" : "NO");
        rc = read_matrix("functional tests\\in_7.txt", &buf, &n, &m);
        printf("Correct work with ivalid \"i j a[i][j]\": %s\n", (rc == INPUT_ERROR) ? "YES" : "NO");
        rc = read_matrix("functional tests\\in_9.txt", &buf, &n, &m);
        printf("Correct work with ivalid \"i j a[i][j]\": %s\n\n", (rc == INPUT_ERROR) ? "YES" : "NO");
        rc = read_matrix("functional tests\\in_30.txt", &buf, &n, &m);
        printf("Correct work with valid params: %s\n\n", (rc == OK) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(buf, n);
    }
    {
        int rc = OK;
        double m1[N][M] =
        {
            { 0, 1, 2 },
            { 3, 4, 5 },
            { 6, 7, 8 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double **res = NULL;
        int res_n, res_m;
        rc = read_matrix("functional tests\\in_15.txt", &res, &res_n, &res_m);
        printf("Correct work with valid matrix: %s\n\n", (rc == OK && check_matrix(p1, s1, c1, res, res_n, res_m) == OK) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(res, res_n);
    }
}

/**
 * @brief test_addition Тестирование сложения
 */
void test_addition(void)
{
    {
        int rc = OK;
        double m1[N][M] =
        {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double m2[N][M] =
        {
            { 2, 5, 7 },
            { 6, 3, 4 },
            { 5, -2, -3 }
        };
        int s2 = sizeof(m2) / sizeof(m2[0]);
        int c2 = sizeof(m2[0]) / sizeof(m2[0][0]);
        double *p2[N];
        for (int i = 0; i < N; i++)
            p2[i] = m2[i];

        double arr[N][M] =
        {
            { 3, 7, 10 },
            { 10, 8, 10 },
            { 12, 6, 6 }
        };
        int s3 = sizeof(arr) / sizeof(arr[0]);
        int c3 = sizeof(arr[0]) / sizeof(arr[0][0]);
        double *p3[N];
        for (int i = 0; i < N; i++)
            p3[i] = arr[i];

        double **res = NULL;
        int res_n, res_m;
        rc = sum_matrix(p1, s1, c1, p2, s2, c2, &res, &res_n, &res_m);
        printf("Correct work with addition of correct matrixes 3x3: %s\n", (rc == OK && check_matrix(p3, s3, c3, res, res_n, res_m) == OK) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(res, res_n);
    }

    {
        int rc = OK;
        double m1[O][O] =
        {
            { -1 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double arr[O][O] =
        {
            { -2 }
        };
        int s3 = sizeof(arr) / sizeof(arr[0]);
        int c3 = sizeof(arr[0]) / sizeof(arr[0][0]);
        double *p3[N];
        for (int i = 0; i < s3; i++)
            p3[i] = arr[i];

        double **res = NULL;
        int res_n, res_m;
        rc = sum_matrix(p1, s1, c1, p1, s1, c1, &res, &res_n, &res_m);
        printf("Correct work with addition of correct matrixes 1x1: %s\n", (rc == OK && check_matrix(p3, s3, c3, res, res_n, res_m) == OK) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(res, res_n);
    }
    {
        int rc = OK;
        double m1[T][M] =
        {
            { 2, -3, 1 },
            { 5, 4, -2 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[T];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double m2[T][M] =
        {
            { -5, -2, -3 },
            { 4, -1, 0 }
        };
        int s2 = sizeof(m2) / sizeof(m2[0]);
        int c2 = sizeof(m2[0]) / sizeof(m2[0][0]);
        double *p2[T];
        for (int i = 0; i < s2; i++)
            p2[i] = m2[i];

        double arr[T][M] =
        {
            { -3, -5, -2 },
            { 9, 3, -2 }
        };
        int s3 = sizeof(m2) / sizeof(m2[0]);
        int c3 = sizeof(m2[0]) / sizeof(m2[0][0]);
        double *p3[T];
        for (int i = 0; i < s3; i++)
            p3[i] = arr[i];

        double **res = NULL;
        int res_n, res_m;
        rc = sum_matrix(p1, s1, c1, p2, s2, c2, &res, &res_n, &res_m);
        printf("Correct work with addition of correct matrixes 2x3: %s\n", (rc == OK && check_matrix(p3, s3, c3, res, res_n, res_m) == OK) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(res, res_n);
    }
    {
        int rc = OK;
        double m1[N][M] =
        {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double m2[T][M] =
        {
            { -5, -2, -3 },
            { 4, -1, 0 }
        };
        int s2 = sizeof(m2) / sizeof(m2[0]);
        int c2 = sizeof(m2[0]) / sizeof(m2[0][0]);

        double *p2[T];
        for (int i = 0; i < s2; i++)
            p2[i] = m2[i];

        double **res = NULL;
        int res_n, res_m;
        rc = sum_matrix(p1, s1, c1, p2, s2, c2, &res, &res_n, &res_m);
        printf("Correct work with addition of invalid matrix size (3x3 + 2x3): %s\n", (rc == N_M_ERROR) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(res, res_n);
    }

    {
        int rc = OK;
        double m1[N][M] =
        {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double m2[T][M] =
        {
            { -5, -2, -3 },
            { 4, -1, 0 }
        };
        int s2 = sizeof(m2) / sizeof(m2[0]);
        int c2 = sizeof(m2[0]) / sizeof(m2[0][0]);

        double *p2[T];
        for (int i = 0; i < s2; i++)
            p2[i] = m2[i];

        double **res = NULL;
        int res_n, res_m;
        rc = sum_matrix(p1, 0, c1, p2, s2, c2, &res, &res_n, &res_m);
        printf("Correct work with addition of invalid matrix size (0x3 + 2x3): %s\n\n", (rc == N_M_ERROR) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(res, res_n);
    }

    {
        int rc = OK;
        double m1[N][M] =
        {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double m2[N][M] =
        {
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 }
        };
        int s2 = sizeof(m2) / sizeof(m2[0]);
        int c2 = sizeof(m2[0]) / sizeof(m2[0][0]);
        double *p2[T];
        for (int i = 0; i < s2; i++)
            p2[i] = m2[i];

        double **res = NULL;
        int res_n, res_m;
        rc = sum_matrix(p1, s1, c1, p2, s2, c2, &res, &res_n, &res_m);
        printf("Correct work with addition of matrix 3x3 with zero matrix: %s\n\n", (rc == OK && check_matrix(p1, s1, c1, res, res_n, res_m) == OK) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(res, res_n);
    }
}

/**
 * @brief test_multiplication Тестирование умножения
 */
void test_multiplication(void)
{
    {
        int rc = OK;
        double m1[N][M] =
        {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double m2[N][M] =
        {
            { 2, 5, 7 },
            { 6, 3, 4 },
            { 5, -2, -3 }
        };
        int s2 = sizeof(m2) / sizeof(m2[0]);
        int c2 = sizeof(m2[0]) / sizeof(m2[0][0]);
        double *p2[N];
        for (int i = 0; i < N; i++)
            p2[i] = m2[i];

        double arr[N][M] =
        {
            { 29, 5, 6 },
            { 68, 23, 30 },
            { 107, 41, 54 }
        };
        int s3 = sizeof(arr) / sizeof(arr[0]);
        int c3 = sizeof(arr[0]) / sizeof(arr[0][0]);
        double *p3[N];
        for (int i = 0; i < N; i++)
            p3[i] = arr[i];

        double **res = NULL;
        int res_n, res_m;
        rc = mult_matrix(p1, s1, c1, p2, s2, c2, &res, &res_n, &res_m);
        printf("Correct work with multiplication of correct matrixes 3x3: %s\n", (rc == OK && check_matrix(p3, s3, c3, res, res_n, res_m) == OK) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(res, res_n);
    }

    {
        int rc = OK;
        double m1[O][O] =
        {
            { -1 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double arr[O][O] =
        {
            { 1 }
        };
        int s3 = sizeof(arr) / sizeof(arr[0]);
        int c3 = sizeof(arr[0]) / sizeof(arr[0][0]);
        double *p3[N];
        for (int i = 0; i < s3; i++)
            p3[i] = arr[i];

        double **res = NULL;
        int res_n, res_m;
        rc = mult_matrix(p1, s1, c1, p1, s1, c1, &res, &res_n, &res_m);
        printf("Correct work with multiplication of correct matrixes 1x1: %s\n", (rc == OK && check_matrix(p3, s3, c3, res, res_n, res_m) == OK) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(res, res_n);
    }
    {
        int rc = OK;
        double m1[T][M] =
        {
            { 2, -3, 1 },
            { 5, 4, -2 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[T];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double m2[T][M] =
        {
            { -5, -2, -3 },
            { 4, -1, 0 }
        };
        int s2 = sizeof(m2) / sizeof(m2[0]);
        int c2 = sizeof(m2[0]) / sizeof(m2[0][0]);
        double *p2[T];
        for (int i = 0; i < s2; i++)
            p2[i] = m2[i];

        double **res = NULL;
        int res_n, res_m;
        rc = mult_matrix(p1, s1, c1, p2, s2, c2, &res, &res_n, &res_m);
        printf("Correct work with multiplication of of invalid matrix size (2x3 * 2x3): %s\n", (rc == N_M_ERROR) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(res, res_n);
    }
    {
        int rc = OK;
        double m1[N][M] =
        {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double m2[T][M] =
        {
            { -5, -2, -3 },
            { 4, -1, 0 }
        };
        int s2 = sizeof(m2) / sizeof(m2[0]);
        int c2 = sizeof(m2[0]) / sizeof(m2[0][0]);

        double *p2[T];
        for (int i = 0; i < s2; i++)
            p2[i] = m2[i];

        double **res = NULL;
        int res_n, res_m;
        rc = mult_matrix(p1, s1, c1, p2, s2, c2, &res, &res_n, &res_m);
        printf("Correct work with multiplication of invalid matrix size (3x3 * 2x3): %s\n", (rc == N_M_ERROR) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(res, res_n);
    }

    {
        int rc = OK;
        double m1[N][M] =
        {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double m2[T][M] =
        {
            { -5, -2, -3 },
            { 4, -1, 0 }
        };
        int s2 = sizeof(m2) / sizeof(m2[0]);
        int c2 = sizeof(m2[0]) / sizeof(m2[0][0]);

        double *p2[T];
        for (int i = 0; i < s2; i++)
            p2[i] = m2[i];

        double **res = NULL;
        int res_n, res_m;
        rc = mult_matrix(p1, 0, c1, p2, s2, c2, &res, &res_n, &res_m);
        printf("Correct work with multiplication of invalid matrix size (0x3 * 2x3): %s\n", (rc == N_M_ERROR) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(res, res_n);
    }
    {
        int rc = OK;
        double m1[N][T] =
        {
            { 1, 2 },
            { 4, 5 },
            { 7, 8 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double m2[T][M] =
        {
            { -5, -2, -3 },
            { 4, -1, 0 }
        };
        int s2 = sizeof(m2) / sizeof(m2[0]);
        int c2 = sizeof(m2[0]) / sizeof(m2[0][0]);
        double *p2[T];
        for (int i = 0; i < s2; i++)
            p2[i] = m2[i];

        double arr[N][M] =
        {
            { 3, -4, -3 },
            { 0, -13, -12 },
            { -3, -22, -21 }
        };
        int s3 = sizeof(arr) / sizeof(arr[0]);
        int c3 = sizeof(arr[0]) / sizeof(arr[0][0]);
        double *p3[N];
        for (int i = 0; i < N; i++)
            p3[i] = arr[i];

        double **res = NULL;
        int res_n, res_m;
        rc = mult_matrix(p1, s1, c1, p2, s2, c2, &res, &res_n, &res_m);
        printf("Correct work with multiplication of correct matrixes (3x2 * 2x3): %s\n\n", (rc == OK && check_matrix(p3, s3, c3, res, res_n, res_m) == OK) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(res, res_n);
    }
    {
        int rc = OK;
        double m1[N][M] =
        {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double m2[N][M] =
        {
            { 1, 0, 0 },
            { 0, 1, 0 },
            { 0, 0, 1 }
        };
        int s2 = sizeof(m2) / sizeof(m2[0]);
        int c2 = sizeof(m2[0]) / sizeof(m2[0][0]);
        double *p2[T];
        for (int i = 0; i < s2; i++)
            p2[i] = m2[i];

        double **res = NULL;
        int res_n, res_m;
        rc = mult_matrix(p1, s1, c1, p2, s2, c2, &res, &res_n, &res_m);
        printf("Correct work with multiplication of matrix 3x3 with unit matrix: %s\n\n", (rc == OK && check_matrix(p1, s1, c1, res, res_n, res_m) == OK) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(res, res_n);
    }
}

void test_swap(void)
{
    {
        double m1[N][T] =
        {
            { 1, 2 },
            { 4, 5 },
            { 7, 8 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];
        double arr[N][T] =
        {
            { 7, 8 },
            { 4, 5 },
            { 1, 2 }
        };
        int s2 = sizeof(arr) / sizeof(arr[0]);
        int c2 = sizeof(arr[0]) / sizeof(arr[0][0]);
        double *res[N];
        for (int i = 0; i < s2; i++)
            res[i] = arr[i];

        swap_str(p1, 0, 2);
        printf("Correct work with swap of the strings in matrix: %s\n\n", (check_matrix(p1, s1, c1, res, s2, c2) == OK) ? "YES" : "NO");
    }

    {
        double m1[N][M] =
        {
            { 1, 2, 11 },
            { 4, 5, 12 },
            { 7, 8, 13 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];
        double arr[N][M] =
        {
            { 7, 8, 13 },
            { 4, 5, 12 },
            { 1, 2, 11 }
        };
        int s2 = sizeof(arr) / sizeof(arr[0]);
        int c2 = sizeof(arr[0]) / sizeof(arr[0][0]);
        double *res[N];
        for (int i = 0; i < s2; i++)
            res[i] = arr[i];

        swap_str(p1, 0, 2);
        printf("Correct work with swap of the strings in matrix: %s\n\n", (check_matrix(p1, s1, c1, res, s2, c2) == OK) ? "YES" : "NO");
    }
}


void test_solve(void)
{
    {
        double m1[T][T] =
        {
            { 1, -5 },
            { 0, 1 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];
        double m2[T][T] =
        {
            { 3, 8 },
            { 6, 5 }
        };
        double *p2[N];
        for (int i = 0; i < s1; i++)
            p2[i] = m2[i];

        double arr[T][T] =
        {
            { 33, 33 },
            { 6, 5 }
        };
        double *p3[N];
        for (int i = 0; i < s1; i++)
            p3[i] = arr[i];
        double res[T][T] =
        {
            { 0, 0 },
            { 0, 0 }
        };
        double *p4[N];
        for (int i = 0; i < s1; i++)
            p4[i] = res[i];

        solve(p1, p2, p4, s1);
        printf("Correct work with finding roots: %s\n", (check_matrix(p3, s1, s1, p4, sizeof(res) / sizeof(res[0]), s1) == OK) ? "YES" : "NO");
    }

    {
        double m1[O][O] =
        {
            { 12 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double m2[O][O] =
        {
            { 3 }
        };
        double *p2[N];
        for (int i = 0; i < s1; i++)
            p2[i] = m2[i];

        double arr[O][O] =
        {
            { 0.25 }
        };
        double *p3[N];
        for (int i = 0; i < s1; i++)
            p3[i] = arr[i];
        double res[O][O] =
        {
            { 0 }
        };
        double *p4[N];
        for (int i = 0; i < s1; i++)
            p4[i] = res[i];

        solve(p1, p2, p4, s1);
        printf("Correct work with finding roots: %s\n", (check_matrix(p3, s1, s1, p4, sizeof(res) / sizeof(res[0]), s1) == OK) ? "YES" : "NO");
    }
    {
        double m1[N][M] =
        {
            { 4, 12, 1 },
            { 0, -8, 5 },
            { 0, 0, 6 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];
        double m2[M][M] =
        {
            { 3, 5, 2 },
            { 7, 6, 4 },
            { 2, 1, 3 }
        };
        double *p2[N];
        for (int i = 0; i < s1; i++)
            p2[i] = m2[i];

        double arr[M][M] =
        {
            { 2.666666, 3.145833, 0.9375 },
            { -0.66666, -0.645833, -0.1875 },
            { 0.333333, 0.1666666, 0.5 }
        };
        double *p3[N];
        for (int i = 0; i < s1; i++)
            p3[i] = arr[i];
        double res[M][M] =
        {
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 }
        };
        double *p4[N];
        for (int i = 0; i < s1; i++)
            p4[i] = res[i];

        solve(p1, p2, p4, s1);
        printf("Correct work with finding roots: %s\n", (check_matrix(p3, s1, s1, p4, sizeof(res) / sizeof(res[0]), s1) == OK) ? "YES" : "NO");
    }
}


/**
 * @brief test_triangular Тестирование функции приведения матрицы к треугольном виду с единицами на диагонали и записи преобразованной единичной матрицы
 */
void test_triangular(void)
{
    {
        int rc = OK;
        double m1[T][M] =
        {
            { 2, -3, 1 },
            { 5, 4, -2 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[T];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];
        double **res = NULL;
        rc = triangular_matrix(p1, res, s1, c1);
        printf("Correct work with finding triangular matrix for invalid parameters (n != m): %s\n", (rc == N_M_ERROR) ? "YES" : "NO");
    }

    {
        int rc = OK;
        double **p1 = NULL;
        double **res = NULL;
        rc = triangular_matrix(p1, res, 0, 0);
        printf("Correct work with finding triangular matrix for invalid parameters (n <= 0): %s\n\n", (rc == N_M_ERROR) ? "YES" : "NO");
    }

    {
        int rc = OK;
        double m1[N][M] =
        {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];
        double mtr[N][M] =
        {
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 }
        };
        double *res[N];
        for (int i = 0; i < s1; i++)
            res[i] = mtr[i];
        rc = triangular_matrix(p1, res, s1, c1);
        printf("Correct work with finding triangular matrix for degenerate matrix: %s\n\n", (rc == DETERMINANT_ERROR) ? "YES" : "NO");
    }

    {
        int rc = OK;
        double m1[O][O] =
        {
            { 45.2 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[O];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];
        double m2[O][O] =
        {
            { 1.0 }
        };
        int s2 = sizeof(m2) / sizeof(m2[0]);
        int c2 = sizeof(m2[0]) / sizeof(m2[0][0]);
        double *p2[O];
        for (int i = 0; i < s2; i++)
            p2[i] = m2[i];
        double mtr[O][O] =
        {
            { 0 }
        };
        double *res[N];
        for (int i = 0; i < s1; i++)
            res[i] = mtr[i];
        rc = triangular_matrix(p1, res, s1, c1);
        printf("Correct work with finding triangular matrix for valid matrix 1x1: %s\n", (rc == OK && check_matrix(res, s1, c1, p2, s2, c2) == OK) ? "YES" : "NO");
    }

    {
        int rc = OK;
        double m1[T][T] =
        {
            { 2, 4 },
            { 7, 3 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[T];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double m2[T][T] =
        {
            { 0, 1 },
            { 1, -0.28571 }
        };
        int s2 = sizeof(m2) / sizeof(m2[0]);
        int c2 = sizeof(m2[0]) / sizeof(m2[0][0]);
        double *p2[T];
        for (int i = 0; i < s2; i++)
            p2[i] = m2[i];
        double mtr[N][M] =
        {
            { 0, 0 },
            { 0, 0 }
        };
        double *res[T];
        for (int i = 0; i < s1; i++)
            res[i] = mtr[i];
        rc = triangular_matrix(p1, res, s1, c1);
        printf("Correct work with finding triangular matrix for valid matrix 2x2: %s\n", (rc == OK && check_matrix(res, s1, c1, p2, s2, c2) == OK) ? "YES" : "NO");
    }

    {
        int rc = OK;
        double m1[N][N] =
        {
            { 1, -5, 6 },
            { 4, 12, 1 },
            { 0, -3, 2 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double m2[N][M] =
        {
            { 0, 1, 0 },
            { 1, -0.25, 0 },
            { -0.375, 0.09375, 1 }
        };
        int s2 = sizeof(m2) / sizeof(m2[0]);
        int c2 = sizeof(m2[0]) / sizeof(m2[0][0]);
        double *p2[N];
        for (int i = 0; i < s2; i++)
            p2[i] = m2[i];
        double mtr[N][M] =
        {
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 }
        };
        double *res[N];
        for (int i = 0; i < s1; i++)
            res[i] = mtr[i];
        rc = triangular_matrix(p1, res, s1, c1);
        printf("Correct work with finding triangular matrix for valid matrix 3x3: %s\n\n", (rc == OK && check_matrix(res, s1, c1, p2, s2, c2) == OK) ? "YES" : "NO");
    }
}

/**
 * @brief test_reverse Тестирование функции нахождения обратной матрицы
 */
void test_reverse(void)
{
    {
        int rc = OK;
        double m1[O][O] =
        {
            { 5.0 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[O];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];
        double m2[O][O] =
        {
            { 0.2 }
        };
        int s2 = sizeof(m2) / sizeof(m2[0]);
        int c2 = sizeof(m2[0]) / sizeof(m2[0][0]);
        double *p2[O];
        for (int i = 0; i < s2; i++)
            p2[i] = m2[i];
        double **buf = NULL;
        int res_n, res_m;
        rc = reverse(p1, s1, c1, &buf, &res_n, &res_m);
        printf("Correct work with reversing matrix for valid matrix 1x1: %s\n", (rc == OK && check_matrix(buf, res_n, res_m, p2, s2, c2) == OK) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(buf, res_n);

    }

    {
        int rc = OK;
        double m1[T][T] =
        {
            { 7, 4 },
            { 5, 3 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[T];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double m2[T][T] =
        {
            { 3.0, -4.0 },
            { -5.0, 7.0 }
        };
        int s2 = sizeof(m2) / sizeof(m2[0]);
        int c2 = sizeof(m2[0]) / sizeof(m2[0][0]);
        double *p2[T];
        for (int i = 0; i < s2; i++)
            p2[i] = m2[i];
        double **buf = NULL;
        int res_n, res_m;
        rc = reverse(p1, s1, c1, &buf, &res_n, &res_m);
        printf("Correct work with reversing matrix for valid matrix 2x2: %s\n", (rc == OK && check_matrix(buf, res_n, res_m, p2, s2, c2) == OK) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(buf, res_n);
    }

    {
        int rc = OK;
        double m1[N][N] =
        {
            { 1, -5, 6 },
            { 4, 12, 1 },
            { 0, -3, 2 }
        };
        int s1 = sizeof(m1) / sizeof(m1[0]);
        int c1 = sizeof(m1[0]) / sizeof(m1[0][0]);
        double *p1[N];
        for (int i = 0; i < s1; i++)
            p1[i] = m1[i];

        double m2[N][N] =
        {
            { -5.40, 1.60, 15.40 },
            { 1.60, -0.40, -4.60 },
            { 2.40, -0.60, -6.40 }
        };
        int s2 = sizeof(m2) / sizeof(m2[0]);
        int c2 = sizeof(m2[0]) / sizeof(m2[0][0]);
        double *p2[N];
        for (int i = 0; i < s2; i++)
            p2[i] = m2[i];
        double **buf = NULL;
        int res_n, res_m;
        rc = reverse(p1, s1, c1, &buf, &res_n, &res_m);
        printf("Correct work with reversing matrix for valid matrix 3x3: %s\n", (rc == OK && check_matrix(buf, res_n, res_m, p2, s2, c2) == OK) ? "YES" : "NO");
        if (rc == OK)
            free_matrix(buf, res_n);
    }
}
int main(void)
{
    test_input();
    test_addition();
    test_multiplication();
    test_swap();
    test_triangular();
    test_solve();
    test_reverse();
}
