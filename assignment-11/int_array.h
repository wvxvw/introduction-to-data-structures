#include <stdlib.h>

#include "array.h"

int compare_ints(const void* a, const void* b);

typedef struct printable_int {
    printable printable;
} printable_int;

const char* to_string_int(const printable_int* p);

array* make_dense_sorted_array(const size_t size, const size_t from);

array* make_sparse_sorted_array(const size_t size, const size_t from, const size_t deviation);

array* make_random_unique_array(const size_t size, const size_t from);

array* make_random_array(const size_t size, const size_t low, const size_t high);
