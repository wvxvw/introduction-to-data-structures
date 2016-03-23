#include <stdlib.h>
#include <stdio.h>
#include <gc.h>

#include "printable.h"
#include "pair.h"

const char* to_string_pair(const pair* p) {
    char* buffer = ALLOCATE(9 * sizeof(char));
    if (p == NULL) {
        sprintf(buffer, "%p", p);
    } else {
        printable* pfirst = p->first;
        printable* plast = p->last;
        const char* first = pfirst->to_string(pfirst);
        const char* last = plast->to_string(plast);
        sprintf(buffer, "(%s, %s)", first, last);
    }
    return buffer;
}

pair* make_pair() {
    pair* result = ALLOCATE(sizeof(pair));
    ((printable*)result)->to_string = (printer)to_string_pair;
    return result;
}
