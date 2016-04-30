/**
 * \file printable_float.h
 *
 * \ingroup libassignment
 *
 * \brief This file defines basic functions for working with printable
 *        floats.
 *
 * This file contains declarations for creating, deleting and printing
 * \c printable_float.
 *
 * \author Oleg Sivokon
 *
 * \date 2016/03/05
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef PRINTABLE_FLOAT_H_
#define PRINTABLE_FLOAT_H_

#include <float.h>
#include "printable.h"

typedef struct printable_float {
    printable printable;
    float* val;
} printable_float;

ASSIGNMENTLIB_API 
int compare_floats(const void* a, const void* b);

ASSIGNMENTLIB_API 
const char* to_string_float(const printable_float* p);

ASSIGNMENTLIB_API 
printable_float* make_printable_float(const float val);

/** \brief Generate \c printable_int from given value.
 *
 *  \param elt The pointer to the original value.
 *
 *  \return A \c printable_int wrapping the original value.
 */
ASSIGNMENTLIB_API 
printable* float_element_generator(void* elt);

#endif // PRINTABLE_FLOAT_H_
