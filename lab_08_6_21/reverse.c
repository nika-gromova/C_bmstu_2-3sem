#include "reverse.h"
#include "io.h"
#include "defines.h"
#include "allocate.h"
#include "math.h"

/**
 * @brief swap_str Функция меняет строки местами
 * @param p1 - адрес первой строки
 * @param p2 - адрес второй строки
 * @param m - количество элементов в строке
 */
/*void swap_str(double *p1, double *p2, int m)
{
    double tmp;
    for (int i = 0; i < m; i++)
    {
        tmp = p1[i];
        p1[i] = p2[i];
        p2[i] = tmp;
    }
}
*/
void swap_str(double **matrix, int i1, int i2)
{
    double *tmp;
    tmp = matrix[i1];
    matrix[i1] = matrix[i2];
    matrix[i2] = tmp;
}

/**
 * @brief solve Функция нахождения решений системы с помощью треугольной матрицы, на главной диагонали которой стоят единицы.
 * @param matrix - указатель на массив указателей на строки матрицы
 * @param unit_column - столбец свободных членов
 * @param result_column - столбец результатов
 * @param n - размерность матрицы
 */
void solve(double **matrix, double **unit_matrix, double **result, int n)
{
    assert(n > 0);
    double tmp = 0.0;

    for (int i = 0; i < n; i++)
    {
        for (int k = n - 1; k > -1; k--)
        {
            for (int j = k + 1; j < n; j++)
                tmp += result[j][i] * matrix[k][j];
            result[k][i] = (unit_matrix[k][i] - tmp) / matrix[k][k];
            tmp = 0.0;
        }
    }
}

/**
 * @brief find_determinant Функция вычисляет определитель треугольной матрицы.
 * @param matrix [in] - тсходная матрица
 * @param n [in] - количество элементов матрицы
 * @return double det - значение определителя матрицы.
 */
double find_determinant(double **matrix, int n)
{
    double det = 1.0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i == j)
                det *= matrix[i][j];
    return det;
}

void unity(double **matrix, int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (i == j)
                matrix[i][j] = 1.0;
            else
                matrix[i][j] = 0.0;
        }
}

/**
 * @brief triangular_matrix Функция приведения матрицы к треугольному виду с единицами на главной диагонали,
 * производящая также одновременные идентичные изменения в единичной матрице того же размера, что и исходная.
 * @param matrix - указатель на массив указателей на строки исходной матрицы
 * @param reversed_matrix - указатель на массив указателей на строки единичной матрицы
 * @param n - количество строк исходной матрицы
 * @param m - количество столбцов исходной матрицы
 * @return rc - возвращает N_M_ERROR, если изначальная матрица не квадратная или размерность матрицы меньше единицы;
 ONE_ELEMENT_MATRIX, если изначальная матрица - единичная (обратная матрица равна самой себе);
 DETERMINANT_ERROR, если определитель матрицы равен нулю (обратной не существует);
 OK, если приведение к треугольному виду прошло успешно.
 */
int triangular_matrix(double **matrix, double **reversed, int n, int m)
{
    if (n != m || n <= 0)
        return N_M_ERROR;
    double tmp;
    double coefficient;
    int i = 0, j = 0;
    double max_elem;
    int max_index;

    unity(reversed, n, m);

    if (n == 1)
        return OK;

    while (i < n && j < m)
    {
        max_elem = 0.0;
        max_index = 0;
        for (int k = i; k < n; k++)
            if(fabs(matrix[k][j]) > max_elem)
            {
                max_elem = fabs(matrix[k][j]);
                max_index = k;
            }

        if (fabs(max_elem) < EPS)
            return DETERMINANT_ERROR;

        if (max_index != i)
        {
            //swap_str(matrix[i], matrix[max_index], m);
            //swap_str(reversed[i], reversed[max_index], m);
            swap_str(matrix, i, max_index);
            swap_str(reversed, i, max_index);
        }
        tmp = matrix[i][j];

        for (int k = i + 1; k < n; k++)
        {
            coefficient = matrix[k][j] / tmp;
            for (int h = 0; h < m; h++)
            {
                matrix[k][h] -= coefficient * matrix[i][h];
                reversed[k][h] -= coefficient * reversed[i][h];
            }
        }
        i++;
        j++;
    }

    double determinant = find_determinant(matrix, n);
    if (fabs(determinant) < EPS)
        return DETERMINANT_ERROR;
    return OK;
}

/**
 * @brief reverse Функция нахождения обратной матрицы для исходной.
 * @param matrix - указатель на массив указателей на строки исходной матрицы
 * @param n - количество строк исходной матрицы
 * @param m - количество столбцов исходной матрицы
 * @param result - указатель на массив указателей на строки результирующей матрицы
 * @param res_n - указатель на переменную, содержащую количество строк результирующей матрицы
 * @param res_m - указатель на переменную, содуржащую количество столбцов результирующей матрицы
 * @return rc - возвращает N_M_ERROR, если исходная матрица не квадратная или её размерность меньше 1;
 MEMORY_ERROR, если не удалось выделить память под результирующую матрицу или единичную матрицу того же размера;
 ONE_ELEMENT_MATRIX, если матрица состоит из одного элемента;
 OK, если обратная матрица найдена и записана в результирующую.
 */
int reverse(double **matrix, int n, int m, double ***result, int *res_n, int *res_m)
{
    int rc = OK;
    if (n != m || n <= 0 || m <= 0)
        return N_M_ERROR;
    *res_n = n;
    *res_m = m;

    double **reversed_matrix = NULL;
    reversed_matrix = allocate_matrix(n, m);
    if (reversed_matrix)
    {
        rc = triangular_matrix(matrix, reversed_matrix, n, m);
        if (rc == OK)
        {
            double **buf = NULL;
            buf = allocate_matrix(n, m);
            if (buf)
            {
                solve(matrix, reversed_matrix, buf, n);
                *result = buf;
            }
            else
                rc = MEMORY_ERROR;
        }
        free_matrix(reversed_matrix, n);
    }
    else
        rc = MEMORY_ERROR;
    return rc;
}
