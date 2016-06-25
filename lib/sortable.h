/**
 * \file sortable.h
 *
 * \ingroup libassignment
 *
 * \brief This file defines generic functions for sortable
 *        data-structures.
 *
 * This file defines generic functions which are shared by some
 * sortable data structures such as array, list, queue and stack.
 *
 * \author Oleg Sivokon
 *
 * \date 2016/03/05
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef SORTABLE_H_
#define SORTABLE_H_

#include "printable.h"

#define CHECK_METHOD_EXISTS(method, type, fptr, defval)                 \
    do {                                                                \
        if ((method) == NULL) {                                         \
            printf("find: Couldn't find method: %s, %d, %p\n",          \
                   __FUNCTION__, (type), (fptr));                       \
            return (defval);                                            \
        }                                                               \
    }                                                                   \
    while (false)

typedef void* sortable;

/** \fn comparison_fn_t
 *  \brief The definition is copied from GCC extension, this is
 *         the comparator function suitable for \c qsort calls.
 *
 *  \param a First value to compare.
 *  \param b Second value to compare.
 */
typedef int comparison_fn_t(const void* a, const void* b);

/** \fn rationalization_fn_t
 *  \brief Functions of this type must translate \c elt to an integral
 *         value in the range between the intergral value of \c min and
 *         the integral value of \c max and project it onto the \c range.
 *
 *  \param elt The element whose value is being computed.
 *  \param min The element whose value should be the lowest possible
 *         value for \c elt.
 *  \param max The element whose value should be the highest possible
 *         value for \c elt.
 *  \param range The returned value should be scaled to fit in the range.
 *         In other words, 0 <= f(elt) <= range.
 */
typedef size_t rationalization_fn_t(
    printable* elt, printable* min, printable* max, size_t range);

/** \fn insertion_sort
 *  \brief Generic function performing insertion sort on arrays,
 *         lists, stacks and queues.
 *
 *  \param unsorted The collection being sorted.
 *  \param cmp Comparison function to use when comparing elements of
 *         collection.
 */
ASSIGNMENTLIB_API 
sortable insertion_sort(sortable unsorted, comparison_fn_t cmp);

/** \fn merge_sort
 *  \brief Generic function performing merge-sort on arrays,
 *         lists, stacks and queues.
 *
 *  \param unsorted The collection being sorted.
 *  \param cmp Comparison function to use when comparing elements of
 *         collection.
 */
ASSIGNMENTLIB_API 
sortable merge_sort(sortable unsorted, comparison_fn_t cmp);

/** \fn length
 *  \brief Generic function computes the number of elements in
 *         collection.
 *
 *  \param input The collection whose length is being computed.
 */
ASSIGNMENTLIB_API
size_t length(sortable input);

ASSIGNMENTLIB_API
sortable reverse(sortable unsorted);

ASSIGNMENTLIB_API
sortable append(sortable a, sortable b);

ASSIGNMENTLIB_API
printable* find(sortable haystack, printable* needle, comparison_fn_t cmp);

ASSIGNMENTLIB_API
printable* put(sortable container, printable* key, printable* val);

ASSIGNMENTLIB_API
printable* pop(sortable container, printable* key);

ASSIGNMENTLIB_API
printable* first(sortable container);

ASSIGNMENTLIB_API
printable* rest(sortable container);

#endif // SORTABLE_H_
