#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <gc.h>

#include "array.h"
#include "printable_int.h"

size_t ints_comparation_count = 0;

void start_int_cmp_count() { ints_comparation_count = 0; }

size_t get_int_cmp_count() { return ints_comparation_count; }

int compare_ints(const void* a, const void* b) {
    const printable* pa = *(printable* const *)a;
    const printable* pb = *(printable* const *)b;
    if (pa == pb) return 0;
    if (pa == NULL) return -1;
    if (pb == NULL) return 1;
    
    if (pa->val == pb->val) return 0;
    if (pa->val == NULL) return -1;
    if (pb->val == NULL) return 1;

    ints_comparation_count++;
    const int* ia = (int*)pa->val;
    const int* ib = (int*)pb->val;
    return (*ia > *ib) - (*ia < *ib);
}

int compare_ints_reverse(const void* a, const void* b) {
    return -compare_ints(a, b);
}

const char* to_string_int(const printable_int* p) {
    char* buffer = ALLOCATE(9 * sizeof(char));
    printable* base = (printable*)p;
    
    if (base->val == NULL) {
        sprintf(buffer, "%p", base->val);
    } else {
        sprintf(buffer, "%d", *(int*)base->val);
    }
    return buffer;
}

printable_int* make_printable_int(const int val) {
    printable_int* result = ALLOCATE(sizeof(printable_int));
    printable* p = (printable*)result;
    
    p->to_string = (printer)to_string_int;
    p->size = sizeof(printable_int*);
    p->val = ALLOCATE(sizeof(int));
    *(int*)p->val = val;
    return result;
}

printable* int_element_generator(void* elt) {
    return (printable*)make_printable_int(*(int*)elt);
}
