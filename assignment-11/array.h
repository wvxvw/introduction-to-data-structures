#ifndef ARRAY_H_
#define ARRAY_H_

#include <stdbool.h>

typedef struct printable printable;

typedef const char* (*printer)(const printable* p);

typedef struct printable {
    printer to_string;
    size_t size;
    void* val;
} printable;

typedef struct {
    printable printable;
    size_t length;
    printable** elements;
} array;

typedef int comparison_fn_t(const void*, const void*);

array* sorted(array* unsorted, comparison_fn_t cmp);

array* shuffled(array* sorted);

array* make_array(const size_t size, printable** data);

printable* make_printable(size_t size, void* data);

const char* to_string_default(const printable* p);

const char* to_string_array(const array* p);

#endif // ARRAY_H_
