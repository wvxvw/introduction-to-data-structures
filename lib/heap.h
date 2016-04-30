/**
 * \file heap.h
 *
 * \ingroup libassignment
 *
 * \brief This file defines basic functions for working with printable
 *        heaps.
 *
 * This file contains declarations for a specific kind of binary trea
 * also known as a heap.  Two different implementations are given, the
 * \c leas_heap uses as \c list as its underlying structure, while
 * \c array_heap uses arrays.  The list-based implementation is more
 * careful in allocating memory while array-based implementation offers
 * somewhat improved access times.
 *
 * \author Oleg Sivokon
 *
 * \date 2016/03/05
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef HEAP_H_
#define HEAP_H_

#include <stdbool.h>

#include "printable.h"
#include "list.h"
#include "array.h"

typedef struct lheap_cell lheap_cell;

typedef struct lheap_cell {

    printable* val;
    
    lheap_cell* left;

    lheap_cell* right;
    
} lheap_cell;

typedef struct list_heap list_heap;

typedef struct list_heap {
    
    printable printable;

    lheap_cell* head;
    
    comparison_fn_t* cmp;
} list_heap;

typedef list_heap* lheap;

typedef lheap_cell* lcell;

ASSIGNMENTLIB_API 
lheap lheapify(printable** raw, size_t size, comparison_fn_t cmp);

ASSIGNMENTLIB_API 
printable* lpeak(lheap heap);

ASSIGNMENTLIB_API 
printable* lpop(lheap heap);

ASSIGNMENTLIB_API 
printable* lput(lheap heap, printable* val);

ASSIGNMENTLIB_API 
char* to_string_lheap(lheap heap);

typedef struct array_heap {
    
    printable printable;

    printable** elements;

    comparison_fn_t* cmp;

    size_t size;

    size_t allocated;
    
} array_heap;

typedef array_heap* aheap;

ASSIGNMENTLIB_API 
aheap aheapify(printable** raw, size_t size, comparison_fn_t cmp);

ASSIGNMENTLIB_API 
printable* apeak(aheap heap);

ASSIGNMENTLIB_API 
printable* apop(aheap heap);

ASSIGNMENTLIB_API 
printable* aput(aheap heap, printable* val);

ASSIGNMENTLIB_API 
char* to_string_aheap(aheap heap);

#endif // HEAP_H_
