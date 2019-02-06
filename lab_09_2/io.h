#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

ssize_t my_getline(char **lineptr, size_t *n, FILE *f);

#endif // IO_H
