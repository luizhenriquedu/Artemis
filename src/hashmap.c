#include "include/hashmap.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

hashmap_t *hashmap_create(uint64_t size, size_t max_collisions)
{
    hashmap_t *map = (hashmap_t *)malloc(sizeof(hashmap_t));
    map->table = (hashmap_table_t *)malloc(sizeof(map->table) * size);
    map->size = size;
    map->max_collisions = max_collisions;
    memset(map->table, 0, sizeof(map->table) * size);
    return map;
}

uint64_t hashmap_hash(const char *key, size_t size)
{
    uint64_t hash_value = 0;
    while (*key)
    {
        hash_value = (hash_value << 5) + *key;
        *key++;
    }

    return hash_value % (size - 1);
}

void hashmap_insert(hashmap_t *hashmap, char *key, void *data)
{
start:
{
    uint64_t hash = hashmap_hash(key, hashmap->size);
    hashmap_table_t *table = &hashmap->table[hash];
    if (table->entries == NULL || table->collisions == 0)
    {
        table->entries = (hashmap_entry_t *)malloc(sizeof(hashmap_table_t) * hashmap->max_collisions);
        memset(table->entries, 0, sizeof(table->entries) * hashmap->max_collisions);
        table->collisions = 0;
    }
    if (table->collisions == hashmap->max_collisions)
    {
        hashmap_resize(hashmap, hashmap->size + 50, hashmap->max_collisions + 30);
        goto start;
    }

    uint64_t index = table->collisions++;
    table->entries[index].key = (char *)malloc(strlen(key) + 1);
    strcpy(table->entries[index].key, key);
    table->entries[index].data = data;
    if (data != NULL)
    {
        printf("\nAdded element to hashmap\n{\tkey: %s,\n\tdata: %d\n}\n", key, (int *)data);
    }
    else
    {
        printf("\nAdded element to hashmap\n{\tkey: %s,\n\tdata: NULL\n}", key);
    }
}
}

void *hashmap_search(hashmap_t *hashmap, char *key)
{
    uint64_t index = hashmap_hash(key, hashmap->size);
    hashmap_table_t *table = &hashmap->table[index];

    if (table->entries == NULL || table->collisions == 0)
    {
        return NULL;
    }

    for (int i = 0; i < table->collisions; i++)
    {
        if (!strcmp(key, table->entries[i].key))
        {
            return table->entries[i].data;
        }
    }
}

void hashmap_resize(hashmap_t *hashmap, size_t new_size, size_t new_collisions)
{
    hashmap_table_t *new_table = (hashmap_table_t *)malloc(sizeof(hashmap_table_t) * new_size);
    hashmap->max_collisions = new_collisions;

    memset(new_table, 0, sizeof(new_table) * new_size);

    for (size_t i = 0; i < hashmap->size; i++)
    {
        if (hashmap->table[i].entries == NULL || hashmap->table[i].collisions == 0)
            continue;
        for (size_t j = 0; j < hashmap->table[i].collisions; j++)
        {
            uint64_t hash = hashmap_hash(hashmap->table[i].entries[j].key, new_size);
            hashmap_table_t *table = &new_table[hash];
            if (table->collisions == 0)
            {
                table->entries = (hashmap_entry_t *)malloc(sizeof(hashmap_entry_t) * new_collisions);
                memset(table->entries, 0, sizeof(hashmap_entry_t) * new_collisions);
            }
            int index = table->collisions++;
            table->entries[index].key = hashmap->table[i].entries[j].key;
            table->entries[index].data = hashmap->table[i].entries[j].key;
        }
        free(hashmap->table[i].entries);
    }
    free(hashmap->table);
    hashmap->table = new_table;
    hashmap->size = new_size;
}