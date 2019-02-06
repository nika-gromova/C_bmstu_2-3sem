#ifndef STR_H
#define STR_H

#include <stdio.h>

size_t len(const char *str);
int str_cmp(const char *str1, const char *str2);
void *my_memcpy(void *dst, const void *src, size_t bytes);

#endif // STR_H
