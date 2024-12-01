#include "include/frontend/list.h"
#include <stdlib.h>

list_t *list_create()
{
    list_t *list = (list_t *)malloc(sizeof(list_t));
    list->head = (list_item_t *)malloc(sizeof(list_item_t));
    list->head->next = list->head->prev = list->head;
    list->count = 0;
    return list;
}

void list_add(list_t *list, void *data)
{
    list_item_t *item = (list_item_t *)malloc(sizeof(list_item_t));
    item->next = list->head;
    item->prev = list->head->prev;
    item->data = data;
    list->head->prev->next = item;
    list->head->prev = item;
    list->count++;
}