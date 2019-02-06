#include "arr_lib.h"
#include "defines.h"
#include <stdlib.h>
#include <stdio.h>

/**
  Ищет максимальный элемент массива и его местоположение в самом массиве.
  В цикле сравнивается значение текущего указателя, если оно больше определенного максимального значения,
  то максимальным значением становится значение текущего указателя, а в *max_i записывается текущий указатель.
 * @param pb [in] - указатель на начало массива
 * @param pe [in] - указатель на конец массива
 * @param max_i [in] - указатель на указатель на максимальный элемент массива
 * @return Возвращает POINTER_ERROR, если указатели на начало и/или конец массива не определены, либо EMPTY_ARRAY, если массив пустой
  или указатель на начало массива больше указателя на конец, либо OK, если максимальный элемент найден и указатель на него записан в *max_i.
 */
int find_max(const int *pb, const int *pe, const int **max_i)
{
    if (pb == NULL || pe == NULL)
        return POINTER_ERROR;
    if (pe <= pb)
        return EMPTY_ARRAY;
    *max_i = pb;
    for (int const *pcur = pb + 1; pcur < pe; pcur++)
    {
        if (*pcur > **max_i)
            *max_i = pcur;
    }
    return OK;
}

/**
  Ищет минимальный элемент массива и его местоположение в самом массиве.
  В цикле сравнивается значение текущего указателя, если оно меньше определенного минимального значения,
  то минимальным значением становится значение текущего указателя, а в *min_i записывается текущий указатель.
 * @param pb [in] - указатель на начало массива
 * @param pe [in] - указатель на конец массива
 * @param min_i [in] - указатель на указатель на минимальный элемент массива
 * @return Возвращает POINTER_ERROR, если указатели на начало и/или конец массива не определены, либо EMPTY_ARRAY, если массив пустой
  или указатель на начало массива больше указателя на конец, либо OK, если минимальный элемент найден и указатель на него записан в *min_i.
 */
int find_min(const int *pb, const int *pe, const int **min_i)
{
    if (pb == NULL || pe == NULL)
        return POINTER_ERROR;
    if (pe <= pb)
        return EMPTY_ARRAY;
    *min_i = pb;
    for (int const *pcur = pb + 1; pcur < pe; pcur++)
    {
        if (*pcur < **min_i)
            *min_i = pcur;
    }
    return OK;
}

/**
  Копирует элементы из одного массива(src) в другой(dst). При этом будут скопированы все элементы src, если они поместятся в dst.
 * @param pb_src [in] - указатель на начало массива, из которого копируются данные
 * @param pe_src [in] - указатель на конец массива, из которого копируются данные
 * @param pb_dst [in] - указатель на начало массива, в который копируются данные
 * @param pe_dst [in] - указатель на конец массива, в который копируются данные
 * @return Возвращает OK, если все элементы src скопированы и dst полностью заполнен, либо PARAM_ERROR.
 */
int copy_arr(const int *pb_src, const int *pe_src, int *pb_dst, int *pe_dst)
{
    for (const int *pcur = pb_src; pcur < pe_src; pcur++)
    {
        if (pb_dst < pe_dst)
        {
            *pb_dst = *pcur;
            pb_dst++;
        }
        //else
            //return PARAM_ERROR;
    }
    if (pb_dst == pe_dst)
        return OK;
    else
        return PARAM_ERROR;
}

/**
  Функция фильтрации. Ищет сначала положения максимального и минимального элементов массива,
  затем определяет количество элементов между максимальным и минимальным. Если оно больше нуля, то
  выделяется память под новый массив для этих элементов. В новый массив копируются все элементы между max_i и min_i.
 * @param pb_src [in] - указатель на начало исходного массива, из которого копируются данные
 * @param pe_src [in] - указатель на конец исходного массива, из которого копируются данные
 * @param pb_dst [in] - указатель на начало нового массива, в который копируются данные
 * @param pe_dst [in] - указатель на конец нового массива, в который копируются данные
 * @return Возвращает POINTER_ERROR, если указатели на начало и/или конец массива не определены, либо EMPTY_ARRAY, если массив пустой
  или указатель на начало массива больше указателя на конец или если между максимальным и минимальным элементами нет других элементов,
  либо OK, если удалось скопировать нужные элементы в новый массив.
 */
int key(const int *pb_src, const int *pe_src, int *pb_dst, int *pe_dst, const int *max_i, const int *min_i)
{
    int rc = OK;
    if (pb_src == NULL || pe_src == NULL)
        return POINTER_ERROR;
    if (pe_src <= pb_src)
        return EMPTY_ARRAY;
    if (pb_dst == NULL || pe_dst == NULL)
        return POINTER_ERROR;
    if (min_i > max_i)
    {
        const int *tmp = min_i;
        min_i = max_i;
        max_i = tmp;
    }
    rc = copy_arr(min_i + 1, max_i, pb_dst, pe_dst);
    return rc;
}
