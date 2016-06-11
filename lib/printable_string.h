/**
 * \file printable_string.h
 *
 * \ingroup libassignment
 *
 * \brief This is an implementation of strings which can be printed
 *        using \c printable struct.
 *
 * This file contains declarations necessary for strings to be printed
 * and for them to use some generic methods from \c sortable and \c
 * printable.
 *
 * \author Oleg Sivokon
 *
 * \date 2016/03/05
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef PRINTABLE_STRING_H_
#define PRINTABLE_STRING_H_

#include <stdlib.h>
#include <stdio.h>

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
int compare_strings(const void* a, const void* b);

/** \struct printable_string
 *  \brief This struct is used to box a bare int pointer.  It also
 *         embeds \c printable, so it can be pretty-printed.
 */
typedef struct printable_string {
    
    /** \brief This struct embeds \c printable in order for us to
     * be able to call \c to_string on it.
     */
    printable printable;
} printable_string;

/** \brief Generate printable representation of a \c printable_string.
 *
 *  \param p The element to be printed.
 *
 *  \return A string (the callers are responsible to deallocate it).
 */
ASSIGNMENTLIB_API 
char* to_string_string(const printable_string* p);

/** \brief Generate \c printable_string from given value.
 *
 *  \param elt The pointer to the original value.
 *
 *  \return A \c printable_string wrapping the original value.
 */
ASSIGNMENTLIB_API 
printable* string_element_generator(void* elt);

printable_string* make_printable_string(char* val);

#endif // PRINTABLE_STRING_H_
