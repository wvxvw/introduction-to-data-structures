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
#include "list.h"
#include "generic.h"

void test_type() {
    array test = make_empty_array(10);
    printf("array's type: %s\n", to_string_type(type_of((printable*)test)));
}

void test_array_to_string() {
    array test = make_random_array(13, 3, 97, int_element_generator);
    printf("new array-to-string: %s\n", to_string((printable*)test));
}

void test_insertion_sort() {
    array unsorted = make_random_array(13, 3, 97, int_element_generator);
    printf("unsorted array: %s\n", to_string((printable*)unsorted));
    array sorted = (array)insertion_sort((sortable)unsorted, compare_ints);
    printf("sorted array: %s\n", to_string((printable*)sorted));
    array larray = make_random_array(13, 3, 97, int_element_generator);
    list lunsorted = make_list(larray->elements, larray->length);
    printf("unsorted list: %s\n", to_string((printable*)lunsorted));
    list lsorted = (list)insertion_sort((sortable)lunsorted, compare_ints);
    printf("sorted list: %s\n", to_string((printable*)lsorted));
}

void test_merge_sort() {
    array unsorted = make_random_array(13, 3, 97, int_element_generator);
    printf("unsorted array: %s\n", to_string((printable*)unsorted));
    array sorted = (array)merge_sort((sortable)unsorted, compare_ints);
    printf("sorted array: %s\n", to_string((printable*)sorted));
}

int main() {
#ifdef WITH_GC
    GC_INIT();
#endif
    test_type();
    test_array_to_string();
    test_insertion_sort();
    test_merge_sort();
    return 0;
}
