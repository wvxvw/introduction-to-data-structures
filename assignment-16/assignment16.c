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
    chashtable test = make_chashtable(hash, 11, data);
    printf("values: %s\n", to_string((printable*)values));
    printf("created hash-table: %s\n", to_string((printable*)test));
}

bool is_alnum(char c) {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

list load_words() {
#define BUFF_SIZE 255
   FILE* fp;
   char buff[BUFF_SIZE];
   list result = NULL;
   bool finished = false;
   char* prefix = "";
   size_t prefix_len = 0;

   fp = fopen("./assignment-16/test.data", "r");

   while (!finished && !feof(fp) && !ferror(fp)) {
       memset(buff, 0, BUFF_SIZE);
       fread(buff, sizeof(char), BUFF_SIZE, fp);
       char current;
       size_t start = 0, word_len, i;
       char* word, *suffix;
       
       for (i = 0; i < BUFF_SIZE; i++) {
           current = buff[i];
           if (current == '\0') {
               finished = true;
               break;
           }
           if (!is_alnum(current)) {
               if (start + 1 < i) {
                   word_len = prefix_len + i - start + 1;
                   suffix = ALLOCATE(sizeof(char) * (i - start));
                   strncpy(suffix, buff + start, i - start);
               } else if (prefix_len > 0) {
                   word_len = prefix_len + 1;
                   suffix = "";
               }
               if (word_len > 1) {
                   word = ALLOCATE(sizeof(char) * word_len);
                   sprintf(word, "%s%s", prefix, suffix);
                   result = cons((printable*)make_printable_string(word), result);
                   prefix_len = 0;
                   prefix = "";
                   word_len = 0;
               }
               start = i + 1;
           }
       }
       if (start + 1 < i) {
           prefix_len = i - start;
           prefix = ALLOCATE(sizeof(char) * prefix_len + 1);
           strncpy(prefix, buff + start, prefix_len);
       }
   }
   fclose(fp);
   return reverse(result);
#undef BUFF_SIZE
}

void test_dictionary_ops() {
    chashtable dic = make_empty_chashtable(hash);
    list words = load_words();
    printf("Loaded words: %s\n", to_string((printable*)words));
    while (words != NULL) {
        int count = 1;
        unsigned char* key = (unsigned char*)words->car->val;
        printable_int* maybe = (printable_int*)chashtable_get(dic, key);
        if (maybe != NULL) count = *(int*)((printable*)maybe)->val + 1;
        printable_int* pi = make_printable_int(count);
        chashtable_put(dic, key, (printable*)pi);
        words = words->cdr;
    }
    printf("Generated hash-table: %s\n", to_string((printable*)dic));
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
    return 0;
}
