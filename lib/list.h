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

typedef struct dcell dcell;

typedef struct dcell {
    
    cell cell;
    
    dcell* dcdr;
} dcell;

typedef dcell* dlist;

ASSIGNMENTLIB_API
dlist dcons(printable* car, dlist cdr);

ASSIGNMENTLIB_API
printable* list_find(list haystack, printable* needle, comparison_fn_t cmp);

/** \fn cons
 *  \brief Constructs new list by prepending \c car.
 *
 *  \param car The element to be added to the list.
 *  \param cdr The list to add \c car to.
 *  \return New list where the head is newly allocated and the tail
 *          reuses the elements of the given list.
 */
ASSIGNMENTLIB_API
list cons(printable* car, list cdr);

/** \fn reverse
 *  \brief Creates new list containing the elements of the given list
 *         in reverse order.
 *
 *  \param input The list whose elements are used to create the
 *         reversed list (not modified).
 *
 *  \return New list containing copies of the elements of the given
 *          list in reverse order.
 */
ASSIGNMENTLIB_API 
list list_reverse(list input);

/** \fn list_length
 *  \brief Computes the length of the given list.
 *
 *  \param input The list whose length is being computed.
 *
 *  \return The length of the given list.
 */
ASSIGNMENTLIB_API 
size_t list_length(list input);

/** \fn make_list
 *  \brief Creates a list using \c elements to initialze it.
 *
 *  \param elements The raw array of elements to be used during
 *         initialization.
 *
 *  \return New list.
 */
ASSIGNMENTLIB_API 
list make_list(printable** elements, size_t size);

/** \fn to_string_list
 *  \brief Implementation of \c to_string.
 *
 *  \param p The list to be printed.
 *
 *  \return String containing printed representation of the given
 *          list.
 */
ASSIGNMENTLIB_API 
char* to_string_list(list p);

/** \fn append
 *  \brief Appends list \c b to the end of list \c a.
 *
 *  \param a The first part of the resulting list.
 *  \param a The last part of the resulting list.
 *
 *  \return Concatenated list (all elements are fresh).
 */
ASSIGNMENTLIB_API 
list list_append(list a, list b);

/** \fn list_merge_sort
 *  \brief Implementation of \c merge_sort.
 *
 *  \param in The list to be sorted.
 *  \param cmp The comparison function.
 *
 *  \return Sorted list.
 */
ASSIGNMENTLIB_API 
list list_merge_sort(list in, comparison_fn_t cmp);

/** \fn list_insertion_sort
 *  \brief Implementation of \c insertion_sort.
 *
 *  \param in The list to be sorted.
 *  \param cmp The comparison function.
 *
 *  \return Sorted list.
 */
ASSIGNMENTLIB_API
list list_insertion_sort(list in, comparison_fn_t cmp);

ASSIGNMENTLIB_API
printable* list_first(list p);

ASSIGNMENTLIB_API
list list_rest(list p);

ASSIGNMENTLIB_API
list list_put(list orig, printable* k, printable* v);

ASSIGNMENTLIB_API 
dlist dlist_reverse(dlist input);

ASSIGNMENTLIB_API 
dlist dlist_append(dlist a, dlist b);

ASSIGNMENTLIB_API
dlist make_dlist(printable** elements, size_t size);

ASSIGNMENTLIB_API
dlist dlist_put(dlist orig, printable* k, printable* v);

#endif // LIST_H_
