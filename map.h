#ifndef MAP_H
#define MAP_H

#include <stdlib.h>

/**
  * This macro creates all the necessary code for a new type of map.
  *
  * \param key_t
  *     the type used for the keys
  * \param value_t
  *     the type used for the values
  * \param assign_key_func
  *     a pointer to a function that asigns to a variable the value of
  *     another, signature: void f(key_t *dest, const key_t *orig)
  * \param assign_value_func
  *     a pointer to a function that asigns to a variable the value of
  *     another, signature: void f(value_t *dest, const value_t *orig)
  * \param hash_func
  *     a pointer to a function that hashes keys
  *     the signature is unsigned int f(const key_t);
  * \param cmp_key_func
  *     a pointer to a function that compares two key_t
  *     the signature is int f(const key_t*, const key_t*);
  */
#define MAP_INIT( \
        key_t          , value_t, \
        assign_key_func, assign_value_func, \
        hash_func      , \
        cmp_key_func \
        ) \
 \
struct node_##key_t##_##value_t { \
    key_t key; \
    value_t value; \
    struct node_##key_t##_##value_t* next; \
}; \
 \
struct map_##key_t##_##value_t { \
    unsigned int key; \
    struct map_##key_t##_##value_t *left; \
    struct map_##key_t##_##value_t *right; \
    struct node_##key_t##_##value_t *node; \
}; \
 \
struct map_##key_t##_##value_t* map_##key_t##_##value_t##_new() { \
    struct map_##key_t##_##value_t *map = (struct map_##key_t##_##value_t *)malloc(sizeof(struct map_##key_t##_##value_t)); \
    map->left = NULL; \
    map->right = NULL; \
    map->node = NULL; \
    return map; \
} \
 \
struct node_##key_t##_##value_t* map_##key_t##_##value_t##_inner_insert_node(struct node_##key_t##_##value_t *node, const key_t *key, const value_t *value) { \
    if (node == NULL) { \
        node = malloc(sizeof(struct node_##key_t##_##value_t)); \
        assign_key_func(&(node->key), key); \
        assign_value_func(&(node->value), value); \
        node->next = NULL; \
    } \
    else node->next = map_##key_t##_##value_t##_inner_insert_node(node->next, key, value); \
    return node; \
} \
 \
struct map_##key_t##_##value_t* map_##key_t##_##value_t##_inner_insert(struct map_##key_t##_##value_t *map, const key_t *key, const value_t *value, unsigned int hashed) { \
    if (map == NULL) map = map_##key_t##_##value_t##_new(); \
    if (map->node == NULL) { \
        map->key = hashed; \
        map->node = map_##key_t##_##value_t##_inner_insert_node(map->node, key, value); \
    } \
    else { \
        if (map->key == hashed) map->node = map_##key_t##_##value_t##_inner_insert_node(map->node, key, value); \
        else if (hashed < map->key) map->left = map_##key_t##_##value_t##_inner_insert(map->left, key, value, hashed); \
        else map->right = map_##key_t##_##value_t##_inner_insert(map->right, key, value, hashed); \
    } \
    return map; \
} \
 \
void map_##key_t##_##value_t##_insert(struct map_##key_t##_##value_t *map, const key_t key, const value_t value) { \
    unsigned int hashed_key = hash_func(key); \
    map_##key_t##_##value_t##_inner_insert(map, &key, &value, hashed_key); \
} \
 \
struct node_##key_t##_##value_t* map_##key_t##_##value_t##_inner_get_node(struct node_##key_t##_##value_t *node, key_t key) { \
    if (node == NULL) return NULL; \
    if (cmp_key_func(&(node->key), &key) == 0) return node; \
    return map_##key_t##_##value_t##_inner_get_node(node->next, key); \
} \
 \
value_t* map_##key_t##_##value_t##_inner_get(struct map_##key_t##_##value_t *map, key_t key, unsigned int hashed_key) { \
    if (map == NULL) return NULL; \
    if (map->key == hashed_key) { \
        struct node_##key_t##_##value_t *node = map_##key_t##_##value_t##_inner_get_node(map->node, key); \
        if (node != NULL) return &(node->value); \
        return NULL; \
    } \
    else if (hashed_key < map->key) return map_##key_t##_##value_t##_inner_get(map->left, key, hashed_key); \
    return map_##key_t##_##value_t##_inner_get(map->right, key, hashed_key); \
} \
 \
value_t* map_##key_t##_##value_t##_get(struct map_##key_t##_##value_t *map, key_t key) { \
    unsigned int hashed_key = hash_func(key); \
    return map_##key_t##_##value_t##_inner_get(map, key, hashed_key); \
}

#endif // MAP_H
