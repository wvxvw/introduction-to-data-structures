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
#include "iterable.h"

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

void test_hashtable_iterator() {
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
    iterator* it = make_hashtable_iterator(test);
    do {
        pair kv = (pair)((printable*)it)->val;
        printf("%s => %s\n", to_string(kv->first), to_string(kv->last));
    } while (next(it));
}

printable* printable_sum(printable* a, printable* b) {
    int ia = *(int*)a->val;
    int ib = *(int*)b->val;
    return (printable*)make_printable_int(ia + ib);
}

list two_summands_of(int sum, chashtable summands) {
    iterator* it = (iterator*)make_hashtable_iterator(summands);
    do {
        pair kv = (pair)((printable*)it)->val;
        printable* a = kv->first;
        int summand = *(int*)a->val;
        printable* b = (printable*)make_printable_int(sum - summand);
        printable* found = chashtable_get(summands, b);
        if (found != NULL) {
            if (summand * 2 == sum && ((list)kv->last)->cdr == NULL) {
                continue;
            } else if (summand * 2 == sum) {
                return cons(((list)kv->last)->car,
                            cons(((list)kv->last)->cdr->car, NULL));
            } else {
                return cons(kv->last, cons(found, NULL));
            }
        }
    } while (next(it));
    return NULL;
}

list four_summands_of(int sum, array summands) {
    chashtable table = make_empty_int_chashtable();
    size_t i, j;

    for (i = 0; i < summands->length; i++) {
        printable* a = summands->elements[i];
        for (j = i + 1; j < summands->length; j++) {
            printable* b = summands->elements[j];
            printable* halfsum = printable_sum(a, b);
            pair elts = make_pair();
            elts->first = a;
            elts->last = b;
            list wrapper = cons((printable*)elts, NULL);
            printable* found = chashtable_get(table, halfsum);
            if (found != NULL) wrapper = cons((printable*)found, wrapper);
            chashtable_put(table, halfsum, (printable*)wrapper);
        }
    }
    list four = two_summands_of(sum, table);
    if (four != NULL) four = append(four->car, four->cdr->car);
    return four;
}

void tests_summands() {
    int ints[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    array test = make_array_from_pointer(
        ints, 8, int_element_generator);
    list summands = four_summands_of(17, test);
    printf("Found decomposition of 17 = %s\n",
           to_string((printable*)summands));
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
    test_hashtable_iterator();
    tests_summands();
    return 0;
}
