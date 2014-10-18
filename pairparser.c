#include "pairparser.h"

MAP_INIT(
        string              , string,
        string_malloc       , string_malloc,
        string_assign       , string_assign,
        string_hash_function,
        string_compare
        );

char* string_malloc(string x) {
    return malloc(sizeof(strlen(x)) * sizeof(char));
}

void string_assign(string *a, string *b) {
    strcpy(*a, *b);
}

unsigned int string_hash_function(string k) {
    char *p = k;
    unsigned int res = *p;
    while (*(++p) != '\0') res *= *p;
    return res%MAX_KEYS;
}

int string_compare(string a, string b) {
    return strcmp(a, b) == 0;
}

void pp_init(struct PairParser *pp, char *txt, char a, char b) {
    char *t1 = txt;
    char *t0 = txt;
    int size;
    map_string_string_init(&(pp->map));
    // TODO: Refactor
    while (*t1 != '\0') {
        // Get the key
        while (*(++t1) != a);
        size = t1 - t0;
        char key[size + 1];
        strncpy(key, t0, sizeof(char) * size);
        key[size] = '\0';
        t1++;
        t0 = t1;

        // Get the value
        while (*(++t1) != b && *t1 != '\0');
        size = t1 - t0;
        char value[size + 1];
        strncpy(value, t0, size);
        value[size] = '\0';
        if (*t1 != '\0') t1++;
        t0 = t1;

        map_string_string_insert(&(pp->map), key, value);
    }
}

char* pp_get(struct PairParser *pp, char *key) {
    return map_string_string_get(pp->map, key);
}
