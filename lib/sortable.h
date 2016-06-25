/**
 * \file sortable.h
 *
 * \ingroup libassignment
 *
 * \brief This file defines generic functions for sortable
 *        data-structures.
 *
 * This file defines generic functions which are shared by some
 * sortable data structures such as \c array, \c list, \c queue and \c
 * stack.
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

/** \brief Functions of this type must translate \c elt to an integral
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

/** \brief Generic function performing insertion sort on arrays,
 *         lists, stacks and queues.
 *
 *  \param unsorted The collection being sorted.
 *  \param cmp Comparison function to use when comparing elements of
 *         collection.
 */
ASSIGNMENTLIB_API 
sortable insertion_sort(sortable unsorted, comparison_fn_t cmp);

/** \brief Generic function performing merge-sort on arrays,
 *         lists, stacks and queues.
 *
 *  \param unsorted The collection being sorted.
 *  \param cmp Comparison function to use when comparing elements of
 *         collection.
 */
ASSIGNMENTLIB_API 
sortable merge_sort(sortable unsorted, comparison_fn_t cmp);

/** \brief Generic function computes the number of elements in
 *         collection.
 *
 *  \param input The collection whose length is being computed.
 */
ASSIGNMENTLIB_API
size_t length(sortable input);

/** \brief Generic function returns a copy of the original container
 *         with its elements in reverse order.
 *
 *  \param unsorted The collection whose elements are reordered.
 */
ASSIGNMENTLIB_API
sortable reverse(sortable unsorted);

/** \brief Concatenates two collections.
 *
 *  \param a The collection whose elements will come up front.
 *  \param b The collection whose elements will come at the back.
 */
ASSIGNMENTLIB_API
sortable append(sortable a, sortable b);

/** \brief Looks for the element who compares equal to the given
 *         element.
 *
 *  All elements of the given container are compared to the given
 *  element, the first one for which the \c cmp function returns zero
 *  is returned.
 *
 *  \param haystack The container to look in.
 *
 *  \param needle The element to compare others to.
 *
 *  \param cmp The comparison function.
 */
ASSIGNMENTLIB_API
printable* find(sortable haystack, printable* needle, comparison_fn_t cmp);

/** \brief Looks up an element in the container by key.
 *
 *  This is different form \c find since this is generally intended
 *  for containers which provide constant time lookups.
 *
 *  \param container The container to look up the element.
 *
 *  \param key The object used to index container's elements.
 */
ASSIGNMENTLIB_API
printable* peek(sortable container, printable* key);

/** \brief Inserts an element into container.
 *
 *  Containers which index their elements will use the \c key
 *  parameter.  However, containers such as \c list will only use the
 *  last parameter.
 *
 *  \param container The container to add the element to.
 *
 *  \param key The key object to use to index the added element (if
 *         possible).
 *
 *  \param val The element being added.
 */
ASSIGNMENTLIB_API
printable* put(sortable container, printable* key, printable* val);

/** \brief Removes the given element from the container.
 *
 *  For elements which index their elements, the \c key parameter
 *  indicates which element to remove.  For containers such as \c
 *  list, the first element is removed to ensure the constant time of
 *  this function.
 *
 *  \param container The container to remove the element from.
 *
 *  \param key The index of the element being removed.
 */
ASSIGNMENTLIB_API
printable* pop(sortable container, printable* key);

/** \brief Returns the first element of the container.
 *
 *  The container is not modified.
 *
 *  \param container The conainer whose elements to look up.
 */
ASSIGNMENTLIB_API
printable* first(sortable container);

/** \brief Returns a conainer conaining the elements of the given
 *         container sans the first one.
 *
 *  The given container is not modified, however the shallow copy is
 *  performed.
 *  
 *  \param container The container whose elements to copy.
 */
ASSIGNMENTLIB_API
printable* rest(sortable container);

#endif // SORTABLE_H_
