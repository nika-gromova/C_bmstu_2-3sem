#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "defines.h"
#include "io.h"
#include "list.h"
#include "structure.h"
#define EPS 0.00000001

/**
 * @brief cmp_elem Функция сравнения двух элементов типа data_t.
 * @param el1 [in] - указатель на первый элемент.
 * @param el2 [in] - указатель на второй элемент.
 * @return Возвращает 0, если элементы равны и -1 в противном случае.
 */
int cmp_elem(const data_t *el1, const data_t *el2)
{
    if (strcmp(el1->country, el2->country) == 0)
        if (strcmp(el1->capital, el2->capital) == 0)
            if (el1->year == el2->year)
                return 0;
    return -1;
}

/**
 * @brief cmp_elem Функция сравнения двух элементов типа node_t.
 * @param el1 [in] - указатель на первый элемент.
 * @param el2 [in] - указатель на второй элемент.
 * @return Возвращает 0, если элементы равны и -1 в противном случае.
 */
int cmp_list_elem(const node_t *el1, const node_t *el2)
{
    if (el1->data == el2->data)
        if (el1->next == el2->next)
            return 0;
    return -1;
}

/**
 * @brief cmp_elem Функция сравнения двух элементов типа double.
 * @param el1 [in] - указатель на первый элемент.
 * @param el2 [in] - указатель на второй элемент.
 * @return Возвращает 0, если элементы равны, -1, если первый элемент меньше второго и 1, если первый элемент больше второго.
 */
int cmp_double_num(const void *data1, const void *data2)
{
    const double *num1 = data1;
    const double *num2 = data2;
    if (fabs(*num1 - *num2) <= EPS)
        return 0;
    if (*num1 - *num2 < EPS)
        return -1;
    else
        return 1;
}

/**
 * @brief cmp_elem_double Функция сравнивает элементты типа double.
 * @param n1 [in] - указатель на первый элемент.
 * @param n2 [in] - указатель на второй элемент.
 * @return Возвращает 0, если элементы равны и -1 в противном случае.
 */
int cmp_elem_double(const double *n1, const double *n2)
{
    if (fabs(*n1 - *n2) <= EPS)
        return 0;
    return -1;
}

/**
 * @brief test_count_line Функция тестирования подсчета строк в файле.
 */
void test_count_line(void)
{
    printf("Tests for 'count_line()':\n");
    {
        char *file_name = "in_1.txt";
        int count = count_line(file_name);
        printf("Correct work with empty file: %s\n", (count == 0) ? "YES" : "NO");
    }
    {
        char *file_name = "in_2.txt";
        int count = count_line(file_name);
        printf("Correct work with 3-line file: %s\n", (count == 3) ? "YES" : "NO");
    }
    {
        char *file_name = "in_5.txt";
        int count = count_line(file_name);
        printf("Correct work with 6-line file: %s\n", (count == 6) ? "YES" : "NO");
    }
    {
        char *file_name = "in_6.txt";
        int count = count_line(file_name);
        printf("Correct work with 9-line file: %s\n", (count == 9) ? "YES" : "NO");
    }
    {
        char *file_name = "in_8.txt";
        int count = count_line(file_name);
        printf("Correct work with 12-line file: %s\n", (count == 12) ? "YES" : "NO");
    }
    {
        char *file_name = "out_7.txt";
        int count = count_line(file_name);
        printf("Correct work with 3-line file: %s\n\n", (count == 3) ? "YES" : "NO");
    }
}

/**
 * @brief test_create_struct Функция тестирования создания структуры типа data_t.
 */
void test_create_struct(void)
{
    printf("Tests for 'create_struct()':\n");
    {
        char *country = "Country";
        char *capital = "Capital";
        int year = 1000;
        data_t check = { "Country", "Capital", 1000 };
        data_t *res = create_struct(country, capital, year);
        printf("Correct work with valid data: %s\n", (cmp_elem(&check, res) == 0) ? "YES" : "NO");
        free(res);
    }
    {
        char *country = "";
        char *capital = "";
        int year = 0;
        data_t check = { "", "", 0 };
        data_t *res = create_struct(country, capital, year);
        printf("Correct work with valid data: %s\n\n", (cmp_elem(&check, res) == 0) ? "YES" : "NO");
        free(res);
    }
}

/**
 * @brief test_read_data Функция тестирования чтения одного элемента из файла.
 */
