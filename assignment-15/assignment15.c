#include <stdio.h>
#include <string.h>
#include <float.h>

#ifdef WITH_GC
#include <gc.h>
#endif

#include "printable.h"
#include "array.h"
#include "list.h"
#include "queue.h"
#include "printable_int.h"
#include "strings.h"

void test_queue() {
    queue q = make_empty_queue(9);
    size_t i = 0;
    printf("Empty queue: %s\n", to_string((printable*)q));
    while (queue_can_push(q)) {
        int val = (int)i;
        printable* elt = int_element_generator(&val);
        queue_push(elt, q);
        printf("Queue grows: %s\n", to_string((printable*)q));
        i++;
    }
    while (queue_can_pop(q)) {
        queue_pop(q);
        printf("Queue shrinks: %s\n", to_string((printable*)q));
    }
    printf("test_queue finished");
}

void test_append() {
    printf("test_append\n");
    array a = make_random_array(13, 3, 97, int_element_generator);
    array b = make_random_array(11, 3, 83, int_element_generator);
    printf("Created two arrays:\n");
    printf("a: %s\nb: %s\n",
           to_string((printable*)a),
           to_string((printable*)b));
    list al = make_list(a->elements, a->length);
    list bl = make_list(b->elements, b->length);
    printf("Created two lists\n");
    printf("a: %s\nb: %s\n",
           to_string((printable*)al),
           to_string((printable*)bl));
    list cl = append(al, bl);
    printf("appended: %s\n", to_string((printable*)cl));
}

void test_merge_sort() {
    array tarray = make_random_array(13, 3, 97, int_element_generator);
    list test = make_list(tarray->elements, tarray->length);
    printf("unsorted: %s\n", to_string((printable*)test));
    test = merge_sort(test, compare_ints);
    printf("sorted: %s\n", to_string((printable*)test));
}

void test_minmax() {
    array tarray = make_random_array(13, 3, 97, int_element_generator);
    printf("unsorted: %s\n", to_string((printable*)tarray));
    pair minmax = array_min_max(tarray, compare_ints);
    printf("min: %s\nmax: %s\n", to_string(minmax->first), to_string(minmax->last));
}

void test_counting_sort() {
    array tarray = make_random_array(13, 3, 97, int_element_generator);
    printf("unsorted: %s\n", to_string((printable*)tarray));
    pair minmax = array_min_max(tarray, compare_ints);
    size_t min = (size_t)(*(int*)minmax->first->val);
    size_t max = (size_t)(*(int*)minmax->last->val);
    array result = counting_sort(tarray, max - min, int_element_normalizer, compare_ints);
    printf("sorted: %s\n", to_string((printable*)result));
}

void test_bucket_sort() {
    array test = make_random_array(13, 3, 97, int_element_generator);
    printf("unsorted: %s\n", to_string((printable*)test));
    bucket_sort(test, int_element_normalizer, compare_ints);
    printf("sorted: %s\n", to_string((printable*)test));
}

int main() {
#ifdef WITH_GC
  GC_INIT();
#endif
    test_queue();
    test_append();
    test_merge_sort();
    test_minmax();
    test_counting_sort();
    test_bucket_sort();
    return 0;
}
