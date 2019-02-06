#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "defines.h"

#define INIT_SIZE 5

/**
 * @brief The set_d struct Описывает множество как динамически расширяемый массив.
 * data - указатель на массив
 * allocated - количество выделенной памяти
 * cur_len - текущая длина массива
 * step - в столько раз увеличивается память при перевыделении памяти (расширении)
 */
struct set_d
{
    double *data;
    int allocated;
    int cur_len;
    int step;
};

/**
 * @brief init_set_array Функция задает начальные значения множества (расширяемый массив)
 * @param set[in] - указатель на структуру, описывающую расширяемый массив
 */
void init_set_array(set_type set)
{
    if (!set)
        return;
    set->allocated = 0;
    set->data = NULL;
    set->cur_len = 0;
    set->step = 2;
}

/**
 * @brief free_set Функция освобождения памяти из-под множества.
 * @param set[in] - указатель на структуру, описывающую множество
 */
void free_set(set_type set)
{
    if (!set)
        return;
    free(set->data);
    set->allocated = 0;
    set->cur_len = 0;
    set->data = NULL;
    free(set);
}

/**
 * @brief is_in_set_array Функция проверяет, содаржится ли в заданном множестве (массиве) элемент num
 * @param A[in] - указатель на структуру, описывающую массив
 * @param num[in] - число для поиска
 * @return Возвращает 1, если элемент num содержится в множестве А, иначе 0
 */
int is_in_set(set_type A, double num)
{
    for (int i = 0; i < A->cur_len; i++)
    {
        if (IS_EQUAL(A->data[i], num))
            return 1;
    }
    return 0;
}

/**
 * @brief create_set - Функция выделяет память под структуру, описывающую множество (динамически расширяемый массив).
 * @return Возвращает указатель на выделенную область памяти
 */
set_type create_set(void)
{
    set_type s = malloc(sizeof(struct set_d));
    if (s)
        init_set_array(s);
    return s;
}

/**
 * @brief set_add_array Функция добавляет элемент num во множество set
 * @param set[in][out] - указатель на структуру, описывающую массив
 * @param num[in] - элемент, который требуется добавить
 * @return Возвращает NULL_POINTER_ERROR, если передан некорректный указатель на множество, либо MEMORY_ERROR, если не удалось выделить память для нового элемента, либо возвращает OK, если память выделена и элемент добавлен.
 */
int set_add(set_type set, double num)
{
    if (!set)
        return NULL_POINTER_ERROR;
    if (is_in_set(set, num))
        return OK;
    if (set->data == NULL)
    {
        set->data = malloc(INIT_SIZE * sizeof(double));
        if (set->data == NULL)
            return MEMORY_ERROR;
        set->allocated = INIT_SIZE;
    }
    if (set->cur_len + 1 > set->allocated)
    {
        double *tmp = realloc(set->data, set->allocated * set->step * sizeof(double));
        if (tmp == NULL)
        {
            free_set(set);
            return MEMORY_ERROR;
        }
        set->data = tmp;
        set->allocated = set->allocated * set->step;
    }
    set->data[set->cur_len] = num;
    set->cur_len += 1;
    return OK;
}

/**
 * @brief set_delete_element Функция удаляет элемент из множества.
 * @param set[in][out] указатель на структуру, описывающую динамически расширяемый массив
 * @param num[in] - элемент, который необходимо удалить
 * @return Возвращает 1, если элемент был найден и удален, либо 0, если элемента нет во множестве
 */
int set_delete_element(set_type set, double num)
{
    if (!set)
        return NULL_POINTER_ERROR;
    for (int i = 0; i < set->cur_len; i++)
    {
        if (IS_EQUAL(set->data[i], num))
        {
            memmove(set->data + i, set->data + i + 1, (set->cur_len - i - 1) * sizeof(double));
            set->cur_len -= 1;
            return 1;
        }
    }
    return 0;
}

/**
 * @brief set_union Функция объединяет два множества A и B и записывает результирующее множество во множество result
 * В result записываются все элементы, которые есть в множестве A, и/или в множестве B
 * @param A[in] - указатель на структуру, описывающую первое множество
 * @param B[in] - указатель на структуру, описывающую второе множество
 * @param result[in][out] - указатель на структуру, описывающую результирующее множество
 * @return Возвращает NULL_POINTER_ERROR, если переданы некорректные указатели на множества, либо MEMORY_ERROR, если не удалось записать элементы в результирующее множество,
 * либо OK, если множества объединены
 */
