#include <stdio.h>
#include "my_struct.h"
#include "list.h"

#define OK 0
#define USAGE_ERROR -1
#define INPUT_ERROR -2
#define OPEN_FILE_ERROR -3
#define MEMORY_ERROR -4

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("app.exe in_1.txt in_2.txt\nFirst number for sum in in_1.txt and second - in in_2.txt\n");
        return USAGE_ERROR;
    }
    int rc = OK;
    unsigned int num_1, num_2, res;
    node_t *head_1 = NULL, *head_2 = NULL, *result = NULL;
    FILE *f_1, *f_2;
    f_1 = fopen(argv[1], "r");
    if (f_1)
    {
        f_2 = fopen(argv[2], "r");
        if (f_2)
        {
            if (fscanf(f_1, "%u", &num_1) == 1)
            {
                if (fscanf(f_2, "%u", &num_2) == 1)
                {
                    printf("Numbers in files: %u %u\n", num_1, num_2);
                    head_1 = create_list(num_1);
                    head_2 = create_list(num_2);
                    if (head_1 != NULL && head_2 != NULL)
                    {
                        printf("Lists of numbers: ");
                        print_list(head_1);
                        print_list(head_2);
                        printf("\n");

                        result = sum(head_1, head_2);
                        if (result != NULL)
                        {
                            printf("Result of addition in list-form:\n");
                            print_list(result);
                            res = form_num(result);
                            printf("\nResult of addition in number-form:\n%u", res);
                        }
                        free_list(head_1);
                        free_list(head_2);
                    }
                    else rc = MEMORY_ERROR;
                }
                else
                    rc = INPUT_ERROR;
            }
            else
                rc = INPUT_ERROR;
            fclose(f_2);
        }
        else
            rc = OPEN_FILE_ERROR;
        fclose(f_1);
    }
    else
        rc = OPEN_FILE_ERROR;
    if (rc == INPUT_ERROR)
        printf("Incorrect input\n");
    if (rc == OPEN_FILE_ERROR)
        printf("Can't open file\n");
    return rc;
}
