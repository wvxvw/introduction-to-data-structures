/**
 * \file printable_int.h
 *
 * \ingroup libassignment
 *
 * \brief This is an implementation of \c array which has all integer
 *        members.
 *
 * This file contains declarations necessary for working with arrays
 * containing integer elements.
 *
 * \author Oleg Sivokon
 *
 * \date 2016/03/05
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef PRINTABLE_INT_H_
#define PRINTABLE_INT_H_

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
ASSIGNMENTLIB_API 
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
ASSIGNMENTLIB_API 
char* to_string_int(const printable_int* p);

/** \brief Generate \c printable_int from given value.
 *
 *  \param elt The pointer to the original value.
 *
 *  \return A \c printable_int wrapping the original value.
 */
ASSIGNMENTLIB_API 
printable* int_element_generator(void* elt);

ASSIGNMENTLIB_API 
void start_int_cmp_count();

ASSIGNMENTLIB_API 
size_t get_int_cmp_count();

ASSIGNMENTLIB_API 
int compare_ints_reverse(const void* a, const void* b);

#endif // PRINTABLE_INT_H_
