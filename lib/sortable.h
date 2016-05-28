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

typedef void* sortable;

/** \fn comparison_fn_t
 *  \brief The definition is copied from GCC extension, this is
 *         the comparator function suitable for \c qsort calls.
 *
 *  \param a First value to compare.
 *  \param b Second value to compare.
 */
typedef int comparison_fn_t(const void* a, const void* b);

ASSIGNMENTLIB_API 
sortable insertion_sort(sortable unsorted, comparison_fn_t cmp);

#endif // SORTABLE_H_
