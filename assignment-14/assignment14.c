#include <stdio.h>
#include <string.h>
#include <float.h>

#ifdef WITH_GC
#include <gc.h>
#endif

#include "printable.h"
#include "list.h"
#include "array.h"
#include "printable_int.h"
#include "strings.h"

size_t bogus_quicksort(array unsorted, size_t order) {
    printable* elt =  nth_order_statistic(unsorted, order, compare_ints);
    size_t position = index_of(unsorted, elt);
    size_t wall = partition_at(unsorted, position, compare_ints);
    array left;
    array right;
    size_t ldepth = 0, rdepth = 0;

    if (wall > 1) {
        left = slice(unsorted, 0, wall);
        ldepth = bogus_quicksort(left, order);
    }
    if (wall < unsorted->length - 2) {
        right = slice(unsorted, wall, unsorted->length - 1);
        rdepth = bogus_quicksort(right, order);
    }
    return 1 + (ldepth > rdepth ? ldepth : rdepth);
}

size_t test_performance(size_t array_length, size_t order) {
    array unsorted = make_random_unique_array(
        array_length, 0, int_element_generator);
    printf("input: %s\n", to_string((printable*)unsorted));
    return bogus_quicksort(unsorted, order);
}

int main() {
    size_t array_length, order, result;
    
#ifdef WITH_GC
    GC_INIT();
#endif
    
    for (array_length = 100; array_length <= 400; array_length *= 2) {
        for (order = 1; order <= 8; order *= 2) {
            result = test_performance(array_length, (100 * order) / 8);
            printf("Given array of length: %d, \n"
                   "nth-order statistic:   %d%%, \n"
                   "recursion depth was:   %d\n\n",
                   (int)array_length, (int)((100 * order) / 8), (int)result);
        }
    }
    return 0;
}
