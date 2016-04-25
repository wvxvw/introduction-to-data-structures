/**
 * \file strings.h
 *
 * \ingroup libassignment
 *
 * \brief This file defines some utility functions to work on strings.
 *
 * \author Oleg Sivokon
 *
 * \date 2016/03/05
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef STRINGS_H_
#define STRINGS_H_

#include <stdio.h>
#include <string.h>
#include "printable.h"

/** \fn join
 *  \brief Concatenates \c len number of strings.
 *
 *  \param chunks Zero-delimited strings to concatenate.
 *  \param len Number of chunks to concatenate.
 *  \param separator A string to insert between concatenated strings.
 *  
 *  \return Concatenated string ending in zero character.
 */
char* join(char** chunks, size_t len, char* separator);

#endif // STRINGS_H_
