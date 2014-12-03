#include <string.h>
#include "../pairparser.h"

int pairparser() {
    struct pairparser *p = pairparser_new("hello=how&are=you&Im=fine&thanks=you", '=', '&');
    return
        strcmp(pairparser_get(p, "hello"), "how") != 0
        || strcmp(pairparser_get(p, "are"), "you") != 0
        || strcmp(pairparser_get(p, "Im"), "fine") != 0
        || strcmp(pairparser_get(p, "thanks"), "you") != 0
        || pairparser_get(p, "tanks") != NULL;
        ;
}