void test_read_data(void)
{
    printf("Tests for 'read_data()':\n");
    {
        int rc;
        FILE *f = fopen("in_1.txt", "r");
        if (f)
        {
            data_t *p_data = NULL;
            rc = read_data(f, &p_data);
            printf("Correct work with empty file: %s\n", (rc == READ_ERROR) ? "YES" : "NO");
            free(p_data);
            fclose(f);
        }
    }
    {
        int rc;
        FILE *f = fopen("in_2.txt", "r");
        if (f)
        {
            data_t *p_data = NULL;
            data_t res = { "Russia", "Moscow", 1147 };
            rc = read_data(f, &p_data);
            printf("Correct work with valid 3-line file: %s\n", (rc == OK && cmp_elem(&res, p_data) == 0) ? "YES" : "NO");
            free(p_data);
            fclose(f);
        }
    }
    {
        int rc;
        FILE *f = fopen("in_5.txt", "r");
        if (f)
        {
            data_t *p_data = NULL;
            data_t res = { "Spain", "Madrid", 932 };
            rc = read_data(f, &p_data);
            printf("Correct work with valid 6-line file: %s\n", (rc == OK && cmp_elem(&res, p_data) == 0) ? "YES" : "NO");
            free(p_data);
            fclose(f);
        }
    }
    {
        int rc;
        FILE *f = fopen("in_10.txt", "r");
        if (f)
        {
            data_t *p_data = NULL;
            rc = read_data(f, &p_data);
            printf("Correct work with invalid 1-line file: %s\n", (rc == INPUT_ERROR) ? "YES" : "NO");
            free(p_data);
            fclose(f);
        }
    }
    {
        int rc;
        FILE *f = fopen("in_11.txt", "r");
        if (f)
        {
            data_t *p_data = NULL;
            rc = read_data(f, &p_data);
            printf("Correct work with invalid 2-line file: %s\n", (rc == INPUT_ERROR) ? "YES" : "NO");
            free(p_data);
            fclose(f);
        }
    }
    {
        int rc;
        FILE *f = fopen("in_12.txt", "r");
        if (f)
        {
            data_t *p_data = NULL;
            rc = read_data(f, &p_data);
            printf("Correct work with invalid 3-line without a number: %s\n", (rc == INPUT_ERROR) ? "YES" : "NO");
            free(p_data);
            fclose(f);
        }
    }
    {
        int rc;
        FILE *f = fopen("in_13.txt", "r");
        if (f)
        {
            data_t *p_data = NULL;
            rc = read_data(f, &p_data);
            printf("Correct work with invalid 1-line file with too long string: %s\n", (rc == INPUT_ERROR) ? "YES" : "NO");
            free(p_data);
            fclose(f);
        }
    }
    {
        int rc;
        FILE *f = fopen("in_12.txt", "r");
        if (f)
        {
            data_t *p_data = NULL;
            rc = read_data(f, &p_data);
            printf("Correct work with invalid 4-line file: %s\n\n", (rc == INPUT_ERROR) ? "YES" : "NO");
            free(p_data);
            fclose(f);
        }
    }
}

/**
 * @brief test_read_file функция тестирования чтения всей информации из файла.
 */
void test_read_file(void)
{
    printf("Tests for 'read_file()':\n");
    {
        int rc = OK;
        data_t *array[1];
        char *file_name = "in_1.txt";
        rc = read_file(file_name, array, 1);
        printf("Correct work with empty file: %s\n", (rc == READ_ERROR) ? "YES" : "NO");
    }
    {
        int rc = OK;
        data_t *array[1];
        char *file_name = "in_10.txt";
        rc = read_file(file_name, array, 1);
        printf("Correct work with invalid file: %s\n", (rc == READ_ERROR) ? "YES" : "NO");
    }
    {
        int rc = OK;
        data_t *array[1];
        char *file_name = "in_11.txt";
        rc = read_file(file_name, array, 1);
        printf("Correct work with invalid file: %s\n", (rc == READ_ERROR) ? "YES" : "NO");
    }
    {
        int rc = OK;
        data_t *array[1];
        char *file_name = "in_12.txt";
        rc = read_file(file_name, array, 1);
        printf("Correct work with invalid file: %s\n", (rc == READ_ERROR) ? "YES" : "NO");
    }
    {
        int rc = OK;
        data_t *array[1];
        char *file_name = "in_13.txt";
        rc = read_file(file_name, array, 1);
        printf("Correct work with invalid file: %s\n", (rc == READ_ERROR) ? "YES" : "NO");
    }
    {
        int rc = OK;
        data_t **array = calloc(1, sizeof(data_t *));
        if (array)
        {
            char *file_name = "in_2.txt";
            data_t res = { "Russia", "Moscow", 1147 };
            rc = read_file(file_name, array, 1);
            //printf("%s %s %d\n", array[0]->country, array[0]->capital, array[0]->year);
            printf("Correct work with valid file with 1 element: %s\n", (rc == OK && cmp_elem(&res, array[0]) == 0) ? "YES" : "NO");
            for (int i = 0; i < 1; i++)
                free(array[i]);
            free(array);
        }
    }
    {
        int rc = OK;
        data_t **array = calloc(2, sizeof(data_t *));
        if (array)
        {
            char *file_name = "in_5.txt";
            data_t res[] = { { "Spain", "Madrid", 932 }, { "Russia", "Moscow", 1147 } };
            rc = read_file(file_name, array, 2);
            int cmp = 0;
            if (rc == OK)
            {
                for (int i = 0; i < 2 && cmp == 0; i++)
                    cmp = cmp_elem(res + i, array[i]);
                printf("Correct work with valid file with 2 elements: %s\n", (cmp == 0) ? "YES" : "NO");
                for (int i = 0; i < 2; i++)
                    free(array[i]);
            }
            //printf("%s %s %d\n", array[1]->country, array[1]->capital, array[1]->year);
            free(array);
        }
    }
    {
        int rc = OK;
        data_t **array = calloc(3, sizeof(data_t *));
        if (array)
        {
            char *file_name = "in_7.txt";
            data_t res[3] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 }, { "Russia", "Moscow", 1147 } };
            rc = read_file(file_name, array, 3);
            int cmp = 0;
            if (rc == OK)
            {
                for (int i = 0; i < 3 && cmp == 0; i++)
                    cmp = cmp_elem(&(res[i]), array[i]);
                printf("Correct work with valid file with 3 elements: %s\n", (rc == OK && cmp == 0) ? "YES" : "NO");
                for (int i = 0; i < 3; i++)
                    free(array[i]);
            }
            free(array);
        }
    }
    {
        int rc = OK;
        data_t **array = calloc(4, sizeof(data_t *));
        char *file_name = "in_8.txt";
        data_t res[4] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 }, { "Russia", "Moscow", 1147 } };
        rc = read_file(file_name, array, 4);
        int cmp = 0;
        if (rc == OK)
        {
            for (int i = 0; i < 4 && cmp == 0; i++)
                cmp = cmp_elem(&(res[i]), array[i]);
            printf("Correct work with valid file with 4 elements: %s\n\n", (rc == OK && cmp == 0) ? "YES" : "NO");
            for (int i = 0; i < 4; i++)
                free(array[i]);
        }
        free(array);
    }
}

