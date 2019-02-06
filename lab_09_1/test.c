#include <stdio.h>
#include <string.h>
#include "process.h"

/**
 * @brief str_cmp Функция сравнения двух строк.
 * @param str1 [in] - указатель на первую строку
 * @param str2 [in] - указатель на вторую строку
 * @return возвращает 0, если строки равны; -1, если строки не равны
 */
int str_cmp(const char *str1, const char *str2)
{
    if (str1 == NULL)
    {
        if (str2 == NULL)
            return 0;
        else
            return -1;
    }
    if (str2 == NULL)
        return -1;

    for (int i = 0; str1[i] == str2[i]; i++)
        if (str1[i] == '\0')
            return 0;
    return -1;
}

void test_my_strpbrk(void)
{
    printf("TESTS FOR my_strpbrk:\n");
    {
        const char *str = "";
        const char *sym = "c";
        const char *init = strpbrk(str, sym);
        const char *my = my_strpbrk(str, sym);
        printf("Correct work with empty string: %s\n\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
    }
    {
        const char *str = "a";
        const char *sym = "a";
        const char *init = strpbrk(str, sym);
        const char *my = my_strpbrk(str, sym);
        printf("Correct work with valid strings size of 1 (a, a): %s\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
    }
    {
        const char *str = "a";
        const char *sym = "b";
        const char *init = strpbrk(str, sym);
        const char *my = my_strpbrk(str, sym);
        printf("Correct worl with valid string size of 1 (a, b): %s\n\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
    }
    {
        const char *str = "ab";
        const char *sym = "a";
        const char *init = strpbrk(str, sym);
        const char *my = my_strpbrk(str, sym);
        printf("Correct work with valid string size of 2 (ab, a): %s\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
    }
    {
        const char *str = "ab";
        const char *sym = "b";
        const char *init = strpbrk(str, sym);
        const char *my = my_strpbrk(str, sym);
        printf("Correct worl with valid string size of 2 (ab, b): %s\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
    }
    {
        const char *str = "ab";
        const char *sym = "c";
        const char *init = strpbrk(str, sym);
        const char *my = my_strpbrk(str, sym);
        printf("Correct worl with valid string size of 2 (ab, c): %s\n\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
    }
    {
        const char *str = "abc";
        const char *sym = "a";
        const char *init = strpbrk(str, sym);
        const char *my = my_strpbrk(str, sym);
        printf("Correct worl with valid string size of 3 (abc, a): %s\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
    }
    {
        const char *str = "abc";
        const char *sym = "b";
        const char *init = strpbrk(str, sym);
        const char *my = my_strpbrk(str, sym);
        printf("Correct work with valid string size of 3 (abc, b): %s\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
    }
    {
        const char *str = "abc";
        const char *sym = "c";
        const char *init = strpbrk(str, sym);
        const char *my = my_strpbrk(str, sym);
        printf("Correct work with valid string size of 3 (abc, c): %s\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
    }
    {
        const char *str = "abc";
        const char *sym = "d";
        const char *init = strpbrk(str, sym);
        const char *my = my_strpbrk(str, sym);
        printf("Correct work with valid string size of 3 (abc, d): %s\n\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
    }
    {
        const char *str = "abc";
        const char *sym = "ab";
        const char *init = strpbrk(str, sym);
        const char *my = my_strpbrk(str, sym);
        printf("Correct work with valid string size of 3 (abc, ab): %s\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
    }
    {
        const char *str = "baaabcaaaabc";
        const char *sym = "ab";
        const char *init = strpbrk(str, sym);
        const char *my = my_strpbrk(str, sym);
        printf("Correct work with valid string size of 12 (baaabcaaaabc, ab): %s\n\n\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
    }
}

void test_my_strdup(void)
{
    printf("TESTS FOR my_strdup:\n");
    {
        const char *str = "";
        char *my = my_strdup(str);
        const char *init = "";
        printf("Correct work with empty string: %s\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
        if (my)
            free(my);
    }
    {
        const char *str = NULL;
        char *my = my_strdup(str);
        const char *init = NULL;
        printf("Correct work with NULL string: %s\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
        if (my)
            free(my);
    }
    {
        const char *str = "a";
        char *my = my_strdup(str);
        const char *init = "a";
        printf("Correct work with valid string sizeof 1 (a): %s\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
        if (my)
            free(my);
    }
    {
        const char *str = "ab";
        char *my = my_strdup(str);
        const char *init = "ab";
        printf("Correct work with valid string sizeof 2 (ab): %s\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
        if (my)
            free(my);
    }
    {
        const char *str = "abc";
        char *my = my_strdup(str);
        const char *init = "abc";
        printf("Correct work with valid string sizeof 3 (abc): %s\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
        if (my)
            free(my);
    }
    {
        const char *str = "abc di ";
        char *my = my_strdup(str);
        const char *init = "abc di ";
        printf("Correct work with valid string sizeof 7 (abc di ): %s\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
        if (my)
            free(my);
    }
    {
        const char *str = "\n";
        char *my = my_strdup(str);
        const char *init = "\n";
        printf("Correct work with valid string sizeof 1 (\\n): %s\n", (str_cmp(init, my) == 0 ? "YES" : "NO"));
        if (my)
            free(my);
    }
}

int main(void)
{
    test_my_strpbrk();
    test_my_strdup();
    return 0;
}
