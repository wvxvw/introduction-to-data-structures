/**
 * \file strings.h
 *
 * \ingroup lib
 *
 * \brief This file defines some utility functions to work on strings.
 *
 * \author Oleg Sivokon
 *
 * \date $Date: 2016/03/05 $
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef STRINGS_H_
#define STRINGS_H_

#include <stdio.h>
#include <string.h>
#include "printable.h"

char* join(char** chunks, size_t len, char* separator);

#endif // STRINGS_H_
