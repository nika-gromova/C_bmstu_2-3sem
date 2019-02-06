#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>

int read_matrix(const char *file_name, double ***matrix, int *n, int *m);
void print_matrix(double **matrix, int n, int m);
int save_matrix(char *file_name, double **matrix, int n, int m);

#endif // IO_H
