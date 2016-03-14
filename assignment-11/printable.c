#include <stdio.h>
#include <stdlib.h>

#include "printable.h"

printable* make_printable(size_t size, void* data) {
    printable* result = malloc(sizeof(printable));
    result->size = size;
    result->val = data;
    return result;
}

const char* to_string_default(const printable* p) {
    char* buffer = malloc(9 * sizeof(char));
    sprintf(buffer, "%p", p->val);
    return buffer;
}

const char* to_string(const printable* p) { return p->to_string(p); }
