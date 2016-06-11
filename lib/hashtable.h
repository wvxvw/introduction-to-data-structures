/**
 * \file hashtable.h
 *
 * \ingroup libassignment
 *
 * \brief This file defines basic functions for working with printable
 *        hash-tables.
 *
 * This file contains declarations for basic data-structures needed to
 * work with differently-typed hash-tables and being able to pretty-print
 * them.
 *
 * \author Oleg Sivokon
 *
 * \date 2016/03/05
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <stdbool.h>

#include "printable.h"
#include "list.h"

typedef size_t (*hash_fn_t)(unsigned char* key);

/** \struct printable_chained_hashtable
 *  \brief This struct is the backbone for all printable arrays.
 */
typedef struct {
    
    /** \brief This array is itself printable (so could be a member of
     *         another such array).
     */
    printable printable;

    /** \brief The number of members in this array.
     */
    size_t length;

    /** \brief The lists containing table values.
     */
    dlist* values;

    dlist* keys;

    hash_fn_t hash;
    
} printable_chained_hashtable;

typedef printable_chained_hashtable* chashtable;

/** \brief Creates new \c chashtable using \c data key-value pairs as
 *         input and returns it.
 */
ASSIGNMENTLIB_API
chashtable make_chashtable(hash_fn_t h, size_t size, list data);

ASSIGNMENTLIB_API
chashtable make_empty_chashtable(hash_fn_t h);

ASSIGNMENTLIB_API
dlist chashtable_put(chashtable table, unsigned char* key, printable* val);

ASSIGNMENTLIB_API
printable* chashtable_pop(chashtable table, unsigned char* key);

ASSIGNMENTLIB_API
printable* chashtable_get(chashtable table, unsigned char* key);

ASSIGNMENTLIB_API
unsigned long hash(unsigned char *str);

#endif // HASHTABLE_H_
