#include <include/hashmap.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint64_t hashmap_hash(const char *key, size_t size)
{
    int hash_value = 0;
    while (*key)
    {
        hash_value = (hash_value << 5) + *key;
        key++;
    }
    return hash_value % (size - 1);
}

hashmap_t *hashmap_create(size_t size, size_t max_collisions)
{
    hashmap_t *map = (hashmap_t *)malloc(sizeof(hashmap_t));
    map->size = size;
    map->max_collisions = max_collisions;
    return map;
}

void hashmap_add(hashmap_t *hashmap, char *key, void *data)
{
start:
{
    uint64_t index = hash(key, hashmap->size);

    hashmap_table_t *table = &hashmap->table[index];
    if (table->entries == NULL || table->collisions == 0)
    {
        table->entries = (hashmap_entry_t *)malloc(sizeof(hashmap_entry_t) * hashmap->max_collisions);
        memset(table->entries, 0, sizeof(hashmap_entry_t) * hashmap->max_collisions);
        table->collisions = 0;
    }

    if (table->collisions == hashmap->max_collisions)
    {

        goto start;
    }

    uint64_t idx = table->collisions++;
    table->entries[idx].key = (char *)malloc(strlen(key));
    strcpy(table->entries[idx].key, key);
    table->entries[idx].data = data;
}
}