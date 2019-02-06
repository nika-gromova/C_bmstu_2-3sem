#ifndef PROCESS_H
#define PROCESS_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structure.h"

int count_words(char *str);
int sep(char *str, char **p_words);
//int add_word(char *word, char ***list_of_words, int *allocated, int *word_count);
//void free_str_array(char **str_array, int n);
int add_unique_word(char *word, struct list_elem **head, int *word_count);
void free_list(struct list_elem *head);
#endif // PROCESS_H
