/**
 * \file int_array.h
 *
 * \ingroup assignment11
 *
 * \brief This is an implementation of \c array which has all integer
 *        members.
 *
 * This file contains declarations necessary for working with arrays
 * containing integer elements.
 *
 * \author Oleg Sivokon
 *
 * \date $Date: 2016/03/05 $
 *
 * Contact: olegsivokon@gmail.com
 */
#include <stdlib.h>

#include "array.h"

/** \brief Implementation of \c comparison_fn_t which operates on
 *         \c printable_int.
 *
 *  \param a This should be a \c printable_int pointer.
 *  \param b This should be a \c printable_int pointer.
 *
 *  \return 0 if the value of a is the same as the value of b.
 *          1 if a is smaller than b and -1 otherwise.
 */
int compare_ints(const void* a, const void* b);

/** \struct printable_int
 *  \brief This struct is used to box a bare int pointer.  It also
 *         embeds \c printable, so it can be pretty-printed.
 */
typedef struct printable_int {
    
    /** \brief This struct embeds \c printable in order for us to
     * be able to call \c to_string on it.
     */
    printable printable;
} printable_int;

/** \brief Generate printable representation of a \c printable_int.
 *
 *  \param p The element to be printed.
 *
 *  \return A string (the callers are responsible to deallocate it).
 */
const char* to_string_int(const printable_int* p);

/** \brief Generate dense sorted \c array with element values starting
 *         from \c from.
 *
 *  \param size How many elements to generate.
 *  \param from The value of the first element.
 *
 *  \return An \c array (the callers are responsible to deallocate it).
 */
array* make_dense_sorted_array(const size_t size, const size_t from);

/** \brief Generate sparse sorted array with element values starting
 *         from \c from and increasing by at most \c deviation, where
 *         the increase is decided using uniform random distribution.
 *
 *  \param size How many elements to generate.
 *  \param from The value of the first element.
 *  \param deviation How much the elements could differ (must be positive).
 *
 *  \return An \c array (the callers are responsible to deallocate it).
 */
array* make_sparse_sorted_array(
    const size_t size, const size_t from, const size_t deviation);

/** \brief Generate an array where all elements are between \c from
 *         and \c from+size of size size, however elements aren't
 *         ordered.
 *
 *  \param size How many elements to generate.
 *  \param from The value of the first element.
 *
 *  \return An \c array (the callers are responsible to deallocate it).
 */
array* make_random_unique_array(const size_t size, const size_t from);

/** \brief Generate an array where all elements are between \c low and
 *         \c high of size size.  Elements may be repeated and appear
 *         in no particular order.
 *
 *  \param size How many elements to generate.
 *  \param low The elements in array are at least this big.
 *  \param high The elements in array are at no larger than this.
 *
 *  \return An \c array (the callers are responsible to deallocate it).
 */
array* make_random_array(const size_t size, const size_t low, const size_t high);
