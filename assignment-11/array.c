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
    char* parts[p->length * 2];
    int lenghts[p->length * 2];
    char* result;
    size_t i, copied, total = 0;

    for (i = 0; i < p->length; i++) {
        printable* elt = p->elements[i];
        char* chunk = (char*)elt->to_string(elt);
        parts[i * 2] = chunk;
        parts[i * 2 + 1] = ", ";
        lenghts[i * 2] = strlen(chunk);
        lenghts[i * 2 + 1] = 2;
        total += lenghts[i * 2] + 2;
    }
    result = malloc(total * sizeof(char));
    result[0] = '[';
    copied = 1;
    
    for (i = 0; i < p->length * 2 - 1; i++) {
        strcpy(result + copied, parts[i]);
        copied += lenghts[i];
    }
    result[copied] = ']';
    return result;
}

printable* make_printable(size_t size, void* data) {
    printable* result = malloc(sizeof(printable));
    result->size = size;
    result->val = data;
    return result;
}

array* make_array(const size_t size, printable** data) {
    array* result = malloc(sizeof(array));
    size_t i = 0;
    result->length = size;
    result->elements = malloc(size * sizeof(printable));
    result->printable.to_string = (printer)to_string_array;
    
    while (i < size) {
        result->elements[i] = data[i];
        i++;
    }
    return result;
}

const array* sorted(const array* unsorted, comparison_fn_t cmp) {
    qsort(unsorted->elements, unsorted->length, unsorted->elements[0]->size, cmp);
    return unsorted;
}