/**
 * @brief test_create_list_elem Функция тестирования создания элемента списка типа node_t.
 */
void test_create_list_elem(void)
{
    printf("Tests for 'create_list_elem()':\n");
    {
        data_t elem = { "Spain", "Madrid", 932 };
        node_t *list_elem = create_list_elem(&elem);
        node_t check = { &elem, NULL };
        printf("Correct work with valid information: %s\n", (cmp_list_elem(&check, list_elem) == 0) ? "YES" : "NO");
        free(list_elem);
    }
    {
        data_t elem = { "Spain", "", 0 };
        node_t *list_elem = create_list_elem(&elem);
        node_t check = { &elem, NULL };
        printf("Correct work with valid information: %s\n", (cmp_list_elem(&check, list_elem) == 0) ? "YES" : "NO");
        free(list_elem);
    }
    {
        data_t elem;
        node_t *list_elem = create_list_elem(&elem);
        node_t check = { &elem, NULL };
        printf("Correct work with valid information: %s\n\n", (cmp_list_elem(&check, list_elem) == 0) ? "YES" : "NO");
        free(list_elem);
    }
}

/**
 * @brief test_add_list_elem Функция тестирования добавления элемента в список.
 */
void test_add_list_elem(void)
{
    printf("Test for 'add_list_alem()':\n");
    {
        int cmp = 0;
        data_t elem[] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 }, { "Russia", "Moscow", 1147 } };
        node_t *head = NULL;
        node_t *list_elem;
        for (int i = 0; i < 4; i++)
        {
            list_elem = create_list_elem(&(elem[i]));
            head = add_list_elem(head, list_elem);
        }
        node_t *tmp = head;
        data_t *cur;
        for (int i = 0; head != NULL && cmp == 0; head = head->next, i++)
        {
            cur = head->data;
            cmp = cmp_elem(cur, &(elem[i]));
        }
        printf("Correct work with valid information: %s\n\n", (cmp == 0) ? "YES" : "NO");
        free_list(tmp);
    }
}

/**
 * @brief test_create_list Функция тестирования создания списка.
 */
void test_create_list(void)
{
    printf("Test for 'create_list()':\n");
    {
        int cmp = 0;
        data_t elem[] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 }, { "Russia", "Moscow", 1147 } };
        data_t *p_elem[] = { &(elem[0]), &(elem[1]), &(elem[2]), &(elem[3]) };
        node_t *head = NULL;
        head = create_list(p_elem, 4);
        node_t *tmp = head;
        data_t *cur;
        for (int i = 0; head != NULL && cmp == 0; head = head->next, i++)
        {
            cur = head->data;
            cmp = cmp_elem(p_elem[i], cur);
        }
        printf("Correct work with valid information: %s\n\n", (cmp == 0) ? "YES" : "NO");
        free_list(tmp);
    }
}

/**
 * @brief test_cmp_country Функция тестирования функции сравнения по первому полю структуры data.
 */
void test_cmp_country(void)
{
    printf("Tests for 'cmp_country()':\n");
    {
        data_t first = { "Russia", "Moscow", 1147 }, second = { "Russia", "Tver", 1135 };
        printf("Correct work with the same country name: %s\n", (cmp_country(&first, &second) == 0) ? "YES" : "NO");
    }
    {
        data_t first = { "Russia", "Moscow", 1147 }, second = { "Brazil", "Brasilia", 1960 };
        printf("Correct work when first is bigger than second (lexico-grammatical order): %s\n", (cmp_country(&first, &second) > 0) ? "YES" : "NO");
    }
    {
        data_t second = { "Russia", "Moscow", 1147 }, first = { "Brazil", "Brasilia", 1960 };
        printf("Correct work when first is bigger than second (lexico-grammatical order): %s\n", (cmp_country(&first, &second) < 0) ? "YES" : "NO");
    }
    {
        data_t first = { "Russia", "Moscow", 1147 }, second = { "Italy", "Roma", -753 };
        printf("Correct work when first is bigger than second (length): %s\n", (cmp_country(&first, &second) > 0) ? "YES" : "NO");
    }

    {
        data_t first = { "Italy", "Roma", -753 }, second = { "Russia", "Moscow", 1147 };
        printf("Correct work when first is smaller than second (length): %s\n\n", (cmp_country(&first, &second) < 0) ? "YES" : "NO");
    }
}

/**
 * @brief test_cmp_year Функция тестирования функции сравнения по третьему полю структуры data.
 */
