#include "../list.h"

LIST_INIT(int);

int list_find(struct list_int *list) {
    int index = list_int_find(list, 103);
    int not_found = list_int_find(list, 3);
    return index != 5 || not_found != -1;
}

int list() {
    struct list_int *list = list_int_new();

    list_int_add(list, 12);
    list_int_add(list, 13);
    list_int_add(list, 17);
    list_int_add(list, 78);
    list_int_add(list, 81);
    list_int_add(list, 88);
    list_int_add(list, 103);

    int first = list_int_get(list, 3);

    list_int_remove(list, 3);

    list_int_remove(list, 30);

    int second = list_int_get(list, 3);

    return first != 78 || second != 81 || list_find(list);
}

