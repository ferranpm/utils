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
    if (list->next == NULL) { \
        list->next = list_##value_t##_new(); \
        list->item = item; \
    } \
    else list->next = list_##value_t##_add(list->next, item); \
    return list; \
} \
 \
value_t list_##value_t##_get_recursive(struct list_##value_t *list, const unsigned int index, const unsigned int count) { \
    if (index == count) return list->item; \
    return list_##value_t##_get_recursive(list->next, index, count + 1); \
} \
 \
value_t list_##value_t##_get(struct list_##value_t *list, const unsigned int index) { \
    return list_##value_t##_get_recursive(list, index, 0); \
} \
 \
struct list_##value_t* list_##value_t##_remove_recursive(struct list_##value_t *list, const unsigned int index, const unsigned int count) { \
    if (index == count) { \
        struct list_##value_t *aux = list; \
        list = list->next; \
        free(aux); \
    } \
    else list->next = list_##value_t##_remove_recursive(list->next, index, count + 1); \
    return list; \
} \
 \
struct list_##value_t* list_##value_t##_remove(struct list_##value_t *list, const unsigned int index) { \
    return list_##value_t##_remove_recursive(list, index, 0); \
} \
 \
int list_##value_t##_find_recursive(struct list_##value_t *list, const value_t value, const int index) { \
    if (list == NULL) return -1; \
    if (list->item == value) return index; \
    return list_##value_t##_find_recursive(list->next, value, index + 1); \
} \
 \
int list_##value_t##_find(struct list_##value_t *list, const value_t value) { \
    return list_##value_t##_find_recursive(list, value, 0); \
}

#endif // LIST_H
