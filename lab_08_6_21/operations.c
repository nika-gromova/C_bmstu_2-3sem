#include "operations.h"
#include "defines.h"
#include "allocate.h"
#include "io.h"

/**
 * @brief operations Функция для обработки операций сложения и умножения. Считывает вторую матрицу из файла file_src, и вызывает соответствующую операции функцию. После выполнения операция память под вторую матрицу освобождается.
 * @param file_src [in] - файл, из которого считывается вторая матрица
 * @param matrix_1 [in] - указатель на массив указателей на строки первой матрицы
 * @param n_1 [in] - количество строк первой матрицы
 * @param m_1 [in] - количество столбцов первой матрицы
 * @param matrix_2 [in] - указатель на массив указателей на строки второй матрицы
 * @param n_2 [in] - количество строк второй матрицы
 * @param m_2 [in] - количество столбцов второй матрицы
 * @param result [in] - указатель на массив указателей на строки результирующей матрицы
 * @param n_3 [in] - указатель на переменную, содержащую количество строк результирующей матрицы
 * @param m_3 [in] - указатель на переменную, содержащую количество столбцов результирующей матрицы
 * @param operation [in] - указатель на функцию, которая производит указанную операцию.
 * @return rc - возвращает INPUT_ERROR, если не удалось считать числа или текущий считанный элемент второй матрицы равен нулю или элемент второй матрицы с текущими считанными индексаи уже был введен,
 либо MEMORY_ERROR, если не удалось выделить память для считываемой второй матрицы или память под матрицу результата,
 либо N_M_ERROR, если введенные размеры второй матрицы некорректны (n или m < 0, или количество ненулевых элементов больше, чем общее количество элементов матрицы,
 или для заданной операции n и m не удовлетворяют условиям,
 либо OK, если вторая матрица успешно считана, заданная операция прошла успешно и результат записан в матрицу-результат.
 */
int operations(char *file_src, double **matrix_1, int n_1, int m_1, double ***matrix_2, int *n_2, int *m_2, double ***result, int *n_3, int *m_3,\
               int(*operation)(double **, int, int, double **, int, int, double ***, int *, int *))
{
    int rc = OK;
    rc = read_matrix(file_src, matrix_2, n_2, m_2);
    if (rc == OK)
    {
        rc = operation(matrix_1, n_1, m_1, *matrix_2, *n_2, *m_2, result, n_3, m_3);
        free_matrix(*matrix_2, *n_2);
    }
    return rc;
}

/**
 * @brief sum_matrix Функция осуществляет сложение матриц, записывая результат в результирующую матрицу.
 * @param matrix_1 [in] - указатель на массив указателей на строки первой матрицы
 * @param n_1 [in] - количество строк первой матрицы
 * @param m_1 [in] - количество столбцов первой матрицы
 * @param matrix_2 [in] - указатель на массив указателей на строки второй матрицы
 * @param n_2 [in] - количество строк второй матрицы
 * @param m_2 [in] - количество столбцов второй матрицы
 * @param result [in] - указатель на массив указателей на строки результирующей матрицы
 * @param n_3 [in] - указатель на переменную, содержащую количество строк результирующей матрицы
 * @param m_3 [in] - указатель на переменную, содержащую количество столбцов результирующей матрицы
 * @return возвращает N_M_ERROR, если количество строк или столбцов складываемых матриц меньше единицы или если количество строк(столбцов)
 первой матрицы не равно количеству строк(столбцов) второй матрицы; MEMORY_ERROR, если не удалось выделить память под результирующую матрицу;
 OK, если вычисления успешно произведены и записаны в результирующую матрицу.
 */
int sum_matrix(double **matrix_1, int n_1, int m_1, double **matrix_2, int n_2, int m_2, double ***result, int *n_3, int *m_3)
{
    if (n_1 < 1 || n_2 < 1 || m_1 < 1 || m_2 < 1)
        return N_M_ERROR;
    if (n_1 != n_2 || m_1 != m_2)
        return N_M_ERROR;
    *n_3 = n_1;
    *m_3 = m_1;

    double **buf = allocate_matrix(*n_3, *m_3);
    if (buf)
    {
        for (int i = 0; i < n_1; i++)
            for (int j = 0; j < m_1; j++)
                buf[i][j] = matrix_1[i][j] + matrix_2[i][j];
        *result = buf;
    }
    else
        return MEMORY_ERROR;
    return OK;
}

/**
 * @brief mult_matrix Функция осуществляет умножение матриц, записывая результат в результирующую матрицу.
 * @param matrix_1 [in] - указатель на массив указателей на строки первой матрицы
 * @param n_1 [in] - количество строк первой матрицы
 * @param m_1 [in] - количество столбцов первой матрицы
 * @param matrix_2 [in] - указатель на массив указателей на строки второй матрицы
 * @param n_2 [in] - количество строк второй матрицы
 * @param m_2 [in] - количество столбцов второй матрицы
 * @param result [in] - указатель на массив указателей на строки результирующей матрицы
 * @param n_3 [in] - указатель на переменную, содержащую количество строк результирующей матрицы
 * @param m_3 [in] - указатель на переменную, содержащую количество столбцов результирующей матрицы
 * @return возвращает N_M_ERROR, если количество строк или столбцов матриц-операндов меньше единицы или если количество столбцов
 первой матрицы не равно количеству строк второй матрицы; MEMORY_ERROR, если не удалось выделить память под результирующую матрицу;
 OK, если вычисления успешно произведены и записаны в результирующую матрицу.
 */
int mult_matrix(double **matrix_1, int n_1, int m_1, double **matrix_2, int n_2, int m_2, double ***result, int *n_3, int *m_3)
{
    if (n_1 < 1 || n_2 < 1 || m_1 < 1 || m_2 < 1)
        return N_M_ERROR;
    if (m_1 != n_2)
        return N_M_ERROR;
    *n_3 = n_1;
    *m_3 = m_2;

    double **buf = allocate_matrix(*n_3, *m_3);
    if (buf)
    {
        for (int i = 0; i < n_1; i++)
        {
            for (int j = 0; j < m_2; j++)
            {
                buf[i][j] = 0;
                for (int k = 0; k < m_1; k++)
                    buf[i][j] += matrix_1[i][k] * matrix_2[k][j];
            }
        }
        *result = buf;
    }
    else
        return MEMORY_ERROR;
    return OK;
}
