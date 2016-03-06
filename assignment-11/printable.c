/**
 * \file printable.h
 *
 * \ingroup assignment11
 *
 * \brief This file defines basic functions for working with printable
 *        objects.
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
#include <stdio.h>
#include <stdlib.h>

#include "printable.h"

printable* make_printable(size_t size, void* data) {
    printable* result = malloc(sizeof(printable));
    result->size = size;
    result->val = data;
    return result;
}

const char* to_string_default(const printable* p) {
    char* buffer = malloc(9 * sizeof(char));
    sprintf(buffer, "%p", p->val);
    return buffer;
}
