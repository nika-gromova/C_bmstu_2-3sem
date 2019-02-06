#include <string.h>
#include <limits.h>

#include "process.h"

/**
 * @brief my_strlen Функция вычисляет длину строки str, не считая символ конца строки '\0'.
 * @param str [in] - указатель на строку.
 * @return Возвращает count - длину строки.
 */
size_t my_strlen(const char *str)
{
    if (str == NULL)
        return 0;
    size_t n;
    const char *tmp = str;
    for (n = 0; (*tmp) != '\0'; n++, tmp++);
    return n;
}

/**
 * @brief my_memcpy Функция копирует bytes байтв из src в dst.
 * @param dst [in][out] - указатель на адрес памяти, куда будет производиться копирование.
 * @param src [in] - указатель на адрес памяти, откуда будет производится копирование.
 * @param bytes [in] - количество байт, которое необходимо скопировать.
 * @return Возвращает NULL, если функции переданы невалидные указатели, или dst - указатель на область памяти, куда скопировалась информация.
 */
char *my_memcpy(char *dst, const char *src, size_t bytes)
{
    if (dst == NULL || src == NULL)
    {
        return NULL;
    }
    char *p_dst = dst;
    const char *p_src = src;
    size_t i = 0;
    while (i < bytes)
    {
        *p_dst = *p_src;
        p_src++;
        p_dst++;
        i++;
    }
    return dst;
}

/**
 * @brief move_to_beg Функция перемещает информацию, рамещеннную с конца массива в начало массива, не меняя при этом последовательность элемнетов.
 * @param s1 [in][out] - результирующий массив
 * @param s2 [in] - исходный массив
 * @param pos [in] - позиция (индекс), с которого начинается информация в исходном массиве.
 */
void move_to_beg(char *s1, char *s2, int pos)
{
    int end = pos;
    for (int j = 0; j < MAX_NUM_LEN - end; j++, pos++)
        s1[j] = s2[pos];
}

/**
 * @brief my_itoa Функция переводит число num в заданной системе счисления system в строку и записывает её в res.
 * @param num [in] - число, которое необходимо конвертировать в строку
 * @param res [in][out] - результирующий массив символов = резульлтирующая строка
 * @param system [in] - система счисления
 */
void my_itoa(unsigned long long int num, char *res, int system)
{
    int residue = 0;
    char tmp[MAX_NUM_LEN + 1];
    int i = MAX_NUM_LEN - 1;
    char flag_del = 1;
    while (flag_del)
    {
        residue = num % system;
        tmp[i] = residue + '0';
        num /= system;
        if (num == 0)
            flag_del = 0;
        else
            i--;
    }
    move_to_beg(res, tmp, i);
    res[MAX_NUM_LEN - i] = '\0';
}

/**
 * @brief my_snprintf Функция записывает в соответствии с управляющей строкой format аргументы, следующие после указания format, в массив символов buf.
 * @param buf [in][out] - результирующий массив символов
 * @param n [in] - размер buf
 * @param format [in] - управляющая строка (сторока форматирования)
 * @return Возвращает SN_ERROR (-10), если размер результирующего массива нулевой, либо если управляющая строка пуста, либо если суммарнное количество
 * символов, которых необходимо записать в результате, превышает размер результирующего массива, либо если не удалось скопировать необходимые символы
 * в результирующий массив, либо в управляющей строке встречаются спецификаторы, отличные от %s %llo %i, иначе возвращает количество записанных в
 * результирующий массив символов, не считая символа конца строки '\0'.
 */
int my_snprintf(char *buf, size_t n, const char *format, ...)
{
    char *str;
    unsigned long long int oct_num;
    char res_oct[MAX_NUM_LEN + 1];
    int int_num;
    long int tmp;
    char res_int[MAX_NUM_LEN + 1];
    int rc = OK;
    int flag_write = 1;
    int negative = 0;

    //if (buf != NULL && n == 0)
        //return SN_ERROR;
    if (buf == NULL && n != 0)
        return SN_ERROR;
    if (n == 0)
        flag_write = 0;

    size_t format_len = my_strlen(format);
    if (format_len == 0)
        return SN_ERROR;
    size_t str_len = 0;
    size_t count = 0;
    va_list argptr;
    va_start(argptr, format);
    //printf("here0, flag = %d\n", flag_write);
    for (int i = 0; i < format_len && rc == OK; i++)
    {
        if (format[i] != '%')
        {
            if (flag_write == 1)
            {
                buf[count] = format[i];
            }
            count++;
        }
        else
        {
            if (strncmp(format + i + 1, "s", 1) == 0)
            {
                i += 1;
                str = va_arg(argptr, char *);
                str_len = my_strlen(str);
                if (flag_write == 1)
                {
                    if (str_len + 1 + count <= n)
                    {
                        if (!my_memcpy(buf + count, str, str_len))
                        {
                            rc = SN_ERROR;
                        }
                    }
                    else
                    {
                        my_memcpy(buf + count, str, str_len + 1 + count - n);
                        str_len = n;
                        rc = SN_ERROR;
                    }
                }
            }
            else if (strncmp(format + i + 1, "llo", 3) == 0)
            {
                i += 3;
                oct_num = va_arg(argptr, unsigned long long int);
                //printf("***%I64u***\n", oct_num);
                my_itoa(oct_num, res_oct, 8);
                str_len = my_strlen(res_oct);
                if (flag_write == 1)
                {
                    if (str_len + 1 + count <= n)
                    {
                        if (!my_memcpy(buf + count, res_oct, str_len))
                            rc = SN_ERROR;
                    }
                    else
                    {
                        my_memcpy(buf + count, res_oct, str_len + 1 + count - n);
                        str_len = n;
                        rc = SN_ERROR;
                    }
                }
                else
                {
                    rc = SN_ERROR;
                }
            }
            else if (strncmp(format + i + 1, "i", 1) == 0)
            {
                i += 1;
                int_num = va_arg(argptr, int);
                tmp = int_num;
                if (tmp < 0)
                {
                    tmp = 0 - tmp;
                    negative = 1;
                }
                my_itoa(tmp, res_int, 10);
                str_len = my_strlen(res_int);
                if (negative)
                {
                    for (int i = str_len; i > -1; i--)
                        res_int[i + 1] = res_int[i];
                    res_int[0] = '-';
                    str_len++;
                }

                if (flag_write == 1)
                {
                    if (str_len + 1 + count <= n)
                    {
                        if (!my_memcpy(buf + count, res_int, str_len))
                            rc = SN_ERROR;
                    }
                    else
                    {
                        my_memcpy(buf + count, res_int, str_len + 1 + count - n);
                        str_len = n;
                        rc = SN_ERROR;
                    }
                }
            }
            else
                rc = SN_ERROR;
            count += str_len;
        }
    }
    if (rc == SN_ERROR)
    {
        va_end(argptr);
        return SN_ERROR;
    }
    if (flag_write == 1)
        buf[count] = '\0';
    va_end(argptr);
    return count;
}
