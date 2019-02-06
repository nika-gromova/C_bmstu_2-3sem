#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>

int count_n(FILE *f);
int input_array(FILE *f, int *pb, int *pe);
int input(FILE *f, int **pb, int **pe);
void output_array(FILE *f, const int *pb, const int *pe);

#endif // IO_H
