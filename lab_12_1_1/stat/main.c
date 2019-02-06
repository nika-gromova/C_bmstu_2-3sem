#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "arr_lib.h"

int main(int argc, char *argv[])
{
    FILE *file_in;
    FILE *file_out;
    int *pb = NULL, *pe = NULL;
    int rc = OK;
    int flag_f = 0;
    const int *i_max = NULL, *i_min = NULL;
    int m;


    if (argc != 3 && argc != 4)
    {
        printf("app.exe in.txt out.txt [f]");
        return USAGE_ERROR;
    }

    if (argc == 4)
    {
        if (strcmp(argv[3], "f") == 0)
        {
            flag_f = 1;
        }
        else
        {
            printf("invalid third parameter");
            return USAGE_ERROR;
        }
    }

    file_in = fopen(argv[1], "r");
    if (file_in)
    {
        file_out = fopen(argv[2], "w");
        if (file_out)
        {
            rc = input(file_in, &pb, &pe);
            if (rc == OK)
            {
                if (flag_f == 1)
                {
                    int *pb_dst = NULL;
                    int *pe_dst = NULL;
                    //
                    rc = find_max(pb, pe, &i_max);
                    if (rc == OK)
                    {
                        rc =find_min(pb, pe, &i_min);
                        if (rc == OK)
                        {
                            m = abs(i_min - i_max) - 1;
                            if (m > 0)
                            {
                                pb_dst = malloc(m * sizeof(int));
                                if (pb_dst)
                                {
                                    pe_dst = pb_dst + m;
                                    rc = key(pb, pe, pb_dst, pe_dst, i_max, i_min);
                                    if (rc == OK)
                                    {
                                        free(pb);
                                        pb = pb_dst;
                                        pe = pe_dst;
                                    }
                                }
                                else
                                    rc = MEMORY_ERROR;
                            }
                            else
                                rc = EMPTY_ARRAY;
                        }
                    }
                }
                if (rc == OK)
                {
                    if (pe - pb != 0)
                    {
                        mysort(pb, pe - pb, sizeof(int), cmp);
                        output_array(file_out, pb, pe);
                    }
                    else
                        rc = EMPTY_ARRAY;
                }
                free(pb);
                //pb = NULL;
            }
            fclose(file_out);
        }
        else
            rc = OPEN_FILE_ERROR;
        fclose(file_in);
    }
    else
        rc = OPEN_FILE_ERROR;
    return rc;
}
