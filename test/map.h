#include "../map.h"

void int_assign(int *dst, const int *src) {
    *dst = *src;
}

unsigned int int_hash(const int x) {
    return x%20;
}

int int_cmp(const int *x, const int *y) {
    return *x != *y;
}

MAP_INIT(
        int, int,
        int_assign, int_assign,
        int_hash,
        int_cmp);

int map() {
    struct map_int_int *map = map_int_int_new();

    map_int_int_insert(map, 1, 10);
    map_int_int_insert(map, 3, 30);
    map_int_int_insert(map, 4, 40);
    map_int_int_insert(map, 2, 20);

    int a = *map_int_int_get(map, 3);
    int b = *map_int_int_get(map, 4);
    int c = *map_int_int_get(map, 1);

    return a != 30 || b != 40 || c != 10;
}
