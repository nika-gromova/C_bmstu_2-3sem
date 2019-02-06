#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "io.h"
#include "my_struct.h"
#include "my_list.h"

int count_list_elements(node_car *head)
{
    int count = 0;
    for (; head; head = head->next, count++)
        ;
    return count;
}

int count_list_berkeley(struct list_head *head)
{
    int count = 0;
    struct list_head *iter;
    list_for_each(iter, head)
    {
        count++;
    }
    return count;
}

int cmp_elem(node_car *elem, int id, const char *model, const char *country, double price, int period)
{
    if (!elem)
        return 1;
    if (elem->id == id && strcmp(elem->model, model) == 0 && strcmp(elem->country, country) == 0 && IS_EQUAL(elem->price, price) && elem->year == period)
        return 0;
    return 1;
}

int cmp_arrays(int *arr1, int n1, int *arr2, int n2)
{
    if (n1 != n2)
        return 1;
    for (int i = 0; i < n1; i++)
        if (arr1[i] != arr2[i])
            return 1;
    return 0;
}
void list_to_array(int *array, int n, node_car *head)
{
    for (int i = 0; i < n && head; i++)
    {
        array[i] = head->id;
        head = head->next;
    }
}

void sort_list_to_array(int *array, int n, struct list_head *head, int index)
{
    node_car *tmp;
    struct list_head *iter;
    int k = 0;
    list_for_each(iter, head)
    {
        tmp = list_entry(iter, node_car, sort[index]);
        if (k < n)
        {
            array[k] = tmp->id;
            k++;
        }
    }
}

void filter_list_to_array(int *array, int n, struct list_head *head, int index)
{
    node_car *tmp;
    struct list_head *iter;
    int k = 0;
    list_for_each(iter, head)
    {
        tmp = list_entry(iter, node_car, filter[index]);
        if (k < n)
        {
            array[k] = tmp->id;
            k++;
        }
    }
}

void test_delete_spaces(void)
{
    printf("Tests for deleting space in the beggining and at the end of the string:\n");
    {
        char *in = "a";
        char out[20];
        char *check = "a";
        delete_spaces(in, out);
        printf("Correct work with 'a': %s\n", (strcmp(check, out) == 0) ? "YES" : "NO");
    }
    {
        char *in = " a";
        char out[20];
        char *check = "a";
        delete_spaces(in, out);
        printf("Correct work with ' a': %s\n", (strcmp(check, out) == 0) ? "YES" : "NO");
    }
    {
        char *in = " a ";
        char out[20];
        char *check = "a";
        delete_spaces(in, out);
        printf("Correct work with ' a ': %s\n", (strcmp(check, out) == 0) ? "YES" : "NO");
    }
    {
        char *in = "  a ";
        char out[20];
        char *check = "a";
        delete_spaces(in, out);
        printf("Correct work with '  a ': %s\n", (strcmp(check, out) == 0) ? "YES" : "NO");
    }
    {
        char *in = "a  ";
        char out[20];
        char *check = "a";
        delete_spaces(in, out);
        printf("%s\n", out);
        printf("Correct work with 'a  ': %s\n", (strcmp(check, out) == 0) ? "YES" : "NO");
    }
    {
        char *in = "a  a";
        char out[20];
        char *check = "a  a";
        delete_spaces(in, out);
        printf("Correct work with 'a  a': %s\n", (strcmp(check, out) == 0) ? "YES" : "NO");
    }
    {
        char *in = "    a  a  ";
        char out[20];
        char *check = "a  a";
        delete_spaces(in, out);
        printf("Correct work with '    a  a  ': %s\n\n", (strcmp(check, out) == 0) ? "YES" : "NO");
    }
    {
        char *in = "       ";
        char out[20];
        char *check = "";
        delete_spaces(in, out);
        printf("Correct work with '       ': %s\n\n", (strcmp(check, out) == 0) ? "YES" : "NO");
    }
}

