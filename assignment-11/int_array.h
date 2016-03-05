#include <stdlib.h>

#include "array.h"

int compare_ints(const void* a, const void* b);

typedef struct printable_int {
    printable printable;
} printable_int;

const char* to_string_int(const printable_int* p);

array* make_random_array(size_t size);
