#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/**
 * \brief This macro creates all the necessary code for a new list with the type value_t
 *
 * \param value_t the type of the values to store in the list
 */
#define LIST_INIT(value_t) \
 \
struct list_##value_t { \
    value_t item; \
    struct list_##value_t *next; \
}; \
 \
struct list_##value_t* list_##value_t##_new() { \
    struct list_##value_t *list = (struct list_##value_t*)malloc(sizeof(struct list_##value_t)); \
    list->next = NULL; \
    return list; \
} \
 \
struct list_##value_t* list_##value_t##_add(struct list_##value_t *list, const value_t item) { \
    if (list == NULL) { \
        list = list_##value_t##_new(); \
        list->item = item; \
    } \
    else list->next = list_##value_t##_add(list->next, item); \
    return list; \
} \
 \
struct list_##value_t* list_##value_t##_find_node(struct list_##value_t *list, unsigned int index, unsigned int count) { \
    if (list == NULL) return NULL; \
    if (index != count) return list_##value_t##_find_node(list->next, index, ++count); \
    return list; \
} \
 \
value_t* list_##value_t##_get(struct list_##value_t *list, unsigned int index) { \
    struct list_##value_t *tmp = list_##value_t##_find_node(list, index, -1); \
    if (tmp != NULL) return &(tmp->item); \
    return NULL; \
} \
 \
void list_##value_t##_delete(struct list_##value_t *list, unsigned int index) { \
    struct list_##value_t *prev = list_##value_t##_find_node(list, index-1, -1); \
    struct list_##value_t *node = list_##value_t##_find_node(list, index, -1); \
    struct list_##value_t *next = list_##value_t##_find_node(list, index+1, -1); \
    free(node); \
    if (prev != NULL && next != NULL) prev->next = next; \
}

#endif // LIST_H
