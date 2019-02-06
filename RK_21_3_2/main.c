#include <stdio.h>
#define OK (0)
#define OPEN_FILE_ERR (-1)
#define IO_ERR (-2)
#define USAGE_ERR (-3)
#define NO_CH_NUM (1)


int get_min_num(FILE *f, int *min)
{
    int num;
    int flag = 0;

    if (fscanf(f, "%d", &num) != 1)
        return IO_ERR;
    rewind(f);

    while (fscanf(f, "%d", &num) == 1)
        if (num % 2 == 0)
        {
            *min = num;
            flag = 1;
            break;
        }
    if (flag == 1)
    {
        while(fscanf(f, "%d", &num) == 1)
        {
            if ((num % 2 == 0) && (num < *min))
            {
                *min = num;
            }
        }
        return OK;
    }

    else
        return NO_CH_NUM;

}

int main(int argc, char *argv[])
{
    FILE *f;
    int rc = OK;
    int res;
    int min;

    if (argc != 2)
    {
        printf("<main.exe> <file nme>");
        return USAGE_ERR;
    }

    f = fopen(argv[1], "r");
    if (f)
    {
        res = get_min_num(f, &min);
        if (res == IO_ERR)
        {
            printf("not enough data");
            rc = IO_ERR;
        }
        else if (res == NO_CH_NUM)
            printf("There are no suitable numbers in file");
        else
            printf("Min chetnoye = %d", min);

        fclose(f);
    }
    else
    {
        printf("can not open a file");
        rc = OPEN_FILE_ERR;
    }

    return rc;
}
