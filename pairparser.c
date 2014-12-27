#include "pairparser.h"

#include <string.h>

#define MAX_KEYS 1024

struct pairparser {
    struct map_string_string *map;
};

typedef char* string;

void string_assign(char **a, char * const *b) {
    *a = (char*)malloc(strlen(*b)*sizeof(char) + 1);
    strcpy(*a, *b);
}

unsigned int string_hash_function(char *k) {
    char *p = k;
    unsigned int res = *p;
    while (*(++p) != '\0') res *= *p;
    return res%MAX_KEYS;
}

int string_compare(char * const *a, char * const *b) {
    return strcmp(*a, *b) != 0;
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

    char *k = (char*)malloc((sa - txt + 1)*sizeof(char));
    strncpy(k, txt, sa - txt);
    k[sa - txt] = 0;

    char *v = (char*)malloc((sb - sa)*sizeof(char));
    strncpy(v, sa + 1, sb - sa - 1);
    v[sb - sa - 1] = 0;

    map_string_string_insert(pp->map, k, v);

    free(k);
    free(v);

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

char* pairparser_get(struct pairparser *pp, char *key) {
    char **buff;
    if ((buff = map_string_string_get(pp->map, key)) == NULL) return NULL;
    return *buff;
}
