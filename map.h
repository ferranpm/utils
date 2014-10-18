#ifndef MAP_H
#define MAP_H

#include <stdlib.h>

#define MAP_INIT(                                                                           \
        key_t          , value_t,                                                           \
        malloc_key_func, malloc_value_func,                                                 \
        asign_key_func , asign_value_func,                                                  \
        hash_func      ,                                                                    \
        cmp_key_func                                                                        \
        )                                                                                   \
                                                                                            \
struct node {                                                                               \
    key_t key;                                                                              \
    value_t value;                                                                          \
    struct node* next;                                                                      \
};                                                                                          \
                                                                                            \
struct map {                                                                                \
    unsigned int key;                                                                       \
    struct map *left;                                                                       \
    struct map *right;                                                                      \
    struct node *node;                                                                      \
};                                                                                          \
                                                                                            \
void map_init(struct map **map) {                                                           \
    *map = NULL;                                                                            \
}                                                                                           \
                                                                                            \
void map_inner_put_node(struct node **node, key_t key, value_t value) {                     \
    if (*node == NULL) {                                                                    \
        *node = malloc(sizeof(struct node));                                                \
        (*node)->key = malloc_key_func(key);                                                \
        asign_key_func(&((*node)->key), &key);                                              \
        (*node)->value = malloc_value_func(value);                                          \
        asign_value_func(&((*node)->value), &value);                                        \
        (*node)->next = NULL;                                                               \
    }                                                                                       \
    else map_inner_put_node(&(*node)->next, key, value);                                    \
}                                                                                           \
                                                                                            \
void map_inner_insert(struct map **map, key_t key, value_t value, unsigned int hashed) {    \
    if (*map == NULL) {                                                                     \
        *map = malloc(sizeof(struct map));                                                  \
        (*map)->key = hashed;                                                               \
        (*map)->left = NULL;                                                                \
        (*map)->right = NULL;                                                               \
        (*map)->node = NULL;                                                                \
        map_inner_put_node(&(*map)->node, key, value);                                      \
    }                                                                                       \
    else {                                                                                  \
        if ((*map)->key == hashed) map_inner_put_node(&(*map)->node, key, value);           \
        else if (hashed < (*map)->key) map_inner_insert(&(*map)->left, key, value, hashed); \
        else map_inner_insert(&(*map)->right, key, value, hashed);                          \
    }                                                                                       \
}                                                                                           \
                                                                                            \
void map_insert(struct map **map, key_t key, value_t value) {                               \
    unsigned int hashed_key = hash_func(key);                                               \
    map_inner_insert(map, key, value, hashed_key);                                          \
}                                                                                           \
                                                                                            \
struct node* map_inner_get_node(struct node *node, key_t key) {                             \
    if (node == NULL) return NULL;                                                          \
    if (cmp_key_func(node->key, key)) return node;                                          \
    return map_inner_get_node(node->next, key);                                             \
}                                                                                           \
                                                                                            \
value_t map_inner_get(struct map *map, key_t key, unsigned int hashed_key) {                \
    if (map == NULL) return 0;                                                              \
    if (map->key == hashed_key) return map_inner_get_node(map->node, key)->value;           \
    else if (hashed_key < map->key) return map_inner_get(map->left, key, hashed_key);       \
    return map_inner_get(map->right, key, hashed_key);                                      \
}                                                                                           \
                                                                                            \
value_t map_get(struct map *map, key_t key) {                                               \
    unsigned int hashed_key = hash_func(key);                                               \
    return map_inner_get(map, key, hashed_key);                                             \
}

#endif // MAP_H
