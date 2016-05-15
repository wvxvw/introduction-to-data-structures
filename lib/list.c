#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "strings.h"

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

list append(list a, list b) {
    list result = NULL;
    while (a != NULL) {
        result = cons(a->car, result);
        a = a->cdr;
    }
    while (b != NULL) {
        result = cons(b->car, result);
        b = b->cdr;
    }
    return reverse(result);
}

list merge(list odds, list evens, comparison_fn_t cmp) {
    list result = NULL;
    odds = merge_sort(odds, cmp);
    evens = merge_sort(evens, cmp);
    printf("merging\n");
    printf("odds: %s\n", to_string((printable*)odds));
    printf("evens: %s\n", to_string((printable*)evens));
    while (true) {
        if (odds == NULL) return append(reverse(result), evens);
        if (evens == NULL) return append(reverse(result), odds);
        if (cmp(&odds->car, &evens->car) <= 0) {
            result = cons(odds->car, result);
            odds = odds->cdr;
        } else {
            result = cons(evens->car, result);
            evens = evens->cdr;
        }
    }
    return NULL;
}

list merge_sort(list in, comparison_fn_t cmp) {
    if (in == NULL) return NULL;
    if (in->cdr == NULL) return in;
    
    list odds = NULL, evens = NULL, it = in;
    size_t i = 0;
    
    while (it != NULL) {
        if ((i & 1) == 1) odds = cons(it->car, odds);
        else evens = cons(it->car, evens);
        it = it->cdr;
        i++;
    }
    return merge(reverse(odds), reverse(evens), cmp);
}

char* to_string_list(list p) {
    list it = p;
    size_t i = 0, len = length(p);
    char** parts = malloc(len * sizeof(char*));
    char* contents, *result;

    while (it != NULL) {
        char* chunk = (char*)to_string(it->car);
        parts[i] = chunk;
        it = it->cdr;
        i++;
    }
    contents = join(parts, len, ", ");
	result = ALLOCATE(sizeof(char) * (strlen(contents) + 3));
	sprintf(result, "(%s)", contents);
    free(parts);
    return result;
}
