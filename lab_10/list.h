#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

node_t *create_list_elem(data_t *info);
node_t *add_list_elem(node_t *head, node_t *elem);
void free_list(node_t *head);
data_t *create_struct(char *country, char *capital, int year);
int cmp_country(const void *elem1, const void *elem2);
int cmp_capital(const void *elem1, const void *elem2);
int cmp_year(const void *elem1, const void *elem2);
node_t *find(node_t *head, const void *data, int (*comparator)(const void*, const void*));
void insert(node_t **head, node_t *elem, node_t *before);
node_t *create_list(data_t *array_struct[], int n);
node_t *reverse(node_t *head);
void front_back_split(node_t *head, node_t **back);
node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void*, const void*));
node_t *sort(node_t *head, int (*comparator)(const void*, const void*));

#endif // LIST_H
