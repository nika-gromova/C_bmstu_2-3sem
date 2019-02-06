#include "defines.h"
#include "io.h"
#include "list.h"
#include "structure.h"
#define BUF_SIZE 128

/**
 * @brief count_line Функция подсчета строк в файле. Для того, чтобы строка была посчитана, необходимо, чтобы она заканчивалась на \n.
 * @param file_name [in] - имя файла
 * @return lines Возвращает количество строк.
 */
int count_line(char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (!f)
        return OPEN_FILE_ERROR;
    int lines = 0;
    char buf[BUF_SIZE];
    int len;
    while (fgets(buf, sizeof(buf), f))
    {
        len = strlen(buf);
        if (buf[len - 1] == '\n')
            lines++;
    }
    fclose(f);
    return lines;
}

/**
 * @brief read_data Функция для чтения данных из файла. Считывает информацию только для одного элемента списка (данные для одной структуры).
 * Создает структуру и заполняет её поля в соответствии со считанной информацией.
 * @param f [in] - файловая переменная, указывающая на файл, из которого производится чтение.
 * @param cur [in][out] - указатель на указатель на структуру типа data_t (сам указатель на структуру меняется).
 * @return Возвращает INPUT_ERROR, введенные данные в файл записаны в неправильном формате, или READ_ERROR, если файл пустой, или OPEN_FILE_ERROR,
 * если файловая переменная неверная.
 */
int read_data(FILE *f, data_t **cur)
{
    if (!f)
        return OPEN_FILE_ERROR;
    char buf1[BUF_SIZE + 1];
    char buf2[BUF_SIZE + 1];
    char ch1[STR_LEN_MAX + 1];
    char ch2[STR_LEN_MAX + 1];
    int year;
    char tmp[2];
    int len;
    if (fgets(buf1, sizeof(buf1), f) != NULL)
    {
        len = strlen(buf1);
        if (buf1[len - 1] == '\n' && len <= STR_LEN_MAX)
        {
            buf1[len - 1] = '\0';
            strcpy(ch1, buf1);
            if (fgets(buf2, sizeof(buf2), f) != NULL)
            {
                len = strlen(buf2);
                if (buf2[len - 1] == '\n' && len <= STR_LEN_MAX)
                {
                    buf2[len - 1] = '\0';
                    strcpy(ch2, buf2);
                    if (fscanf(f, "%d", &year) == 1)
                    {
                        fgets(tmp, sizeof(tmp), f);
                        if (tmp[0] == '\n')
                        {
                            *cur = create_struct(ch1, ch2, year);
                            return OK;
                        }
                    }
                }
            }
        }
        return INPUT_ERROR;
    }
    return READ_ERROR;
}

/**
 * @brief read_file Функция считывает всю информацию из файла, для каждой записи формирует структуру, записывает указатель на эту
 * структуру в массив указателей на структуры.
 * @param file_name [in] - имя файла для чтения.
 * @param struct_array [in][out] - массив указателей на структуры.
 * @return Возвращает OPEN_FILE_ERROR, если не удалось открыть файл для чтения, или READ_ERROR, если файл пуст,
 * или INPUT_ERROR, если данные в файле не корректны, или OK, если чтение прошло успешно.
 */
int read_file(char *file_name, data_t *struct_array[], int count)
{
    FILE *f = fopen(file_name, "r");
    int rc = OK;
    int i = 0;
    if (f)
    {
        while (i < count && (rc = read_data(f, struct_array + i)) == OK)
            i++;
        if (i == 0)
            rc = READ_ERROR;
        else if (rc == INPUT_ERROR)
        {
            for (int j = 0; j < i; j++)
                free(struct_array[j]);
            rc = INPUT_ERROR;
        }
        fclose(f);
    }
    else
        return OPEN_FILE_ERROR;
    return rc;
}

/**
 * @brief save_list Функция сохраняет список в файл.
 * @param file_name [in] - имя файла, в который необходимо записать информацию.
 * @param head [in] - указатель на начало списка.
 * @return Возвращает OPEN_FILE_ERROR, если не удалось открыть файл на запись, или OK, если запись произведена успешно.
 */
int save_list(char *file_name, node_t *head)
{
    FILE *f = fopen(file_name, "w");
    if (f)
    {
        if (head)
        {
            node_t *tmp = head;
            data_t *cur;
            for (; tmp != NULL; tmp = tmp->next)
            {
                cur = tmp->data;
                fprintf(f, "%s %s %d\n", cur->country, cur->capital, cur->year);
            }
        }
        else
            fprintf(f, "Not found\n");
        fclose(f);
        return OK;
    }
    return OPEN_FILE_ERROR;
}

/**
 * @brief save_elem Функция сохраняет один элемент списка в файл.
 * @param file_name [in] - имя файла, в который необходимо записать информацию.
 * @param head [in] -  указатель на элемент списка.
 * @return Возвращает OPEN_FILE_ERROR, если не удалось открыть файл на запись, или OK, если запись произведена успешно.
 */
int save_elem(char *file_name, node_t *head)
{
    FILE *f = fopen(file_name, "w");
    if (f)
    {
        if (head)
        {
            data_t *cur;
            cur = head->data;
            fprintf(f, "%s %s %d\n", cur->country, cur->capital, cur->year);
        }
        else
            fprintf(f, "Not found\n");
        fclose(f);
        return OK;
    }
    return OPEN_FILE_ERROR;
}
