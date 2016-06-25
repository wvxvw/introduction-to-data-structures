#include <stdio.h>
#include "sortable.h"
#include "printable.h"
#include "generic.h"

sortable insertion_sort(sortable unsorted, comparison_fn_t cmp) {
    if (unsorted == NULL) return NULL;
    printable* p = unsorted;
    sortable (*fptr)(sortable, comparison_fn_t) = insertion_sort;
    sortable (*method)(sortable, comparison_fn_t) = find_method(p->type, fptr);
    CHECK_METHOD_EXISTS(method, p->type, fptr, NULL);
    return method(p, cmp);
}

sortable merge_sort(sortable unsorted, comparison_fn_t cmp) {
    if (unsorted == NULL) return NULL;
    printable* p = unsorted;
    sortable (*fptr)(sortable, comparison_fn_t) = merge_sort;
    sortable (*method)(sortable, comparison_fn_t) = find_method(p->type, fptr);
    CHECK_METHOD_EXISTS(method, p->type, fptr, NULL);
    return method(p, cmp);
}

size_t length(sortable input) {
    if (input == NULL) return 0;
    printable* p = input;
    size_t (*fptr)(sortable) = length;
    size_t (*method)(sortable) = find_method(p->type, fptr);
    CHECK_METHOD_EXISTS(method, p->type, fptr, 0);
    return method(p);
}

sortable reverse(sortable unsorted) {
    if (unsorted == NULL) return NULL;
    printable* p = unsorted;
    sortable (*fptr)(sortable) = reverse;
    sortable (*method)(sortable) = find_method(p->type, fptr);
    CHECK_METHOD_EXISTS(method, p->type, fptr, NULL);
    return method(unsorted);
}

sortable append(sortable a, sortable b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    printable* p = a;
    sortable (*fptr)(sortable, sortable) = append;
    sortable (*method)(sortable, sortable) = find_method(p->type, fptr);
    CHECK_METHOD_EXISTS(method, p->type, fptr, NULL);
    return method(a, b);
}

printable* find(sortable haystack, printable* needle, comparison_fn_t cmp) {
    if (haystack == NULL) return false;
    printable* p = haystack;
    printable* (*fptr)(sortable, printable*, comparison_fn_t) = find;
    printable* (*method)(sortable, printable*, comparison_fn_t) = find_method(p->type, fptr);
    CHECK_METHOD_EXISTS(method, p->type, fptr, NULL);
    return method(haystack, needle, cmp);
}

printable* peek(sortable container, printable* key) {
    if (container == NULL) return false;
    printable* p = container;
    printable* (*fptr)(sortable, printable*) = peek;
    printable* (*method)(sortable, printable*) = find_method(p->type, fptr);
    CHECK_METHOD_EXISTS(method, p->type, fptr, NULL);
    return method(container, key);
}

printable* put(sortable container, printable* key, printable* val) {
    if (container == NULL) return NULL;
    printable* p = container;
    printable* (*fptr)(sortable, printable*, printable*) = put;
    printable* (*method)(sortable, printable*, printable*) = find_method(p->type, fptr);
    CHECK_METHOD_EXISTS(method, p->type, fptr, NULL);
    return method(container, key, val);
}

printable* pop(sortable container, printable* key) {
    if (container == NULL) return NULL;
    printable* p = container;
    printable* (*fptr)(sortable, printable*) = pop;
    printable* (*method)(sortable, printable*) = find_method(p->type, fptr);
    CHECK_METHOD_EXISTS(method, p->type, fptr, NULL);
    return method(container, key);
}

printable* first(sortable container) {
    if (container == NULL) return NULL;
    printable* p = container;
    printable* (*fptr)(sortable) = first;
    printable* (*method)(sortable) = find_method(p->type, fptr);
    CHECK_METHOD_EXISTS(method, p->type, fptr, NULL);
    return method(container);
}

printable* rest(sortable container) {
    if (container == NULL) return NULL;
    printable* p = container;
    printable* (*fptr)(sortable) = rest;
    printable* (*method)(sortable) = find_method(p->type, fptr);
    CHECK_METHOD_EXISTS(method, p->type, fptr, NULL);
    return method(container);
}
