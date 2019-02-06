#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "defines.h"
#include "str.h"
#include "io.h"
#include "replace.h"

void usage(void)
{
    printf("Example of command line options:\n\n");
    printf("app.exe in.txt out.txt -s search -r replace\n\n");
    printf("where in.txt - input data file, out.txt - file for output data\n");
    printf("search - string for search and to be replaced, replace - string that would replace 'search'.\n");
    printf("parametrs -s and -r are always required.\n\n");
}

int main(int argc, char *argv[])
{
    int rc = OK;
    const char *search, *replace;

    int i_r = 6;
    if (argc < 5 || argc > 7)
    {
        usage();
        return USAGE_ERROR;
    }
    if (argc != 7)
    {
        usage();
        return USAGE_ERROR;
    }
    if (str_cmp(argv[3], "-s") == 0)
    {
        if (str_cmp(argv[4], "-r") == 0)
        {
            i_r--;
            search = '\0';
        }
        else if (str_cmp(argv[5], "-r") == 0)
            search = argv[4];
        else
        {
            usage();
            return USAGE_ERROR;
        }
        if (i_r != argc - 1)
            replace = '\0';
        else
            replace = argv[i_r];
    }
    else
    {
        usage();
        return USAGE_ERROR;
    }


    FILE *f_in = fopen(argv[1], "r");
    FILE *f_out = fopen(argv[2], "w");
    char *line = NULL;
    char *result = NULL;
    size_t n = 0;
    ssize_t read = 0;
    int count = 0;
    if (f_in)
    {
        if (f_out)
        {
            while ((read = my_getline(&line, &n, f_in)) != -1)
            {
                result = str_replace(line, search, replace);
                fprintf(f_out, "%s", result);
                free(result);
                result = NULL;
                count++;
            }
            if (count == 0)
                rc = EMPTY_FILE;
            free(line);
            fclose(f_out);
        }
        else
            rc = OPEN_FILE_ERROR;
        fclose(f_in);
    }
    else
        rc = OPEN_FILE_ERROR;
    printf("%d", rc);
    return rc;
}
