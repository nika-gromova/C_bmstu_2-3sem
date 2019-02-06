#include <stdlib.h>
#include <stdio.h>
#include "set.h"
#include "defines.h"

/**
  * Элемент списка
  * num - информационное поле, содержит число - элемент множества
  * next - ссылочное поле - указатель на следующий элемент списка
  */
typedef struct node
{
    double num;
    struct node *next;
} set_node;

/**
 * Дескриптор списка, содержит указатель на начало списка
 */
struct set_d
{
    set_node *head;
};

/**
 * @brief free_list Функция освобождения списка
 * @param head[in] - указателб на начало списка
 */
void free_list(set_node *head)
{
    set_node *cur = head;
    while (head)
    {
        cur = head->next;
        free(head);
        head = cur;
    }
}

/**
 * @brief free_set Функция освобождения памяти из-под множества.
 * @param set[in] - указатель на структуру, описывающую множество
 */
void free_set(set_type set)
{
    free_list(set->head);
    free(set);
}

/**
 * @brief create_set - Функция выделяет память под структуру, описывающую множество (дескриптор списка).
 * @return Возвращает указатель на выделенную область памяти
 */
set_type create_set(void)
{
    set_type s = malloc(sizeof(struct set_d));
    if (s)
        s->head = NULL;
    return s;
}

/**
 * @brief create_set_list_node Функция создает элемент списка, выделяя память под него
 * @param num[in] - данные, которые будут храниться в элементе списка
 * @return Возвращает указатель на выделенную память, или NULL, если память не выделилась
 */
set_node *create_set_list_node(double num)
{
    set_node *in = malloc(sizeof(set_node));
    if (in)
    {
        in->num = num;
        in->next = NULL;
    }
    return in;
}

/**
 * @brief is_in_set_list Функция проверяет, содаржится ли в заданном множестве (списке) элемент num
 * @param A[in] - указатель на структуру, описывающую список
 * @param num[in] - число для поиска
 * @return Возвращает 1, если элемент num содержится в списке, иначе 0
 */
int is_in_set(set_type A, double num)
{
    set_node *head = A->head;
    while (head)
    {
        if (IS_EQUAL(head->num, num))
            return 1;
        head = head->next;
    }
    return 0;
}

/**
 * @brief set_add_array Функция добавляет элемент num во множество set
 * @param set[in][out] - указатель на структуру, описывающую список
 * @param num[in] - элемент, который требуется добавить
 * @return Возвращает NULL_POINTER_ERROR, если передан некорректный указатель на множество, либо MEMORY_ERROR, если не удалось выделить память для нового элемента, либо возвращает OK, если память выделена и элемент добавлен.
 */
int set_add(set_type set, double num)
{
    if (!set)
        return NULL_POINTER_ERROR;
    if (is_in_set(set, num))
        return OK;
    set_node *in = create_set_list_node(num);
    set_node *tmp = set->head;
    if (in)
    {
        if (set->head == NULL)
            set->head = in;
        else
        {
            for (; tmp->next; tmp = tmp->next)
                ;
            tmp->next = in;
        }
        return OK;
    }
    return MEMORY_ERROR;
}

/**
 * @brief set_delete_element Функция удаляет элемент из множества.
 * @param set[in][out] указатель на структуру, описывающую список
 * @param num[in] - элемент, который необходимо удалить
 * @return Возвращает 1, если элемент был найден и удален, либо 0, если элемента нет во множестве
 */
int set_delete_element(set_type set, double num)
{
    if (!set)
        return NULL_POINTER_ERROR;
    set_node *prev = NULL;
    set_node *cur = set->head;
    while (cur)
    {
        if (IS_EQUAL(cur->num, num))
        {
            if (prev)
                prev->next = cur->next;
            else
                set->head = cur->next;
            free(cur);
            return 1;
        }
        prev = cur;
        cur = cur->next;
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
    set_node *head_A = A->head;
    set_node *head_B = B->head;
    while (head_A && rc == OK)
    {
        rc = set_add(result, head_A->num);
        if (rc != OK)
            free_list(result->head);
        head_A = head_A->next;
    }
    while (head_B && rc == OK)
    {
        rc = set_add(result, head_B->num);
        if (rc != OK)
            free_list(result->head);
        head_B = head_B->next;
    }
    return rc;
}

/**
 * @brief count_list Функция подсчитывает количество элементов в списке
 * @param head[in] - указатель на начало списка
 * @return Возвращает количество элементов в списке
 */
int count_list(set_node *head)
{
    int count = 0;
    for (; head; head = head->next, count++)
        ;
    return count;
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
    set_node *tmp = NULL;
    set_node *head_A = A->head;
    set_node *head_B = B->head;
    set_type big = A;
    int rc = OK;
    if (count_list(head_A) < count_list(head_B))
    {
        tmp = head_A;
        head_A = head_B;
        head_B = tmp;
        big = B;
    }
    while (head_B && rc == OK)
    {
        if (is_in_set(big, head_B->num))
        {
            rc = set_add(result, head_B->num);
            if (rc != OK)
                free_list(result->head);
        }
        head_B = head_B->next;
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
    set_node *head_A = A->head;
    int rc = OK;
    while (head_A && rc == OK)
    {
        if (is_in_set(B, head_A->num) == 0)
        {
            rc = set_add(result, head_A->num);
            if (rc != OK)
                free_list(result->head);
        }
        head_A = head_A->next;
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
    set_type tmp_1;
    set_type tmp_2;
    tmp_1 = create_set();
    if (tmp_1)
    {
        tmp_2 = create_set();
        if (tmp_2)
        {
            rc = set_difference(A, B, tmp_1);
            if (rc == OK)
            {
                rc = set_difference(B, A, tmp_2);
                if (rc == OK)
                {
                    rc = set_union(tmp_1, tmp_2, result);
                }
            }
            free_set(tmp_2);
        }
        free_set(tmp_1);
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
    if (!A)
        return NULL_POINTER_ERROR;
    set_node *head_A = A->head;
    int n_1 = count_list(head_A);
    if (n_1 != size)
        return 1;
    for (int i = 0; i < size; i++)
        if (!is_in_set(A, array[i]))
            return 1;
    return 0;
}
