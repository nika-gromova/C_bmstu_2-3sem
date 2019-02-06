#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "io.h"
#include "structure.h"
#include "list.h"



void free_struct_array(data_t **struct_array, int count)
{
    for (int i = 0; i < count; i++)
        free(struct_array[i]);
    free(struct_array);
}

/*
 * Предметная область программы  - страны, их столицы и год основания города-столицы.
 * Информационная часть списка представлена структурой с двумя текстовыми полями и одним целочисленным.
 * app.exe позволяет проверить работу каждой функции (find, insert, reverse, sort)
 * при указании соответствующего ключа и необходимых данных в командной строке.
 * Условие задачи: найти элемент списка с самой "молодой" столицей и поместить его перед элементом списка, который содержит самую древнюю столицу.
 * Для запуска программы, решающей поставленную задачу необходимо запустить app.exe с ключом -task (и необходимыми данными) в командной строке.
 */
void usage(void)
{
    printf("Hello. This is a programme for work with a list.\n");
    printf("The list contains informmation about countries, its capitals and date of capital's foundation.\n");
    printf("Plese, enter options like this:\n\n");
    printf("app.exe o [parameter1] [parameter2] [parameter3] [parameter4] in.txt out.txt\n\n");
    printf("All of the parameter1, parameter2, parameter3, parameter4 should start and end with \".\n");
    printf("Here 'o' stands for 'operation', that can be:\n\n");
    printf("'-find' - to find an element in the list. Here [parameter1] is needed.\n");
    printf("Example (finding country 'Russia' in the list):\n");
    printf("app.exe -find \"Russia\" in.txt out.txt\n\n");
    printf("'-insert' - to inser an element to the list, before the selected elements. Here all [parameter1] - [parameter4] are needed.\n");
    printf("parameter1 is used to select the element, before which iserting is needed.\n");
    printf("parameter2 - parameter4 are used for the fields of new elements.\n");
    printf("Example (inserting element 'Great Britain London 50' to the list before 'Russia'):\n");
    printf("app.exe -insert \"Russia\" \"Great Britain\" \"London\" 50 in.txt out.txt\n\n");
    printf("'-reverse' - to reverse list.\n");
    printf("'-sort' - to sort list in ascending of year of foundation. The oldest cities will be in the beginnig.\n");
    printf("'-task' - this operation solves a task of finding a country with the newest capital in the list and inserting it before the oldest one.\n");
    printf("app.exe task in.txt out.txt\n");
    printf("The intial list should be in in.txt and the result of the programme will be in out.txt\n\n");
    printf("Information in in.txt should be replaced like this:\n");
    printf("Spain\n");
    printf("Madrid\n");
    printf("932\n");
    printf("And the most important thing: file should end with the simbol of a new line: \\n\n");
}

int main(int argc, char *argv[])
{
    int rc = OK;
    char *file_in, *file_out;
    int choice = 0;
    if (argc < 4 || argc > 8)
    {
        usage();
        return USAGE_ERROR;
    }
    if (strcmp(argv[1], "-find") == 0)
    {
        if (argc != 5)
        {
            usage();
            return USAGE_ERROR;
        }
        file_in = argv[3];
        file_out = argv[4];
        choice = 1;
    }
    else if (strcmp(argv[1], "-insert") == 0)
    {
        if (argc != 8)
        {
            usage();
            return USAGE_ERROR;
        }
        file_in = argv[6];
        file_out = argv[7];
        choice = 2;
    }
    else if (strcmp(argv[1], "-reverse") == 0)
    {
        if (argc != 4)
        {
            usage();
            return USAGE_ERROR;
        }
        file_in = argv[2];
        file_out = argv[3];
        choice = 3;
    }
    else if (strcmp(argv[1], "-sort") == 0)
    {
        if (argc != 4)
        {
            usage();
            return USAGE_ERROR;
        }
        file_in = argv[2];
        file_out = argv[3];
        choice = 4;
    }
    else if (strcmp(argv[1], "-task") == 0)
    {
        if (argc != 4)
        {
            usage();
            return USAGE_ERROR;
        }
        file_in = argv[2];
        file_out = argv[3];
        choice = 5;
    }
    else
    {
        usage();
        return USAGE_ERROR;
    }

    int count = count_line(file_in);
    if (count == 0)
        return READ_ERROR;
    if (count % 3 == 0)
        count /= 3;
    else
        return READ_ERROR;

    data_t **struct_array = calloc(count, sizeof(data_t *));
    if (!struct_array)
        return MEMORY_ERROR;

    node_t *head;
    rc = read_file(file_in, struct_array, count);
    if (rc == OK)
    {
        head = create_list(struct_array, count);
        if (head)
        {
            if (choice == 1)
            {
                node_t *res;
                data_t search;
                strcpy(search.country, argv[2]);
                res = find(head, &search, cmp_country);
                rc = save_elem(file_out, res);
            }
            if (choice == 2)
            {
                data_t before_data;
                strcpy(before_data.country, argv[2]);
                node_t *before = find(head, &before_data, cmp_country);
                if (before)
                {
                    data_t new_data;
                    strcpy(new_data.country, argv[3]);
                    strcpy(new_data.capital, argv[4]);
                    new_data.year = atoi(argv[5]);
                    node_t *new_elem = create_list_elem(&new_data);
                    if (new_elem)
                    {
                        insert(&head, new_elem, before);
                        rc = save_list(file_out, head);
                    }
                    else
                        rc = MEMORY_ERROR;
                }
                else
                    rc = save_list(file_out, before);
            }
            if (choice == 3)
            {
                head = reverse(head);
                rc = save_list(file_out, head);
            }
            if (choice == 4)
            {
                head = sort(head, cmp_year);
                rc = save_list(file_out, head);
            }
            if (choice == 5)
            {
                node_t *tmp_list = create_list(struct_array, count);
                if (tmp_list)
                {
                    tmp_list = sort(tmp_list, cmp_year);
                    data_t *before_data = tmp_list->data;
                    node_t *before = find(head, before_data, cmp_country);
                    tmp_list = reverse(tmp_list);
                    data_t *res = tmp_list->data;
                    node_t *elem = create_list_elem(res);
                    if (elem)
                    {
                        insert(&head, elem, before);
                        rc = save_list(file_out, head);
                    }
                    else
                        rc = MEMORY_ERROR;
                    free_list(tmp_list);
                }
                else
                    rc = MEMORY_ERROR;
            }
        }
        free_list(head);
        free_struct_array(struct_array, count);
    }
    return rc;
}