void test_cmp_year(void)
{
    printf("Tests for 'cmp_year()':\n");
    {
        data_t first = { "Russia", "Moscow", 1147 }, second = { "Russia", "Tver", 1135 };
        printf("Correct work when first date is bigger than second: %s\n", (cmp_year(&first, &second) > 0) ? "YES" : "NO");
    }
    {
        data_t first = { "Russia", "Moscow", 1135 }, second = { "Russia", "Tver", 1136 };
        printf("Correct work when second date is bigger than first: %s\n", (cmp_year(&first, &second) < 0) ? "YES" : "NO");
    }
    {
        data_t first = { "Russia", "Moscow", 1135 }, second = { "Russia", "Tver", 1135 };
        printf("Correct work with the same year: %s\n\n", (cmp_year(&first, &second) == 0) ? "YES" : "NO");
    }
}

/**
 * @brief test_find Функция тестирования поиска элемента в списке.
 */
void test_find(void)
{
    printf("Tests for 'find()':\n");
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 }, { "Russia", "Moscow", 1147 } };
        data_t *p_elements[] = { &(elemts[0]), &(elemts[1]), &(elemts[2]), &(elemts[3]) };
        node_t *head = NULL;
        head = create_list(p_elements, 4);
        node_t *res = find(head, p_elements[0], cmp_country);
        printf("Correct work with finding existing element (first): %s\n", (cmp_elem(res->data, p_elements[0]) == 0) ? "YES" : "NO");
        free_list(head);
    }
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 }, { "Russia", "Moscow", 1147 } };
        data_t *p_elements[] = { &(elemts[0]), &(elemts[1]), &(elemts[2]), &(elemts[3]) };
        node_t *head = NULL;
        head = create_list(p_elements, 4);
        node_t *res = find(head, p_elements[2], cmp_country);
        printf("Correct work with finding existing element (middle): %s\n", (cmp_elem(res->data, p_elements[2]) == 0) ? "YES" : "NO");
        free_list(head);
    }
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 }, { "Russia", "Moscow", 1147 } };
        data_t *p_elements[] = { &(elemts[0]), &(elemts[1]), &(elemts[2]), &(elemts[3]) };
        node_t *head = NULL;
        head = create_list(p_elements, 4);
        node_t *res = find(head, p_elements[3], cmp_country);
        printf("Correct work with finding existing element (end): %s\n", (cmp_elem(res->data, p_elements[3]) == 0) ? "YES" : "NO");
        free_list(head);
    }
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 }, { "Russia", "Moscow", 1147 } };
        data_t *p_elements[] = { &(elemts[0]), &(elemts[1]), &(elemts[2]), &(elemts[3]) };
        data_t search = { "Brazil", "Brasilia", 1960 };
        node_t *head = NULL;
        head = create_list(p_elements, 4);
        node_t *res = find(head, &search, cmp_country);
        printf("Correct work with finding not existing element: %s\n\n", (res == NULL) ? "YES" : "NO");
        free_list(head);
    }
}

/**
 * @brief test_insert Функция тестирования вставки элемента в список.
 */
void test_insert(void)
{
    printf("Tests for 'insert()':\n");
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 }, { "Russia", "Moscow", 1147 } };
        data_t *p_elements[] = { &(elemts[0]), &(elemts[1]), &(elemts[2]), &(elemts[3]) };
        node_t *head = NULL;
        head = create_list(p_elements, 4);
        data_t insert_data = { "Brazil", "Brasilia", 1960 };
        node_t *insert_list = create_list_elem(&insert_data);

        node_t *before = (head->next)->next;
        insert(&head, insert_list, before);

        node_t *tmp = head;
        int cmp = 0;
        int i = 0;
        int match = 0;
        data_t *cur;
        for (; head != NULL && cmp == 0; head = head->next)
        {
            cur = head->data;
            //printf("%s %s %d\n", cur->country, cur->capital, cur->year);
            if (i == 2)
            {
                cmp = cmp_elem(cur, &insert_data);
                i++;
                match = 1;
            }
            else
            {
                if (match == 1)
                    cmp = cmp_elem(cur, p_elements[i - 1]);
                else
                    cmp = cmp_elem(cur, p_elements[i]);
                i++;
            }
        }
        printf("Correct work with inserting element in the middle: %s\n", (cmp == 0) ? "YES" : "NO");
        free_list(tmp);
    }
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 }, { "Russia", "Moscow", 1147 } };
        data_t *p_elements[] = { &(elemts[0]), &(elemts[1]), &(elemts[2]), &(elemts[3]) };
        data_t insert_data = { "Brazil", "Brasilia", 1960 };
        node_t *insert_list = create_list_elem(&insert_data);
        node_t *head = NULL;
        head = create_list(p_elements, 4);
        node_t *before = head;
        insert(&head, insert_list, before);
        node_t *tmp = head;
        int cmp = 0;
        int i = 0;
        int match = 0;
        data_t *cur;
        for (; head != NULL && cmp == 0; head = head->next)
        {
            cur = head->data;
            if (i == 0)
            {
                cmp = cmp_elem(cur, &insert_data);
                i++;
                match = 1;
            }
            else
            {
                if (match == 1)
                    cmp = cmp_elem(cur, p_elements[i - 1]);
                else
                    cmp = cmp_elem(cur, p_elements[i]);
                i++;
            }
        }
        printf("Correct work with inserting element in the beginning: %s\n", (cmp == 0) ? "YES" : "NO");
        free_list(tmp);
    }
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 }, { "Russia", "Moscow", 1147 } };
        data_t *p_elements[] = { &(elemts[0]), &(elemts[1]), &(elemts[2]), &(elemts[3]) };
        data_t insert_data = { "Brazil", "Brasilia", 1960 };
        node_t *insert_list = create_list_elem(&insert_data);
        node_t *head = NULL;
        head = create_list(p_elements, 4);
        node_t *before = ((head->next)->next)->next;
        insert(&head, insert_list, before);
        node_t *tmp = head;
        int cmp = 0;
        int i = 0;
        int match = 0;
        data_t *cur;
        for (; head != NULL && cmp == 0; head = head->next)
        {
            cur = head->data;
            if (i == 3)
            {
                cmp = cmp_elem(cur, &insert_data);
                i++;
                match = 1;
            }
            else
            {
                if (match == 1)
                    cmp = cmp_elem(cur, p_elements[i - 1]);
                else
                    cmp = cmp_elem(cur, p_elements[i]);
                i++;
            }
        }
        printf("Correct work with inserting element in the end: %s\n\n", (cmp == 0) ? "YES" : "NO");
        free_list(tmp);
    }
}

