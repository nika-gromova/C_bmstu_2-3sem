#ifndef REVERSE_H
#define REVERSE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//void swap_str(double *p1, double *p2, int m);
void swap_str(double **matrix, int i1, int i2);
void less_matrix(double **matrix, double **new_matrix, int p_i, int p_j, int n, int new_n);
double find_determinant(double **matrix, int n);
void solve(double **matrix, double **unit_matrix, double **result, int n);
int triangular_matrix(double **matrix, double **reversed, int n, int m);
int reverse(double **matrix, int n, int m, double ***result, int *res_n, int *res_m);
void transposition(double **matrix, int n, int m);
#endif // REVERSE_H
