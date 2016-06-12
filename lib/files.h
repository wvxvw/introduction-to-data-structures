/**
 * \file files.h
 *
 * \ingroup libassignment
 *
 * \brief This file defines some utility functions to work on files.
 *
 * \author Oleg Sivokon
 *
 * \date 2016/03/05
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef FILES_H_
#define FILES_H_

#include "list.h"

/** \fn join
 *  \brief Reads all words longer than one character and returns
 *         the list of all words read.
 *
 *  \param file_name The name of the file to read the words from.
 *  
 *  \return List of the words red from file.
 */
ASSIGNMENTLIB_API 
list load_words(const unsigned char* file_name);

#endif // FILES_H_
