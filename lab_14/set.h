#ifndef SET_ARRAY_H
#define SET_ARRAY_H

typedef struct set_d *set_type;

set_type create_set(void);
void free_set(set_type set);
int set_add(set_type set, double num);
int set_delete_element(set_type set, double num);
int set_union(set_type A, set_type B, set_type result);
int set_intersection(set_type A, set_type B, set_type result);
int set_difference(set_type A, set_type B, set_type result);
int set_sym_difference(set_type A, set_type B, set_type result);
int is_in_set(set_type A, double num);
// Тестирование
int cmp_set_array(set_type A, double *array, int size);

#endif // SET_ARRAY_H