int set_union(set_type A, set_type B, set_type result)
{
    if (!A || !B)
        return NULL_POINTER_ERROR;
    int rc = OK;
    for (int i = 0; i < A->cur_len && rc == OK; i++)
    {
        rc = set_add(result, A->data[i]);
    }
    for (int i = 0; i < B->cur_len && rc == OK; i++)
    {
        rc = set_add(result, B->data[i]);
    }
    return rc;
}

/**
 * @brief set_intersection Функция пересекает множество A с множеством B и записывает результирующее множество во множество result
 * В result записываются все элементы, которые есть и в множестве A, и в множестве B
 * @param A[in] - указатель на структуру, описывающую первое множество
 * @param B[in] - указатель на структуру, описывающую второе множество
 * @param result[in][out] - указатель на структуру, описывающую результирующее множество
 * @return Возвращает NULL_POINTER_ERROR, если переданы некорректные указатели на множества, либо MEMORY_ERROR, если не удалось записать элементы в результирующее множество,
 * либо OK, если множества пересечены
 */
int set_intersection(set_type A, set_type B, set_type result)
{
    if (!A || !B)
        return NULL_POINTER_ERROR;
    int rc = OK;
    set_type tmp;
    if (A->cur_len < B->cur_len)
    {
        tmp = A;
        A = B;
        B = tmp;
    }
    for (int i = 0; i < B->cur_len && rc == OK; i++)
    {
        if (is_in_set(A, B->data[i]))
            rc = set_add(result, B->data[i]);
    }
    return rc;
}

/**
 * @brief set_difference Функция разности множеств
 * записывает в результирующее множество result все те элементы, которые содержатся в множестве A и не содержатся в множестве B
 * @param A[in] - указатель на структуру, описывающую первое множество
 * @param B[in] - указатель на структуру, описывающую второе множество
 * @param result[in][out] - указатель на структуру, описывающую результирующее множество
 * @return Возвращает NULL_POINTER_ERROR, если переданы некорректные указатели на множества, либо MEMORY_ERROR, если не удалось записать элементы в результирующее множество,
 * либо OK, если произведена разность множества A и B
 */
int set_difference(set_type A, set_type B, set_type result)
{
    if (!A || !B)
        return NULL_POINTER_ERROR;
    int rc = OK;
    for (int i = 0; i < A->cur_len; i++)
    {
        if (is_in_set(B, A->data[i]) == 0)
            rc = set_add(result, A->data[i]);
    }
    return rc;
}

/**
 * @brief set_sym_difference Функция симметрической разности множеств
 * записывает в результирующее множество result все те элементы, которые содержатся в множестве A и не содержатся в множестве B, или все те, которые содержатся в B и не содержатся в A
 * @param A[in] - указатель на структуру, описывающую первое множество
 * @param B[in] - указатель на структуру, описывающую второе множество
 * @param result[in][out] - указатель на структуру, описывающую результирующее множество
 * @return Возвращает NULL_POINTER_ERROR, если переданы некорректные указатели на множества, либо MEMORY_ERROR, если не удалось записать элементы в результирующее множество,
 * либо OK, если произведена симметрическая разность множества A и B
 */
int set_sym_difference(set_type A, set_type B, set_type result)
{
    if (!A || !B)
        return NULL_POINTER_ERROR;
    int rc = OK;
    set_type tmp1 = create_set();
    set_type tmp2 = create_set();
    if (tmp1)
    {
        if (tmp2)
        {
            rc = set_difference(A, B, tmp1);
            if (rc == OK)
            {
                rc = set_difference(B, A, tmp2);
                if (rc == OK)
                {
                    rc = set_union(tmp1, tmp2, result);
                }
            }
            free_set(tmp2);
        }
        free_set(tmp1);
    }
    return rc;
}

/**
 * @brief cmp_set_array Функция сравнивает массив и множество
 * @param A[in] - указатель на структуру, описывающую множество
 * @param array[in] - указатель на массив
 * @param size[in] - размер массива
 * @return Возвращает NULL_POINTER_ERROR, если переданы некорректные указатели, либо 1, если элементы массива не совпадают с элементами множества, либо 0, если совпадают
 */
int cmp_set_array(set_type A, double *array, int size)
{
    if (!A || !array)
        return NULL_POINTER_ERROR;
    if (A->cur_len != size)
        return 1;
    for (int i = 0; i < A->cur_len; i++)
        if (!is_in_set(A, array[i]))
                return 1;
    return 0;
}
