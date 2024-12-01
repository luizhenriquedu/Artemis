#include <include/hashmap.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t hashmap_hash(char *key, size_t size)
{
    int hash_value = 0;
    while (*key)
    {
        hash_value = (hash_value << 5) + *key;
        key++;
    }
    return hash_value % size;
}

hashmap_t *hashmap_create(size_t size, size_t max_collisions)
{
    hashmap_t *map = (hashmap_t *)malloc(sizeof(hashmap_t));
    map->size = size;
    map->max_collisions = max_collisions;
    return map;
}
