#include <stdlib.h>
#include <stdio.h>
#include "my_struct.h"
#include "list.h"

void free_list(node_t *head)
{
    node_t *tmp = head;
    while (head)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}

node_t *create_node(int value)
{
    node_t *out = malloc(sizeof(node_t));
    if (out)
    {
        out->n = value;
        out->next = NULL;
        return out;
    }
    return NULL;
}

node_t *push_back(node_t *head, node_t *elem)
{
    if (head == NULL)
    {
        return elem;
    }
    node_t *tmp = head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = elem;
    return head;
}

node_t *create_list(unsigned int number)
{
    node_t *cur = NULL, *head = NULL;
    int tmp = number % 10;
    if (number / 10 == 0)
    {
        cur = create_node(tmp);
        return cur;
    }
    while (number / 10 != 0)
    {
        cur = create_node(tmp);
        if (!cur)
        {
            free_list(head);
            return NULL;
        }
        head = push_back(head, cur);
        number /= 10;
        tmp = number % 10;
    }
    cur = create_node(tmp);
    if (!cur)
    {
        free_list(head);
        return NULL;
    }
    head = push_back(head, cur);
    return head;
}

int len_num(node_t *head)
{
    int count = 0;
    for (; head; head = head->next, count++)
        ;
    return count;
}

node_t *sum(node_t *head_1, node_t *head_2)
{
    node_t *buf = NULL, *cur = NULL;
    int ost = 0;
    int count_1 = len_num(head_1);
    int count_2 = len_num(head_2);
    if (count_1 < count_2)
    {
        buf = head_1;
        head_1 = head_2;
        head_2 = buf;
    }
    node_t *tmp_1 = head_1, *tmp_2 = head_2;
    while (tmp_1)
    {
        if (tmp_2 != NULL)
            tmp_1->n += tmp_2->n;
        if (tmp_1->next != NULL)
            tmp_1->next->n += (tmp_1->n / 10);
        else
            ost = (tmp_1->n / 10);
        tmp_1->n %= 10;
        tmp_1 = tmp_1->next;
        if (tmp_2 != NULL)
            tmp_2 = tmp_2->next;
    }
    if (ost != 0)
    {
        cur = create_list(ost);
        if (cur)
        {
            head_1 = push_back(head_1, cur);
        }
        else
            return NULL;
    }
    return head_1;
}

void print_list(node_t *head)
{
    while (head)
    {
        printf("%d", head->n);
        head = head->next;
    }
    printf(" ");
}

unsigned int form_num(node_t *head)
{
    int tmp = 0;
    int n = 1;
    while (head)
    {
        tmp += n * head->n;
        n *= 10;
        head = head->next;
    }
    return tmp;
}
