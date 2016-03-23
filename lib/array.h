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

#include "printable.h"

/** \fn element_generator
 *  \brief The functions of this kind are used when generating all
 *          sorts of arrays (typically an array will implement a
 *          generator corresponding to its type).
 *
 *  \param elt The pointer to the value to wrap in \c printable.
 *  \return Boxed value of the element.
 */
typedef printable* element_generator(void* elt);

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

/** \enum search_direction
 *  \brief Defines search direction.
 */
typedef enum { BACK, FORWARD } search_direction;

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

/** \brief Creates an array that shares data with \c input, but
 *         starts from \c from and up to \c to.
 */
array* slice(const array* input, const size_t from, const size_t to);

/** \brief Performs binary search on \c input for \c elt.
 *         The comparison is carried out using \c cmp callback.
 *  \return The index of the searched element in the array.
 * 
 * When the element is not found in the array, the value returned is the
 * array's length.  Note that the array is assumed to be sorted, however
 * duplicate items are OK.
 */
size_t binsearch(const array* input, const printable* elt, comparison_fn_t cmp);

/** \brief Generate dense sorted \c array with element values starting
 *         from \c from.
 *
 *  \param size How many elements to generate.
 *  \param from The value of the first element.
 *  \param generator The function to generate array elements.
 *
 *  \return An \c array (the callers are responsible to deallocate it).
 */
array* make_dense_sorted_array(const size_t size,
                               const size_t from,
                               element_generator generator);

/** \brief Generate sparse sorted array with element values starting
 *         from \c from and increasing by at most \c deviation, where
 *         the increase is decided using uniform random distribution.
 *
 *  \param size How many elements to generate.
 *  \param from The value of the first element.
 *  \param deviation How much the elements could differ (must be positive).
 *  \param generator A function to generate an element given a pointer to the
 *         generated value.
 *
 *  \return An \c array (the callers are responsible to deallocate it).
 */
array* make_sparse_sorted_array(const size_t size,
                                const size_t from,
                                const size_t deviation,
                                element_generator generator);

/** \brief Generate an array where all elements are between \c from
 *         and \c from+size of size size, however elements aren't
 *         ordered.
 *
 *  \param size How many elements to generate.
 *  \param from The value of the first element.
 *  \param generator A function to generate an element given a pointer to the
 *         generated value.
 *
 *  \return An \c array (the callers are responsible to deallocate it).
 */
array* make_random_unique_array(const size_t size,
                                const size_t from,
                                element_generator generator);

/** \brief Generate an array where all elements are between \c low and
 *         \c high of size size.  Elements may be repeated and appear
 *         in no particular order.
 *
 *  \param size How many elements to generate.
 *  \param low The elements in array are at least this big.
 *  \param high The elements in array are at no larger than this.
 *  \param generator The function to generate array elements.
 *
 *  \return An \c array (the callers are responsible to deallocate it).
 */
array* make_random_array(const size_t size,
                         const size_t low,
                         const size_t high,
                         element_generator generator);

/** \brief Same as \c make_random_array, except the elements are already
 *         sorted
 *
 *  \param size How many elements to generate.
 *  \param low The elements in array are at least this big.
 *  \param high The elements in array are at no larger than this.
 *  \param cmp A function to compare two array elements.
 *  \param generator The function to generate array elements.
 *
 *  \return An \c array (the callers are responsible to deallocate it).
 */
array* make_random_sorted_array(const size_t size,
                                const size_t low,
                                const size_t high,
                                comparison_fn_t cmp,
                                element_generator generator);

/** \brief Generate an array from a simile C array of ints.
 *
 *  \param size How many elements to generate.
 *  \param data The original C array.
 *  \param generator A function to generate an element given a pointer to the
 *         generated value.
 *
 *  \return An \c array (the callers are responsible to deallocate it).
 */
array* make_array_from_pointer(const int* data,
                               const size_t size,
                               element_generator generator);

/** \brief Generate an array where elements in odd places decrease by one
 *         while the elements in even places increase by one until they
 *         are equal.
 *
 *  \param half_size The largest element in this array.
 *  \param generator A function to generate an element given a pointer to the
 *         generated value.
 *
 *  \return An \c array (the callers are responsible to deallocate it).
 */
array* make_increasing_decreasing_array(const size_t half_size,
                                        element_generator generator);

/** \brief Generate an array where elements in in its first half decrease
 *         by one starting with half the size of the array, while the elements
 *         in its second half increase by one as well, but starting from
 *         the element of the size of the array.
 *
 *  \param half_size The largest element in this array.
 *  \param generator A function to generate an element given a pointer to the
 *         generated value.
 *
 *  \return An \c array (the callers are responsible to deallocate it).
 */
array* make_vedge_array(const size_t half_size,
                        element_generator generator);

/** \brief Sorts the array using given comparison function
 *
 *  \param unsorted The array to sort (modified in place)
 *  \param cmp The function to compare two elements of the given array.
 *
 *  \return An \c array (no new allocations are made).
 */
array* insertion_sort(array* unsorted, comparison_fn_t cmp);

/** \brief Restets the swap operation counter
 */
void start_swap_count();

/** \brief Returns the number of \c swap operations performed since
 *         swap conter was last reset.
 */
long get_swap_count();

/** \brief Generates a string representing the given \c array.
 *  \param p The \c array to print.
 */
char* to_string_array(array* p);

typedef struct iterator_impl iterator_impl;

/** \brief The function to advance the iterator one position
 *  \param it The iterator being acted on.
 */
typedef bool (*iterator_func)(iterator_impl* it);

/** \brief The iterator information storage cell.
 */
typedef struct iterator_impl {

    /** \brief The iterator function (the one which actually does the iteration).
     */
    iterator_func it;

    /** \brief The current position of iterator.
     */
    size_t pos;

    /** \brief The array being iterated.
     */
    array* iterated;

    /** \brief The current value of the iterator.
     */
    printable* value;
} iterator_impl;

/** \brief The interface to iterating the array.
 *
 *  \param impl The iterator aced on.
 */
bool next(iterator_impl* impl);

/** \brief The concrete iterator implementation.
 *
 *  \param iterated The array to create an iterator for.
 */
iterator_impl* iterator(array* iterated);
    
#endif // ARRAY_H_
