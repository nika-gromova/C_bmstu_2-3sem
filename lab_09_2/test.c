#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "defines.h"
#include "io.h"
#include "replace.h"
#include "str.h"

#define NOTEQ -2

/**
 * @brief arraycmp Функция сравниавет два массива.
 * @param a [in] - указатель на первый для сравнения массив
 * @param b [in] - указатель на второй для сравнения массив
 * @param n [in] - количество элементов первого массива
 * @param m [in] - количесвто элементов второго массива
 * @return Возвращает OK, если массивы равны, либо NOTEQ, если массивы не равны.
 */
int arraycmp(int *a, int *b, int n, int m)
{
    if (n != m)
        return NOTEQ;
    for (int i = 0; i < n; i++)
        if (a[i] != b[i])
            return NOTEQ;
    return OK;
}

/**
 * @brief test_len Тестирование функции, которая определяет длину строку.
 */
void test_len(void)
{
    {
        char *a = "";
        printf("Correct work of function len(): %s\n", (len(a) == strlen(a)) ? "YES" : "NO");
    }
    {
        char *a = "a";
        printf("Correct work of function len(): %s\n", (len(a) == strlen(a)) ? "YES" : "NO");
    }
    {
        char *a = "ab";
        printf("Correct work of function len(): %s\n", (len(a) == strlen(a)) ? "YES" : "NO");
    }
    {
        char *a = "abc";
        printf("Correct work of function len(): %s\n\n", (len(a) == strlen(a)) ? "YES" : "NO");
    }
}

/**
 * @brief test_str_cmp Тестирование функции, которая сравнивает строки.
 */
void test_str_cmp(void)
{
    {
        char *a = "";
        char *b = "";
        printf("Correct work of function str_cmp(): %s\n", (str_cmp(a, b) == strcmp(a, b)) ? "YES" : "NO");
    }
    {
        char *a = "";
        char *b = "a";
        printf("Correct work of function str_cmp(): %s\n", (str_cmp(a, b) == -1 && strcmp(a, b) != 0) ? "YES" : "NO");
    }
    {
        char *a = "a";
        char *b = "b";
        printf("Correct work of function str_cmp(): %s\n", (str_cmp(a, b) == -1 && strcmp(a, b) != 0) ? "YES" : "NO");
    }
    {
        char *a = "aaaa";
        char *b = "aaa";
        printf("Correct work of function str_cmp(): %s\n", (str_cmp(a, b) == -1 && strcmp(a, b) != 0) ? "YES" : "NO");
    }
    {
        char *a = "abcabc";
        char *b = "abc";
        printf("Correct work of function str_cmp(): %s\n", (str_cmp(a, b) == -1 && strcmp(a, b) != 0) ? "YES" : "NO");
    }
    {
        char *a = "abc";
        char *b = "abc";
        printf("Correct work of function str_cmp(): %s\n\n", (str_cmp(a, b) == strcmp(a, b)) ? "YES" : "NO");
    }
}

/**
 * @brief test_my_memcpy Тестирование функции, которая копирует участок памяти из одного места в другое.
 */
void test_my_memcpy(void)
{
    {
        char *a = "";
        size_t len_a = strlen(a);
        char *b = malloc(2);
        if (b)
        {
            b[0] = 'a';
            my_memcpy(b + 1, a, len_a);
            b[len_a + 1] = '\0';
            char *res = "a";
            printf("Correct work of function my_memcpy() for str: %s\n", (strcmp(res, b) == 0) ? "YES" : "NO");
            free(b);
        }
    }
    {
        char *a = "abc";
        size_t len_a = strlen(a);
        char *b = malloc(len_a + 1);
        if (b)
        {
            my_memcpy(b, a, len_a);
            b[len_a] = '\0';
            printf("Correct work of function my_memcpy() for str: %s\n", (strcmp(a, b) == 0) ? "YES" : "NO");
            free(b);
        }
    }
    {
        char *a = "abc";
        size_t len_a = strlen(a);
        char *b = malloc(len_a + 2);
        if (b)
        {
            b[0] = 'g';
            my_memcpy(b + 1, a, len_a);
            b[len_a + 1] = '\0';
            char *res = "gabc";
            printf("Correct work of function my_memcpy() for str: %s\n", (strcmp(res, b) == 0) ? "YES" : "NO");
            free(b);
        }
    }
    {
        char *a = "abc";
        size_t len_a = strlen(a);
        char *b = malloc(len_a);
        if (b)
        {
            my_memcpy(b, a + 1, len_a);
            b[len_a - 1] = '\0';
            char *res = "bc";
            printf("Correct work of function my_memcpy() for str: %s\n", (strcmp(res, b) == 0) ? "YES" : "NO");
            free(b);
        }
    }

    {
        int a[3] = { 2, 3, 4 };
        int size_a = sizeof(a) / sizeof(a[0]);
        int *b = malloc(size_a * sizeof(int));
        if (b)
        {
            my_memcpy(b, a, size_a * sizeof(int));
            printf("\nCorrect work of function my_memcpy() for int: %s\n", (arraycmp(a, b, size_a, size_a) == 0) ? "YES" : "NO");
            free(b);
        }
    }
    {
        int a[3] = { 2, 3, 4 };
        int size_a = sizeof(a) / sizeof(a[0]);
        int *b = malloc((size_a - 1) * sizeof(int));
        if (b)
        {
            my_memcpy(b, a + 1, (size_a - 1) * sizeof(int));
            int res[] = { 3, 4 };
            printf("Correct work of function my_memcpy() for int: %s\n", (arraycmp(res, b, size_a - 1, size_a - 1) == 0) ? "YES" : "NO");
            free(b);
        }
    }
    {
        int a[3] = { 2, 3, 4 };
        int size_a = sizeof(a) / sizeof(a[0]);
        int *b = malloc(size_a * sizeof(int));
        if (b)
        {
            b[0] = 0;
            my_memcpy(b + 1, a, (size_a - 1) * sizeof(int));
            int res[] = { 0, 2, 3 };
            printf("Correct work of function my_memcpy() for int: %s\n\n", (arraycmp(res, b, sizeof(res) / sizeof(res[0]), size_a) == 0) ? "YES" : "NO");
            free(b);
        }
    }
}

