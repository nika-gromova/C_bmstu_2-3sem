#ifndef MY_STRUCT_H
#define MY_STRUCT_H

#include "list.h"

#define MAX_LENGTH 20
#define MAX_SORT_INDX 3
#define MAX_FILTER_INDX 2

/*
 * Структура, описывающая элемент односвязного линейного списка:
 * model - название марки автомобиля
 * country - страна производитель автомобиля
 * price - цена автоиобиля
 * year - срок гарантии
 * id - уникальный номер элемента списка, присваивается при добавлении
 * sort[MAX_SORT_INDX] - массив списков Беркли: в первом хранятся отсортированные по названию марки в лексикографическом порядке автомобили,
 * во втором - отсортиротированные по цене и в третьем - отсортированные по цене и сроку гарантии (если цена оказалась одинаковая, то сравнивается срок гарантии)
 * filter[MAX_FILTER_INDX] - массив списков Беркли: в первом хранятся все те автомобили, для которых страна-производитель - Германия, во втором - все те,
 * для которых срок гарантии больше или равен 4 годам
 * next - указатель на следующий элемент односвязного линейного списка.
*/
typedef struct car
{
    char model[MAX_LENGTH + 1];
    char country[MAX_LENGTH + 1];
    double price;
    int year;
    int id;
    struct list_head sort[MAX_SORT_INDX];
    struct list_head filter[MAX_FILTER_INDX];
    struct car *next;
} node_car;

// Структура, в которой хранятся головы всех используемых списков Беркли
typedef struct head_l
{
    struct list_head sort_model;
    struct list_head sort_price;
    struct list_head sort_price_and_guarantee;
    struct list_head filter_country;
    struct list_head filter_guarantee;
} heads_index_filter;

#endif // MY_STRUCT_H
