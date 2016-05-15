#include <stdio.h>
#include <stdlib.h>

#include "printable.h"

printable* make_printable(size_t size, void* data) {
    printable* result = ALLOCATE(sizeof(printable));
    result->size = size;
    result->val = data;
    return result;
}

char* to_string_default(printable* p) {
    char* buffer = ALLOCATE(9 * sizeof(char));
    sprintf(buffer, "%p", p->val);
    return buffer;
}

char* to_string(printable* p) {
    if (p == NULL) return "NULL";
    return p->to_string(p);
}
