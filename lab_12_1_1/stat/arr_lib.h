#ifndef ARR_LIB_H
#define ARR_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int count_n(FILE *f);
int input_array(FILE *f, int *pb, int *pe);
int input(FILE *f, int **pb, int **pe);
void output_array(FILE *f, const int *pb, const int *pe);
int find_max(const int *pb, const int *pe, const int **max_i);
int find_min(const int *pb, const int *pe, const int **min_i);
int copy_arr(const int *pb_src, const int *pe_src, int *pb_dst, int *pe_dst);
int key(const int *pb_src, const int *pe_src, int *pb_dst, int *pe_dst, const int *max_i, const int *min_i);
void put_elem(void *left, void *right, size_t size);
int cmp(const void *left, const void *right);
int cmp_float(const void *left, const void *right);
int cmp_char(const void *left, const void *right);
char *binary_search(void *p_low, void *p_high, void *p_cur_elem, size_t size, int(*cmp)(const void*, const void*));
void mysort(void *base, size_t nmemb, size_t size, int(*cmp)(const void*, const void*));

#endif // ARR_LIB_H
