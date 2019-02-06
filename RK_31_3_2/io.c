#include "io.h"
#include "defines.h"

/**
 * @brief save Функция сохраняет информацию, хнранящуюся в списке с началом head в файл f.
 * @param head [in] - Указатель на начало списка.
 * @param f [in] - Файловая переменная.
 */
void save(struct list_elem *head, FILE *f)
{
    if (!head)
    {
        fprintf(f, "None\n");
        return;
    }
    struct list_elem *tmp = head;
    for (; tmp; tmp = tmp->next)
        fprintf(f, "%s\n", tmp->word);
}
