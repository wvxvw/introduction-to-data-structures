#include <stdio.h>
#include <stdlib.h>

#include "printable.h"
#include "generic.h"

DEFTYPE(printable);

char* to_string_default(printable* p) {
    char* buffer = ALLOCATE(9 * sizeof(char));
    sprintf(buffer, "%p", p->val);
    return buffer;
}

char* to_string(printable* p) {
    if (p == NULL) return "NULL";
    char* (*fptr)(printable*) = to_string;
    char* (*method)(printable*) = find_method(p->type, fptr);
    return method(p);
}

printable* make_printable(size_t size, void* data) {
    printable* result = ALLOCATE(sizeof(printable));
    result->size = size;
    result->val = data;
    result->type = printable_type();
    define_method(result->type, to_string, to_string_default);
    return result;
}
