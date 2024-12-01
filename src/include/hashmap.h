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

hashmap_t *hashmap_create(size_t size, size_t collisions);
uint64_t hashmap_hash(const char *key, size_t size);
void *hashmap_get(hashmap_t *hm, char *key);
void hashmap_resize(hashmap_t *hm, uint64_t new_size, uint64_t max_collisions);
void hashmap_import(hashmap_t *to, hashmap_t *from);
void hashmap_destroy(hashmap_t *hm);
void hashmap_destroy_free_items(hashmap_t *hm);