#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

const char* to_string_default(const printable* p) {
    char* buffer = malloc(9 * sizeof(char));
    sprintf(buffer, "%p", p->val);
    return buffer;
}

const char* to_string_array(const array* p) {
    const char** parts = malloc(p->length * sizeof(char*));
    char* result;
    int lenghts[p->length];
    size_t i, copied, total = 0;
    
    for (i = 0; i < p->length; i++) {
        printable* elt = p->elements[i];
        const char* chunk = elt->to_string(elt);
        parts[i] = chunk;
        lenghts[i] = strlen(chunk);
        total += lenghts[i];
    }
    result = malloc(total + 1);
    for (i = 0; i < p->length; i++) {
        strcpy(result + copied, parts[i]);
        copied += lenghts[i];
    }
    return result;
}

printable* make_printable(size_t size, void* data) {
    printable* result = malloc(sizeof(printable));
    result->size = size;
    result->val = data;
    return result;
}

array* make_array(size_t size, printable** const data) {
    array* result = malloc(sizeof(array));
    result->length = size;
    result->elements = malloc(size * sizeof(printable));
    
    while (size > 0) {
        result->elements[size] = data[size];
        size--;
    }
    return result;
}

const array* sorted(const array* unsorted, comparison_fn_t cmp) {
    qsort(unsorted->elements, unsorted->length, unsorted->elements[0]->size, cmp);
    return unsorted;
}
