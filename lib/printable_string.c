#include <stdio.h>
#include <string.h>
#include "printable.h"
#include "generic.h"
#include "printable_string.h"

DEFTYPE(string);

int compare_strings(const void* a, const void* b) {
    const printable* pa = *(printable* const *)a;
    const printable* pb = *(printable* const *)b;
    if (pa == pb) return 0;
    if (pa == NULL) return -1;
    if (pb == NULL) return 1;
    
    if (pa->val == pb->val) return 0;
    if (pa->val == NULL) return -1;
    if (pb->val == NULL) return 1;

    char* ia = (char*)pa->val;
    size_t sa = pa->size;
    char* ib = (char*)pb->val;
    size_t sb = pb->size;
    size_t min = sa < sb ? sa : sb;
    
    while (min > 0) {
        if (ia[0] > ib[0]) return 1;
        if (ia[0] < ib[0]) return -1;
        ia++;
        ib++;
        min--;
    }
    return (sa > sb) - (sa < sb);
}

char* to_string_string(const printable_string* p) {
    // TODO: Quote
    return (char*)((printable*)p)->val;
}

printable_string* make_printable_string(char* val) {
    printable_string* result = ALLOCATE(sizeof(printable_string));
    printable* presult = (printable*)result;
    presult->type = string_type();
    presult->val = val;
    presult->size = strlen(val);
    define_method(presult->type, to_string, to_string_string);
    return result;
}

printable* string_element_generator(void* elt) {
    int val = *(int*)elt;
    char* buffer = ALLOCATE(11 * sizeof(char));
    
    sprintf(buffer, "%d", val);
    return (printable*)make_printable_string(buffer);
}
