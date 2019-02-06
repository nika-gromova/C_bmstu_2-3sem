#ifndef ARRAY_LIB_H
#define ARRAY_LIB_H

#ifdef ARRAY_EXPORTS
#define ARRAY_DLL __declspec(dllexport)
#else
#define ARRAY_DLL __declspec(dllimport)
#endif

#define ARRAY_DECL __cdecl

ARRAY_DLL int ARRAY_DECL fill_fib(unsigned long int *arr, int m);
ARRAY_DLL int ARRAY_DECL first_occurrence(double *src, int n_src, double *dst, int *n_dst);

#endif // ARRAY_LIB_H
