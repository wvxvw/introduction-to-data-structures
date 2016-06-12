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
#include "printable_string.h"
#include "array.h"
#include "list.h"
#include "generic.h"
#include "hashtable.h"
#include "files.h"

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

void test_dlist() {
    array unsorted = make_random_array(13, 3, 97, int_element_generator);
    dlist test = make_dlist(unsorted->elements, unsorted->length);
    printf("doubly-linked list: %s\n", to_string((printable*)test));
}

void test_chashtable() {
    char* keys[4] = { "foo", "bar", "baz", "qux" };
    array values = make_random_array(4, 17, 123, int_element_generator);
    list data = NULL;
    size_t i;

    for (i = 0; i < values->length; i++) {
        pair kv = make_pair();
        kv->first = (printable*)make_printable_string(keys[i]);
        kv->last = values->elements[i];
        data = cons((printable*)kv, data);
    }
    chashtable test = make_string_chashtable(11, data);
    printf("values: %s\n", to_string((printable*)values));
    printf("created hash-table: %s\n", to_string((printable*)test));
}

void test_dictionary_ops() {
    chashtable dic = make_empty_string_chashtable();
    list words = load_words("./assignment-16/test.data");
    printf("Loaded words: %s\n", to_string((printable*)words));
    while (words != NULL) {
        int count = 1;
        printable_int* maybe = (printable_int*)chashtable_get(dic, words->car);
        if (maybe != NULL) count = *(int*)((printable*)maybe)->val + 1;
        printable_int* pi = make_printable_int(count);
        chashtable_put(dic, words->car, (printable*)pi);
        words = words->cdr;
    }
    printf("Generated hash-table: %s\n", to_string((printable*)dic));
}

void test_int_hash() {
    array keys = make_random_array(17, 17, 123, int_element_generator);
    array values = make_random_array(17, 17, 123, int_element_generator);
    list data = NULL;
    size_t i;
    
    for (i = 0; i < values->length; i++) {
        pair kv = make_pair();
        kv->first = keys->elements[i];
        kv->last = values->elements[i];
        data = cons((printable*)kv, data);
    }
    chashtable dic = make_int_chashtable(17, data);
    printf("Generated int hash-table: %s\n", to_string((printable*)dic));
}

int main() {
#ifdef WITH_GC
    GC_INIT();
#endif
    test_type();
    test_array_to_string();
    test_insertion_sort();
    test_merge_sort();
    test_dlist();
    test_chashtable();
    test_dictionary_ops();
    test_int_hash();
    return 0;
}