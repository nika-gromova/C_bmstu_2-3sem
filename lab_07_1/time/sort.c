#include "sort.h"

void put_elem(void *left, void *right, size_t size)
{
    char *p_left = left;
    char *p_right = right;

    for (char *pcur = p_left; pcur < p_left + size; pcur++)
    {
        *pcur = *p_right;
        p_right++;
    }
}

int cmp(const void *left, const void *right)
{
    const int *p_left = left;
    const int *p_right = right;
    return *p_left - *p_right;
}

char *binary_search(char *low, char *high, char *cur_elem, size_t size, int(*cmp)(const void*, const void*))
{
    char *mid = NULL;
    while (low <= high)
    {
        mid = low + size * (((high - low) / 2) / size);
        if (cmp(cur_elem, mid) > 0)
            low = mid + size;
        else
            high = mid - size;
    }
    return low;
}


void mysort(void *base, size_t nmemb, size_t size, int(*cmp)(const void*, const void*))
{
    assert(nmemb >= 0);

    char *low, *high;
    char *begin = base;
    char *end = (char *)base + nmemb * size;
    char *cur_element = malloc(size);
    assert(cur_element);
    for (char *pi = (char *)base + size; pi < end; pi += size)
    {
        if (cmp(pi - size, pi) > 0)
        {
            put_elem(cur_element, pi, size);
            low = begin;
            high = pi;
            low = binary_search(low, high, cur_element, size, cmp);
            for (char *pj = pi; pj > low; pj -= size)
                put_elem(pj, pj - size, size);
            put_elem(low, cur_element, size);
        }
    }
    free(cur_element);
}
