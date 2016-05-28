#include <stdlib.h>
#include <stdio.h>

#include "printable.h"
#include "generic.h"
#include "pair.h"

DEFTYPE(pair);

const char* to_string_pair(const pair p) {
    char* buffer = ALLOCATE(9 * sizeof(char));
    if (p == NULL) {
        sprintf(buffer, "%p", p);
    } else {
        printable* pfirst = p->first;
        printable* plast = p->last;
        const char* first = to_string(pfirst);
        const char* last = to_string(plast);
        sprintf(buffer, "(%s, %s)", first, last);
    }
    return buffer;
}

pair make_pair() {
    pair result = ALLOCATE(sizeof(printable_pair));
    printable* presult = (printable*)result;
    presult->type = pair_type();
    define_method(presult->type, to_string, to_string_pair);
    return result;
}
