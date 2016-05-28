#include <stdio.h>
#include <string.h>
#include <float.h>
#include <time.h>
#include <math.h>

#ifdef WITH_GC
#include <gc.h>
#endif

#include "printable.h"
#include "printable_int.h"
#include "array.h"
#include "generic.h"

void test_type() {
    array test = make_empty_array(10);
    printf("array's type: %s\n", to_string_type(type_of((printable*)test)));
}

void test_array_to_string() {
    array test = make_random_array(13, 3, 97, int_element_generator);
    printf("new array-to-string: %s\n", to_string((printable*)test));
}

int main() {
#ifdef WITH_GC
    GC_INIT();
#endif
    test_type();
    test_array_to_string();
    return 0;
}
