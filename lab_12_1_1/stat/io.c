#include "arr_lib.h"
#include "defines.h"

/**
  Функция считает количество целых чисел в файле.
 * @brief count_n
 * @param f [in] - файл, в котором считается количество целых чисел
 * @return Возвращает INPUT_ERROR если все целые цисла считаны, но конец файла не достигнут,
  либо n - количество целых чисел в файле.
 *
 */
int count_n(FILE *f)
{
    int n = 0;
    int num;
    while (fscanf(f, "%d", &num) == 1)
        n++;
    if (feof(f) == 0)
        return INPUT_ERROR;
    return n;
}

/**
  Считывает целые числа из файла и записывает их в массив.
 * @brief input_array
 * @param f [in] - файл, из которого происходит чтение данных
 * @param pb [in] - указатель на начало массива, в котором будут храниться прочитанные данные
 * @param pe [in] - указатель на конец массива, в котором будут храниться прочитанные данные
 * @return Возвращает INPUT_ERROR если считанное не является целым числом или не достигнут конец файла,
  либо OK, если все данные считаны из файла (все считанное - целые числа) и записаны в массив.
 */
int input_array(FILE *f, int *pb, int *pe)
{
    int *pcur = pb;
    while (pcur < pe)
    {
        if (fscanf(f, "%d", pcur) != 1)
            return INPUT_ERROR;
        pcur++;
    }
    if (feof(f) == 0)
        return INPUT_ERROR;
    return OK;
}

/**
  Функция находит количество целых чисел в файле n, выделяет память для массива размера n,
  записывает в новый массив считанные целые числа из файла.
 * @brief input
 * @param f [in] - файл, из которого происходит чтение данных
 * @param pb [in] - указатель на начало массива, в котором будут храниться прочитанные данные
 * @param pe [in] - указатель на конец массива, в котором будут храниться прочитанные данные
 * @return Возвращает MEMORY_ERROR, если по каким-то причинам не удалось выделить память под новый массив,
  либо EMPTY_ARRAY, если в файле нет целых чисел или же в файле содержатся не только целые числа или же если файл пустой,
  либо OK, если значения успешно считаны и записаны в новый массив.
 */
int input(FILE *f, int **pb, int **pe)
{
    int rc, n;
    rewind(f);
    n = count_n(f);
    if (n > 0)
    {
        int *buf = malloc(n * sizeof(int));
        if (buf)
        {
            rewind(f);
            rc = input_array(f, buf, buf + n);
            if (rc == OK)
            {
                *pb = buf;
                *pe = buf + n;
            }
            else
                free(buf);
        }
        else
            rc = MEMORY_ERROR;
    }
    else
        rc = EMPTY_ARRAY;
    return rc;
}

/**
  Функция записи массива в файл
 * @brief output_array
 * @param f [in] - файл, в который необходимо записать массив
 * @param pb [in] - указатель на начало массива
 * @param pe [in] - указатель на конец массива
 */
void output_array(FILE *f, const int *pb, const int *pe)
{
    for (const int *pcur = pb; pcur < pe; pcur++)
    {
        fprintf(f, "%d ", *pcur);
    }
}
