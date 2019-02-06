#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A"(d));
    return d;
}

void rand_arr(int *a, int n)
{
    srand(time(NULL));
    int num;
    for (int *pcur = a; pcur < a + n; pcur++)
    {
        num =  0 + rand() % 100;
        *pcur = num;
    }
}

void inc_arr(int *a, int n)
{
    for (int *pcur = a; pcur < a + n; pcur++)
        *pcur = pcur - a;
}

void dec_arr(int *a, int n)
{
    for (int *pcur = a; pcur < a + n; pcur++)
        *pcur = n - (pcur - a);
}

unsigned long time_m(int *a, int n, void(*create)(int *a, int n), \
                     void(*sort)(void *base, size_t nmemb, size_t size, int(*cmp)(const void*, const void*)))
{
    unsigned long long t1, t2;
    unsigned long total;
    t1 = tick();
    for (int i = 0; i < 10; i++)
    {
        sort(a, n, sizeof(int), cmp);
        create(a, n);
    }
    t2 = tick();
    total = (t2 - t1) / 10;
    return total;
}


int main(void)
{
    unsigned long total_time;
    FILE *f_qsort, *f_mysort;
    f_qsort = fopen("q_sort.txt", "a");
    if (f_qsort)
    {
        f_mysort = fopen("my_sort.txt", "a");
        if (f_mysort)
        {
            fprintf(f_qsort, "Dimension 1-10:\n");
            fprintf(f_mysort, "Dimension 1-10:\n");
            {
                int n = 1;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    inc_arr(a, n);
                    total_time = time_m(a, n, inc_arr, mysort);
                    fprintf(f_mysort, "%d %lu\n", n, total_time);
                    n++;
                }
                n = 1;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    inc_arr(a, n);
                    total_time = time_m(a, n, inc_arr, qsort);
                    fprintf(f_qsort, "%d %lu\n", n, total_time);
                    n++;
                }
            }

            {
                int n = 1;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    rand_arr(a, n);
                    total_time = time_m(a, n, rand_arr, mysort);
                    fprintf(f_mysort, "%d %lu\n", n, total_time);
                    n++;
                }
                n = 1;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    rand_arr(a, n);
                    total_time = time_m(a, n, rand_arr, qsort);
                    fprintf(f_qsort, "%d %lu\n", n, total_time);
                    n++;
                }
            }

            {
                int n = 1;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    dec_arr(a, n);
                    total_time = time_m(a, n, dec_arr, mysort);
                    fprintf(f_mysort, "%d %lu\n", n, total_time);
                    n++;
                }
                n = 1;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    dec_arr(a, n);
                    total_time = time_m(a, n, dec_arr, qsort);
                    fprintf(f_qsort, "%d %lu\n", n, total_time);
                    n++;
                }
            }
            fprintf(f_qsort, "Next dimension 10-100:\n");
            fprintf(f_mysort, "Next dimension 10-100:\n");
            {
                int n = 10;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    inc_arr(a, n);
                    total_time = time_m(a, n, inc_arr, mysort);
                    fprintf(f_mysort, "%d %lu\n", n, total_time);
                    n += 10;
                }
                n = 10;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    inc_arr(a, n);
                    total_time = time_m(a, n, inc_arr, qsort);
                    fprintf(f_qsort, "%d %lu\n", n, total_time);
                    n += 10;
                }
            }

            {
                int n = 10;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    rand_arr(a, n);
                    total_time = time_m(a, n, rand_arr, mysort);
                    fprintf(f_mysort, "%d %lu\n", n, total_time);
                    n += 10;
                }
                n = 10;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    rand_arr(a, n);
                    total_time = time_m(a, n, rand_arr, qsort);
                    fprintf(f_qsort, "%d %lu\n", n, total_time);
                    n += 10;
                }
            }

            {
                int n = 10;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    dec_arr(a, n);
                    total_time = time_m(a, n, dec_arr, mysort);
                    fprintf(f_mysort, "%d %lu\n", n, total_time);
                    n += 10;
                }
                n = 10;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    dec_arr(a, n);
                    total_time = time_m(a, n, dec_arr, qsort);
                    fprintf(f_qsort, "%d %lu\n", n, total_time);
                    n += 10;
                }
            }
            fprintf(f_qsort, "Next dimension 100-1000:\n");
            fprintf(f_mysort, "Next dimension 100-1000:\n");
            {
                int n = 100;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    inc_arr(a, n);
                    total_time = time_m(a, n, inc_arr, mysort);
                    fprintf(f_mysort, "%d %lu\n", n, total_time);
                    n += 100;
                }
                n = 100;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    inc_arr(a, n);
                    total_time = time_m(a, n, inc_arr, qsort);
                    fprintf(f_qsort, "%d %lu\n", n, total_time);
                    n += 100;
                }
            }

            {
                int n = 100;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    rand_arr(a, n);
                    total_time = time_m(a, n, rand_arr, mysort);
                    fprintf(f_mysort, "%d %lu\n", n, total_time);
                    n += 100;
                }
                n = 100;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    rand_arr(a, n);
                    total_time = time_m(a, n, rand_arr, qsort);
                    fprintf(f_qsort, "%d %lu\n", n, total_time);
                    n += 100;
                }
            }

            {
                int n = 100;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    dec_arr(a, n);
                    total_time = time_m(a, n, dec_arr, mysort);
                    fprintf(f_mysort, "%d %lu\n", n, total_time);
                    n += 100;
                }
                n = 100;
                for (int i = 0; i < 10; i++)
                {
                    int a[n];
                    dec_arr(a, n);
                    total_time = time_m(a, n, dec_arr, qsort);
                    fprintf(f_qsort, "%d %lu\n", n, total_time);
                    n += 100;
                }
            }
            fclose(f_mysort);
        }
        fclose(f_qsort);
    }

    return 0;
}
