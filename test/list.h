#include "../list.h"

LIST_INIT(int);

int list() {
    struct list_int *list = list_int_new();

    list_int_add(list, 12);
    list_int_add(list, 13);
    list_int_add(list, 17);
    list_int_add(list, 78);
    list_int_add(list, 81);
    list_int_add(list, 88);
    list_int_add(list, 103);

    int first = *list_int_get(list, 3);
    list_int_delete(list, 3);
    int second = *list_int_get(list, 3);

    return first != 78 || second != 81;
}

