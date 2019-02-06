#include "io.h"
#include "defines.h"
#include "allocate.h"

void zero(double **matrix, int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matrix[i][j] = 0.0;
}

/**
 * Функция считывает матрицу, записанной в файле "file_name" в координатном виде, и записывает её в выделенный блок памяти, указатель на которую изменяется в самой функции.
 * @brief read_matrix
 * @param file_name [in] - имя файла, откуда считывается матрица
 * @param matrix [in] - указатель на массив указателей на строки матрицы
 * @param n [in] - указатель на переменную, содержащую количество строк матрицы
 * @param m [in] - указатель на переменную, содержащую количество столбцов матрицы
 * @return rc - возвращает INPUT_ERROR, если не удалось считать числа или текущий считанный элемент матрицы равен нулю или элемент матрицы с текущими считанными индексаи уже был введен,
 либо MEMORY_ERROR, если не удалось выделить память для считываемой матрицы,
 либо N_M_ERROR, если введенные размеры матрицы некорректны (n или m < 0, или количество ненулевых элементов больше, чем общее количество элементов матрицы),
 либо OK, если ввод успешен.
 */
int read_matrix(const char *file_name, double ***matrix, int *n, int *m)
{
    FILE *f;
    int rc = OK;
    int i = 0; int j = 0;
    int not_null;
    double **buf = NULL;
    f = fopen(file_name, "r");
    if (f)
    {
        if (fscanf(f, "%d %d %d", n, m, &not_null) == 3)
        {
            if (*n > 0 && *m > 0 && not_null > 0 && not_null <= (*n) * (*m))
            {
                buf = allocate_matrix(*n, *m);
                if (buf)
                {
                    zero(buf, *n, *m);
                    for (int k = 0; k < not_null && rc == OK; k++)
                    {
                        if (fscanf(f, "%d %d", &i, &j) == 2 && i > 0 && j > 0 && i <= *n && j <= *m)
                        {
                            if ((buf[i - 1][j - 1] != 0) || fscanf(f, "%lf", &buf[i - 1][j - 1]) != 1 || buf[i - 1][j - 1] == 0)
                                rc = INPUT_ERROR;
                        }
                        else
                            rc = INPUT_ERROR;
                        if (k + 1 != not_null && feof(f) != 0)
                            rc = INPUT_ERROR;
                    }
                    if (rc == INPUT_ERROR)
                        free_matrix(buf, *n);
                    else
                    {
                        *matrix = buf;
                        /*if (feof(f) == 0)
                        {
                            rc = INPUT_ERROR;
                            free_matrix(buf);
                        }*/
                    }
                }
                else
                    rc = MEMORY_ERROR;
            }
            else
                rc = N_M_ERROR;
        }
        else
            rc = INPUT_ERROR;
        fclose(f);
    }
    else
        return FILE_OPEN_ERROR;
    return rc;
}

/**
 * @brief print_matrix Печать матрицы, использовалась как отладочная
 * @param matrix [in] - указатель на массив указателей на строки матрицы
 * @param n [in] - количество строк матрицы
 * @param m [in] - количество столбцов матрицы
 */
void print_matrix(double **matrix, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%.2lf ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

/**
 * @brief save_matrix Сохранение матрицы в файл в обычном (простом) формате.
 * @param file_name [in] - файл, в который записывается матрица
 * @param matrix [in] - указатель на массив указателей на строки матрицы
 * @param n [in] - количество строк матрицы
 * @param m [in] - количество столбцов матрицы
 * @return rc - возвращает FILE_OPEN_ERROR, если не удалось открыть файл для записи, либо OK, если матрица записана успешно.
 */
int save_matrix(char *file_name, double **matrix, int n, int m)
{
    int rc = OK;
    FILE *f;
    f = fopen(file_name, "w");
    if (f)
    {
        fprintf(f, "%d %d\n", n, m);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                fprintf(f, "%lf ", matrix[i][j]);
            fprintf(f, "\n");
        }
        fclose(f);
    }
    else
        rc = FILE_OPEN_ERROR;
    return rc;
}
