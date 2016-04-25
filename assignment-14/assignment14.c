#include <stdio.h>
#include <string.h>
#include <float.h>
#include <gc.h>

#include "printable.h"
#include "list.h"
#include "array.h"
#include "printable_int.h"
#include "strings.h"

size_t bogus_quicksort(array unsorted, size_t order) {
    printf("1\n");
    printable* elt =  nth_order_statistic(unsorted, order, compare_ints);
    printf("2\n");
    size_t position = index_of(unsorted, elt);
    printf("3\n");
    size_t wall = partition_at(unsorted, position, compare_ints);
    printf("4\n");
    array left;
    array right;
    size_t ldepth = 0, rdepth = 0;

    printf("input: %s\n", to_string((printable*)unsorted));
    printf("bogus_quicksort: %d, wall: %d, position: %d, elt: %s\n",
           (int)unsorted->length, (int)wall, (int)position, to_string(elt));
    if (wall > 1) {
        left = slice(unsorted, 0, wall);
        printf("left: %d\n", (int)left->length);
        ldepth = bogus_quicksort(left, order);
    }
    if (wall < unsorted->length - 2) {
        right = slice(unsorted, wall, unsorted->length - 1);
        printf("right: %d\n", (int)right->length);
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

    GC_INIT();
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
