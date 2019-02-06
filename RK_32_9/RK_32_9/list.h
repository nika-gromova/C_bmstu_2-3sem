#ifndef LIST_H
#define LIST_H

#include "my_struct.h"
node_t *create_list(unsigned int number);
void print_list(node_t *head);
void free_list(node_t *head);
node_t *sum(node_t *head_1, node_t *head_2);
unsigned int form_num(node_t *head);
#endif // LIST_H
