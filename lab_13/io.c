#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "defines.h"
#include "io.h"
#include "my_struct.h"
#include "list.h"
#include "my_list.h"

#define BUF_SIZE 200

/**
 * @brief delete_spaces Функция удаляет пробелы в начале и в конце строки
 * @param str[in] - указатель на строку, из которой удаляютс пробелы
 * @param res[in][out] - указатель на результирующую строку, в которую записываются всесимволы исходной строки, но уже без пробелов в начале или конце
 */
void delete_spaces(char *str, char *res)
{
    int length = strlen(str);
    while (length > 0 && str[length - 1] == ' ')
        length--;
    while (*str && *str == ' ' && length > 0)
    {
        str++;
        length--;
    }
    for (int i = 0; i < length; i++)
    {
        res[i] = str[i];
    }
    res[length] = '\0';
}


/**
 * @brief parse_line Функция разбивает строку на информационные элементы и записывает их в соответствующие поля структуры
 * @param line[in] - указатель на строку
 * @param cur[in][out] - указател на структуру односвязного линейного списка
 * @return Возвращает READ_FILE_ERROR, если строка содержит некорректные значения, либо ОК, если строка была разбита успешно и данные записаны в поля структуры
 */
int parse_line(char *line, node_car *cur)
{
    if (!line)
        return READ_FILE_ERROR;
    char *sep = ";";
    char *istr = '\0';
    char *end = NULL;
    double price;
    int year;
    istr = strtok(line, sep);
    if (istr)
    {
        strcpy(cur->model, istr);
        istr = strtok(NULL, sep);
        if (istr)
        {
            strcpy(cur->country, istr);
            istr = strtok(NULL, sep);
            if (istr)
            {
                price = strtod(istr, &end);
                if (*end == '\0')
                {
                    cur->price = price;
                    istr = strtok(NULL, sep);
                    if (istr)
                    {
                        year = atoi(istr);
                        if (year > 0)
                        {
                            cur->year = year;
                            return OK;
                        }
                    }
                }
            }
        }
    }
    return READ_FILE_ERROR;
}

/**
 * @brief read_file Функция считывает данные из файла построчно
 * @param filename[in] - название файла
 * @param head[in][out] - указаьтель на голову односвязного линейного списка
 * @param heads_berkeley[in][out] - указатель на структуру, содержащую головы списков Беркли
 * @return Возвращает OPEN_FILE_ERROR, если файл не удалось открыть на чтение, EMPTY_FILE_ERROR, если файл пуст,
 * MEMORY_ERROR, если не удалось выделить память под очередной элемент списка, OK, если данные из файла успешно прочитаны и занемены в список
 */
int read_file(char *filename, node_car **head, heads_index_filter *heads_berkeley)
{
    FILE *f;
    f = fopen(filename, "r");
    if (f == NULL)
        return OPEN_FILE_ERROR;
    char buf[BUF_SIZE];
    node_car *cur = NULL;
    char is_empty = 1;
    int rc = OK;
    char new_str[BUF_SIZE];
    new_str[BUF_SIZE - 1] = '\0';
    while (rc == OK && fgets(buf, sizeof(buf), f))
    {
        is_empty = 0;
        delete_spaces(buf, new_str);
        if (strlen(new_str) > 0)
        {
            cur = create_list_elem();
            if (cur)
            {
                rc = parse_line(buf, cur);
                if (rc == OK)
                {
                    add_lo_list(heads_berkeley, cur, head);
                }
                else
                    free(cur);
            }
            else
                rc = MEMORY_ERROR;
        }
        else
            rc = MEMORY_ERROR;
    }
    fclose(f);
    if (is_empty)
        return EMPTY_FILE_ERROR;
    if (rc != OK)
    {
        delete_list(*head);
        return rc;
    }
    return OK;
}

/**
 * @brief read_line Функция посимвольно считывает данные с потока ввода
 * @param str[in][out] - указатель на строку, в которую записываются символы
 * @param n[in] - размер памяти, выделенный под строку (в байтах)
 * @return Возвращает количество записанных в строку символов
 */
