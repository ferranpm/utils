#include "pairparser.h"

#include <string.h>

#define MAX_KEYS 1024

struct pairparser {
    struct map_string_string *map;
};

// Hem de declarar aixi els strings per a evitar que
// hi hagi segmentation faults degut a les operacions
// que es fan en map_string_string
typedef struct { char x[50]; } string;

void string_assign(string *a, const string *b) {
    strcpy(a->x, b->x);
}

unsigned int string_hash_function(string k) {
    char *p = k.x;
    unsigned int res = *p;
    while (*(++p) != '\0') res *= *p;
    return res%MAX_KEYS;
}

int string_compare(string a, string b) {
    return strcmp(a.x, b.x) != 0;
}

MAP_INIT(
        string              , string,
        string_assign       , string_assign,
        string_hash_function,
        string_compare
        );

/////////////////////////////////
// PAIRPARSER PUBLIC FUNCTIONS //
/////////////////////////////////
struct pairparser* pairparser_new(char *txt, const char a, const char b) {
    struct pairparser *pp = (struct pairparser*)malloc(sizeof(struct pairparser));
    pp->map = map_string_string_new();

    char *t1 = txt;
    char *t0 = txt;
    int size;
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

        string k, v;
        strcpy(k.x, key);
        strcpy(v.x, value);
        map_string_string_insert(pp->map, k, v);
    }
    return pp;
}

char* pairparser_get(struct pairparser *pp, char *key) {
    string *k = (string*)malloc(sizeof(string));
    char *buff = (char*)malloc(sizeof(char)*50);

    strcpy(k->x, key);
    k = map_string_string_get(pp->map, *k);
    strcpy(buff, k->x);

    return buff;
}
