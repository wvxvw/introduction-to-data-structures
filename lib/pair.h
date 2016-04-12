/**
 * \file pair.h
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
#ifndef PAIR_H_
#define PAIR_H_

#include <stdlib.h>

#include "printable.h"

typedef struct pair {
    printable printable;
    printable* first;
    printable* last;
} pair;

pair* make_pair();

const char* to_string_pair(const pair* p);

#endif // PAIR_H_