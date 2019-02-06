#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "io.h"
#include "process.h"
#include "structure.h"

void usage(void)
{
    printf("USAGE: main.exe in.txt out.txt");
}
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        usage();
        return USAGE_ERROR;
    }
    char *file_in = argv[1];
    char *file_out = argv[2];
    FILE *f = fopen(file_in, "r");
    FILE *f_out;
    char buf[BUF_SIZE + 1];
    char *str = NULL; // текущая строка, считанная из файла
    int len; // длина текущей строки

    int rc = OK;
    struct list_elem *head = NULL; // указатель на результирующий список неповторяющихся слов
    int unique_words = 0; // количество неповторяющихся слов
    int count; // количество слов в текущей строке
    char **words = NULL; // массив указателей на слова в текущей строке

    if (f)
    {
        f_out = fopen(file_out, "w");
        if (f_out)
        {
            while (fgets(buf, sizeof(buf), f))
            {
                len = strlen(buf);
                if (len == 0)
                    return INPUT_ERROR;
                if (buf [len - 1] == '\n')
                {
                    buf[len - 1] = '\0';
                    len--;
                    str = malloc((len + 1) * sizeof(char));
                    if (str)
                    {
                        strcpy(str, buf);
                        count = count_words(str);
                        words = malloc(count * sizeof(char *));
                        if (words)
                        {
                            count = sep(str, words);
                            if (count != 0)
                                for (int i = 0; i < count; i++)
                                    rc = add_unique_word(words[i], &head, &unique_words);
                            free(words);
                        }
                        else
                            rc = MEMORY_ERROR;
                        free(str);
                    }
                    else
                        return MEMORY_ERROR;
                }
                else
                    return INPUT_ERROR;
            }
            if (rc == OK)
            {
                printf("The number of unique words in file: %d", unique_words);
                save(head, f_out);
                free_list(head);
            }
            fclose(f_out);
        }
        fclose(f);
    }
    else
        return OPEN_FILE_ERROR;
    return rc;
}
