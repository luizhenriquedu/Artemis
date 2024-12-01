#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct list_item_t
{
    struct list_item_t *next;
    struct list_item_t *prev;
    void *data;
} list_item_t;

typedef struct
{
    list_item_t *head;
    int count;
} list_t;

list_t *list_create();
void list_add(list_t *list, void *data);