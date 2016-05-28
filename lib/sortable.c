#include "sortable.h"
#include "printable.h"
#include "generic.h"

sortable insertion_sort(sortable unsorted, comparison_fn_t cmp) {
    if (unsorted == NULL) return NULL;
    printable* p = (printable*)unsorted;
    sortable (*fptr)(sortable, comparison_fn_t) = insertion_sort;
    sortable (*method)(sortable, comparison_fn_t) = find_method(p->type, fptr);
    return method(p, cmp);
}

sortable merge_sort(sortable unsorted, comparison_fn_t cmp) {
    if (unsorted == NULL) return NULL;
    printable* p = (printable*)unsorted;
    sortable (*fptr)(sortable, comparison_fn_t) = merge_sort;
    sortable (*method)(sortable, comparison_fn_t) = find_method(p->type, fptr);
    return method(p, cmp);
}

size_t length(sortable input) {
    if (input == NULL) return 0;
    printable* p = (printable*)input;
    size_t (*fptr)(sortable) = length;
    size_t (*method)(sortable) = find_method(p->type, fptr);
    return method(p);
}
