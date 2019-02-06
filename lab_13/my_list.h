#ifndef MY_LIST_H
#define MY_LIST_H

#include "my_struct.h"
node_car *create_list_elem(void);
node_car *push_back(node_car *head, node_car *elem);
void add_element_to_berkeley(heads_index_filter *heads, node_car *elemnt);
void add_lo_list(heads_index_filter *heads_berkeley, node_car *cur, node_car **head);
void delete_list(node_car *head);
void delete_berkeley(node_car *cur);
node_car *delete_element(node_car *head, int index, int *rc);
node_car *find_element(node_car *head, int index);

#endif // MY_LIST_H
