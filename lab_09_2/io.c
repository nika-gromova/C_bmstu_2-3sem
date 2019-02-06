#include "io.h"
#include "str.h"
#include "defines.h"

/**
 * @brief my_getline Функция считывает строку из файла, результат записывается в строку, указатель на которую передается через параметр функции.
 * Считывание происходит либо до символа перехода на новую строку (этот символ записывается в результирующую строку), либо до конца файла (при этом
 * функция возвращает отрицательное значение, но считанные данные все равно сохраняется в *lineptr.
 * @param lineptr [in][out] - указатель на строку
 * @param n [in][out] - количество выделенных байт под строку
 * @param f [in] - файл для чтения
 * @return  Возвращает length - количество считанных байт, либо GETLINE_ERROR (-1) в случае ошибки открытия файла, ошибки выделения памяти, пустого файла и достижения конца файла.
 */
ssize_t my_getline(char **lineptr, size_t *n, FILE *f)
{
    if (!f)
        return GETLINE_ERROR;
    if (feof(f))
        return GETLINE_ERROR;
    if (lineptr == NULL || n == NULL)
        return GETLINE_ERROR;

    if (*lineptr != NULL)
        if (len(*lineptr) + 1 > *n)
            return GETLINE_ERROR;
    char cur[BUF_SIZE + 1];
    char *tmp = NULL;
    size_t cur_len;
    ssize_t length = 0;
    char flag_read = 1;
    while (flag_read && fgets(cur, sizeof(cur), f))
    {
        cur_len = len(cur);
        if (cur_len == 0)
            return GETLINE_ERROR;
        if (length + cur_len + 1 > *n)
        {
            tmp = realloc(*lineptr, length + cur_len + 1);
            if (!tmp)
            {
                free(*lineptr);
                *lineptr = NULL;
                return GETLINE_ERROR;
            }
            *lineptr = tmp;
        }
        my_memcpy(*lineptr + length, cur, cur_len + 1);
        length += cur_len;
        if (cur[cur_len - 1] == '\n')
            flag_read = 0;
    }
    *n = length + 1;
    if (length == 0)
        return GETLINE_ERROR;
    return length;
}