int read_line(char *str, int n)
{
    char ch;
    int i = 0;
    int flag_overflow = 0;
    if ((ch = getchar()) != '\n')
    {
        str[i] = ch;
        i++;
    }
    while((ch = getchar()) != '\n' && ch != EOF)
    {
        if (i < n - 1)
            str[i++] = ch;
        else
            flag_overflow = 1;
    }
    if (flag_overflow == 0)
        str[i] = '\0';
    else
        i = 0;
    return i;
}

/**
 * @brief scan_data Функция считывает строку из потока ввода и записывает информацию в поля структуры
 * @param cur[in][out] - указатель структуру, содержащую элемент списка
 * @return Возвращает INPUT_ERROR, если данные введены некорректно, либо OK, если данные считаны и записаны успешно
 */
int scan_data(node_car *cur)
{
    char buf[BUF_SIZE];
    int len;
    printf("model and country not more than 20 symbols, price id a real num, period of guarantee is an integer.\n");
    printf("Input format:\nmodel of the car;country;price;period of guarantee\n");
    if ((len = read_line(buf, sizeof(buf))) > 0)
    {
        if (parse_line(buf, cur) == OK)
        {
            return OK;
        }
    }
    printf("Incorrect input :( Try again!\n");
    return INPUT_ERROR;
}

/**
 * @brief print_berkeley_sort Функция печати списков Беркли для сортировки
 * @param head[in] - указатель на голову соответствующего списка Беркли
 * @param index[in] - индекс массива, в котором хранится соответствующий список Беркли в структуре, содержашей элемент односвязного списка.
 */
void print_berkeley_sort(struct list_head *head, int index)
{
    printf("\n");
    printf("%3s%20s%20s%15s%15s\n", "Id", "Model", "Country", "Price", "Guarantee");
    node_car *tmp;
    struct list_head *iter;
    list_for_each(iter, head)
    {
        tmp = list_entry(iter, node_car, sort[index]);
        printf("%2d.%20s%20s%15.2lf%15d\n", tmp->id, tmp->model, tmp->country, tmp->price, tmp->year);
    }
    printf("\n");
}

/**
 * @brief print_berkeley_filter Функция печати списков Беркли для фильтрации
 * @param head[in] - указатель на голову соответствующего списка Беркли
 * @param index[in] - индекс массива, в котором хранится соответствующий список Беркли в структуре, содержашей элемент односвязного списка.
 */
void print_berkeley_filter(struct list_head *head, int index)
{
    printf("\n");
    printf("%3s%20s%20s%15s%15s\n", "Id", "Model", "Country", "Price", "Guarantee");
    node_car *tmp;
    struct list_head *iter;
    list_for_each(iter, head)
    {
        tmp = list_entry(iter, node_car, filter[index]);
        printf("%2d.%20s%20s%15.2lf%15d\n", tmp->id, tmp->model, tmp->country, tmp->price, tmp->year);
    }
    printf("\n");
}

/**
 * @brief print_data Печать элементов односвязного линейного списка
 * @param head[in] - указатель на голову списка
 */
void print_data(node_car *head)
{
    printf("\n");
    printf("Current data in database:\n");
    printf("%3s%20s%20s%15s%15s\n", "Id", "Model", "Country", "Price", "Guarantee");
    while (head)
    {
        printf("%2d.%20s%20s%15.2lf%15d\n", head->id, head->model, head->country, head->price, head->year);
        head = head->next;
    }
    printf("\n");
}

/**
 * @brief save_data Функция сохраняет данные, хранящиеся в односвязном линейном списке,  в файл
 * @param file_name[in] - имя файла
 * @param head[in] - указатель на начало списк
 * @return Возвращает OPEN_FILE_ERROR, если не удалось отрыть файл на запись, OK, если информация записана успешно
 */
int save_data(char *file_name, node_car *head)
{
    int rc = OK;
    FILE *f = fopen(file_name, "w");
    if (f)
    {
        while(head)
        {
            fprintf(f, "%s;%s;%.2lf;%d\n", head->model, head->country, head->price, head->year);
            head = head->next;
        }
        fclose(f);
    }
    else
        rc = OPEN_FILE_ERROR;
    return rc;
}
