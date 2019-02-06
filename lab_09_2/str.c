#include "str.h"

/**
 * @brief len Функуия определяет длину строки (не учитывая терминирующий ноль).
 * @param str [in] - указатель на строку
 * @return n - количество символов в строке.
 */
size_t len(const char *str)
{
    if (str == NULL)
        return 0;
    size_t n;
    const char *tmp = str;
    for (n = 0; (*tmp) != '\0'; n++, tmp++);
    return n;
}

/**
 * @brief str_cmp Функция сравнивает две строки.
 * @param str1 [in] - указатель на первую для сравнения строку
 * @param str2 [in] - указатель на вторую для сравнения строку
 * @return Возвращает 0, если строки равны, либо -1, если строки не равны.
 */
int str_cmp(const char *str1, const char *str2)
{
    if (str1 == NULL)
    {
        if (str2 == NULL)
            return 0;
        else
            return -1;
    }
    if (str2 == NULL)
        return -1;

    for (int i = 0; str1[i] == str2[i]; i++)
        if (str1[i] == '\0')
            return 0;
    return -1;
}

/**
 * @brief my_memcpy Функция копирует bytes байтов памяти из src в dst.
 * @param dst [in] - указатель на адрес памяти, куда будет производиться копирование
 * @param src [in] - указатель на адрес памяти, откуда будет производиться копирование
 * @param bytes [in] - количество байтов для копирования
 * @return Возвращает dst - указатель на область памяти, куда скопировалась информация, либо NULL, если указатели на dst и src нулевые.
 */
void *my_memcpy(void *dst, const void *src, size_t bytes)
{
    if (dst == NULL)
        return NULL;
    if (src == NULL)
        return dst;
    char *char_dst = (char *)dst;
    const char *char_src = (const char *)src;
    size_t i = 0;
    while (i < bytes)
    {
        *char_dst = *char_src;
        char_dst++;
        char_src++;
        i++;
    }
    return dst;
}