/**
 * @brief test_my_getline Тестирование функции, которая считывает строку из файла.
 */
void test_my_getline(void)
{
    {
        FILE *f = fopen("in_1.txt", "r");
        if (f)
        {
            char *line = NULL;
            size_t n = 0;
            ssize_t read = my_getline(&line, &n, f);
            printf("Correct work of function my_getline(): %s\n", (read == -1) ? "YES" : "NO");
            free(line);
            fclose(f);
        }
    }
    {
        FILE *f = fopen("in_2.txt", "r");
        if (f)
        {
            char *line = NULL;
            size_t n = 0;
            ssize_t read = my_getline(&line, &n, f);
            printf("Correct work of function my_getline(): %s\n", (read == 2 && strcmp(line, "a\n") == 0) ? "YES" : "NO");
            free(line);
            fclose(f);
        }
    }
    {
        FILE *f = fopen("in_6.txt", "r");
        if (f)
        {
            char *line = NULL;
            size_t n = 0;
            ssize_t read = my_getline(&line, &n, f);
            printf("Correct work of function my_getline(): %s\n", (read == 4 && strcmp(line, "aca\n") == 0) ? "YES" : "NO");
            free(line);
            fclose(f);
        }
    }
    {
        FILE *f = fopen("in_15.txt", "r");
        if (f)
        {
            char *line = NULL;
            size_t n = 0;
            ssize_t read = my_getline(&line, &n, f);
            char *res = "hkjhkjhkjhkhj                                                                                     hjkh                                                    hjhk                                                                                                             hjkhj              hjk                                                  hjk                                     hjk\n";
            printf("Correct work of function my_getline(): %s\n", (read = 383 && strcmp(res, line) == 0) ? "YES" : "NO");
            free(line);
            fclose(f);
        }
    }
    {
        FILE *f = fopen("in_16.txt", "r");
        if (f)
        {
            char *line = NULL;
            size_t n = 0;
            ssize_t read = my_getline(&line, &n, f);
            printf("Correct work of function my_getline(): %s\n\n", (read == 3 && strcmp(line, "abc") == 0) ? "YES" : "NO");
            free(line);
            fclose(f);
        }
    }
    {
        FILE *f = fopen("in_16.txt", "r");
        if (f)
        {
            char *line = malloc(3);
            if (line)
            {
                size_t n = 3;
                strcpy(line, "kd");
                ssize_t read = my_getline(&line, &n, f);
                printf("Correct work of function my_getline(): %s\n\n", (read == 3 && n == 4 && str_cmp(line, "abc") == 0) ? "YES" : "NO");
                free(line);
            }
            fclose(f);
        }
    }
}

/**
 * @brief test_my_strstr Тестирование функции, которая ищет первое вхождение подстроки в строку.
 */
