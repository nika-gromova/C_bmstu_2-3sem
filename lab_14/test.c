#include <stdio.h>
#include <stdlib.h>

#include "set.h"
#include "defines.h"

void test_is_in_set(void)
{
    printf("Tests for checking is element in set:\n");
    {
        set_type my_set = create_set();
        double num = 2.4;
        int rc = is_in_set(my_set, num);
        printf("correct work for checking in empty set: %s\n", (rc == 0) ? "YES" : "NO");
        free_set(my_set);
    }
    {
        set_type my_set = create_set();
        double num = 2.4;
        int rc = set_add(my_set, num);
        if (rc == OK)
        {
            rc = is_in_set(my_set, num);
            printf("correct work for checking in 1-element set (found): %s\n", (rc == 1) ? "YES" : "NO");
        }
        free_set(my_set);
    }
    {
        set_type my_set = create_set();
        double num = 2.4;
        int rc = set_add(my_set, num);
        if (rc == OK)
        {
            rc = is_in_set(my_set, 2.0);
            printf("correct work for checking in 1-element set (not found): %s\n", (rc == 0) ? "YES" : "NO");
        }
        free_set(my_set);
    }
    {
        set_type my_set = create_set();
        double num = 2.4;
        int rc = set_add(my_set, num);
        if (rc == OK)
        {
            rc = set_add(my_set, 2.0);
            if (rc == OK)
            {
                rc = is_in_set(my_set, 2.0);
                printf("correct work for checking in 2-element set (found): %s\n", (rc == 1) ? "YES" : "NO");
            }
        }
        free_set(my_set);
    }
    {
        set_type my_set = create_set();
        double num = 2.4;
        int rc = set_add(my_set, num);
        if (rc == OK)
        {
            rc = set_add(my_set, 2.0);
            if (rc == OK)
            {
                rc = is_in_set(my_set, 2.3);
                printf("correct work for checking in 2-element set (not found): %s\n", (rc == 0) ? "YES" : "NO");
            }
        }
        free_set(my_set);
    }
    printf("\n");
}


void test_set_add_delete(void)
{
    printf("Tests for adding numbers to set:\n");
    {
        set_type my_set = create_set();
        int rc;
        double num = 3.5;
        double check[] = { 3.5 };
        int check_size = sizeof(check) / sizeof(check[0]);
        if (my_set)
        {
            rc = set_add(my_set, num);
            if (rc == OK)
            {
                printf("correct work for adding 1 element to an empty set: %s\n", (cmp_set_array(my_set, check, check_size) == 0) ? "YES" : "NO");
            }
            free_set(my_set);
        }
    }
    {
        set_type my_set = create_set();
        int rc = OK;
        double check[] = { 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5 };
        int check_size = sizeof(check) / sizeof(check[0]);
        if (my_set)
        {
            for (int i = 0; i < 10 && rc == OK; i++)
                rc = set_add(my_set, i + 0.5);
            if (rc == OK)
            {
                printf("correct work for adding 10 elements to an empty set: %s\n", (cmp_set_array(my_set, check, check_size) == 0) ? "YES" : "NO");
            }
            free_set(my_set);
        }
    }
    printf("Tests for deleting numbers from set:\n");
    {
        set_type my_set = create_set();
        int rc = OK;
        double num = 4.5;
        double check[] = { 0.5, 1.5, 2.5, 3.5, 5.5, 6.5, 7.5, 8.5, 9.5 };
        int check_size = sizeof(check) / sizeof(check[0]);
        if (my_set)
        {
            for (int i = 0; i < 10 && rc == OK; i++)
                rc = set_add(my_set, i + 0.5);
            if (rc == OK)
            {
                rc = set_delete_element(my_set, num);
                printf("correct work with deleting 1 element from 10-element set: %s\n", (rc && cmp_set_array(my_set, check, check_size) == 0) ? "YES" : "NO");
            }
            free_set(my_set);
        }
    }
    {
        set_type my_set = create_set();
        int rc = OK;
        double check[] = { 1 };
        int check_size = 0;
        if (my_set)
        {
            for (int i = 0; i < 10 && rc == OK; i++)
                rc = set_add(my_set, i + 0.5);
            if (rc == OK)
            {
                for (int i = 0; i < 10; i++)
                    rc = set_delete_element(my_set, i + 0.5);
                printf("correct work with deleting all elements from 10-element set: %s\n", (cmp_set_array(my_set, check, check_size) == 0) ? "YES" : "NO");
            }
            free_set(my_set);
        }
    }
    {
        set_type my_set = create_set();
        double check[] = { 1 };
        int check_size = 0;
        if (my_set)
        {
            int rc = set_add(my_set, 23.1);
            if (rc == OK)
            {
                set_delete_element(my_set, 23.1);
                printf("correct work with deleting 1 element a from 1-element set (a): %s\n", (cmp_set_array(my_set, check, check_size) == 0) ? "YES" : "NO");
            }
            free_set(my_set);
        }
    }
    {
        set_type my_set = create_set();
        double check[] = { 23.1 };
        int check_size = 1;
        if (my_set)
        {
            int rc = set_add(my_set, 23.1);
            if (rc == OK)
            {
                rc = set_delete_element(my_set, 23);
                printf("correct work with deleting 1 element a from 1-element set (b): %s\n\n", (rc == 0 && cmp_set_array(my_set, check, check_size) == 0) ? "YES" : "NO");
            }
            free_set(my_set);
        }
    }
}

