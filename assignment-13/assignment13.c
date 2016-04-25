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

void test_partition() {
    array arr = make_random_unique_array(27, 13, int_element_generator);
    printf("Generated source array: %s\n", to_string((printable*)arr));
    size_t wall = partition(arr, compare_ints);
    printf("After partitioning: %s, wall: %d\n", to_string((printable*)arr), (int)wall);
}

void test_exercise_1() {
    array ascending = make_random_sorted_array(27, 13, 67, compare_ints, int_element_generator);
    array descending = make_random_sorted_array(27, 13, 67, compare_ints_reverse, int_element_generator);
    printf("Ascending: %s\n", to_string((printable*)ascending));
    printf("Descending: %s\n", to_string((printable*)descending));
    start_int_cmp_count();
    partition(ascending, compare_ints);
    printf("Ascending %d comparisons\n", (int)get_int_cmp_count());
    start_int_cmp_count();
    partition(descending, compare_ints);
    printf("Descending %d comparisons\n", (int)get_int_cmp_count());
}

void test_three_way_partition() {
    array arr = make_random_unique_array(27, 13, int_element_generator);
    printf("Generated source array: %s\n", to_string((printable*)arr));
    pair walls = three_way_partition(arr, compare_ints);
    printf("After partitioning: %s, walls: %s\n",
           to_string((printable*)arr),
           to_string((printable*)walls));
}

void test_three_way_quicksort() {
    array arr = make_random_unique_array(27, 13, int_element_generator);
    printf("Generated source array: %s\n", to_string((printable*)arr));
    three_way_quicksort(arr, compare_ints, 0);
    printf("Fully sorted: %s\n", to_string((printable*)arr));
    
    arr = make_random_unique_array(27, 13, int_element_generator);
    printf("Generated source array: %s\n", to_string((printable*)arr));
    three_way_quicksort(arr, compare_ints, 4);
    printf("sorted with error(%d): %s\n", 4, to_string((printable*)arr));
}

void test_three_way_partition_1() {
    int ints[8] = {25, 20, 24, 23, 22, 21, 27, 26};
    array arr = make_array_from_pointer(ints, 8, int_element_generator);
    printf("Generated source array: %s\n", to_string((printable*)arr));
    pair walls = three_way_partition(arr, compare_ints);
    printf("After partitioning: %s, walls: %s\n",
           to_string((printable*)arr),
           to_string((printable*)walls));
}

int main() {
#ifdef WITH_GC
  GC_INIT();
#endif
    test_partition();
    test_exercise_1();
    test_three_way_partition();
    test_three_way_partition_1();
    test_three_way_quicksort();
    return 0;
}
