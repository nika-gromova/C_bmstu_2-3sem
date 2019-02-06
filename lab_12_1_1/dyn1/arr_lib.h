#ifndef ARR_LIB_H
#define ARR_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#ifdef EXPORT
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)
#endif

#define ARR_DECL __cdecl

ARR_DLL int ARR_DECL count_n(FILE *f);
ARR_DLL int ARR_DECL input_array(FILE *f, int *pb, int *pe);
ARR_DLL int ARR_DECL input(FILE *f, int **pb, int **pe);
ARR_DLL void ARR_DECL output_array(FILE *f, const int *pb, const int *pe);
ARR_DLL int ARR_DECL find_max(const int *pb, const int *pe, const int **max_i);
ARR_DLL int ARR_DECL find_min(const int *pb, const int *pe, const int **min_i);
ARR_DLL int ARR_DECL copy_arr(const int *pb_src, const int *pe_src, int *pb_dst, int *pe_dst);
ARR_DLL int ARR_DECL key(const int *pb_src, const int *pe_src, int *pb_dst, int *pe_dst, const int *max_i, const int *min_i);
ARR_DLL void ARR_DECL put_elem(void *left, void *right, size_t size);
ARR_DLL int ARR_DECL cmp(const void *left, const void *right);
ARR_DLL int ARR_DECL cmp_float(const void *left, const void *right);
ARR_DLL int ARR_DECL cmp_char(const void *left, const void *right);
ARR_DLL char ARR_DECL *binary_search(void *p_low, void *p_high, void *p_cur_elem, size_t size, int(*cmp)(const void*, const void*));
ARR_DLL void ARR_DECL mysort(void *base, size_t nmemb, size_t size, int(*cmp)(const void*, const void*));

#endif // ARR_LIB_H
