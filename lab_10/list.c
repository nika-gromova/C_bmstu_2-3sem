#include "list.h"
#include "structure.h"

/**
 * @brief create_list_elem Функция создает элемент списка.
 * @param info [in] - Указатель на структуру, содержащую данные.
 * @return Возвращает указатель на созданный элемент списка.
 */
node_t *create_list_elem(data_t *info)
{
    node_t *elem = calloc(1, sizeof(node_t));
    if (elem)
    {
        elem->data = info;
    }
    return elem;
}

/**
 * @brief add_list_elem Функция добавляет элемент в конец списка. Если список пуст, то указателем на начало списка становится сам элемент.
 * @param head [in] - указатель на начало списка.
 * @param elem [in] - элменет, который необходимо добавить.
 * @return Возвращает указатель на начало списка.
 */
node_t *add_list_elem(node_t *head, node_t *elem)
{
    node_t *tmp = head;
    if (!head)
        return elem;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = elem;
    return head;
}

/**
 * @brief create_list Функция создает список, используя массив указателей на структуры, в которых содержатся данные.
 * @param array_struct [in] - массив указателей на структуры.
 * @param n [in] - размерность массива.
 * @return Возвращает указатель на начало созданного списка.
 */
node_t *create_list(data_t *array_struct[], int n)
{
    node_t *head = NULL;
    node_t *cur;
    for (int i = 0; i < n; i++)
    {
        cur = create_list_elem(array_struct[i]);
        if (cur)
        {
            head = add_list_elem(head, cur);
        }
        else
        {
            free_list(head);
            return NULL;
        }
    }
    return head;
}

/**
 * @brief create_struct Функция создает структуру и заполняет её поля соответствующими данными.
 * @param country [in] - указатель на строку, содержащую информацию для первого поля структуры.
 * @param capital [in] - указатель на строку, содержащую информацию для второго поля структуры.
 * @param year [in] - число для записи в третье поле структуры.
 * @return Возвращает указатель на созданную структуру.
 */
data_t *create_struct(char *country, char *capital, int year)
{
    data_t *cur = calloc(1, sizeof(data_t));
    if (cur)
    {
        strcpy(cur->country, country);
        strcpy(cur->capital, capital);
        cur->year = year;
    }
    return cur;
}

/**
 * @brief cmp_country Функция сравнивает в алфавитном порядке структуры по первому полю.
 * @param elem1 [in] - указатель на первую структуру.
 * @param elem2 [in] - указатель на вторую структуру.
 * @return Возвращает -1, если в первый элемент меньше второго, 1, если первый элемент больше второго и 0, если они равны.
 */
int cmp_country(const void *elem1, const void *elem2)
{
    const data_t *s1 = elem1, *s2 = elem2;
    return (strcmp(s1->country, s2->country));
}

/**
 * @brief cmp_capital Функция сравнивает в алфавитном порядке структуры по второму полю.
 * @param elem1 [in] - указатель на первую структуру.
 * @param elem2 [in] - указатель на вторую структуру.
 * @return Возвращает -1, если в первый элемент меньше второго, 1, если первый элемент больше второго и 0, если они равны.
 */
int cmp_capital(const void *elem1, const void *elem2)
{
    const data_t *s1 = elem1, *s2 = elem2;
    return (strcmp(s1->capital, s2->capital));
}

/**
 * @brief cmp_year Функция сравнивает в числовом порядке структуры по третьему полю.
 * @param elem1 [in] - указатель на первую структуру.
 * @param elem2 [in] - указатель на вторую структуру.
 * @return Возвращает -1, если в первый элемент меньше второго, 1, если первый элемент больше второго и 0, если они равны.
 */
int cmp_year(const void *elem1, const void *elem2)
{
    const data_t *s1 = elem1, *s2 = elem2;
    if (s1->year == s2->year)
        return 0;
    else if (s1->year < s2->year)
        return -1;
    else
        return 1;
}


/**
 * @brief find Функция ищет элемент структуры с данными data в списке.
 * @param head [in] - указатель на начало списка.
 * @param data [in] - указатель на структуру, в которой содержатся данные.
 * @param comporator [in] - указатель на функцию сравнения.
 * @return Возвращает указатель на найденный элемент в списке, если такой есть, иначе возвращает NULL.
 */
node_t *find(node_t *head, const void *data, int (*comparator)(const void*, const void*))
{
    node_t *tmp = head;
    data_t *cur = NULL;
    const data_t *search = data;
    for (; tmp != NULL; tmp = tmp->next)
    {
        cur = tmp->data;
        if (comparator(cur, search) == 0)
            return tmp;
    }
    return NULL;
}

/**
 * @brief insert Функция вставляет элемент elem в список перед элементом before.
 * @param head [in] - указатель на начало списка.
 * @param elem [in] - указатель на элемент списка, который необходимо вставить.
 * @param before [in] - указатель на элемнет списка, перед которым необходимо вставить elem.
 */
