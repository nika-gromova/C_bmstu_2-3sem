#ifndef STRUCTURE_H
#define STRUCTURE_H
#define STR_LEN_MAX 30
typedef struct data data_t;

/**
 * Структура данных data содержит два строковых поля (название страны и название столицы) и одно целочисленное поле (год основания столицы).
 */
struct data
{
    char country[STR_LEN_MAX + 1];
    char capital[STR_LEN_MAX + 1];
    int year;
};

typedef struct node node_t;

/**
 * Структура данных node содеожит бестиповой указатель на данные и указатель на следующий элемент списка.
 */
struct node
{
    void *data;
    node_t *next;
};


#endif // STRUCTURE_H