/**
 * @brief test_reverse Функция тестирования обращения списка.
 */
void test_reverse(void)
{
    printf("Tests for 'reverse()':\n");
    {
        data_t elemts = { "Spain", "Madrid", 932 };
        data_t *p_elements[] = { &(elemts) };
        node_t *head = NULL;
        head = create_list(p_elements, 1);
        head = reverse(head);
        node_t *tmp = head;
        data_t *cur;
        int cmp = 0;
        for (int i = 0; i < 1 && head != NULL && cmp == 0; i++)
        {
            cur = head->data;
            cmp = cmp_elem(cur, &elemts);
            head = head->next;
        }
        printf("Correct work with reversing 1-element list: %s\n", (cmp == 0) ? "YES" : "NO");
        free_list(tmp);
    }
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 } };
        data_t *p_elements[] = { &(elemts[0]), &(elemts[1]) };
        node_t *head = NULL;
        head = create_list(p_elements, 2);
        head = reverse(head);
        node_t *tmp = head;
        data_t *cur;
        int cmp = 0;
        for (int i = 1; i > -1 && head != NULL && cmp == 0; i--)
        {
            cur = head->data;
            cmp = cmp_elem(cur, &(elemts[i]));
            head = head->next;
        }
        printf("Correct work with reversing 2-element list: %s\n", (cmp == 0) ? "YES" : "NO");
        free_list(tmp);
    }
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 } };
        data_t *p_elements[] = { &(elemts[0]), &(elemts[1]), &(elemts[2]) };
        node_t *head = NULL;
        head = create_list(p_elements, 3);
        head = reverse(head);
        node_t *tmp = head;
        data_t *cur;
        int cmp = 0;
        for (int i = 2; i > -1 && head != NULL && cmp == 0; i--)
        {
            cur = head->data;
            cmp = cmp_elem(cur, &(elemts[i]));
            head = head->next;
        }
        printf("Correct work with reversing 3-element list: %s\n", (cmp == 0) ? "YES" : "NO");
        free_list(tmp);
    }
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 } };
        data_t *p_elements[] = { &(elemts[0]) };
        node_t *head = NULL;
        head = create_list(p_elements, 0);
        head = reverse(head);
        printf("Correct work with reversing empty list: %s\n\n", (head == NULL) ? "YES" : "NO");
        free_list(head);
    }
}

/**
 * @brief test_front_back_split Функция тестирования деления списка на два пополам.
 */
void test_front_back_split(void)
{
    printf("Test for 'front_back_split()':\n");
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 } };
        data_t *p_elements[] = { &(elemts[0]) };
        node_t *head = NULL;
        node_t *back = NULL;
        head = create_list(p_elements, 0);
        front_back_split(head, &back);
        printf("Correct work with splitting empty list: %s\n", (head == NULL && back == NULL) ? "YES" : "NO");
        free_list(head);
    }
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 } };
        data_t *p_elements[] = { &(elemts[0]) };
        node_t *head = NULL;
        node_t *back = NULL;
        head = create_list(p_elements, 1);
        node_t *tmp = head;
        front_back_split(head, &back);
        printf("Correct work with splitting 1-element list: %s\n", (tmp == head && head->next == NULL && back == NULL) ? "YES" : "NO");
        free_list(head);
    }
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 } };
        data_t *p_elements[] = { &(elemts[0]), &(elemts[1]) };
        node_t *head = NULL;
        node_t *back = NULL;
        head = create_list(p_elements, 2);
        node_t *tmp = head;
        front_back_split(head, &back);
        data_t *cur = back->data;
        printf("Correct work with splitting 2-element list: %s\n", (tmp == head && head->next == NULL && cmp_elem(cur, p_elements[1]) == 0 && back->next == NULL) ? "YES" : "NO");
        free_list(head);
        free_list(back);
    }
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 } };
        data_t *p_elements[] = { &(elemts[0]), &(elemts[1]), &(elemts[2]) };
        node_t *head = NULL;
        node_t *back = NULL;
        head = create_list(p_elements, 3);
        front_back_split(head, &back);
        node_t *tmp_h = head, *tmp_b = back;
        data_t *cur;
        int cmp = 0;
        int i = 0;
        for (; head != NULL && cmp == 0; head = head->next, i++)
        {
            cur = head->data;
            cmp = cmp_elem(cur, p_elements[i]);
        }
        for (; back != NULL && cmp == 0; back = back->next, i++)
        {
            cur = back->data;
            cmp = cmp_elem(cur, p_elements[i]);
        }
        printf("Correct work with splitting 3-element list: %s\n", (cmp == 0 && i == 3) ? "YES" : "NO");
        free_list(tmp_h);
        free_list(tmp_b);
    }
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 }, { "Russia", "Moscow", 1147 } };
        data_t *p_elements[] = { &(elemts[0]), &(elemts[1]), &(elemts[2]), &(elemts[3]) };
        node_t *head = NULL;
        node_t *back = NULL;
        head = create_list(p_elements, 4);
        front_back_split(head, &back);
        node_t *tmp_h = head, *tmp_b = back;
        data_t *cur;
        int cmp = 0;
        int i = 0;
        for (; head != NULL && cmp == 0; head = head->next, i++)
        {
            cur = head->data;
            cmp = cmp_elem(cur, p_elements[i]);
        }
        for (; back != NULL && cmp == 0; back = back->next, i++)
        {
            cur = back->data;
            cmp = cmp_elem(cur, p_elements[i]);
        }
        printf("Correct work with splitting 4-element list: %s\n\n", (cmp == 0 && i == 4) ? "YES" : "NO");
        free_list(tmp_h);
        free_list(tmp_b);
    }
}

