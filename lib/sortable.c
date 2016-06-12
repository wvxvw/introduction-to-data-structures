#include <stdio.h>
#include "sortable.h"
#include "printable.h"
#include "generic.h"

sortable insertion_sort(sortable unsorted, comparison_fn_t cmp) {
    if (unsorted == NULL) return NULL;
    printable* p = unsorted;
    sortable (*fptr)(sortable, comparison_fn_t) = insertion_sort;
    sortable (*method)(sortable, comparison_fn_t) = find_method(p->type, fptr);
    return method(p, cmp);
}

sortable merge_sort(sortable unsorted, comparison_fn_t cmp) {
    if (unsorted == NULL) return NULL;
    printable* p = unsorted;
    sortable (*fptr)(sortable, comparison_fn_t) = merge_sort;
    sortable (*method)(sortable, comparison_fn_t) = find_method(p->type, fptr);
    return method(p, cmp);
}

size_t length(sortable input) {
    if (input == NULL) return 0;
    printable* p = input;
    size_t (*fptr)(sortable) = length;
    size_t (*method)(sortable) = find_method(p->type, fptr);
    return method(p);
}

sortable reverse(sortable unsorted) {
    if (unsorted == NULL) return NULL;
    printable* p = unsorted;
    sortable (*fptr)(sortable) = reverse;
    sortable (*method)(sortable) = find_method(p->type, fptr);
    return method(unsorted);
}

sortable append(sortable a, sortable b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    printable* p = a;
    sortable (*fptr)(sortable, sortable) = append;
    sortable (*method)(sortable, sortable) = find_method(p->type, fptr);
    return method(a, b);
}

printable* find(sortable haystack, printable* needle) {
    if (haystack == NULL) return false;
    printable* p = haystack;
    printable* (*fptr)(sortable, printable*) = find;
    printable* (*method)(sortable, printable*) = find_method(p->type, fptr);
    return method(haystack, needle);
}
