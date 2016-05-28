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
