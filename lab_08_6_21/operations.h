#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdio.h>

int sum_matrix(double **matrix_1, int n_1, int m_1, double **matrix_2, int n_2, int m_2, double ***result, int *n_3, int *m_3);
int mult_matrix(double **matrix_1, int n_1, int m_1, double **matrix_2, int n_2, int m_2, double ***result, int *n_3, int *m_3);
int operations(char *file_src, double **matrix_1, int n_1, int m_1, double ***matrix_2, int *n_2, int *m_2, double ***result, int *n_3, int *m_3, int(*operation)(double **, int, int, double **, int, int, double ***, int *, int *));

#endif // OPERATIONS_H
