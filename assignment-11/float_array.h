/**
 * \file float_array.h
 *
 * \ingroup assignment11
 *
 * \brief This file defines basic functions for working with printable
 *        floats.
 *
 * This file contains declarations for creating, deleting and printing
 * \c printable_float.
 *
 * \author Oleg Sivokon
 *
 * \date $Date: 2016/03/05 $
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef FLOAT_ARRAY_H_
#define FLOAT_ARRAY_H_

#include <float.h>
#include "printable.h"

typedef struct printable_float {
    printable printable;
    float* val;
} printable_float;

int compare_floats(const void* a, const void* b);

const char* to_string_float(const printable_float* p);

printable_float* make_printable_float(const float val);

/** \brief Generate \c printable_int from given value.
 *
 *  \param elt The pointer to the original value.
 *
 *  \return A \c printable_int wrapping the original value.
 */
printable* float_element_generator(void* elt);

#endif // FLOAT_ARRAY_H_
