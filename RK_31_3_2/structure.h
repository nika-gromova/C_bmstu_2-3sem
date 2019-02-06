#ifndef STRUCTURE_H
#define STRUCTURE_H

#define MAX_WORD_LEN 20 // максимальная допустимая длина слова

struct list_elem
{
    char word[MAX_WORD_LEN + 1];
    struct list_elem *next;
};

#endif // STRUCTURE_H
