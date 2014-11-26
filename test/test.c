#include <stdio.h>
#include "clientserver.h"
#include "pairparser.h"
#include "map.h"
#include "list.h"
#include "matrix.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"

struct test {
    int (*function)();
    char *text;
};

struct test tests[] = {
    { map, "map" },
    { list, "list" },
    { clientserver, "clientserver"},
    { pairparser, "pairparser" },
    { matrix, "matrix" },
    { NULL, NULL}
};

int main(int argc, char *argv[]) {
    int i;

    for (i = 0; tests[i].function != NULL; i++) {
        printf("%s", tests[i].text);
        if (tests[i].function() != 0)
            printf("\t--> %sERROR%s\n", KRED, KNRM);
        else
            printf("\t--> %sOK%s\n", KGRN, KNRM);
    }

    return 0;
}
