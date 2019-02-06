#include "process.h"

const char *my_strpbrk(const char *str, const char *sym)
{
    const char *s1 = str, *s2 = sym;
    for (int i = 0; s1[i] != '\0'; i++)
    {
        for (int j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j])
                return s1 + i;
    }
    return NULL;
}

int len(const char *str)
{
    int n;
    for (n = 0; str[n] != '\0'; n++);
    return n;
}

char *my_strdup(const char *str)
{
    if (str == NULL)
        return NULL;

    int length = len(str);
    char *new_str = malloc((length + 1) * sizeof (char));
    if (new_str)
    {
        for (int i = 0; i < length + 1; i++)
            new_str[i] = str[i];
        return new_str;
    }
    else
        return NULL;
}
