#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include "defines.h"

#define LIB_ERROR -9
#define FUNCTION_ERROR -10

typedef int (__cdecl *fn_input)(FILE *, int **, int **);
typedef int (__cdecl *fn_find)(const int *, const int *, const int **);
typedef int (__cdecl *fn_key)(const int *, const int *, int *, int *, const int *, const int *);
typedef void (__cdecl *fn_mysort)(void *, size_t, size_t, int(*cmp)(const void*, const void*));
typedef void (__cdecl *fn_output_array)(FILE *, const int *, const int *);
typedef int (__cdecl *fn_cmp)(const void *, const void *);

struct functions
{
	fn_input input;
	fn_find find_max;
	fn_find find_min;
	fn_key key;
	fn_mysort mysort;
	fn_output_array output_array;
	fn_cmp cmp;
};

int load_lib(HMODULE *hlib, struct functions *func)
{
	*hlib = LoadLibrary("arr.dll");
	if (!(*hlib))
	{
		return LIB_ERROR;
	}
	func->input = (fn_input) GetProcAddress(*hlib, "input");
	if (func->input)
	{
		func->find_max = (fn_find) GetProcAddress(*hlib, "find_max");
		if (func->find_max)
		{
			func->find_min = (fn_find) GetProcAddress(*hlib, "find_min");
			if (func->find_min)
			{
				func->key = (fn_key) GetProcAddress(*hlib, "key");
				if (func->key)
				{
					func->mysort = (fn_mysort) GetProcAddress(*hlib, "mysort");
					if (func->mysort)
					{
						func->output_array = (fn_output_array) GetProcAddress(*hlib, "output_array");
						if (func->output_array)
						{
							func->cmp = (fn_cmp) GetProcAddress(*hlib, "cmp");
							if (func->cmp)
								return OK;
						}
					}
				}
			}
		}
	}
	return FUNCTION_ERROR;
}
	

int main(int argc, char *argv[])
{
	HMODULE hlib;
	struct functions my_functions;
	struct functions *p_my_functions = &my_functions;
	
    FILE *file_in;
    FILE *file_out;
    int *pb = NULL, *pe = NULL;
    int rc = FUNCTION_ERROR;
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
	
	/*hlib = LoadLibrary("arr.dll");
	if (!hlib)
	{
		printf("Library was not loaded\n");
		return LIB_ERROR;
	}
	input = (fn_input) GetProcAddress(hlib, "input");
	if (input)
	{
		find_max = (fn_find) GetProcAddress(hlib, "find_max");
		if (find_max)
		{
			find_min = (fn_find) GetProcAddress(hlib, "find_min");
			if (find_min)
			{
				key = (fn_key) GetProcAddress(hlib, "key");
				if (key)
				{
					mysort = (fn_mysort) GetProcAddress(hlib, "mysort");
					if (mysort)
					{
						output_array = (fn_output_array) GetProcAddress(hlib, "output_array");
						if (output_array)
						{
							cmp = (fn_cmp) GetProcAddress(hlib, "cmp");
							if (cmp)
								rc = OK;
						}
					}
				}
			}
		}
	}*/
	rc = load_lib(&hlib, p_my_functions);
	if (rc == LIB_ERROR)
	{
		printf("Library was not loaded\n");
		return LIB_ERROR;
	}
	if (rc == FUNCTION_ERROR)
	{
		printf("Functions were not loaded\n");
		FreeLibrary(hlib);
		return FUNCTION_ERROR;
	}

    file_in = fopen(argv[1], "r");
    if (file_in)
    {
        file_out = fopen(argv[2], "w");
        if (file_out)
        {
            rc = p_my_functions->input(file_in, &pb, &pe);
            if (rc == OK)
            {
                if (flag_f == 1)
                {
                    int *pb_dst = NULL;
                    int *pe_dst = NULL;
                    //
                    rc = p_my_functions->find_max(pb, pe, &i_max);
                    if (rc == OK)
                    {
                        rc = p_my_functions->find_min(pb, pe, &i_min);
                        if (rc == OK)
                        {
                            m = abs(i_min - i_max) - 1;
                            if (m > 0)
                            {
                                pb_dst = malloc(m * sizeof(int));
                                if (pb_dst)
                                {
                                    pe_dst = pb_dst + m;
                                    rc = p_my_functions->key(pb, pe, pb_dst, pe_dst, i_max, i_min);
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
                        p_my_functions->mysort(pb, pe - pb, sizeof(int), p_my_functions->cmp);
                        p_my_functions->output_array(file_out, pb, pe);
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
    {
        rc = OPEN_FILE_ERROR;
    }
	
	FreeLibrary(hlib);
    printf("rc = %d\n", rc);
    return rc;
}
