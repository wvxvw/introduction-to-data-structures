#include <stdio.h>
#include <float.h>
#include <gc.h>

#include "printable.h"
#include "list.h"
#include "int_array.h"

int main() {
    GC_INIT();
    printable* numbers[19];
    size_t i;
    
    for (i = 0; i < 19; i++) {
        numbers[i] = int_element_generator(&i);
    }
    printf("last: %d\n", *(int*)numbers[18]->val);
    list nums = make_list(numbers, 19);
    printf("Generated list: %s\n", to_string((printable*)nums));
    return 1;
}
