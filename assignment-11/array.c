#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    result = malloc(total * sizeof(char) + 1);
    result[0] = '[';
    copied = 1;
    
    for (i = 0; i < p->length * 2 - 1; i++) {
        strcpy(result + copied, parts[i]);
        copied += lenghts[i];
    }
    result[copied] = ']';
    result[copied + 1] = '\0';
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

void free_array(array* freed) {
    free(freed);
}

array* sorted(array* unsorted, comparison_fn_t cmp) {
    qsort(unsorted->elements, unsorted->length, unsorted->elements[0]->size, cmp);
    return unsorted;
}

array* shuffled(array* sorted) {
    size_t i;
    time_t t;

    srand((unsigned)time(&t));
    
    for (i = 0; i < sorted->length; i++) {
        size_t j = i + rand() / (RAND_MAX / (sorted->length - i) + 1);
        printable* elt = sorted->elements[j];
        sorted->elements[j] = sorted->elements[i];
        sorted->elements[i] = elt;
    }
    return sorted;
}

array* slice(const array* input, const size_t from, const size_t to) {
    printable** elts = input->elements;
    printable** offset = &elts[from];
    return make_array(to - from, offset);
}