/**
 * @brief test_sorted_merge Функция тестирования слияния двух упорядоченных списков в один.
 */
void test_sorted_merge(void)
{
    printf("Tests for 'sorted_merge()':\n");
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 } };
        data_t *p_elements[] = { &(elemts[0]) };
        node_t *head1 = NULL;
        node_t *head2 = NULL;
        node_t *res;
        head1 = create_list(p_elements, 0);
        head2 = create_list(p_elements, 0);
        res = sorted_merge(&head1, &head2, cmp_year);
        printf("Correct work with merging empty lists: %s\n", (res == NULL) ? "YES" : "NO");
        free_list(res);
    }
    {
        data_t element = { "Spain", "Madrid", 932 };
        data_t *p_elements[1] = { &(element) };
        node_t *head1 = NULL;
        node_t *head2 = NULL;
        node_t *res;
        head1 = create_list(p_elements, 1);
        head2 = create_list(p_elements, 0);
        res = sorted_merge(&head1, &head2, cmp_year);
        data_t *res_data = res->data;
        printf("Correct work with merging 1-element list with empty list: %s\n", (cmp_elem(res_data, p_elements[0]) == 0) ? "YES" : "NO");
        free_list(res);
    }
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 } };
        data_t *p_elements[] = { &(elemts[0]) };
        node_t *head1 = NULL;
        node_t *head2 = NULL;
        node_t *res;
        head1 = create_list(p_elements, 0);
        head2 = create_list(p_elements, 1);
        res = sorted_merge(&head1, &head2, cmp_year);
        data_t *res_data = res->data;
        printf("Correct work with merging empty list with 1-element list : %s\n", (cmp_elem(res_data, p_elements[0]) == 0) ? "YES" : "NO");
        free_list(res);
    }
    {
        data_t elemts1[] = { { "Spain", "Madrid", 932 } };
        data_t elemts2[] = { { "Great Britain", "London", 50 } };
        data_t result[] = { { "Great Britain", "London", 50 }, { "Spain", "Madrid", 932 } };
        data_t *p_elements1[] = { &(elemts1[0]) };
        data_t *p_elements2[] = { &(elemts2[0]) };
        node_t *head1 = NULL;
        node_t *head2 = NULL;
        node_t *res;
        head1 = create_list(p_elements1, 1);
        head2 = create_list(p_elements2, 1);
        res = sorted_merge(&head1, &head2, cmp_year);
        node_t *tmp = res;
        data_t *cur;
        int cmp = 0;
        int i = 0;
        for (; res != NULL && cmp == 0; res = res->next, i++)
        {
            cur = res->data;
            cmp = cmp_elem(cur, &(result[i]));
        }
        printf("Correct work with merging 1-element list with 1-element list : %s\n", (cmp == 0 && i == 2) ? "YES" : "NO");
        free_list(tmp);
    }
    {
        data_t elemts1[] = { { "Great Britain", "London", 50 }, { "Spain", "Madrid", 932 } };
        data_t elemts2[] = { { "Japan", "Tokyo", 1497 } };
        data_t result[] = { { "Great Britain", "London", 50 }, { "Spain", "Madrid", 932 }, { "Japan", "Tokyo", 1497 } };
        data_t *p_elements1[] = { &(elemts1[0]), &(elemts1[1]) };
        data_t *p_elements2[] = { &(elemts2[0]) };
        node_t *head1 = NULL;
        node_t *head2 = NULL;
        node_t *res;
        head1 = create_list(p_elements1, 2);
        head2 = create_list(p_elements2, 1);
        res = sorted_merge(&head1, &head2, cmp_year);
        node_t *tmp = res;
        data_t *cur;
        int cmp = 0;
        int i = 0;
        for (; res != NULL && cmp == 0; res = res->next, i++)
        {
            cur = res->data;
            cmp = cmp_elem(cur, &(result[i]));
        }
        printf("Correct work with merging 2-element list with 1-element list : %s\n", (cmp == 0 && i == 3) ? "YES" : "NO");
        free_list(tmp);
    }
    {
        data_t elemts1[] = { { "Great Britain", "London", 50 }, { "Spain", "Madrid", 932 } };
        data_t elemts2[] = { { "Country", "Capital", 12 } };
        data_t result[] = { { "Country", "Capital", 12 }, { "Great Britain", "London", 50 }, { "Spain", "Madrid", 932 } };
        data_t *p_elements1[] = { &(elemts1[0]), &(elemts1[1]) };
        data_t *p_elements2[] = { &(elemts2[0]) };
        node_t *head1 = NULL;
        node_t *head2 = NULL;
        node_t *res;
        head1 = create_list(p_elements1, 2);
        head2 = create_list(p_elements2, 1);
        res = sorted_merge(&head1, &head2, cmp_year);
        node_t *tmp = res;
        data_t *cur;
        int cmp = 0;
        int i = 0;
        for (; res != NULL && cmp == 0; res = res->next, i++)
        {
            cur = res->data;
            cmp = cmp_elem(cur, &(result[i]));
        }
        printf("Correct work with merging 2-element list with 1-element list : %s\n", (cmp == 0 && i == 3) ? "YES" : "NO");
        free_list(tmp);
    }
    {
        data_t elemts1[] = { { "Great Britain", "London", 50 }, { "Spain", "Madrid", 932 } };
        data_t elemts2[] = { { "Country", "Capital", 70 } };
        data_t result[] = { { "Great Britain", "London", 50 }, { "Country", "Capital", 70 }, { "Spain", "Madrid", 932 } };
        data_t *p_elements1[] = { &(elemts1[0]), &(elemts1[1]) };
        data_t *p_elements2[] = { &(elemts2[0]) };
        node_t *head1 = NULL;
        node_t *head2 = NULL;
        node_t *res;
        head1 = create_list(p_elements1, 2);
        head2 = create_list(p_elements2, 1);
        res = sorted_merge(&head1, &head2, cmp_year);
        node_t *tmp = res;
        data_t *cur;
        int cmp = 0;
        int i = 0;
        for (; res != NULL && cmp == 0; res = res->next, i++)
        {
            cur = res->data;
            cmp = cmp_elem(cur, &(result[i]));
        }
        printf("Correct work with merging 2-element list with 1-element list : %s\n", (cmp == 0 && i == 3) ? "YES" : "NO");
        free_list(tmp);
    }
    {
        data_t elemts1[] = { { "Great Britain", "London", 50 }, { "Spain", "Madrid", 932 }, { "Japan", "Tokyo", 1497 } };
        data_t elemts2[] = { { "Country", "Capital", 70 } };
        data_t result[] = { { "Great Britain", "London", 50 }, { "Country", "Capital", 70 }, { "Spain", "Madrid", 932 }, { "Japan", "Tokyo", 1497 } };
        data_t *p_elements1[] = { &(elemts1[0]), &(elemts1[1]), &(elemts1[2]) };
        data_t *p_elements2[] = { &(elemts2[0]) };
        node_t *head1 = NULL;
        node_t *head2 = NULL;
        node_t *res;
        head1 = create_list(p_elements1, 3);
        head2 = create_list(p_elements2, 1);
        res = sorted_merge(&head1, &head2, cmp_year);
        node_t *tmp = res;
        data_t *cur;
        int cmp = 0;
        int i = 0;
        for (; res != NULL && cmp == 0; res = res->next, i++)
        {
            cur = res->data;
            cmp = cmp_elem(cur, &(result[i]));
        }
        printf("Correct work with merging 3-element list with 1-element list : %s\n", (cmp == 0 && i == 4) ? "YES" : "NO");
        free_list(tmp);
    }
    {
        data_t elemts2[] = { { "Great Britain", "London", 50 }, { "Spain", "Madrid", 932 }, { "Japan", "Tokyo", 1497 } };
        data_t elemts1[] = { { "Country", "Capital", 70 } };
        data_t result[] = { { "Great Britain", "London", 50 }, { "Country", "Capital", 70 }, { "Spain", "Madrid", 932 }, { "Japan", "Tokyo", 1497 } };
        data_t *p_elements2[] = { &(elemts2[0]), &(elemts2[1]), &(elemts2[2]) };
        data_t *p_elements1[] = { &(elemts1[0]) };
        node_t *head1 = NULL;
        node_t *head2 = NULL;
        node_t *res;
        head1 = create_list(p_elements1, 1);
        head2 = create_list(p_elements2, 3);
        res = sorted_merge(&head1, &head2, cmp_year);
        node_t *tmp = res;
        data_t *cur;
        int cmp = 0;
        int i = 0;
        for (; res != NULL && cmp == 0; res = res->next, i++)
        {
            cur = res->data;
            cmp = cmp_elem(cur, &(result[i]));
        }
        printf("Correct work with merging 1-element list with 3-element list : %s\n\n", (cmp == 0 && i == 4) ? "YES" : "NO");
        free_list(tmp);
    }
    {
        data_t elemts2[] = { { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 }, { "Spain", "Madrid", 932 } };
        data_t elemts1[] = { { "Country", "Capital", 70 } };
        data_t result[] = { { "Country", "Capital", 70 }, { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 }, { "Spain", "Madrid", 932 } };
        data_t *p_elements2[] = { &(elemts2[0]), &(elemts2[1]), &(elemts2[2]) };
        data_t *p_elements1[] = { &(elemts1[0]) };
        node_t *head1 = NULL;
        node_t *head2 = NULL;
        node_t *res;
        head1 = create_list(p_elements1, 1);
        head2 = create_list(p_elements2, 3);
        res = sorted_merge(&head1, &head2, cmp_country);
        node_t *tmp = res;
        data_t *cur;
        int cmp = 0;
        int i = 0;
        for (; res != NULL && cmp == 0; res = res->next, i++)
        {
            cur = res->data;
            cmp = cmp_elem(cur, &(result[i]));
        }
        printf("Correct work with merging 1-element list with 3-element list : %s\n\n", (cmp == 0 && i == 4) ? "YES" : "NO");
        free_list(tmp);
    }
}
/**
 * @brief create_list_elem_double Функция создания элемента списка с данными типа double.
 * @param info [in] - указатель на данные.
 * @return Возвращает указатель на новый элемент списка.
 */
