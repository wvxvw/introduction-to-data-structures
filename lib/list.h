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
#include "array.h"

typedef struct cell cell;

typedef struct cell {
    
    printable printable;
    
    printable* car;
    
    cell* cdr;
} cell;

typedef cell* list;

ASSIGNMENTLIB_API 
list cons(printable* car, list cdr);

ASSIGNMENTLIB_API 
list reverse(list input);

ASSIGNMENTLIB_API 
size_t length(list input);

ASSIGNMENTLIB_API 
list make_list(printable** elements, size_t size);

ASSIGNMENTLIB_API 
char* to_string_list(list p);

ASSIGNMENTLIB_API 
list append(list a, list b);

ASSIGNMENTLIB_API 
list merge_sort(list in, comparison_fn_t cmp);

ASSIGNMENTLIB_API 
list list_insertion_sort(list in, comparison_fn_t cmp);

#endif // LIST_H_
