#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <assert.h>
#include <math.h>

void put_elem(void *left, void *right, size_t size);
int cmp(const void *left, const void *right);
int cmp_float(const void *left, const void *right);
int cmp_char(const void *left, const void *right);
char *binary_search(void *p_low, void *p_high, void *p_cur_elem, size_t size, int(*cmp)(const void*, const void*));
void mysort(void *base, size_t nmemb, size_t size, int(*cmp)(const void*, const void*));

#endif // SORT_H