void test_set_array(void)
{
    printf("Tests for operations on sets (like arrays):\n");
    {
        set_type A = create_set();
        set_type B = create_set();
        set_type result = create_set();
        double check_u[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int check_size_u = sizeof(check_u) / sizeof(check_u[0]);
        double check_i[] = { 1 };
        int check_size_i = 0;
        double check_d[] = { 0, 1, 2, 3, 4 };
        int check_size_d = sizeof(check_d) / sizeof(check_d[0]);
        double check_s[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int check_size_s = sizeof(check_s) / sizeof(check_s[0]);
        int rc = OK;
        if (A && B && result)
        {
            for (int i = 0; i < 5 && rc == OK; i++)
                rc = set_add(A, i);
            if (rc == OK)
            {
                for (int i = 5; i < 10 && rc == OK; i++)
                    rc = set_add(B, i);
                if (rc == OK)
                {
                    rc = set_union(A, B, result);
                    if (rc == OK)
                    {
                        printf("correct work with union of not null sets (both include): %s\n", (cmp_set_array(result, check_u, check_size_u) == 0) ? "YES" : "NO");
                        free_set(result);
                        result = create_set();
                        if (result)
                        {
                            rc = set_intersection(A, B, result);
                            if (rc == OK)
                            {
                                printf("correct work with untersection of not null sets (nothing in intersection): %s\n", (cmp_set_array(result, check_i, check_size_i) == 0) ? "YES" : "NO");
                                free_set(result);
                                result = create_set();
                                if (result)
                                {
                                    rc = set_difference(A, B, result);
                                    if (rc == OK)
                                    {
                                        printf("correct work with diffrence of not null sets: %s\n", (cmp_set_array(result, check_d, check_size_d) == 0) ? "YES" : "NO");
                                        free_set(result);
                                        result = create_set();
                                        if (result)
                                        {
                                            rc = set_sym_difference(A, B, result);
                                            if (rc == OK)
                                            {
                                                printf("correct work with semetric diffrence of not null sets (nothing in intersection): %s\n\n", (cmp_set_array(result, check_s, check_size_s) == 0) ? "YES" : "NO");
                                                free_set(result);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            free_set(A);
            free_set(B);
        }
    }
    {
        set_type A = create_set();
        set_type B = create_set();
        set_type result = create_set();
        double check_u[] = { 0, 1, 2, 3, 4 };
        int check_size_u = sizeof(check_u) / sizeof(check_u[0]);
        double check_i[] = { 0, 1, 2, 3, 4 };
        int check_size_i = sizeof(check_i) / sizeof(check_i[0]);
        double check_d[] = { 1 };
        int check_size_d = 0;
        double check_s[] = { 1 };
        int check_size_s = 0;
        int rc = OK;
        if (A && B && result)
        {
            for (int i = 0; i < 5 && rc == OK; i++)
                rc = set_add(A, i);
            if (rc == OK)
            {
                for (int i = 0; i < 5 && rc == OK; i++)
                    rc = set_add(B, i);
                if (rc == OK)
                {
                    rc = set_union(A, B, result);
                    if (rc == OK)
                    {
                        printf("correct work with union of not null sets (equal): %s\n", (cmp_set_array(result, check_u, check_size_u) == 0) ? "YES" : "NO");
                        free_set(result);
                        result = create_set();
                        if (result)
                        {
                            rc = set_intersection(A, B, result);
                            if (rc == OK)
                            {
                                printf("correct work with untersection of not null sets (equal): %s\n", (cmp_set_array(result, check_i, check_size_i) == 0) ? "YES" : "NO");
                                free_set(result);
                                result = create_set();
                                if (result)
                                {
                                    rc = set_difference(A, B, result);
                                    if (rc == OK)
                                    {
                                        printf("correct work with diffrence of not null sets (nothing): %s\n", (cmp_set_array(result, check_d, check_size_d) == 0) ? "YES" : "NO");
                                        free_set(result);
                                        result = create_set();
                                        if (result)
                                        {
                                            rc = set_sym_difference(A, B, result);
                                            if (rc == OK)
                                            {
                                                printf("correct work with semetric diffrence of not null sets (nothing): %s\n\n", (cmp_set_array(result, check_s, check_size_s) == 0) ? "YES" : "NO");
                                                free_set(result);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            free_set(A);
            free_set(B);
        }
    }
    {
        set_type A = create_set();
        set_type B = create_set();
        set_type result = create_set();
        double check_u[] = { 0, 1, 2, 3, 4 };
        int check_size_u = sizeof(check_u) / sizeof(check_u[0]);
        double check_i[] = { 1 };
        int check_size_i = 0;
        double check_d[] = { 0, 1, 2, 3, 4 };
        int check_size_d = sizeof(check_d) / sizeof(check_d[0]);
        double check_s[] = { 0, 1, 2, 3, 4 };
        int check_size_s = sizeof(check_s) / sizeof(check_s[0]);
        int rc = OK;
        if (A && B && result)
        {
            for (int i = 0; i < 5 && rc == OK; i++)
                rc = set_add(A, i);
            if (rc == OK)
            {
                rc = set_union(A, B, result);
                if (rc == OK)
                {
                    printf("correct work with union of not null first set and null second: %s\n", (cmp_set_array(result, check_u, check_size_u) == 0) ? "YES" : "NO");
                    free_set(result);
                    result = create_set();
                    if (result)
                    {
                        rc = set_intersection(A, B, result);
                        if (rc == OK)
                        {
                            printf("correct work with untersection of not null first set and null second: %s\n", (cmp_set_array(result, check_i, check_size_i) == 0) ? "YES" : "NO");
                            free_set(result);
                            result = create_set();
                            if (result)
                            {
                                rc = set_difference(A, B, result);
                                if (rc == OK)
                                {
                                    printf("correct work with diffrence of not null first set and null second: %s\n", (cmp_set_array(result, check_d, check_size_d) == 0) ? "YES" : "NO");
                                    free_set(result);
                                    result = create_set();
                                    if (result)
                                    {
                                        rc = set_sym_difference(A, B, result);
                                        if (rc == OK)
                                        {
                                            printf("correct work with semetric diffrence of not null first set and null second: %s\n\n", (cmp_set_array(result, check_s, check_size_s) == 0) ? "YES" : "NO");
                                            free_set(result);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            free_set(A);
            free_set(B);
        }
    }
    {
        set_type A = create_set();
        set_type B = create_set();
        set_type result = create_set();
        double check_u[] = { 0, 1, 2, 3, 4 };
        int check_size_u = sizeof(check_u) / sizeof(check_u[0]);
        double check_i[] = { 1 };
        int check_size_i = 0;
        double check_d[] = { 1 };
        int check_size_d = 0;
        double check_s[] = { 0, 1, 2, 3, 4 };
        int check_size_s = sizeof(check_s) / sizeof(check_s[0]);
        int rc = OK;
        if (A && B && result)
        {
            for (int i = 0; i < 5 && rc == OK; i++)
                rc = set_add(B, i);
            if (rc == OK)
            {
                rc = set_union(A, B, result);
                if (rc == OK)
                {
                    printf("correct work with union of not null second set and null first: %s\n", (cmp_set_array(result, check_u, check_size_u) == 0) ? "YES" : "NO");
                    free_set(result);
                    result = create_set();
                    if (result)
                    {
                        rc = set_intersection(A, B, result);
                        if (rc == OK)
                        {
                            printf("correct work with untersection of not null second set and null first: %s\n", (cmp_set_array(result, check_i, check_size_i) == 0) ? "YES" : "NO");
                            free_set(result);
                            result = create_set();
                            if (result)
                            {
                                rc = set_difference(A, B, result);
                                if (rc == OK)
                                {
                                    printf("correct work with diffrence of not null second set and null first: %s\n", (cmp_set_array(result, check_d, check_size_d) == 0) ? "YES" : "NO");
                                    free_set(result);
                                    result = create_set();
                                    if (result)
                                    {
                                        rc = set_sym_difference(A, B, result);
                                        if (rc == OK)
                                        {
                                            printf("correct work with semetric diffrence of not null second set and null first: %s\n\n", (cmp_set_array(result, check_s, check_size_s) == 0) ? "YES" : "NO");
                                            free_set(result);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            free_set(A);
            free_set(B);
        }
    }
    {
        set_type A = create_set();
        set_type B = create_set();
        set_type result = create_set();
        double check_u[] = { 0, 1, 2, 3, 4 };
        int check_size_u = sizeof(check_u) / sizeof(check_u[0]);
        double check_i[] = { 2 };
        int check_size_i = sizeof(check_i) / sizeof(check_i[0]);
        double check_d[] = { 0, 1 };
        int check_size_d = sizeof(check_d) / sizeof(check_d[0]);
        double check_s[] = { 0, 1, 3, 4 };
        int check_size_s = sizeof(check_s) / sizeof(check_s[0]);
        int rc = OK;
        if (A && B && result)
        {
            for (int i = 0; i < 3 && rc == OK; i++)
                rc = set_add(A, i);
            if (rc == OK)
            {
                for (int i = 2; i < 5 && rc == OK; i++)
                    rc = set_add(B, i);
                if (rc == OK)
                {
                    rc = set_union(A, B, result);
                    if (rc == OK)
                    {
                        printf("correct work with union of not null sets (1 element is common): %s\n", (cmp_set_array(result, check_u, check_size_u) == 0) ? "YES" : "NO");
                        free_set(result);
                        result = create_set();
                        if (result)
                        {
                            rc = set_intersection(A, B, result);
                            if (rc == OK)
                            {
                                printf("correct work with untersection of not null sets (1 element is common): %s\n", (cmp_set_array(result, check_i, check_size_i) == 0) ? "YES" : "NO");
                                free_set(result);
                                result = create_set();
                                if (result)
                                {
                                    rc = set_difference(A, B, result);
                                    if (rc == OK)
                                    {
                                        printf("correct work with diffrence of not null sets (1 element is common): %s\n", (cmp_set_array(result, check_d, check_size_d) == 0) ? "YES" : "NO");
                                        free_set(result);
                                        result = create_set();
                                        if (result)
                                        {
                                            rc = set_sym_difference(A, B, result);
                                            if (rc == OK)
                                            {
                                                printf("correct work with semetric diffrence of not null sets (1 element is common): %s\n\n", (cmp_set_array(result, check_s, check_size_s) == 0) ? "YES" : "NO");
                                                free_set(result);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            free_set(A);
            free_set(B);
        }
    }
    {
        set_type A = create_set();
        set_type B = create_set();
        set_type result = create_set();
        double check_u[] = { 0, 1, 2, 3, 4 };
        int check_size_u = sizeof(check_u) / sizeof(check_u[0]);
        double check_i[] = { 2, 3 };
        int check_size_i = sizeof(check_i) / sizeof(check_i[0]);
        double check_d[] = { 0, 1 };
        int check_size_d = sizeof(check_d) / sizeof(check_d[0]);
        double check_s[] = { 0, 1, 4 };
        int check_size_s = sizeof(check_s) / sizeof(check_s[0]);
        int rc = OK;
        if (A && B && result)
        {
            for (int i = 0; i < 4 && rc == OK; i++)
                rc = set_add(A, i);
            if (rc == OK)
            {
                for (int i = 2; i < 5 && rc == OK; i++)
                    rc = set_add(B, i);
                if (rc == OK)
                {
                    rc = set_union(A, B, result);
                    if (rc == OK)
                    {
                        printf("correct work with union of not null sets (2 elements is common): %s\n", (cmp_set_array(result, check_u, check_size_u) == 0) ? "YES" : "NO");
                        free_set(result);
                        result = create_set();
                        if (result)
                        {
                            rc = set_intersection(A, B, result);
                            if (rc == OK)
                            {
                                printf("correct work with untersection of not null sets (2 elements is common): %s\n", (cmp_set_array(result, check_i, check_size_i) == 0) ? "YES" : "NO");
                                free_set(result);
                                result = create_set();
                                if (result)
                                {
                                    rc = set_difference(A, B, result);
                                    if (rc == OK)
                                    {
                                        printf("correct work with diffrence of not null sets (2 elements is common): %s\n", (cmp_set_array(result, check_d, check_size_d) == 0) ? "YES" : "NO");
                                        free_set(result);
                                        result = create_set();
                                        if (result)
                                        {
                                            rc = set_sym_difference(A, B, result);
                                            if (rc == OK)
                                            {
                                                printf("correct work with semetric diffrence of not null sets (2 elements is common): %s\n\n", (cmp_set_array(result, check_s, check_size_s) == 0) ? "YES" : "NO");
                                                free_set(result);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            free_set(A);
            free_set(B);
        }
    }
}
int main(void)
{
    test_is_in_set();
    test_set_add_delete();
    test_set_array();
    return 0;
}