node_t *create_list_elem_double(double *info)
{
    node_t *elem = malloc(sizeof(node_t));
    if (elem)
    {
        elem->data = info;
        elem->next = NULL;
    }
    return elem;
}
/**
 * @brief create_list_double Функция создает список элементов с данными типа double;
 * @param array_struct [in] - массив указателей на double
 * @param n [in] - размерность массива.
 * @return Возвращает указатель на начало списка.
 */
node_t *create_list_double(double *array_struct[], int n)
{
    node_t *head = NULL;
    node_t *cur;
    for (int i = 0; i < n; i++)
    {
        cur = create_list_elem_double(array_struct[i]);
        if (cur)
        {
            head = add_list_elem(head, cur);
        }
        else
            free_list(head);
    }
    return head;
}

/**
 * @brief test_sort Функция тестирования сортировки.
 */
void test_sort(void)
{
    printf("Tests for 'sort()':\n");
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 }, { "Russia", "Moscow", 1147 } };
        data_t result[] = { { "Great Britain", "London", 50 }, { "Spain", "Madrid", 932 }, { "Russia", "Moscow", 1147 } , { "Japan", "Tokyo", 1497 } };
        data_t *p_elements[] = { &(elemts[0]), &(elemts[1]), &(elemts[2]), &(elemts[3]) };
        node_t *head = NULL;
        head = create_list(p_elements, 4);
        head = sort(head, cmp_year);
        node_t *tmp = head;
        int cmp = 0;
        data_t *cur;
        for (int i = 0; head != NULL && cmp == 0; head = head->next, i++)
        {
            cur = head->data;
            cmp = cmp_elem(cur, &(result[i]));
        }
        printf("Correct work with sorting 4-element list by year: %s\n", (cmp == 0) ? "YES" : "NO");
        free_list(tmp);
    }
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 }, { "Russia", "Moscow", 1147 } };
        data_t result[] = { { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 }, { "Russia", "Moscow", 1147 }, { "Spain", "Madrid", 932 } };
        data_t *p_elements[] = { &(elemts[0]), &(elemts[1]), &(elemts[2]), &(elemts[3]) };
        node_t *head = NULL;
        head = create_list(p_elements, 4);
        head = sort(head, cmp_country);
        node_t *tmp = head;
        int cmp = 0;
        data_t *cur;
        for (int i = 0; head != NULL; head = head->next, i++)
        {
            cur = head->data;
            cmp = cmp_elem(cur, &(result[i]));
        }
        printf("Correct work with sorting 4-element list by country (in alphabetical order): %s\n", (cmp == 0) ? "YES" : "NO");
        free_list(tmp);
    }
    {
        data_t elemts[] = { { "Spain", "Madrid", 932 }, { "Great Britain", "London", 50 }, { "Japan", "Tokyo", 1497 }, { "Russia", "Moscow", 1147 } };
        data_t result[] = { { "Great Britain", "London", 50 }, { "Spain", "Madrid", 932 }, { "Russia", "Moscow", 1147 }, { "Japan", "Tokyo", 1497 } };
        data_t *p_elements[] = { &(elemts[0]), &(elemts[1]), &(elemts[2]), &(elemts[3]) };
        node_t *head = NULL;
        head = create_list(p_elements, 4);
        head = sort(head, cmp_capital);
        node_t *tmp = head;
        int cmp = 0;
        data_t *cur;
        for (int i = 0; head != NULL; head = head->next, i++)
        {
            cur = head->data;
            cmp = cmp_elem(cur, &(result[i]));
        }
        printf("Correct work with sorting 4-element list by capital (in alphabetical order): %s\n", (cmp == 0) ? "YES" : "NO");
        free_list(tmp);
    }
    {
        double elemts[] = { 0.02, 2.5, 10.7, -9.3, 3.2, 0.11, 1.0 };
        double result[] = { -9.3, 0.02, 0.11, 1.0, 2.5, 3.2, 10.7 };
        double *p_elements[] = { &(elemts[0]), &(elemts[1]), &(elemts[2]), &(elemts[3]),  &(elemts[4]),  &(elemts[5]),  &(elemts[6]) };
        node_t *head = NULL;
        head = create_list_double(p_elements, 7);
        head = sort(head, cmp_double_num);
        node_t *tmp = head;
        int cmp = 0;
        double *cur;
        for (int i = 0; head != NULL; head = head->next, i++)
        {
            cur = head->data;
            cmp = cmp_elem_double(cur, &(result[i]));
        }
        printf("Correct work with sorting 7-element list where data is a number of type 'double': %s\n", (cmp == 0) ? "YES" : "NO");
        free_list(tmp);
    }
}

int main(void)
{
    test_count_line();
    test_create_struct();
    test_read_data();
    test_read_file();
    test_create_list_elem();
    test_add_list_elem();
    test_create_list();
    test_cmp_country();
    test_cmp_year();
    test_find();
    test_insert();
    test_reverse();
    test_front_back_split();
    test_sorted_merge();
    test_sort();
    return OK;
}
