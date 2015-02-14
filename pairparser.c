#include "pairparser.h"

#include <string.h>

#define MAX_KEYS 1024

struct pairparser {
    struct map_string_string *map;
};

#ifndef STR_SIZE
#define STR_SIZE 20
#endif

typedef struct {char x[STR_SIZE];} string;

void string_assign(string *a, const string *b) {
    strcpy(a->x, b->x);
}

unsigned int string_hash_function(const string k) {
    int i;
    unsigned int res = 1;
    for (i = 0; i < STR_SIZE; i++) res *= k.x[i];
    return res%MAX_KEYS;
}

int string_compare(const string *a, const string *b) {
    return strcmp(a->x, b->x) != 0;
}

MAP_INIT(
        string              , string,
        string_assign       , string_assign,
        string_hash_function,
        string_compare
        );

struct pairparser* pairparser_inner_new(struct pairparser* pp, char *txt, const char a, const char b) {
    char *sa = index(txt, a);
    char *sb = index(txt, b);

    if (sa == NULL) return pp;
    else if (sb == NULL) sb = txt + strlen(txt);

    string k;
    strncpy(k.x, txt, sa - txt);
    k.x[sa - txt] = 0;

    string v;
    strncpy(v.x, sa + 1, sb - sa - 1);
    v.x[sb - sa - 1] = 0;

    map_string_string_insert(pp->map, k, v);

    pairparser_inner_new(pp, sb + 1, a, b);
    return pp;
}

/////////////////////////////////
// PAIRPARSER PUBLIC FUNCTIONS //
/////////////////////////////////
struct pairparser* pairparser_new(char *txt, const char a, const char b) {
    struct pairparser *pp = (struct pairparser*)malloc(sizeof(struct pairparser));
    pp->map = map_string_string_new();
    pp = pairparser_inner_new(pp, txt, a, b);
    return pp;
}

void pairparser_delete(struct pairparser *pp) {
    map_string_string_delete(pp->map);
    free(pp);
}

char* pairparser_get(struct pairparser *pp, char *key) {
    string *buff;
    string k;
    strcpy(k.x, key);
    if ((buff = map_string_string_get(pp->map, k)) == NULL) return NULL;
    return buff->x;
}
