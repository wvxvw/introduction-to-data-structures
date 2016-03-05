#include <stdlib.h>
#include <stdio.h>

#include "array.h"
#include "int_array.h"

int compare_ints(const void* a, const void* b) {
  const int* ia = (const int*) a;
  const int* ib = (const int*) b;

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

array* make_random_array(size_t size) {
    printable_int** ints = malloc(size * sizeof(printable_int*));
    size_t i = 0;
    
    while (i < size) {
        printable_int* pint = malloc(sizeof(printable_int));
        printable* elt = ((printable*)pint);
        elt->to_string = (printer)to_string_int;
        elt->val = malloc(sizeof(int));
        *(int*)elt->val = (int)i;
        ints[i] = pint;
        i++;
    }
    return make_array(size, (printable**)ints);
}
