#include "defines.h"
#include "sort.h"

/**
  Функция присваивает левому элементу значение правого. Присваивание происходит по байтам, размер присваиваемого элемента - size.
  Указатель *left указывает на первый байт левого элемента, *right - на первый байт правого. Каждому байту левого элемента присваивается
  значение соответсвующего байта правого элемента.
 * @brief put_elem
 * @param left [in] - указатель на левый элемент операции присваивания
 * @param right [in] -  указатель на правый элемент операции присваивания
 * @param size [in] - размер элемента в байтах
 */
void put_elem(void *left, void *right, size_t size)
{
    char *p_left = left;
    char *p_right = right;

    for (char *pcur = p_left; pcur < p_left + size; pcur++)
    {
        *pcur = *p_right;
        p_right++;
    }
}

/**
  Функция сравнения двух целых чисел. Возвращает разность значений, на которые указывают подаваемые на вход указатели.
 * @brief cmp
 * @param left [in] - указатель на левый элемент операции сравнения
 * @param right [in] - указатель на правый элемент операции сравнения
 * @return Возвращает целое число. Если оно больше 0, то левый элемент больше правого,
  если 0 - они равны, если больше 0 - левый элемент меньше правого.
 */
int cmp(const void *left, const void *right)
{
    const int *p_left = left;
    const int *p_right = right;
    return *p_left - *p_right;
}

/**
  Функция сравнения двух переменных типа char. Возвращает разность значений, на которые указывают подаваемые на вход указатели.
 * @brief cmp_char
 * @param left [in] - указатель на левый элемент операции сравнения
 * @param right [in] - указатель на правый элемент операции сравнения
 * @return Возвращает целое число. Если оно больше 0, то левый элемент больше правого,
  если 0 - они равны, если больше 0 - левый элемент меньше правого.
 */
int cmp_char(const void *left, const void *right)
{
    const char *p_left = left;
    const char *p_right = right;
    return *p_left - *p_right;
}

/**
  Функция сравнения двух вещественных чисел типа float. Возвращает разность значений, на которые указывают подаваемые на вход указатели.
 * @brief cmp_float
 * @param left [in] - указатель на левый элемент операции сравнения
 * @param right [in] - указатель на правый элемент операции сравнения
 * @return Возвращает целое число. Если оно больше 0, то левый элемент больше правого,
  если 0 - они равны, если больше 0 - левый элемент меньше правого.
 */
int cmp_float(const void *left, const void *right)
{
    const float *p_left = left;
    const float *p_right = right;
    if (fabs(*p_left - *p_right) <= 0.000001)
        return 0;
    else if (*p_left - *p_right < 0.000001)
        return -1;
    else
        return 1;
}

/**
  Функция осуществляет бинарный поиск. *low - указатель на левую границу, *high - на правую. Значение текущего элемента сравнивается со
  значением элемента, стоящего посередине между low и high, и далее (в зависимости от результата) меняется либо правая либо левая граница.
 * @brief binary_search
 * @param low [in] - указатель на элемент, который является левой границей бинарного поиска
 * @param high [in] - указатель на элемент, который является правой границей бинарного поиска
 * @param cur_elem [in] - указатель на текущий элемент, позицию которого необходимо найти
 * @param size [in] - размер одного элемента массива в байтах
 */
char *binary_search(void *p_low, void *p_high, void *p_cur_elem, size_t size, int(*cmp)(const void*, const void*))
{
    char *low = p_low;
    char *high = p_high;
    char *cur_elem = p_cur_elem;
    char *mid = NULL;
    while (low <= high)
    {
        mid = low + size * (((high - low) / 2) / size);
        if (cmp(cur_elem, mid) > 0)
            low = mid + size;
        else
            high = mid - size;
    }
    return low;
}

/**
  Функция сортировки вставками с бинарным поиском, меняет исходный массив таким образом, чтобы он стал упорядоченным по возрастанию.
 * @brief mysort
 * @param base [in] - указатель на начало массива, который необходимо отсортировать
 * @param nmemb [in] - количество элементов этого массива
 * @param size [in] - размер одного элемента массива
 * @param cmp [in] - указатель на функцию сравнения
 */
void mysort(void *base, size_t nmemb, size_t size, int(*cmp)(const void*, const void*))
{
    assert(nmemb >= 0);

    char *low, *high;
    char *begin = base;
    char *end = (char *)base + nmemb * size;
    char *cur_element = malloc(size);
    assert(cur_element);
    for (char *pi = (char *)base + size; pi < end; pi += size)
    {
        if (cmp(pi - size, pi) > 0)
        {
            put_elem(cur_element, pi, size);
            low = begin;
            high = pi;
            low = binary_search(low, high, cur_element, size, cmp);
            for (char *pj = pi; pj > low; pj -= size)
                put_elem(pj, pj - size, size);
            put_elem(low, cur_element, size);
        }
    }
    free(cur_element);
}
