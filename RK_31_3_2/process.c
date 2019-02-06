#include "defines.h"
#include "process.h"

/**
 * @brief count_words Функция подсчета слов в строке str. Разделитель для слов: пробельный символ.
 * @param str [in] - Указатель на строку.
 * @return Возвращает count -  количество слов в строке.
 */
int count_words(char *str)
{
    int len = strlen(str);
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        if (strchr(" ", str[i]) == NULL)
        {
            if (i == 0 || strchr(" ", str[i - 1]) != NULL)
                count++;
        }
    }
    return count;
}

/**
 * @brief sep Функция "разделяет" строку на слова, записывая в массив указателей на строки p_words указатель на начало каждого слова в строке str.
 * @param str [in] - Указатель на строку.
 * @param p_words [in][out] - Массив указателей на строки.
 * @return Возвращает count - количество слов в строке.
 */
int sep(char *str, char **p_words)
{
    int len = strlen(str);
    int words = 0;
    for (int i = 0; i < len; i++)
    {
        if (strchr(" ", str[i]) != NULL)
            str[i] = '\0';
        else
            if (i == 0 || str[i - 1] == '\0')
            {
                p_words[words] = str + i;
                words++;
            }
    }
    return words;
}

/**
 * @brief create_elem Функция создает элемент списка, который содержит строквое поле - слово.
 * @param word [in] - Указатель на строку.
 * @return Возвращает NULL, если не удалось выделить память под новый элемент списка либо длина слова превышает допустимую максимальную (20 символов),
 * или указатель на новый созданный элемент списка типа list_elem *.
 */
struct list_elem *create_elem(char *word)
{
    if (strlen(word) > 20)
        return NULL;
    struct list_elem *cur = malloc(sizeof(struct list_elem));
    if (cur)
    {
        strcpy(cur->word, word);
        cur->next = NULL;
    }
    return cur;
}

/**
 * @brief add_elem Функция добавляет элемент elem в конец списка с началом head.
 * @param head [in][out] - Указатель на начало списка.
 * @param elem [in] - Указатель на элемент, который необходимо добавить в спискок.
 * @return Возвращает указатель на начало списка.
 */
struct list_elem *add_elem(struct list_elem *head, struct list_elem *elem)
{
    if (head == NULL)
        return elem;
    struct list_elem *tmp = head;
    for (; tmp->next != NULL; tmp = tmp->next)
        ;
    tmp->next = elem;
    return head;
}

/**
 * @brief free_list Функция освобождения памяти из-под списка.
 * @param head [in] - Указатель на начало списка.
 */
void free_list(struct list_elem *head)
{
    struct list_elem *tmp;
    for (; head; head = tmp)
    {
        tmp = head->next;
        free(head);
    }
}

/**
 * @brief add_unique_word Функция добавляет слово в список, если его там еще нет.
 * @param word [in] - Указатель на строку, содержащую слово
 * @param head [in][out] - Указатель на начало списка
 * @param word_count [in][out] - Количество неповторяющихся слов в списке.
 * @return Возвращает MEMORY_ERROR, если не удалось выделить память для очередного элемента спика или, если длина слова превышает допустимую максимальную (20),
 * либо возвращает OK, если слово было успешно добавлено или это слово уже есть в списке.
 */
int add_unique_word(char *word, struct list_elem **head, int *word_count)
{
    struct list_elem *new = NULL;
    if (*head == NULL)
    {
        new = create_elem(word);
        if (!new)
            return MEMORY_ERROR;
        *head = add_elem(*head, new);
        *word_count = 1;
        return OK;
    }
    struct list_elem *tmp = *head;
    for (; tmp != NULL; tmp = tmp->next)
    {
        if (strcmp(tmp->word, word) == 0)
            return OK;
    }
    new = create_elem(word);
    if (!new)
    {
        free_list(*head);
        return MEMORY_ERROR;
    }
    *head = add_elem(*head, new);
    (*word_count)++;
    return OK;
}
