#ifndef PAIRPARSER_H
#define PAIRPARSER_H

#include "map.h"
#include <string.h>

#define MAX_KEYS 1024

typedef char* string;

char* string_malloc(string);
void string_assign(string *, string *);
unsigned int string_hash_function(string);
int string_compare(string, string);

struct PairParser {
    struct map_string_string *map;
};

void pp_init(struct PairParser *, char *, char, char);
char* pp_get(struct PairParser *, char *);

#endif // PAIRPARSER_H
