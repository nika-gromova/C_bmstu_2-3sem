/*
 * Обработка двоичного файла, содержащего целые числа
 * Команды:
 * "cf" - создание нового двоичного файла и заполнение случайными числами
 * "p" - печать чисел из файла
 * "s" - упорядочивание чисел в файле
 * Упорядочивание происходит по возрастанию методом шейкера
 * Выбранный целочисленный тип: int
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#define OK (0)
#define USAGE_ERROR (-1)
#define OPEN_FILE_ERROR (-2)
#define IO_ERROR (-3)
#define PUT_NUM_ERROR (-4)

//#define SIZE (10)

// Функция, сообщающая правильный порядок ввода парметров командной строки
void usage(void)
{
    printf("main.exe <action> <quantity of numbers in file> [start] [end] <file name>\n");
    printf("\nactions:\n");
    printf("\"cf\" - create file <file name>\n");
    printf("and fill it with <quantity of numbers in file> random numbers in range from <start> to <end>\n");
    printf("for action \"cf\" parameters <start> and <end> are strictly required\n");
    printf("\n\"p\" - print numbers from file <file name>\n");
    printf("\"s\" - sort numbers in file <file name>\n");
    printf("for actions \"p\" and \"s\" parameters <start> and <end> are not required\n");
}

// Функция, печатающая числа из файла
int print_num(FILE *f)
{
    int num;
    int i = 0;
    while (fread(&num, sizeof(int), 1, f) == 1)
    {
        fprintf(stdout, "%d ", num);
        i++;
    }
    if (i != 0)
        return OK;
    return IO_ERROR;
}

// Функция, возвращающая число по номеру его позиции
int get_number_by_pos(FILE *f, int position, int *tmp)
{
    int num;
    if (fseek(f, position * sizeof(int), SEEK_SET) == 0)
    {
        if (fread(&num, sizeof(int), 1, f) == 1)
        {
            *tmp = num;
            return OK;
        }
        else
            return IO_ERROR;
    }
    return IO_ERROR;
}

// Функция, записывающая число на указанную позицию
int put_number_by_pos(FILE *f, int value, int position)
{
    if (fseek(f, position * sizeof(int), SEEK_SET) == 0)
    {
        if (fwrite(&value, sizeof(int), 1, f) == 1)
            return OK;
        else
            return IO_ERROR;
    }
    else
        return IO_ERROR;
}

// Функция, меняющая два числа в файле местами
int swap(FILE *f, int position1, int position2)
{
    int tmp1 = 0, tmp2 = 0;

    if (get_number_by_pos(f, position1, &tmp1) == OK)
    {
        if (get_number_by_pos(f, position2, &tmp2) == OK)
        {
            if (put_number_by_pos(f, tmp1, position2) == OK)
            {
                if (put_number_by_pos(f, tmp2, position1) == OK)
                    return OK;
                else
                    return IO_ERROR;
            }
            else
                return IO_ERROR;
        }
        else
            return IO_ERROR;
    }
    else
        return IO_ERROR;
    return IO_ERROR;
}

// Функция сортировки
int sort(FILE *f, int n)
{
    int left = 0;
    int right = n - 1;
    int tmp1 = 0, tmp2 = 0;
    int rc = OK;

    if (right == -1)
        return IO_ERROR;

    while (left <= right)
    {
        for (int i = left; i < right; i++)
        {
            if (get_number_by_pos(f, i, &tmp1) == OK)
            {
                if (get_number_by_pos(f, i + 1, &tmp2) == OK)
                {
                    if (tmp1 > tmp2)
                    {
                        rc = swap(f, i + 1, i);
                        if (rc != OK)
                            return IO_ERROR;
                    }
                }
                else
                    return IO_ERROR;
            }
            else
                return IO_ERROR;
        }
        right--;

        for (int i = right; i > left; i--)
        {
            if (get_number_by_pos(f, i - 1, &tmp1) == OK)
            {
                if (get_number_by_pos(f, i, &tmp2) == OK)
                {
                    if (tmp1 > tmp2)
                    {
                        rc = swap(f, i - 1, i);
                        if (rc != OK)
                            return IO_ERROR;
                    }
                }
                else
                    return IO_ERROR;
            }
            else
                return IO_ERROR;
        }
        left++;
    }
    return OK;
}

int random_num(FILE *created_file, int a, int b, int n)
{
    srand(time(NULL));
    int c;
    int r;

    for (int i = 0; i < n; i++)
    {
        r = a + rand() % (b - a + 1);
        if ((c = fwrite(&r, sizeof(int), 1, created_file)) != 1)
            return PUT_NUM_ERROR;
    }
    return OK;
}

// Основная функция
int main(int argc, char *argv[])
{
    FILE *f, *created_file;
    int rc = OK;

    if ((argc != 4 && (strcmp(argv[1], "p") == 0 || strcmp(argv[1], "s") == 0)) || (argc != 6 && (strcmp(argv[1], "cf")) == 0))
    {
        usage();
        return USAGE_ERROR;
    }
    int n = atoi(argv[2]);

    if (strcmp(argv[1], "cf") == 0)
    {
        created_file = fopen(argv[5], "wb");
        if (created_file)
        {
            int a = atoi(argv[3]);
            int b = atoi(argv[4]);

            rc = random_num(created_file, a, b, n);
            if (rc == OK)
                fprintf(stdout, "new file was created and filled with random numbers");
            else
                fprintf(stdout, "some errors with writing num to a file");

            fclose(created_file);
        }
        else
        {
            fprintf(stderr, "Could not create file %s because of %s", argv[2], strerror(errno));
            rc = OPEN_FILE_ERROR;
        }
    }
    else if (strcmp(argv[1], "p") == 0)
    {
        f = fopen(argv[3], "rb");
        if (f)
        {
            rc = print_num(f);
            if (rc != OK)
                fprintf(stdout, "Input error");
            fclose(f);
        }
        else
        {
            fprintf(stderr, "Could not open file %s because of %s", argv[2], strerror(errno));
            rc = OPEN_FILE_ERROR;
        }
    }
    else if (strcmp(argv[1], "s") == 0)
    {
        f = fopen(argv[3], "r+b");
        if (f)
        {
            rc = sort(f, n);
            if (rc != OK)
                fprintf(stdout, "Input error. Not enough data");
            else
                fprintf(stdout, "sorting was finished");
            fclose(f);
        }
        else
        {
            fprintf(stderr, "Could not open file %s because of %s", argv[2], strerror(errno));
            rc = OPEN_FILE_ERROR;
        }
    }
    else
    {
        usage();
        rc = USAGE_ERROR;
    }
    return rc;
}
