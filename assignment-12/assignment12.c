#include <stdio.h>
#include <string.h>
#include <float.h>
#include <gc.h>

#include "printable.h"
#include "list.h"
#include "array.h"
#include "int_array.h"
#include "heap.h"
#include "strings.h"

void test_lheap() {
    array* arr = make_random_unique_array(27, 13, int_element_generator);
    printf("Generated source array: %s\n", to_string((printable*)arr));
    lheap heap = lheapify(arr->elements, arr->length, compare_ints);
    
    printf("Generated heap: %s\n", to_string((printable*)heap));
}

void test_aheap() {
    array* arr = make_random_unique_array(27, 13, int_element_generator);
    printf("Generated source array: %s\n", to_string((printable*)arr));
    aheap heap = aheapify(arr->elements, arr->length, compare_ints);
    
    printf("Generated heap: %s\n", to_string((printable*)heap));
}

void test_list() {
    printable* numbers[19];
    size_t i;
    
    for (i = 0; i < 19; i++) {
        numbers[i] = int_element_generator(&i);
    }
    printf("last: %d\n", *(int*)numbers[18]->val);
    list nums = make_list(numbers, 19);
    printf("Generated list: %s\n", to_string((printable*)nums));
}

void test_join() {
    char* chunks[5];
    const char* original[5] = { "foo", "bar", "qux", "x", "abcdefg" };
    size_t i;

    for (i = 0; i < 5; i++) {
        chunks[i] = ALLOCATE(sizeof(char) * (strlen(original[i]) + 1));
        sprintf(chunks[i], original[i]);
    }
    printf("Joined string: '%s'\n", join(chunks, 5, "-x-"));
}

int main() {
    GC_INIT();
    test_list();
    test_lheap();
    test_join();
    test_aheap();
    return 1;
}
