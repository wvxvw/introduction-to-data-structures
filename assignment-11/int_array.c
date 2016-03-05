#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "array.h"
#include "int_array.h"

int compare_ints(const void* a, const void* b) {
    const printable* pa = *(printable* const *)a;
    const printable* pb = *(printable* const *)b;
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

const char* to_string_int(const printable_int* p) {
    char* buffer = malloc(9 * sizeof(char));
    printable* base = (printable*)p;
    
    if (base->val == NULL) {
        sprintf(buffer, "%p", base->val);
    } else {
        sprintf(buffer, "%d", *(int*)base->val);
    }
    return buffer;
}

array* make_random_array(const size_t size, const size_t low, const size_t high) {
    printable_int** ints = malloc(size * sizeof(printable_int*));
    size_t i = 0;
    time_t t;

    srand((unsigned)time(&t));
    
    while (i < size) {
        printable_int* pint = malloc(sizeof(printable_int));
        printable* elt = ((printable*)pint);
        elt->to_string = (printer)to_string_int;
        elt->size = sizeof(printable_int*);
        elt->val = malloc(sizeof(int));
        *(int*)elt->val = (int)(low + rand() % (high - low));
        ints[i] = pint;
        i++;
    }
    return sorted(make_array(size, (printable**)ints), compare_ints);
}

array* make_dense_sorted_array(const size_t size, const size_t from) {
    printable_int** ints = malloc(size * sizeof(printable_int*));
    size_t i = 0;
    
    while (i < size) {
        printable_int* pint = malloc(sizeof(printable_int));
        printable* elt = ((printable*)pint);
        elt->to_string = (printer)to_string_int;
        elt->val = malloc(sizeof(int));
        elt->size = sizeof(printable_int*);
        *(int*)elt->val = (int)(i + from);
        ints[i] = pint;
        i++;
    }
    return make_array(size, (printable**)ints);
}
array* make_sparse_sorted_array(const size_t size, const size_t from, const size_t deviation) {
    printable_int** ints = malloc(size * sizeof(printable_int*));
    size_t next = from, i = 0;
    time_t t;

    srand((unsigned)time(&t));
    
    while (i < size) {
        printable_int* pint = malloc(sizeof(printable_int));
        printable* elt = ((printable*)pint);
        elt->to_string = (printer)to_string_int;
        elt->val = malloc(sizeof(int));
        elt->size = sizeof(printable_int*);
        next += 1 + rand() % (deviation - 1);
        *(int*)elt->val = (int)next;
        ints[i] = pint;
        i++;
    }
    return make_array(size, (printable**)ints);
}

array* make_random_unique_array(const size_t size, const size_t from) {
    printable_int** ints = malloc(size * sizeof(printable_int*));
    size_t i = 0;
    
    while (i < size) {
        printable_int* pint = malloc(sizeof(printable_int));
        printable* elt = ((printable*)pint);
        elt->to_string = (printer)to_string_int;
        elt->val = malloc(sizeof(int));
        elt->size = sizeof(printable_int*);
        *(int*)elt->val = (int)(i + from);
        ints[i] = pint;
        i++;
    }
    return shuffled(make_array(size, (printable**)ints));
}

array* make_array_from_pointer(const int* data, const size_t size) {
    printable_int** ints = malloc(size * sizeof(printable_int*));
    size_t i = 0;
    
    while (i < size) {
        printable_int* pint = malloc(sizeof(printable_int));
        printable* elt = ((printable*)pint);
        elt->to_string = (printer)to_string_int;
        elt->val = malloc(sizeof(int));
        elt->size = sizeof(printable_int*);
        *(int*)elt->val = data[i];
        ints[i] = pint;
        i++;
    }
    return make_array(size, (printable**)ints);
}
