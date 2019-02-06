#include <stdio.h>
#include "list.h"
#include "my_struct.h"

void test(void)
{
    printf("Tests for addition:\n");
    node_t *head_1 = NULL, *head_2 = NULL, *result = NULL;
    {
        unsigned int num_1 = 0, num_2 = 0, res, check = 0;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
    {
        unsigned int num_1 = 0, num_2 = 1, res, check = 1;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
    {
        unsigned int num_1 = 1, num_2 = 0, res, check = 1;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
    {
        unsigned int num_1 = 1, num_2 = 12, res, check = 13;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
    {
        unsigned int num_1 = 15, num_2 = 1, res, check = 16;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
    {
        unsigned int num_1 = 155, num_2 = 1, res, check = 156;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
    {
        unsigned int num_1 = 159, num_2 = 1, res, check = 160;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
    {
        unsigned int num_1 = 159, num_2 = 17, res, check = 176;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
    {
        unsigned int num_1 = 159, num_2 = 217, res, check = 376;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
    {
        unsigned int num_1 = 159, num_2 = 2107, res, check = 2266;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
    {
        unsigned int num_1 = 1591, num_2 = 2107, res, check = 3698;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
    {
        unsigned int num_1 = 1593, num_2 = 2107, res, check = 3700;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
    {
        unsigned int num_1 = 99999, num_2 = 9, res, check = 100008;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
    {
        unsigned int num_1 = 9, num_2 = 902909, res, check = 902918;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
    {
        unsigned int num_1 = 921921921, num_2 = 9, res, check = 921921930;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
    {
        unsigned int num_1 = 80, num_2 = 921921921, res, check = 921922001;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
    {
        unsigned int num_1 = 765700880, num_2 = 921921921, res, check = 1687622801;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
    {
        unsigned int num_1 = 765700880, num_2 = 921921921, res, check = 1687622801;
        head_1 = create_list(num_1);
        head_2 = create_list(num_2);
        if (head_1 != NULL && head_2 != NULL)
        {
            result = sum(head_1, head_2);
            if (result != NULL)
            {
                res = form_num(result);
                printf("Correct work with %u + %u: %s\n", num_1, num_2, (check == res) ? "YES" : "NO");
            }
            free_list(head_1);
            free_list(head_2);
        }
    }
}

int main(void)
{
    test();
    return 0;
}