void insert(node_t **head, node_t *elem, node_t *before)
{
    node_t *tmp = *head;
    if (elem == NULL)
        return;
    if (tmp == before || tmp->next == NULL)
    {
        elem->next = *head;
        *head = elem;
        return;
    }
    for (; tmp != NULL; tmp = tmp->next)
    {
        if (tmp->next == before)
        {
            elem->next = tmp->next;
            tmp->next = elem;
            return;
        }
    }
}

/**
 * @brief rec Функция рекурсивно меняет ссылки между элементами списка cur и before.
 * @param cur [in] - текущий элемент спика.
 * @param before [in] - предшествующий элемент списка.
 * @return Возвращает указатель на начало перевернутого списка.
 */
node_t *rec(node_t *cur, node_t *before)
{
    if (cur == NULL)
        return NULL;
    if (cur->next == NULL)
    {
        cur->next = before;
        return cur;
    }
    node_t *tmp = cur->next;
    cur->next = before;
    return rec(tmp, cur);
}

/**
 * @brief reverse Функция рекурсивно оборачивает список.
 * @param head [in] - указатель на начало списка.
 * @return Возвращает указатель на начало перевернутого списка.
 */
node_t *reverse(node_t *head)
{
    node_t *begin = head;
    head = rec(begin, NULL);
    return head;
}

/**
 * @brief front_back_split Функция делит список на два списка пополам.
 * @param head [in][out] - указатель на начало спика, который после работы функции является указателем на начало первого списка.
 * @param back [in][out] - указатель на начало второго списка (меняется по ходу работы функции).
 */
void front_back_split(node_t *head, node_t **back)
{
    if (head == NULL || head->next == NULL)
    {
        *back = NULL;
        return;
    }
    node_t *tmp = head;
    node_t *faster = head->next;
    while (faster != NULL)
    {
        faster = faster->next;
        if (faster)
        {
            tmp = tmp->next;
            faster = faster->next;
        }
    }
    *back = tmp->next;
    tmp->next = NULL;
}

/**
 * @brief sorted_merge Функция получает на фход два упорядоченных списка и объединяет их в один упорядоченный.
 * @param head_a [in][out] - указатель на первый упорядоченный список.
 * @param head_b [in][out] - указатель на второй упорядоченный список.
 * @param comporator [in] - указатель на функцию сравнения.
 * @return Возвращает указатель на начало нового упорядоченного списка.
 */
node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void*, const void*))
{
    node_t *new_head;   
    if (*head_a == NULL)
    {
        new_head = *head_b;
        *head_b = NULL;
        return new_head;
    }
    if (*head_b == NULL)
    {
        new_head = *head_a;
        *head_a = NULL;
        return new_head;
    }

    node_t *tmp_a = *head_a, *tmp_b = *head_b;
    node_t *del_a, *del_b;

    if (comparator(tmp_a->data, tmp_b->data) < 0)
    {
        new_head = tmp_a;
        del_a = tmp_a->next;
        tmp_a->next = NULL;
        tmp_a = del_a;
        del_a = NULL;
    }
    else
    {
        new_head = tmp_b;
        del_b = tmp_b->next;
        tmp_b->next = NULL;
        tmp_b = del_b;
        del_b = NULL;
    }
    node_t *tmp_new = new_head;
    while (tmp_a != NULL && tmp_b != NULL)
    {
        if (comparator(tmp_a->data, tmp_b->data) < 0)
        {
            tmp_new->next = tmp_a;
            del_a = tmp_a->next;
            tmp_a->next = NULL;
            tmp_a = del_a;
            del_a = NULL;
        }
        else
        {
            tmp_new->next = tmp_b;
            del_b = tmp_b->next;
            tmp_b->next = NULL;
            tmp_b = del_b;
            del_b = NULL;
        }
        tmp_new = tmp_new->next;
    }
    if (tmp_b != NULL)
        tmp_new->next = tmp_b;
    if (tmp_a != NULL)
        tmp_new->next = tmp_a;
    tmp_a = NULL;
    tmp_b = NULL;
    *head_a = NULL;
    *head_b = NULL;

    return new_head;
}

/**
 * @brief sort Функция сортировки слиянием списка.
 * @param head [in][out] - указатель на начало списка.
 * @param comporator [in] - указатель на функцию сравнения.
 * @return Возвращает указатель на отсортированный список.
 */
node_t *sort(node_t *head, int (*comparator)(const void*, const void*))
{
    node_t *begin = head, *end = NULL;
    if (head == NULL || head->next == NULL)
        return head;
    front_back_split(begin, &end);
    begin = sort(begin, comparator);
    end = sort(end, comparator);
    head = sorted_merge(&begin, &end, comparator);
    return head;
}

/**
 * @brief free_list Функция освобождения памяти из-под списка.
 * @param head [in] - указатель на начало списка.
 */
void free_list(node_t *head)
{
    node_t *tmp = head;
    while (tmp != NULL)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}