void test_my_strstr(void)
{
    {
        char *a = '\0';
        char *b = '\0';
        char *c = '\0';
        char *res = my_strstr(a, b);
        printf("Correct work of function my_strstr(): %s\n", (str_cmp(c, res) == 0) ? "YES" : "NO");
    }

    {
        char *a = '\0';
        char *b = "a";
        char *res = my_strstr(a, b);
        printf("Correct work of function my_strstr(): %s\n", (res == NULL) ? "YES" : "NO");
    }
    {
        char *a = "a";
        char *b = '\0';
        char *res = my_strstr(a, b);
        printf("Correct work of function my_strstr(): %s\n", (res == NULL) ? "YES" : "NO");
    }
    {
        char *a = "b";
        char *b = "a";
        char *res = my_strstr(a, b);
        printf("Correct work of function my_strstr(): %s\n", (res == NULL) ? "YES" : "NO");
    }
    {
        char *a = "ab";
        char *b = "a";
        char *res = my_strstr(a, b);
        printf("Correct work of function my_strstr(): %s\n", (strcmp(res, a) == 0) ? "YES" : "NO");
    }
    {
        char *a = "ab";
        char *b = "b";
        char *res = my_strstr(a, b);
        printf("Correct work of function my_strstr(): %s\n", (str_cmp(res, b) == 0) ? "YES" : "NO");
    }
    {
        char *a = "cab";
        char *b = "a";
        char *new = my_strstr(a, b);
        char *res = "ab";
        printf("Correct work of function my_strstr(): %s\n", (str_cmp(res, new) == 0) ? "YES" : "NO");
    }
    {
        char *a = "ghjabab";
        char *b = "a";
        char *new = my_strstr(a, b);
        char *res = "abab";
        printf("Correct work of function my_strstr(): %s\n", (str_cmp(res, new) == 0) ? "YES" : "NO");
    }
    {
        char *a = "kcablab";
        char *b = "ab";
        char *new = my_strstr(a, b);
        char *res = "ablab";
        printf("Correct work of function my_strstr(): %s\n", (strcmp(res, new) == 0) ? "YES" : "NO");
    }
    {
        char *a = "kcadlab";
        char *b = "ab";
        char *new = my_strstr(a, b);
        char *res = "ab";
        printf("Correct work of function my_strstr(): %s\n\n", (strcmp(res, new) == 0) ? "YES" : "NO");
    }
}

/**
 * @brief test_str_replace Тестирование функции, которая производит в строке все замены одной подстроки на другую.
 */
void test_str_replace(void)
{
    {
        char *source = '\0';
        char *search = "a";
        char *replace = "*";
        char *res = '\0';
        char *new = str_replace(source, search, replace);
        printf("Correct work of function str_replace(): %s\n", (str_cmp(res, new) == 0) ? "YES" : "NO");
        free(new);
    }
    {
        char *source = '\0';
        char *search = '\0';
        char *replace = "*";
        char *res = '\0';
        char *new = NULL;
        new = str_replace(source, search, replace);
        printf("Correct work of function str_replace(): %s\n", (str_cmp(res, new) == 0) ? "YES" : "NO");
        free(new);
    }
    {
        char *source = '\0';
        char *search = '\0';
        char *replace = '\0';
        char *res = '\0';
        char *new = str_replace(source, search, replace);
        printf("Correct work of function str_replace(): %s\n", (str_cmp(res, new) == 0) ? "YES" : "NO");
        free(new);
    }
    {
        char *source = "a";
        char *search = "a";
        char *replace = '\0';
        char *res = "";
        char *new = str_replace(source, search, replace);
        printf("Correct work of function str_replace(): %s\n", (str_cmp(res, new) == 0) ? "YES" : "NO");
        free(new);
    }
    {
        char *source = "a";
        char *search = '\0';
        char *replace = '\0';
        char *res = "a";
        char *new = str_replace(source, search, replace);
        printf("Correct work of function str_replace(): %s\n", (str_cmp(res, new) == 0) ? "YES" : "NO");
        free(new);
    }
    {
        char *source = "abc";
        char *search = "a";
        char *replace = "fgh";
        char *res = "fghbc";
        char *new = str_replace(source, search, replace);
        printf("Correct work of function str_replace(): %s\n", (str_cmp(res, new) == 0) ? "YES" : "NO");
        free(new);
    }
    {
        char *source = "abcda";
        char *search = "bc";
        char *replace = "*";
        char *res = "a*da";
        char *new = str_replace(source, search, replace);
        printf("Correct work of function str_replace(): %s\n", (str_cmp(res, new) == 0) ? "YES" : "NO");
        free(new);
    }
    {
        char *source = "b*c*d*a";
        char *search = "*";
        char *replace = "A";
        char *res = "bAcAdAa";
        char *new = str_replace(source, search, replace);
        printf("Correct work of function str_replace(): %s\n", (str_cmp(res, new) == 0) ? "YES" : "NO");
        free(new);
    }
    {
        char *source = "11/11/11";
        char *search = "11";
        char *replace = "01";
        char *res = "01/01/01";
        char *new = str_replace(source, search, replace);
        printf("Correct work of function str_replace(): %s\n", (str_cmp(res, new) == 0) ? "YES" : "NO");
        free(new);
    }
    {
        char *source = "###{###}#,##";
        char *search = "###";
        char *replace = ".";
        char *res = ".{.}#,##";
        char *new = str_replace(source, search, replace);
        printf("Correct work of function str_replace(): %s\n", (str_cmp(res, new) == 0) ? "YES" : "NO");
        free(new);
    }
}

int main(void)
{
    test_len();
    test_str_cmp();
    test_my_memcpy();
    test_my_getline();
    test_my_strstr();
    test_str_replace();
    return OK;
}
