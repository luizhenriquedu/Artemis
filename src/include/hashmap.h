#pragma once
#include <stdint.h>
#include <stddef.h>
typedef struct
{
    char *key;
    void *data;
} hashmap_entry_t;

typedef struct
{
    hashmap_entry_t *entries;
    size_t collision;
} hm_table_t;

typedef struct
{
    size_t size;
    size_t max_collisions;
    hm_table_t *table;
    uint64_t flags;
} hashmap_t;
