#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list cons(printable* car, list cdr) {
    list result = ALLOCATE(sizeof(cell));
    ((printable*)result)->to_string = (printer)to_string_list;
    result->car = car;
    result->cdr = cdr;
    return result;
}

list reverse(list input) {
    list result = NULL;
    while (input != NULL) {
        result = cons(input->car, result);
        input = input->cdr;
    }
    return result;
}

list make_list(printable** elements, size_t size) {
    size_t i;
    list result = NULL;
    
    for (i = size; i > 0; i--) result = cons(elements[i - 1], result);
    return result;
}

size_t length(list input) {
    size_t i = 0;
    list it = input;

    while (it != NULL) {
        i++;
        it = it->cdr;
    }
    return i;
}

char* to_string_list(list p) {
    list it = p;
    size_t len = length(p);
    size_t i = 0;
    size_t total = 0;
    size_t copied = 0;
    char* parts[len * 2];
    size_t lengths[len * 2];
    char* result;

    while (it != NULL) {
        char* chunk = (char*)to_string(it->car);
        parts[i * 2] = chunk;
        parts[i * 2 + 1] = ", ";
        lengths[i * 2] = strlen(chunk);
        lengths[i * 2 + 1] = 2;
        total += lengths[i * 2] + 2;
        it = it->cdr;
        i++;
    }
    result = ALLOCATE(total * sizeof(char) + 1);
    result[0] = '(';
    copied = 1;

    for (i = 0; i < len * 2; i++) {
        strcpy(result + copied, parts[i]);
        copied += lengths[i];
    }
    result[copied - 2] = ')';
    result[copied - 1] = '\0';
    return result;
}
