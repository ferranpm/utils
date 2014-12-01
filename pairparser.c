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

    string k, v;
    strncpy(k.x, txt, sa - txt);
    k.x[sa - txt] = 0;
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

char* pairparser_get(struct pairparser *pp, char *key) {
    string *k = (string*)malloc(sizeof(string));
    char *buff = (char*)malloc(sizeof(char)*50);

    strcpy(k->x, key);
    k = map_string_string_get(pp->map, *k);
    strcpy(buff, k->x);

    return buff;
}
