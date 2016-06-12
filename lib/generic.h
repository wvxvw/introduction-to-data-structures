/**
 * \file generic.h
 *
 * \ingroup libassignment
 *
 * \brief This file defines some generic functions working on
 *        different data-structures.
 *
 * This file contains declarations that allow different other
 * data-structures to use the same function name providing different
 * implementation.
 *
 * \author Oleg Sivokon
 *
 * \date 2016/03/05
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef GENERIC_H_
#define GENERIC_H_

#include <stdbool.h>
#include "printable.h"

typedef struct vt {
    void** methods;
    void** generics;
    size_t len;
    size_t cap;
    char* name;
} vt;

vt* type_of(printable* p);

size_t make_type();

void register_type(size_t type, char* name);

void define_method(size_t type, void* generic, void* method);

void* find_method(size_t type, void* generic);

char* to_string_type(vt* type);

void print_methods(size_t type);

#define DEFTYPE(type)                                   \
    static bool type ## _type_initialized = false;      \
    static size_t raw_ ## type ## _type;                \
                                                        \
    size_t type ## _type() {                            \
        if (!type ## _type_initialized) {               \
            raw_ ## type ## _type = make_type(#type);   \
            type ## _type_initialized = true;           \
        }                                               \
        return raw_ ## type ## _type;                   \
    }


/* #define DEFGENERIC(name, receiver, ...) name(__VA_ARGS__) {  \ */
/*     void (*fpointer)() = &name; \ */
/*     void* method = find_method(type_of(receiver), fpointer); \ */
/*     } */

#endif // GENERIC_H_
