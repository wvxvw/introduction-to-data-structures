#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "generic.h"
#include "array.h"
#include "printable_int.h"

DEFTYPE(printable_int);

size_t ints_comparation_count = 0;

void start_int_cmp_count() { ints_comparation_count = 0; }

size_t get_int_cmp_count() { return ints_comparation_count; }

int compare_ints(const void* a, const void* b) {
    const printable* pa = *(printable* const *)a;
    const printable* pb = *(printable* const *)b;

    ints_comparation_count++;
    if (pa == pb) return 0;
    if (pa == NULL) return -1;
    if (pb == NULL) return 1;
    
    if (pa->val == pb->val) return 0;
    if (pa->val == NULL) return -1;
    if (pb->val == NULL) return 1;

    const int* ia = (int*)pa->val;
    const int* ib = (int*)pb->val;
    return (*ia > *ib) - (*ia < *ib);
}

int compare_ints_reverse(const void* a, const void* b) {
    return -compare_ints(a, b);
}

char* to_string_int(const printable_int* p) {
    char* buffer = ALLOCATE(11 * sizeof(char));
    printable* base = (printable*)p;
    
    if (base->val == NULL) sprintf(buffer, "%p", base->val);
    else sprintf(buffer, "%d", *(int*)base->val);
    return buffer;
}

printable_int* make_printable_int(const int val) {
    printable_int* result = ALLOCATE(sizeof(printable_int));
    printable* p = (printable*)result;
    p->type = printable_int_type();
    define_method(p->type, to_string, to_string_int);
    p->size = sizeof(printable_int*);
    p->val = ALLOCATE(sizeof(int));
    *(int*)p->val = val;
    return result;
}

printable* int_element_generator(void* elt) {
    return (printable*)make_printable_int(*(int*)elt);
}

size_t int_element_normalizer(
    printable* elt, printable* min, printable* max, size_t range) {
    int e = *(int*)elt->val;
    int x = *(int*)max->val;
    int n = *(int*)min->val;
    if (x == n) return 0;
    return (size_t)(range * (e - n) / (x - n));
}
