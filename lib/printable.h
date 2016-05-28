/**
 * \file printable.h
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
#ifndef PRINTABLE_H_
#define PRINTABLE_H_

#ifdef WITH_GC
#include <gc.h>
#endif

#include <stdlib.h>

#ifdef WITH_GC
#define ALLOCATE(X) GC_MALLOC(X)
#else
#define ALLOCATE(X) malloc(X)
#endif

#ifdef _WIN32
#ifdef ASSIGNMENTLIB_EXPORTS
#define ASSIGNMENTLIB_API __declspec(dllexport)
#else
#define ASSIGNMENTLIB_API __declspec(dllimport)
#endif
#else
#define ASSIGNMENTLIB_API
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
    size_t type;
    
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
ASSIGNMENTLIB_API printable* make_printable(size_t size, void* data);

/** \brief Generates a string representing the default \c printable.
 *  \param p The \c printable to print.
 */
ASSIGNMENTLIB_API char* to_string_default(printable* p);

/** \brief Translates the \c to_string call to \c p
 *  \param p The \c printable to print.
 */
ASSIGNMENTLIB_API char* to_string(printable* p);

#endif // PRINTABLE_H_
