#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <float.h>

#include "array.h"
#include "printable_float.h"
#include "generic.h"

DEFTYPE(printable_float);

int compare_floats(const void* a, const void* b) {
    const printable* pa = *(printable* const *)a;
    const printable* pb = *(printable* const *)b;
    if (pa == pb) return 0;
    if (pa == NULL) return -1;
    if (pb == NULL) return 1;
    
    if (pa->val == pb->val) return 0;
    if (pa->val == NULL) return -1;
    if (pb->val == NULL) return 1;

    const float* ia = (float*)pa->val;
    const float* ib = (float*)pb->val;
    /* printf("Comparing floats: %f = %f is %s\n", */
    /*        *ia, *ib, *ia == *ib ? "yes" : "no"); */
    return (*ia > *ib) - (*ia < *ib);
}

const char* to_string_float(const printable_float* p) {
    char* buffer = ALLOCATE(9 * sizeof(char));
    printable* base = (printable*)p;
    
    if (base->val == NULL) sprintf(buffer, "%p", base->val);
    else sprintf(buffer, "%f", *(float*)base->val);
    return buffer;
}

printable_float* make_printable_float(const float val) {
    printable_float* result = ALLOCATE(sizeof(printable_float));
    printable* p = (printable*)result;
    
    p->size = sizeof(printable_float*);
    p->val = ALLOCATE(sizeof(float));
    p->type = printable_float_type();
    define_method(p->type, to_string, to_string_float);
    *(float*)p->val = val;
    return result;
}

printable* float_element_generator(void* elt) {
    int original = *(int*)elt;
    return (printable*)make_printable_float((float)original);
}
