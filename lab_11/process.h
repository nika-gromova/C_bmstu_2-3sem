#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

#define OK 0
#define SN_ERROR -10
#define MAX_NUM_LEN 30

size_t my_strlen(const char *str);
char *my_memcpy(char *dst, const char *src, size_t bytes);
void my_itoa(unsigned long long int num, char *res, int system);
int my_snprintf(char *buf, size_t n, const char *format, ...);

#endif // PROCESS_H
