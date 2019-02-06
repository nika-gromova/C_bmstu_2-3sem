#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

int count_line(char *file_name);
int read_file(char *file_name, data_t *struct_array[], int count);
int read_data(FILE *f, data_t **cur);
int save_list(char *file_name, node_t *head);
int save_elem(char *file_name, node_t *head);

#endif // IO_H
