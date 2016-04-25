/**
 * \file list.h
 *
 * \ingroup libassignment
 *
 * \brief This file defines basic functions for working with printable
 *        arrays.
 *
 * This file contains declarations for basic data-structures needed to
 * work with differently-typed arrays and being able to pretty-print
 * them.
 *
 * \author Oleg Sivokon
 *
 * \date 2016/03/05
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>

#include "printable.h"

typedef struct cell cell;

typedef struct cell {
    
    printable printable;
    
    printable* car;
    
    cell* cdr;
} cell;

typedef cell* list;

list cons(printable* car, list cdr);

list reverse(list input);

size_t length(list input);

list make_list(printable** elements, size_t size);

char* to_string_list(list p);

#endif // LIST_H_
