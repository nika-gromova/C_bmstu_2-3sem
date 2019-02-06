#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "process.h"
#include "structure.h"

void test_count_words(void)
{
    printf("Tests for count_words():\n");
    {
        char *str = "";
        int count = count_words(str);
        printf("Correct work with empty string: %s\n", (count == 0) ? "YES" : "NO");
    }
    {
        char *str = "a";
        int count = count_words(str);
        printf("Correct work with 1-word string: %s\n", (count == 1) ? "YES" : "NO");
    }
    {
        char *str = " a  ";
        int count = count_words(str);
        printf("Correct work with 1-word string: %s\n", (count == 1) ? "YES" : "NO");
    }
    {
        char *str = "a a";
        int count = count_words(str);
        printf("Correct work with 2-word string: %s\n", (count == 2) ? "YES" : "NO");
    }
    {
        char *str = " a   a ";
        int count = count_words(str);
        printf("Correct work with 2-word string: %s\n", (count == 2) ? "YES" : "NO");
    }
    {
        char *str = "a a a";
        int count = count_words(str);
        printf("Correct work with 3-word string: %s\n", (count == 3) ? "YES" : "NO");
    }
    {
        char *str = " a   a f";
        int count = count_words(str);
        printf("Correct work with 3-word string: %s\n\n", (count == 3) ? "YES" : "NO");
    }
}

void test_sep(void)
{
    printf("Tests for sep():\n");
    {
        char *str = "";
        char **p_words = NULL;
        int count = sep(str, p_words);
        printf("Correct work with empty string: %s\n", (count == 0 && p_words == NULL) ? "YES" : "NO");
    }
    {
        char *str = "a";
        char **p_words = malloc(sizeof(char *));
        int count = sep(str, p_words);
        printf("Correct work with empty string: %s\n", (count == 1 && strcmp(p_words[0], "a") == 0) ? "YES" : "NO");
        free(p_words);
    }
    {
        char *str = strdup("a a");
        int count = count_words(str);
        char **p_words = malloc(count * sizeof(char *));;
        count = sep(str, p_words);
        int cmp = 0;
        char *res[] = { "a", "a" };
        for (int i = 0; i < count && cmp == 0; i++)
            cmp = strcmp(res[i], p_words[i]);
        printf("Correct work with empty string: %s\n", (count == 2 && cmp == 0) ? "YES" : "NO");
        free(p_words);
        free(str);
    }
    {
        char *str = strdup("  a a   d");
        int count = count_words(str);
        char **p_words = malloc(count * sizeof(char *));;
        count = sep(str, p_words);
        int cmp = 0;
        char *res[] = { "a", "a", "d" };
        for (int i = 0; i < count && cmp == 0; i++)
            cmp = strcmp(res[i], p_words[i]);
        printf("Correct work with empty string: %s\n\n", (count == 3 && cmp == 0) ? "YES" : "NO");
        free(p_words);
        free(str);
    }
}

void test_add_unique_word(void)
{
    printf("Tests for add_unique_word():\n");
    {
        char *word = "aaaaaaaaaaaaaaaaaaaaa";
        struct list_elem *head = NULL;
        int count = 0;
        int rc = add_unique_word(word, &head, &count);
        printf("Correct work with too long word: %s\n", (count == 0 && rc == MEMORY_ERROR) ? "YES" : "NO");
        free_list(head);
    }
    {
        char *word = "Hi!";
        struct list_elem *head = NULL;
        int count = 0;
        int rc = add_unique_word(word, &head, &count);
        char *res[] = { "Hi!", "My", "name", "is" };
        int cmp = 0;
        struct list_elem *tmp = head;
        for (int i = 0; i < count && tmp && cmp == 0; tmp = tmp->next, i++)
            cmp = strcmp(res[i], tmp->word);
        printf("Correct work with 1 unique word: %s\n", (count == 1 && rc == OK && cmp == 0 && tmp == NULL) ? "YES" : "NO");
        word = "My";
        rc = add_unique_word(word, &head, &count);
        tmp = head;
        for (int i = 0; i < count && tmp && cmp == 0; tmp = tmp->next, i++)
            cmp = strcmp(res[i], tmp->word);
        printf("Correct work with 2 unique words: %s\n", (count == 2 && rc == OK && cmp == 0 && tmp == NULL) ? "YES" : "NO");
        word = "name";
        rc = add_unique_word(word, &head, &count);
        tmp = head;
        for (int i = 0; i < count && tmp && cmp == 0; tmp = tmp->next, i++)
            cmp = strcmp(res[i], tmp->word);
        printf("Correct work with 3 unique words: %s\n", (count == 3 && rc == OK && cmp == 0 && tmp == NULL) ? "YES" : "NO");
        word = "is";
        rc = add_unique_word(word, &head, &count);
        tmp = head;
        for (int i = 0; i < count && tmp && cmp == 0; tmp = tmp->next, i++)
            cmp = strcmp(res[i], tmp->word);
        printf("Correct work with 4 unique words: %s\n", (count == 4 && rc == OK && cmp == 0 && tmp == NULL) ? "YES" : "NO");
        word = "My";
        rc = add_unique_word(word, &head, &count);
        tmp = head;
        for (int i = 0; i < count && tmp && cmp == 0; tmp = tmp->next, i++)
            cmp = strcmp(res[i], tmp->word);
        printf("Correct work with 4 unique words and duplicate words: %s\n", (count == 4 && rc == OK && cmp == 0 && tmp == NULL) ? "YES" : "NO");
        word = "Hi!";
        rc = add_unique_word(word, &head, &count);
        tmp = head;
        for (int i = 0; i < count && tmp && cmp == 0; tmp = tmp->next, i++)
            cmp = strcmp(res[i], tmp->word);
        printf("Correct work with 4 unique words and duplicate words: %s\n", (count == 4 && rc == OK && cmp == 0 && tmp == NULL) ? "YES" : "NO");
        free_list(head);
    }
}

int main(void)
{
    test_count_words();
    test_sep();
    test_add_unique_word();
    return OK;
}
