/**
 * \file printable.h
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
#ifndef PRINTABLE_H_
#define PRINTABLE_H_

#include <gc.h>
#include <stdlib.h>

#ifdef ALLOCATE
#define ALLOCATE(X) GC_MALLOC(X)
#else
#define ALLOCATE(X) malloc(X)
#endif

/** \struct printable
 *  \brief This struct provides the backbone for anything that can
 *         go inside a printable array.
 */
typedef struct printable printable;

/** \fn printer
 *  \brief Anything \c printable must have an implementation of this
 *         function (it will be called by the code using \c printable
 *         to print it).
 *
 * \param p The pointer to the \c printable object which will be printed.
 */
typedef char* (*printer)(printable* p);

typedef struct printable {
    
    /** \brief The printing function.
     */
    printer to_string;
    
    /** \brief How much data is stored in this element (must be
     *         suitable for \c sizeof call).
     */
    size_t size;

    /** \brief The actual value stored inside.
     */
    void* val;
} printable;

/** \brief Creates new \c printable wrapping \c data and returns it.
 */
printable* make_printable(size_t size, void* data);

/** \brief Generates a string representing the default \c printable.
 *  \param p The \c printable to print.
 */
char* to_string_default(printable* p);

/** \brief Translates the \c to_string call to \c p
 *  \param p The \c printable to print.
 */
char* to_string(printable* p);

#endif // PRINTABLE_H_
