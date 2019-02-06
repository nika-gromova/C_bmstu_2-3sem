#include <stdio.h>
#include <string.h>

#include "io.h"
#include "reverse.h"
#include "defines.h"
#include "operations.h"
#include "allocate.h"

void usage(void)
{
    printf("\nExample:\n");
    printf("app.exe action mtr_1.txt [mtr_2.txt] res.txt\n");
    printf("action: a - for addition, m - for multiplication, o - for reverse (matr_2.txt doesn't need), h - for help\n");
}

int main(int argc, char *argv[])
{
    int rc = OK;
    double **matrix = NULL;
    double **res = NULL;
    int n, m;
    int res_n, res_m;

    if (argc < 2)
    {
        usage();
        return USAGE_ERROR;
    }
    if (strcmp(argv[1], "a") != 0 && strcmp(argv[1], "m") != 0 && strcmp(argv[1], "o") != 0 && strcmp(argv[1], "h") != 0)
    {
        usage();
        return USAGE_ERROR;
    }
    if ((strcmp(argv[1], "a") == 0 || strcmp(argv[1], "m") == 0) && argc != 5)
    {
        usage();
        return USAGE_ERROR;
    }
    if (strcmp(argv[1], "o") == 0 && argc != 4)
    {
        usage();
        return USAGE_ERROR;
    }

    if (strcmp(argv[1], "h") == 0)
    {
        printf("Hello. This is the program for addition, multiplication and reversing matrix.\nPlease enter the options like this");
        usage();
        printf("app.exe - is the executable file of the program;\n"
               "res.txt - file where the result matrix will be saved;\n"
               "mtr_1.txt - file that contains first initial matrix;\n"
               "mtr_2.txt - contains second initial matrix (it's only for addition and multiplication).\n"
               "The format of the input of the matrix should be coordinate (indexing starts from 1), otherwise the program won't be able to scan the data.\n"
               "Example of input:\n"
               "3 3 4\n"
               "1 1 2\n"
               "1 2 9\n"
               "2 3 7\n"
               "3 1 -8\n"
               "The result:\n"
               " 2 9 0\n"
               " 0 0 7\n"
               "-8 0 0\n"
               "The output will be in ordinary format with size of the matrix in the first line.\n");
        return OK;
    }

    rc = read_matrix(argv[2], &matrix, &n, &m);
    if (rc == OK)
    {
        if (argc == 5)
        {
            if (strcmp(argv[1], "a") == 0)
            {
                double **matrix_2 = NULL;
                int n_2, m_2;
                rc = operations(argv[3], matrix, n, m, &matrix_2, &n_2, &m_2, &res, &res_n, &res_m, sum_matrix);
            }
            if (strcmp(argv[1], "m") == 0)
            {
                double **matrix_2 = NULL;
                int n_2, m_2;
                rc = operations(argv[3], matrix, n, m, &matrix_2, &n_2, &m_2, &res, &res_n, &res_m, mult_matrix);
            }
            if (rc == OK)
            {
                rc = save_matrix(argv[4], res, res_n, res_m);
                free_matrix(res, res_n);
            }
        }

        if (strcmp(argv[1], "o") == 0)
        {
            rc = reverse(matrix, n, m, &res, &res_n, &res_m);
            if (rc == OK)
            {
                rc = save_matrix(argv[3], res, res_n, res_m);
                free_matrix(res, res_n);
            }
            else
                printf("error\n");
        }
        free_matrix(matrix, n);
    }
    //printf("%d", rc);
    return rc;
}
