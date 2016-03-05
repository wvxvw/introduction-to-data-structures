/**
 * \file array.h
 *
 * \ingroup assignment11
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
 * \date $Date: 2016/03/05 $
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef ARRAY_H_
#define ARRAY_H_

#include <stdbool.h>

/** \struct printable
 *  \brief This struct provides the backbone for anything that can
 *         go inside a printable array.
 */
typedef struct printable printable;

/** \fn printer
 *  \brief Anything \c printable must have an implementation of this
 *         function (it will be called by the code using \c printable
 *         to print it).
 *
 * \param p The pointer to the \c printable object which will be printed.
 */
typedef const char* (*printer)(const printable* p);

typedef struct printable {
    
    /** \brief The printing function.
     */
    printer to_string;
    
    /** \brief How much data is stored in this element (must be
     *         suitable for \c sizeof call).
     */
    size_t size;

    /** \brief The actual value stored inside.
     */
    void* val;
} printable;

/** \struct array
 *  \brief This struct is the backbone for all printable arrays.
 */
typedef struct {
    
    /** \brief This array is itself printable (so could be a member of
     *         another such array).
     */
    printable printable;

    /** \brief The number of members in this array.
     */
    size_t length;

    /** \brief The actual members.
     */
    printable** elements;
} array;

/** \fn comparison_fn_t
 *  \brief The definition is copied from GCC extension, this is
 *         the comparator function suitable for \c qsort calls.
 *
 *  \param a First value to compare.
 *  \param b Second value to compare.
 */
typedef int comparison_fn_t(const void* a, const void* b);

/** \brief Sorts the \c array in-place using \c cmp function and
 *         returns it.
 */
array* sorted(array* unsorted, comparison_fn_t cmp);

/** \brief Shuffles the \c array in-place and returns it.
 */
array* shuffled(array* sorted);

/** \brief Creates new \c array using \c data elements as input and
 *         returns it.
 */
array* make_array(const size_t size, printable** data);

/** \brief Creates new \c printable wrapping \c data and returns it.
 */
printable* make_printable(size_t size, void* data);

/** \brief Generates a string representing the default \c printable.
 *  \param p The \c printable to print.
 */
const char* to_string_default(const printable* p);

/** \brief Generates a string representing the given \c array.
 *  \param p The \c array to print.
 */
const char* to_string_array(const array* p);

#endif // ARRAY_H_
