#include "allocate.h"

/**
 * @brief allocate_matrix Функция выделения памяти под матрицу с хранением указателей на каждую строку матрицы
 * @param n - количество строк матрицы
 * @param m - количество столбцов матрицы
 * @return возвращает NULL, если память выделить не удалось, либо указатель на массив указателей на строки матрицы
 */
// Объединенный подход 1 ( память под массив указателей на строки и под данные)
double **allocate_matrix(int n, int m)
{
    double **matrix = calloc(n, sizeof(double *));
    if (matrix)
    {
        for (int i = 0; i < n; i++)
        {
            matrix[i] = calloc(m, sizeof(double));
            if (!matrix[i])
            {
                free_matrix(matrix, n);
                return NULL;
            }
        }
    }
    return matrix;
//    double **matrix = malloc((n + 1) * sizeof(double *));
//    if (matrix)
//    {
//        double *data = calloc(n * m, sizeof(double));
//        if (data)
//        {
//            for (int k = 0; k < n; k++)
//                matrix[k] = data + k * m;
//            matrix[n] = data;
//        }
//        else
//        {
//            free(matrix);
//            return NULL;
//        }
//    }
//    return matrix;
}

// Массив указателей на строки
/*double **allocate_matrix(int n, int m)
{
    double **matrix = malloc(n * sizeof(double *));
    if (matrix)
    {
        for (int k = 0; k < n; k++)
        {
            matrix[k] = calloc(m, sizeof(double));
            if (!matrix[k])
            {
                free_matrix(matrix, n);
                return NULL;
            }
        }
    }
    return matrix;
}*/

// Объединенный подход 2 (память под массив указателей на строки и данные сразу в одном блоке)
/*double **allocate_matrix(int n, int m)
{
    double **matrix = malloc(n * sizeof(double *) + n * m * sizeof(double));
    if (matrix)
    {
        for (int i = 0; i < n; i++)
            matrix[i] = (double *)((char *)matrix + n * sizeof(double *) + i * m * sizeof(double));
    }
    return matrix;
}
*/

/**
 * @brief free_matrix Функция освобождения памяти из-под матрицы
 * @param matrix - указатель на массив указателей на строки матрицы
 */
// Объединенный подход 1
void free_matrix(double **matrix, int n)
{
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
//    free(matrix[n]);
//    free(matrix);
}

// Массив указателей на строки
/*void free_matrix(double **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}*/

// Объединенный подход 2
/*void free_matrix(double **matrix, int n)
{
    free(matrix);
}*/
