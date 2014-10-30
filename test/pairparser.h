#include <string.h>
#include "../pairparser.h"

int pairparser() {
    struct pairparser *p = pairparser_new("hello=how&are=you&Im=fine&thanks=you", '=', '&');
    return strcmp(pairparser_get(p, "Im"), "fine") != 0;
}
