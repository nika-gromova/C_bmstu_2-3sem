#include <string.h>
#include <stdlib.h>
#include "my_struct.h"
#include "my_list.h"
#include "defines.h"
#include "list.h"

/**
 * @brief delete_list Функция освобождает память из под односвящного линейного списка
 * @param head[in] - указатель на голову списка
 */
void delete_list(node_car *head)
{
    node_car *tmp;
    while (head)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}

/**
 * @brief push_back Функция добавляет элемент в конец односвязного линейного списка
 * @param head[in] - указатель на голову списка
 * @param elem[in] - указатель на структуру, содержащую элемент списка
 * @return Возвращает указатель на новую голову списка
 */
node_car *push_back(node_car *head, node_car *elem)
{
    node_car *cur = head;
    if (!head)
    {
        elem->id = 1;
        return elem;
    }
    for (; cur->next; cur = cur->next)
        ;
    elem->id = cur->id + 1;
    cur->next = elem;
    return head;
}

/**
 * @brief cmp_model Функция сравнения элементов списка по названию марки (в лексикографическом порядке)
 * @param elem1[in] - указатель на структуру, содержащую один элемент списка
 * @param elem2[in] - указатель на структуру, содержащую второй элемент списка
 * @return Возвращает 0, если элементы равны, 1, если первый элемент больше второго, иначе возвращает -1
 */
int cmp_model(node_car *elem1, node_car *elem2)
{
    return strcmp(elem1->model, elem2->model);
}

/**
 * @brief cmp_price Функция сравнения элементов списка по цене
 * @param elem1[in] - указатель на структуру, содержащую один элемент списка
 * @param elem2[in] - указатель на структуру, содержащую второй элемент списка
 * @return Возвращает 0, если элементы равны, 1, если первый элемент больше второго, иначе возвращает -1
 */
int cmp_price(node_car *elem1, node_car *elem2)
{
    if (IS_EQUAL(elem1->price, elem2->price))
        return 0;
    if (elem1->price > elem2->price)
        return 1;
    return -1;
}

/**
 * @brief cmp_price_and_guarantee Функция сравнения элементов по цене и сроку гарантии
 * Если цена одинаковая, то сравнивается срок гарантии
 * @param elem1[in] - указатель на структуру, содержащую один элемент списка
 * @param elem2[in] - указатель на структуру, содержащую второй элемент списка
 * @return Возвращает 0, если элементы равны, 1, если первый элемент больше второго, иначе возвращает -1
 */
int cmp_price_and_guarantee(node_car *elem1, node_car *elem2)
{
    if (IS_EQUAL(elem1->price, elem2->price))
    {
        if (elem1->year == elem2->year)
            return 0;
        if (elem1->year > elem2->year)
            return 1;
        return -1;
    }
    if (elem1->price > elem2->price)
        return 1;
    return -1;
}

/**
 * @brief insert_sorted Функция помещает элемент в выстроенный по возрастанию (отсортированный) список Беркли
 * @param head[in][out] - указатель на голову списка Беркли
 * @param elem[in] - элемент односвязного списка, который необходимо добавить
 * @param cmp[in] - функция сравнения
 * @param index[in] - индекс массива списка Беркли
 */
void insert_sorted(struct list_head *head, node_car *elem, int(*cmp)(node_car*, node_car*), int index)
{
    struct list_head *inserting = &(elem->sort[index]);
    struct list_head *tmp;
    node_car *data;
    list_for_each(tmp, head)
    {
        data = list_entry(tmp, node_car, sort[index]);
        if (cmp(data, elem) == 1)
        {
            list_add_tail(inserting, tmp);
            return;
        }
    }
    list_add_tail(inserting, head);
}

/**
 * @brief add_element_to_berkeley Функция добавляет элемент односвязного линейного списка во все необходимые списки Беркли
 * @param heads[in][out] - указатель на структуру, содержащую головы списков Беркли
 * @param elemnt[in] - указатель на элемент, который необходимо добавить
 */
