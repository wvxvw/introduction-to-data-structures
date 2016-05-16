/**
 * \file pair.h
 *
 * \ingroup libassignment
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
 * \date 2016/03/05
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef PAIR_H_
#define PAIR_H_

#include <stdlib.h>

#include "printable.h"

typedef struct printable_pair {
    printable printable;
    printable* first;
    printable* last;
} printable_pair;

typedef printable_pair* pair;

ASSIGNMENTLIB_API 
pair make_pair();

ASSIGNMENTLIB_API 
const char* to_string_pair(const pair p);

#endif // PAIR_H_