void test_parse_line(void)
{
    printf("Tests for parsing line and putting data to information fields:\n");
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;b;0.5;1";
            char *check_1 = "a";
            char *check_2 = "b";
            double check_3 = 0.5;
            int check_4 = 1;
            int rc = parse_line(str, cur);
            printf("Correct work with parsing correct line: %s\n", (rc == OK && (strcmp(cur->model, check_1) == 0) && \
                                                                    (strcmp(cur->country, check_2) == 0) &&\
                                                                    (IS_EQUAL(cur->price, check_3)) && (cur->year == check_4)) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char *str = NULL;
            int rc = parse_line(str, cur);
            printf("Correct work with parsing empty line: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = " ";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line without ';': %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line with 1 element: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;a";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line with 2 element: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;a;";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line with 2 element: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;a;a";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line with 2 element: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;a;12a;1";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line with invalid 3 element: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;a;12.3;g";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line with invalid 4 element: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;a;12.3;-5";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line with invalid 4 element: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }

    {
        node_car *cur = malloc(sizeof(node_car));
        if (cur)
        {
            char str[] = "a;a;12.3;0";
            int rc = parse_line(str, cur);
            printf("Correct work with parsing line with invalid 4 element: %s\n\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
        }
        free(cur);
    }
}

void test_add_delete_list(void)
{
    printf("Tests for adding and deleting from ordinary list:\n");
    {
        int rc;
        node_car *head = NULL;
        node_car *elem = create_list_elem();
        char str1[] = "a;b;2;3";
        char str2[] = "c;d;4;5";
        if (elem)
        {
            rc = parse_line(str1, elem);
            if (rc == OK)
            {
                head = push_back(head, elem);
                printf("Correct work with adding element to an empty list: ");
                if (cmp_elem(head, 1, "a", "b", 2, 3) == 0)
                    printf("YES\n");
                else
                    printf("NO\n");
            }
            elem = create_list_elem();
            if (elem)
            {
                rc = parse_line(str2, elem);
                if (rc == OK)
                {
                    head = push_back(head, elem);
                    printf("Correct work with adding element to not empty list: ");
                    if (head->next)
                    {
                        if (cmp_elem(head->next, 2, "c", "d", 4, 5) == 0)
                            printf("YES\n");
                        else
                            printf("NO\n");
                    }
                    else
                        printf("NO");
                    printf("Correct work with deleting 1 element from 2-elemnt list: ");
                    head = delete_element(head, 1, &rc);
                    if (rc == 1)
                    {
                        if (cmp_elem(head, 2, "c", "d", 4, 5) == 0)
                            printf("YES\n");
                        else
                            printf("NO\n");
                    }
                    else
                        printf("NO\n");
                    head = delete_element(head, 3, &rc);
                    printf("Correct work with deleting not existing element: %s\n", (rc == 2) ? "YES" : "NO");
                    head = delete_element(head, 1, &rc);
                    printf("Correct work with deleting already deleted element: %d %s\n", rc, (rc == 2) ? "YES" : "NO");
                    head = delete_element(head, 2, &rc);
                    printf("Correct work with deleting 1 element from 1-element list:%s\n", (rc == 1 && head == NULL) ? "YES" : "NO");
                    head = delete_element(head, 1, &rc);
                    printf("Correct work with deleting element from empty array: %s\n", (rc ==  0) ? "YES" : "NO");
                }
            }
        }
        delete_list(head);
    }
    printf("\n");
}

void test_add_delete_berkeley(void)
{
    printf("Tests for adding and deleting from berkeley list:\n");
    {
        node_car *head = NULL;
        node_car *elem = create_list_elem();
        node_car *cur = NULL;
        struct list_head *iter;
        heads_index_filter heads_berkeley;
        INIT_LIST_HEAD(&(heads_berkeley.sort_model));
        INIT_LIST_HEAD(&(heads_berkeley.sort_price));
        INIT_LIST_HEAD(&(heads_berkeley.sort_price_and_guarantee));
        INIT_LIST_HEAD(&(heads_berkeley.filter_country));
        INIT_LIST_HEAD(&(heads_berkeley.filter_guarantee));
        char str1[] = "A;D;1.1;6";
        char str2[] = "C;B;1.1;4";
        int cmp1, cmp2;
        int cmp3;
        if (elem)
        {
            parse_line(str1, elem);
            add_lo_list(&(heads_berkeley), elem, &head);
            elem = create_list_elem();
            if (elem)
            {
                parse_line(str2, elem);
                add_lo_list(&(heads_berkeley), elem, &head);
                iter = heads_berkeley.sort_model.next;
                cur = list_entry(iter, node_car, sort[0]);
                cmp1 = cmp_elem(cur, 1, "A", "D", 1.1, 6);
                cmp2 = cmp_elem(cur->next, 2, "C", "B", 1.1, 4);
                if (cmp1 == 0 && cmp2 == 0)
                {
                    iter = heads_berkeley.sort_price.next;
                    cur = list_entry(iter, node_car, sort[1]);
                    cmp1 = cmp_elem(cur, 1, "A", "D", 1.1, 6);
                    cmp2 = cmp_elem(cur->next, 2, "C", "B", 1.1, 4);
                    if (cmp1 == 0 && cmp2 == 0)
                    {
                        iter = heads_berkeley.sort_price_and_guarantee.next;
                        cur = list_entry(iter, node_car, sort[2]);
                        cmp1 = cmp_elem(cur, 2, "C", "B", 1.1, 4);
                        cur = list_entry(iter->next, node_car, sort[2]);
                        cmp2 = cmp_elem(cur, 1, "A", "D", 1.1, 6);
                    }
                }
                printf("correct work with adding element to sort lists: %s\n", (cmp1 == 0 && cmp2 == 0) ? "YES" : "NO");
                cmp3 = list_empty(&(heads_berkeley.filter_country));
                if (cmp3 == 1)
                {
                    iter = heads_berkeley.filter_guarantee.next;
                    cur = list_entry(iter, node_car, filter[1]);
                    cmp1 = cmp_elem(cur, 1, "A", "D", 1.1, 6);
                    cmp2 = cmp_elem(cur->next, 2, "C", "B", 1.1, 4);
                }
                printf("correct work with adding element to filter lists: %s\n", (cmp3 == 1 && cmp1 == 0 && cmp2 == 0) ? "YES" : "NO");
                delete_berkeley(head->next);
                iter = heads_berkeley.sort_model.next;
                cur = list_entry(iter, node_car, sort[0]);
                cmp1 = cmp_elem(cur, 1, "A", "D", 1.1, 6);
                if (cmp1 == 0)
                {
                    iter = heads_berkeley.sort_price.next;
                    cur = list_entry(iter, node_car, sort[1]);
                    cmp1 = cmp_elem(cur, 1, "A", "D", 1.1, 6);
                    if (cmp1 == 0)
                    {
                        iter = heads_berkeley.sort_price_and_guarantee.next;
                        cur = list_entry(iter, node_car, sort[2]);
                        cmp1 = cmp_elem(cur, 1, "A", "D", 1.1, 6);
                    }
                }
                printf("Correct work with deleting element from sort lists: %s\n", (cmp1 == 0) ? "YES" : "NO");
                cmp3 = list_empty(&(heads_berkeley.filter_country));
                if (cmp3 == 1)
                {
                    iter = heads_berkeley.filter_guarantee.next;
                    cur = list_entry(iter, node_car, filter[1]);
                    cmp1 = cmp_elem(cur, 1, "A", "D", 1.1, 6);
                }
                printf("Correct work with deleting element from filter lists: %s\n", (cmp3 == 1 && cmp1 == 0) ? "YES" : "NO");
            }
        }
        delete_list(head);
    }
    printf("\n");
}

void test_read_file(void)
{
    printf("Tests for reading data from file:\n");
    heads_index_filter heads_berkeley;
    INIT_LIST_HEAD(&(heads_berkeley.sort_model));
    INIT_LIST_HEAD(&(heads_berkeley.sort_price));
    INIT_LIST_HEAD(&(heads_berkeley.sort_price_and_guarantee));
    INIT_LIST_HEAD(&(heads_berkeley.filter_country));
    INIT_LIST_HEAD(&(heads_berkeley.filter_guarantee));
    {
        char *file = "in.txt";
        node_car *head = NULL;
        int rc = read_file(file, &head, &heads_berkeley);
        printf("Correct work with null file: %s\n", (rc == OPEN_FILE_ERROR) ? "YES" : "NO");
    }
    {
        char *file = "in_1.txt";
        node_car *head = NULL;
        int rc = read_file(file, &head, &heads_berkeley);
        printf("Correct work with empty file: %s\n", (rc == EMPTY_FILE_ERROR) ? "YES" : "NO");
    }
    {
        char *file = "in_3.txt";
        node_car *head = NULL;
        int rc = read_file(file, &head, &heads_berkeley);
        printf("Correct work with spaces: %s\n", (rc == MEMORY_ERROR) ? "YES" : "NO");
    }
    {
        char *file = "in_4.txt";
        node_car *head = NULL;
        int rc = read_file(file, &head, &heads_berkeley);
        printf("Correct work with incorrect data in file: %s\n", (rc == READ_FILE_ERROR) ? "YES" : "NO");
    }
    {
        char *file = "in_2.txt";
        node_car *head = NULL;
        int rc = read_file(file, &head, &heads_berkeley);
        int cmp;
        int check[] = { 1, 2, 3, 4 };
        int n_check = sizeof(check) / sizeof(check[0]);
        int sort_1[] = { 1, 4, 3, 2 };
        int n_sort_1 = sizeof(sort_1) / sizeof(sort_1[0]);
        int sort_2[] = { 2, 1, 3, 4 };
        int n_sort_2 = sizeof(sort_2) / sizeof(sort_2[0]);
        int sort_3[] = { 2, 1, 4, 3 };
        int n_sort_3 = sizeof(sort_3) / sizeof(sort_3[0]);
        int filter_1[] = { 3, 4 };
        int n_filter_1 = sizeof(filter_1) / sizeof(filter_1[0]);
        int filter_2[] = { 1 };
        int n_filter_2 = sizeof(filter_2) / sizeof(filter_2[0]);

        int n = count_list_berkeley(&(heads_berkeley.sort_model));
        int sort[n];

        int f1 = count_list_berkeley(&(heads_berkeley.filter_country));
        int filt1[f1];
        int f2 = count_list_berkeley(&(heads_berkeley.filter_guarantee));
        int filt2[f2];

        int n_total = count_list_elements(head);
        int total[n_total];
        list_to_array(total, n_total, head);
        cmp = cmp_arrays(check, n_check, total, n_total);
        if (cmp == 0)
        {
            sort_list_to_array(sort, n, &(heads_berkeley.sort_model), 0);
            cmp = cmp_arrays(sort_1, n_sort_1, sort, n);
            if (cmp == 0)
            {
                sort_list_to_array(sort, n, &(heads_berkeley.sort_price), 1);
                cmp = cmp_arrays(sort_2, n_sort_2, sort, n);
                if (count_list_berkeley(&(heads_berkeley.sort_price)) != n)
                    cmp = 1;
                if (cmp == 0)
                {
                    sort_list_to_array(sort, n, &(heads_berkeley.sort_price_and_guarantee), 2);
                    cmp = cmp_arrays(sort_3, n_sort_3, sort, n);
                    if (count_list_berkeley(&(heads_berkeley.sort_price_and_guarantee)) != n)
                        cmp = 1;
                    if (cmp == 0)
                    {
                        filter_list_to_array(filt1, f1, &(heads_berkeley.filter_country), 0);
                        cmp = cmp_arrays(filter_1, n_filter_1, filt1, f1);
                        if (cmp == 0)
                        {
                            filter_list_to_array(filt2, f2, &(heads_berkeley.filter_guarantee), 1);
                            cmp = cmp_arrays(filter_2, n_filter_2, filt2, f2);
                        }
                    }
                }
            }
        }
        printf("Correct work with no empty file: %s\n", (rc == OK && cmp == 0) ? "YES" : "NO");
        delete_list(head);
    }
    {
        char *file = "in_5.txt"; // уже отсортированы по цене
        node_car *head = NULL;
        INIT_LIST_HEAD(&(heads_berkeley.sort_model));
        INIT_LIST_HEAD(&(heads_berkeley.sort_price));
        INIT_LIST_HEAD(&(heads_berkeley.sort_price_and_guarantee));
        INIT_LIST_HEAD(&(heads_berkeley.filter_country));
        INIT_LIST_HEAD(&(heads_berkeley.filter_guarantee));
        int rc = read_file(file, &head, &heads_berkeley);

        int cmp;
        int check[] = { 1, 2, 3, 4 };
        int n_check = sizeof(check) / sizeof(check[0]);
        int sort_1[] = { 2, 4, 3, 1 };
        int n_sort_1 = sizeof(sort_1) / sizeof(sort_1[0]);
        int sort_2[] = { 1, 2, 3, 4 };
        int n_sort_2 = sizeof(sort_2) / sizeof(sort_2[0]);
        int sort_3[] = { 1, 2, 3, 4 };
        int n_sort_3 = sizeof(sort_3) / sizeof(sort_3[0]);
        int filter_1[] = { 4 };
        int n_filter_1 = sizeof(filter_1) / sizeof(filter_1[0]);
        int filter_2[] = { 2 };
        int n_filter_2 = sizeof(filter_2) / sizeof(filter_2[0]);

        int n = count_list_berkeley(&(heads_berkeley.sort_model));
        int sort[n];

        int f1 = count_list_berkeley(&(heads_berkeley.filter_country));
        int filt1[f1];
        int f2 = count_list_berkeley(&(heads_berkeley.filter_guarantee));
        int filt2[f2];

        int n_total = count_list_elements(head);
        int total[n_total];
        list_to_array(total, n_total, head);
        cmp = cmp_arrays(check, n_check, total, n_total);
        if (cmp == 0)
        {
            sort_list_to_array(sort, n, &(heads_berkeley.sort_model), 0);
            cmp = cmp_arrays(sort_1, n_sort_1, sort, n);
            if (cmp == 0)
            {
                sort_list_to_array(sort, n, &(heads_berkeley.sort_price), 1);
                cmp = cmp_arrays(sort_2, n_sort_2, sort, n);
                if (count_list_berkeley(&(heads_berkeley.sort_price)) != n)
                    cmp = 1;
                if (cmp == 0)
                {
                    sort_list_to_array(sort, n, &(heads_berkeley.sort_price_and_guarantee), 2);
                    cmp = cmp_arrays(sort_3, n_sort_3, sort, n);
                    if (count_list_berkeley(&(heads_berkeley.sort_price_and_guarantee)) != n)
                        cmp = 1;
                    if (cmp == 0)
                    {
                        filter_list_to_array(filt1, f1, &(heads_berkeley.filter_country), 0);
                        cmp = cmp_arrays(filter_1, n_filter_1, filt1, f1);
                        if (cmp == 0)
                        {
                            filter_list_to_array(filt2, f2, &(heads_berkeley.filter_guarantee), 1);
                            cmp = cmp_arrays(filter_2, n_filter_2, filt2, f2);
                        }
                    }
                }
            }
        }
        printf("Correct work with no empty file (sorted price): %s\n", (rc == OK && cmp == 0) ? "YES" : "NO");
        delete_list(head);
    }
    {
        char *file = "in_6.txt"; // уже отсортированы по модели
        node_car *head = NULL;
        INIT_LIST_HEAD(&(heads_berkeley.sort_model));
        INIT_LIST_HEAD(&(heads_berkeley.sort_price));
        INIT_LIST_HEAD(&(heads_berkeley.sort_price_and_guarantee));
        INIT_LIST_HEAD(&(heads_berkeley.filter_country));
        INIT_LIST_HEAD(&(heads_berkeley.filter_guarantee));
        int rc = read_file(file, &head, &heads_berkeley);

        int cmp;
        int check[] = { 1, 2, 3, 4 };
        int n_check = sizeof(check) / sizeof(check[0]);
        int sort_1[] = { 1, 2, 3, 4 };
        int n_sort_1 = sizeof(sort_1) / sizeof(sort_1[0]);
        int sort_2[] = { 4, 1, 3, 2 };
        int n_sort_2 = sizeof(sort_2) / sizeof(sort_2[0]);
        int sort_3[] = { 4, 1, 3, 2 };
        int n_sort_3 = sizeof(sort_3) / sizeof(sort_3[0]);
        int filter_1[] = { 2 };
        int n_filter_1 = sizeof(filter_1) / sizeof(filter_1[0]);
        int filter_2[] = { 1 };
        int n_filter_2 = sizeof(filter_2) / sizeof(filter_2[0]);

        int n = count_list_berkeley(&(heads_berkeley.sort_model));
        int sort[n];

        int f1 = count_list_berkeley(&(heads_berkeley.filter_country));
        int filt1[f1];
        int f2 = count_list_berkeley(&(heads_berkeley.filter_guarantee));
        int filt2[f2];

        int n_total = count_list_elements(head);
        int total[n_total];
        list_to_array(total, n_total, head);
        cmp = cmp_arrays(check, n_check, total, n_total);
        if (cmp == 0)
        {
            sort_list_to_array(sort, n, &(heads_berkeley.sort_model), 0);
            cmp = cmp_arrays(sort_1, n_sort_1, sort, n);
            if (cmp == 0)
            {
                sort_list_to_array(sort, n, &(heads_berkeley.sort_price), 1);
                cmp = cmp_arrays(sort_2, n_sort_2, sort, n);
                if (count_list_berkeley(&(heads_berkeley.sort_price)) != n)
                    cmp = 1;
                if (cmp == 0)
                {
                    sort_list_to_array(sort, n, &(heads_berkeley.sort_price_and_guarantee), 2);
                    cmp = cmp_arrays(sort_3, n_sort_3, sort, n);
                    if (count_list_berkeley(&(heads_berkeley.sort_price_and_guarantee)) != n)
                        cmp = 1;
                    if (cmp == 0)
                    {
                        filter_list_to_array(filt1, f1, &(heads_berkeley.filter_country), 0);
                        cmp = cmp_arrays(filter_1, n_filter_1, filt1, f1);
                        if (cmp == 0)
                        {
                            filter_list_to_array(filt2, f2, &(heads_berkeley.filter_guarantee), 1);
                            cmp = cmp_arrays(filter_2, n_filter_2, filt2, f2);
                        }
                    }
                }
            }
        }
        printf("Correct work with no empty file (sorted model): %s\n", (rc == OK && cmp == 0) ? "YES" : "NO");
        delete_list(head);
    }
    {
        char *file = "in_7.txt"; // одинаковые цены
        node_car *head = NULL;
        INIT_LIST_HEAD(&(heads_berkeley.sort_model));
        INIT_LIST_HEAD(&(heads_berkeley.sort_price));
        INIT_LIST_HEAD(&(heads_berkeley.sort_price_and_guarantee));
        INIT_LIST_HEAD(&(heads_berkeley.filter_country));
        INIT_LIST_HEAD(&(heads_berkeley.filter_guarantee));
        int rc = read_file(file, &head, &heads_berkeley);

        int cmp;
        int check[] = { 1, 2, 3, 4 };
        int n_check = sizeof(check) / sizeof(check[0]);
        int sort_1[] = { 1, 2, 3, 4 };
        int n_sort_1 = sizeof(sort_1) / sizeof(sort_1[0]);
        int sort_2[] = { 1, 2, 3, 4 };
        int n_sort_2 = sizeof(sort_2) / sizeof(sort_2[0]);
        int sort_3[] = { 2, 4, 3, 1 };
        int n_sort_3 = sizeof(sort_3) / sizeof(sort_3[0]);
        int filter_1[] = { 2 };
        int n_filter_1 = sizeof(filter_1) / sizeof(filter_1[0]);
        int filter_2[] = { 1 };
        int n_filter_2 = sizeof(filter_2) / sizeof(filter_2[0]);

        int n = count_list_berkeley(&(heads_berkeley.sort_model));
        int sort[n];

        int f1 = count_list_berkeley(&(heads_berkeley.filter_country));
        int filt1[f1];
        int f2 = count_list_berkeley(&(heads_berkeley.filter_guarantee));
        int filt2[f2];

        int n_total = count_list_elements(head);
        int total[n_total];
        list_to_array(total, n_total, head);
        cmp = cmp_arrays(check, n_check, total, n_total);
        if (cmp == 0)
        {
            sort_list_to_array(sort, n, &(heads_berkeley.sort_model), 0);
            cmp = cmp_arrays(sort_1, n_sort_1, sort, n);
            if (cmp == 0)
            {
                sort_list_to_array(sort, n, &(heads_berkeley.sort_price), 1);
                cmp = cmp_arrays(sort_2, n_sort_2, sort, n);
                if (count_list_berkeley(&(heads_berkeley.sort_price)) != n)
                    cmp = 1;
                if (cmp == 0)
                {
                    sort_list_to_array(sort, n, &(heads_berkeley.sort_price_and_guarantee), 2);
                    cmp = cmp_arrays(sort_3, n_sort_3, sort, n);
                    if (count_list_berkeley(&(heads_berkeley.sort_price_and_guarantee)) != n)
                        cmp = 1;
                    if (cmp == 0)
                    {
                        filter_list_to_array(filt1, f1, &(heads_berkeley.filter_country), 0);
                        cmp = cmp_arrays(filter_1, n_filter_1, filt1, f1);
                        if (cmp == 0)
                        {
                            filter_list_to_array(filt2, f2, &(heads_berkeley.filter_guarantee), 1);
                            cmp = cmp_arrays(filter_2, n_filter_2, filt2, f2);
                        }
                    }
                }
            }
        }
        printf("Correct work with no empty file (equal price, sorting by guarantee): %s\n", (rc == OK && cmp == 0) ? "YES" : "NO");
        delete_list(head);
    }
    {
        char *file = "in_8.txt"; // все страны-производители - Германия
        node_car *head = NULL;
        INIT_LIST_HEAD(&(heads_berkeley.sort_model));
        INIT_LIST_HEAD(&(heads_berkeley.sort_price));
        INIT_LIST_HEAD(&(heads_berkeley.sort_price_and_guarantee));
        INIT_LIST_HEAD(&(heads_berkeley.filter_country));
        INIT_LIST_HEAD(&(heads_berkeley.filter_guarantee));
        int rc = read_file(file, &head, &heads_berkeley);

        int cmp;
        int check[] = { 1, 2, 3, 4 };
        int n_check = sizeof(check) / sizeof(check[0]);
        int sort_1[] = { 4, 1, 2, 3 };
        int n_sort_1 = sizeof(sort_1) / sizeof(sort_1[0]);
        int sort_2[] = { 3, 2, 4, 1 };
        int n_sort_2 = sizeof(sort_2) / sizeof(sort_2[0]);
        int sort_3[] = { 3, 2, 4, 1 };
        int n_sort_3 = sizeof(sort_3) / sizeof(sort_3[0]);
        int filter_1[] = { 1, 2, 3, 4 };
        int n_filter_1 = sizeof(filter_1) / sizeof(filter_1[0]);
        int filter_2[] = { 1 };
        int n_filter_2 = sizeof(filter_2) / sizeof(filter_2[0]);

        int n = count_list_berkeley(&(heads_berkeley.sort_model));
        int sort[n];

        int f1 = count_list_berkeley(&(heads_berkeley.filter_country));
        int filt1[f1];
        int f2 = count_list_berkeley(&(heads_berkeley.filter_guarantee));
        int filt2[f2];
        int n_total = count_list_elements(head);
        int total[n_total];
        list_to_array(total, n_total, head);
        cmp = cmp_arrays(check, n_check, total, n_total);
        if (cmp == 0)
        {
            sort_list_to_array(sort, n, &(heads_berkeley.sort_model), 0);
            cmp = cmp_arrays(sort_1, n_sort_1, sort, n);
            if (cmp == 0)
            {
                sort_list_to_array(sort, n, &(heads_berkeley.sort_price), 1);
                cmp = cmp_arrays(sort_2, n_sort_2, sort, n);
                if (count_list_berkeley(&(heads_berkeley.sort_price)) != n)
                    cmp = 1;
                if (cmp == 0)
                {
                    sort_list_to_array(sort, n, &(heads_berkeley.sort_price_and_guarantee), 2);
                    cmp = cmp_arrays(sort_3, n_sort_3, sort, n);
                    if (count_list_berkeley(&(heads_berkeley.sort_price_and_guarantee)) != n)
                        cmp = 1;
                    if (cmp == 0)
                    {
                        filter_list_to_array(filt1, f1, &(heads_berkeley.filter_country), 0);
                        cmp = cmp_arrays(filter_1, n_filter_1, filt1, f1);
                        if (cmp == 0)
                        {
                            filter_list_to_array(filt2, f2, &(heads_berkeley.filter_guarantee), 1);
                            cmp = cmp_arrays(filter_2, n_filter_2, filt2, f2);
                        }
                    }
                }
            }
        }
        printf("Correct work with no empty file (all countries of manufacture are 'Germeny'): %s\n", (rc == OK && cmp == 0) ? "YES" : "NO");
        delete_list(head);
    }
    {
        char *file = "in_9.txt"; // нет немецких машин
        node_car *head = NULL;
        INIT_LIST_HEAD(&(heads_berkeley.sort_model));
        INIT_LIST_HEAD(&(heads_berkeley.sort_price));
        INIT_LIST_HEAD(&(heads_berkeley.sort_price_and_guarantee));
        INIT_LIST_HEAD(&(heads_berkeley.filter_country));
        INIT_LIST_HEAD(&(heads_berkeley.filter_guarantee));
        int rc = read_file(file, &head, &heads_berkeley);

        int cmp;
        int check[] = { 1, 2, 3, 4 };
        int n_check = sizeof(check) / sizeof(check[0]);
        int sort_1[] = { 1, 3, 2, 4 };
        int n_sort_1 = sizeof(sort_1) / sizeof(sort_1[0]);
        int sort_2[] = { 3, 1, 2, 4 };
        int n_sort_2 = sizeof(sort_2) / sizeof(sort_2[0]);
        int sort_3[] = { 3, 1, 2, 4 };
        int n_sort_3 = sizeof(sort_3) / sizeof(sort_3[0]);
        int filter_1[] = { 1 };
        int n_filter_1 = 0;
        int filter_2[] = { 2, 3 };
        int n_filter_2 = sizeof(filter_2) / sizeof(filter_2[0]);

        int n = count_list_berkeley(&(heads_berkeley.sort_model));
        int sort[n];

        int f1 = count_list_berkeley(&(heads_berkeley.filter_country));
        int filt1[f1];
        int f2 = count_list_berkeley(&(heads_berkeley.filter_guarantee));
        int filt2[f2];
        int n_total = count_list_elements(head);
        int total[n_total];
        list_to_array(total, n_total, head);
        cmp = cmp_arrays(check, n_check, total, n_total);
        if (cmp == 0)
        {
            sort_list_to_array(sort, n, &(heads_berkeley.sort_model), 0);
            cmp = cmp_arrays(sort_1, n_sort_1, sort, n);
            if (cmp == 0)
            {
                sort_list_to_array(sort, n, &(heads_berkeley.sort_price), 1);
                cmp = cmp_arrays(sort_2, n_sort_2, sort, n);
                if (count_list_berkeley(&(heads_berkeley.sort_price)) != n)
                    cmp = 1;
                if (cmp == 0)
                {
                    sort_list_to_array(sort, n, &(heads_berkeley.sort_price_and_guarantee), 2);
                    cmp = cmp_arrays(sort_3, n_sort_3, sort, n);
                    if (count_list_berkeley(&(heads_berkeley.sort_price_and_guarantee)) != n)
                        cmp = 1;
                    if (cmp == 0)
                    {
                        filter_list_to_array(filt1, f1, &(heads_berkeley.filter_country), 0);
                        cmp = cmp_arrays(filter_1, n_filter_1, filt1, f1);
                        if (cmp == 0)
                        {
                            filter_list_to_array(filt2, f2, &(heads_berkeley.filter_guarantee), 1);
                            cmp = cmp_arrays(filter_2, n_filter_2, filt2, f2);
                        }
                    }
                }
            }
        }
        printf("Correct work with no empty file (none countries of manufacture are 'Germeny'): %s\n", (rc == OK && cmp == 0) ? "YES" : "NO");
        delete_list(head);
    }
    {
        char *file = "in_10.txt"; // у всех машин период гарантии >= 4
        node_car *head = NULL;
        INIT_LIST_HEAD(&(heads_berkeley.sort_model));
        INIT_LIST_HEAD(&(heads_berkeley.sort_price));
        INIT_LIST_HEAD(&(heads_berkeley.sort_price_and_guarantee));
        INIT_LIST_HEAD(&(heads_berkeley.filter_country));
        INIT_LIST_HEAD(&(heads_berkeley.filter_guarantee));
        int rc = read_file(file, &head, &heads_berkeley);

        int cmp;
        int check[] = { 1, 2, 3, 4 };
        int n_check = sizeof(check) / sizeof(check[0]);
        int sort_1[] = { 1, 3, 2, 4 };
        int n_sort_1 = sizeof(sort_1) / sizeof(sort_1[0]);
        int sort_2[] = { 3, 1, 2, 4 };
        int n_sort_2 = sizeof(sort_2) / sizeof(sort_2[0]);
        int sort_3[] = { 3, 1, 2, 4 };
        int n_sort_3 = sizeof(sort_3) / sizeof(sort_3[0]);
        int filter_1[] = { 1 };
        int n_filter_1 = 0;
        int filter_2[] = { 1, 2, 3, 4 };
        int n_filter_2 = sizeof(filter_2) / sizeof(filter_2[0]);

        int n = count_list_berkeley(&(heads_berkeley.sort_model));
        int sort[n];

        int f1 = count_list_berkeley(&(heads_berkeley.filter_country));
        int filt1[f1];
        int f2 = count_list_berkeley(&(heads_berkeley.filter_guarantee));
        int filt2[f2];
        int n_total = count_list_elements(head);
        int total[n_total];
        list_to_array(total, n_total, head);
        cmp = cmp_arrays(check, n_check, total, n_total);
        if (cmp == 0)
        {
            sort_list_to_array(sort, n, &(heads_berkeley.sort_model), 0);
            cmp = cmp_arrays(sort_1, n_sort_1, sort, n);
            if (cmp == 0)
            {
                sort_list_to_array(sort, n, &(heads_berkeley.sort_price), 1);
                cmp = cmp_arrays(sort_2, n_sort_2, sort, n);
                if (count_list_berkeley(&(heads_berkeley.sort_price)) != n)
                    cmp = 1;
                if (cmp == 0)
                {
                    sort_list_to_array(sort, n, &(heads_berkeley.sort_price_and_guarantee), 2);
                    cmp = cmp_arrays(sort_3, n_sort_3, sort, n);
                    if (count_list_berkeley(&(heads_berkeley.sort_price_and_guarantee)) != n)
                        cmp = 1;
                    if (cmp == 0)
                    {
                        filter_list_to_array(filt1, f1, &(heads_berkeley.filter_country), 0);
                        cmp = cmp_arrays(filter_1, n_filter_1, filt1, f1);
                        if (cmp == 0)
                        {
                            filter_list_to_array(filt2, f2, &(heads_berkeley.filter_guarantee), 1);
                            cmp = cmp_arrays(filter_2, n_filter_2, filt2, f2);
                        }
                    }
                }
            }
        }
        printf("Correct work with no empty file (all periods of guarantee are >= 4): %s\n", (rc == OK && cmp == 0) ? "YES" : "NO");
        delete_list(head);
    }
    {
        char *file = "in_11.txt"; // у всех машин период гарантии < 4
        node_car *head = NULL;
        INIT_LIST_HEAD(&(heads_berkeley.sort_model));
        INIT_LIST_HEAD(&(heads_berkeley.sort_price));
        INIT_LIST_HEAD(&(heads_berkeley.sort_price_and_guarantee));
        INIT_LIST_HEAD(&(heads_berkeley.filter_country));
        INIT_LIST_HEAD(&(heads_berkeley.filter_guarantee));
        int rc = read_file(file, &head, &heads_berkeley);

        int cmp;
        int check[] = { 1, 2, 3, 4 };
        int n_check = sizeof(check) / sizeof(check[0]);
        int sort_1[] = { 1, 3, 2, 4 };
        int n_sort_1 = sizeof(sort_1) / sizeof(sort_1[0]);
        int sort_2[] = { 3, 1, 2, 4 };
        int n_sort_2 = sizeof(sort_2) / sizeof(sort_2[0]);
        int sort_3[] = { 3, 1, 2, 4 };
        int n_sort_3 = sizeof(sort_3) / sizeof(sort_3[0]);
        int filter_1[] = { 1 };
        int n_filter_1 = 0;
        int filter_2[] = { 1 };
        int n_filter_2 = 0;

        int n = count_list_berkeley(&(heads_berkeley.sort_model));
        int sort[n];

        int f1 = count_list_berkeley(&(heads_berkeley.filter_country));
        int filt1[f1];
        int f2 = count_list_berkeley(&(heads_berkeley.filter_guarantee));
        int filt2[f2];
        int n_total = count_list_elements(head);
        int total[n_total];
        list_to_array(total, n_total, head);
        cmp = cmp_arrays(check, n_check, total, n_total);
        if (cmp == 0)
        {
            sort_list_to_array(sort, n, &(heads_berkeley.sort_model), 0);
            cmp = cmp_arrays(sort_1, n_sort_1, sort, n);
            if (cmp == 0)
            {
                sort_list_to_array(sort, n, &(heads_berkeley.sort_price), 1);
                cmp = cmp_arrays(sort_2, n_sort_2, sort, n);
                if (count_list_berkeley(&(heads_berkeley.sort_price)) != n)
                    cmp = 1;
                if (cmp == 0)
                {
                    sort_list_to_array(sort, n, &(heads_berkeley.sort_price_and_guarantee), 2);
                    cmp = cmp_arrays(sort_3, n_sort_3, sort, n);
                    if (count_list_berkeley(&(heads_berkeley.sort_price_and_guarantee)) != n)
                        cmp = 1;
                    if (cmp == 0)
                    {
                        filter_list_to_array(filt1, f1, &(heads_berkeley.filter_country), 0);
                        cmp = cmp_arrays(filter_1, n_filter_1, filt1, f1);
                        if (cmp == 0)
                        {
                            filter_list_to_array(filt2, f2, &(heads_berkeley.filter_guarantee), 1);
                            cmp = cmp_arrays(filter_2, n_filter_2, filt2, f2);
                        }
                    }
                }
            }
        }
        printf("Correct work with no empty file (all periods of guarantee are < 4): %s\n", (rc == OK && cmp == 0) ? "YES" : "NO");
        delete_list(head);
    }
}

int main(void)
{
    test_delete_spaces();
    test_parse_line();
    test_add_delete_list();
    test_add_delete_berkeley();
    test_read_file();
    return 0;
}