void add_element_to_berkeley(heads_index_filter *heads, node_car *elemnt)
{
    if (strcmp(elemnt->country, "Germany") == 0)
    {
        list_add_tail(&(elemnt->filter[0]), &(heads->filter_country));
    }
    if (elemnt->year >= 4)
    {
        list_add_tail(&(elemnt->filter[1]), &(heads->filter_guarantee));
    }
    insert_sorted(&(heads->sort_model), elemnt, cmp_model, 0);
    insert_sorted(&(heads->sort_price), elemnt, cmp_price, 1);
    insert_sorted(&(heads->sort_price_and_guarantee), elemnt, cmp_price_and_guarantee, 2);
}

/**
 * @brief init_element Функция инициализирует поля структуры, содержащей элемент односвязного линейного списка
 * @param cur[in][out] - указатель на элемент, который необходимо инициализировать
 */
void init_element(node_car *cur)
{
    INIT_LIST_HEAD(&(cur->filter[0]));
    INIT_LIST_HEAD(&(cur->filter[1]));
    INIT_LIST_HEAD(&(cur->sort[0]));
    INIT_LIST_HEAD(&(cur->sort[1]));
    INIT_LIST_HEAD(&(cur->sort[2]));
    cur->next = NULL;
}

/**
 * @brief create_list_elem Функция выделяет память под элемент односвязного линейного списка
 * @return Возвращает указатель на выделенную область памяти
 */
node_car *create_list_elem(void)
{
    node_car *in = malloc(sizeof(node_car));
    if (in)
        init_element(in);
    return in;
}

/**
 * @brief add_lo_list Функция добавления элемента в односвязный линейный список и в списки Беркли
 * @param heads_berkeley[in][out] - указатель на структуру, содержащую головы списков Беркли
 * @param cur[in] - указатель на добавляемый элемент
 * @param head[in][out] - указатель на голову односвязного линейного списка
 */
void add_lo_list(heads_index_filter *heads_berkeley, node_car *cur, node_car **head)
{
    *head = push_back(*head, cur);
    add_element_to_berkeley(heads_berkeley, cur);
}

/**
 * @brief delete_berkeley Функция удаления элемента из списков Беркли
 * @param cur[in] - элемент списка, который нужно удалить из списков Беркли
 */
void delete_berkeley(node_car *cur)
{
    list_del(&(cur->filter[0]));
    list_del(&(cur->filter[1]));
    list_del(&(cur->sort[0]));
    list_del(&(cur->sort[1]));
    list_del(&(cur->sort[2]));
}

/**
 * @brief delete_element Функция удаления элемента из односвязного линейного списка и из списка Беркли
 * @param head[in] - указатель на голову односвязного линейного списка
 * @param index[in] - номер (id) того элемента, который нужно удалить
 * @param rc[out] - код возврата (0 - список пуст, 1 - элемент найден и удален, 2 - элемент не найден)
 * @return Возвращает указатель на новую голову списка
 */
node_car *delete_element(node_car *head, int index, int *rc)
{
    *rc = 0;
    if (!head)
        return NULL;
    node_car *prev = NULL, *cur = head;
    while (cur)
    {
        if (cur->id == index)
        {
            if (prev)
            {
                prev->next = cur->next;
            }
            else
            {
                head = cur->next;
            }
            delete_berkeley(cur);
            free(cur);
            *rc = 1;
            return head;
        }
        prev = cur;
        cur = cur->next;
    }
    *rc = 2;
    return head;
}

/**
 * @brief find_element Функция поиска элемента в односвязном линейном списке
 * @param head[in] - указатель на голову списка
 * @param index[in] - номер(id) элемента, который необходимо найти
 * @return Возвращает указатель на стркутуру, содержащую найденный элемент, или NULL, если элемент не найден
 */
node_car *find_element(node_car *head, int index)
{
    while (head)
    {
        if (head->id == index)
            return head;
        head = head->next;
    }
    return NULL;
}
