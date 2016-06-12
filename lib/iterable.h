/**
 * \file iterable.h
 *
 * \ingroup libassignment
 *
 * \brief This file defines several iterators for different data-structures.
 *
 * This file contains declarations for array and hash-table iterators.
 *
 * \author Oleg Sivokon
 *
 * \date 2016/03/05
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef ITERABLE_H_
#define ITERABLE_H_

#include <stdbool.h>
#include "array.h"
#include "hashtable.h"

typedef struct iterator iterator;

/** \brief The function to advance the iterator one position
 *  \param it The iterator being acted on.
 */
typedef bool next_fn_t(iterator* it);

typedef bool has_fn_t(iterator* it);

typedef struct iterator {

    printable printable;

    /** \brief The container being iterated.
     */
    printable* iterated;
} iterator;

/** \brief Iterator implementation for arrays.
 */
typedef struct array_iterator {

    iterator iterator;

    /** \brief The current position of iterator.
     */
    size_t pos;
} array_iterator;

/** \brief Iterator implementation for hash-tables.
 */
typedef struct hashtable_iterator {

    iterator iterator;

    /** \brief The current position of iterator.
     */
    size_t pos;

    dlist key;
    
    dlist value;
} hashtable_iterator;

/** \brief The interface to iterating the array.
 *
 *  \param impl The iterator aced on.
 */
ASSIGNMENTLIB_API
bool next(iterator* impl);

ASSIGNMENTLIB_API
bool array_next(iterator* impl);

ASSIGNMENTLIB_API 
bool hashtable_next(iterator* impl);

/** \brief The interface to iterating the array.
 *
 *  \param impl The iterator aced on.
 */
ASSIGNMENTLIB_API 
bool has(iterator* impl);

ASSIGNMENTLIB_API 
bool array_has(iterator* impl);

ASSIGNMENTLIB_API 
bool hashtable_has(iterator* impl);

/** \brief The concrete iterator implementation.
 *
 *  \param iterated The array to create an iterator for.
 */
ASSIGNMENTLIB_API
iterator* make_array_iterator(array iterated);

ASSIGNMENTLIB_API
iterator* make_hashtable_iterator(chashtable iterated);

#endif // ITERABLE_H_
