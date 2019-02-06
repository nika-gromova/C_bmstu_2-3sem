#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <assert.h>

void put_elem(void *left, void *right, size_t size);
int cmp(const void *left, const void *right);
char *binary_search(char *low, char *high, char *cur_elem, size_t size, int(*cmp)(const void*, const void*));
void mysort(void *base, size_t nmemb, size_t size, int(*cmp)(const void*, const void*));

#endif // SORT_H
