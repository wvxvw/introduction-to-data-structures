/**
 * \file library.h
 *
 * \ingroup exercises
 *
 * \brief This file defines functions and data-structures for working
 *        with a make-believe library.
 *
 * This file contains declarations needed to support the following
 * operations on library and its patrons:
 *   - adding books to the library.
 *   - adding patrons to the library.
 *   - removing patrons from the library.
 *   - borrowing books.
 *   - returning books.
 *   - printing diagnostic info and querying the state of the database.
 *
 * \author Oleg Sivokon
 *
 * \date 2016/03/05
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "printable.h"
#include "printable_string.h"
#include "hashtable.h"
#include "list.h"
#include "query.h"

/** \struct printable_library
 *  \brief This struct conains all information about the library.
 */
typedef struct {

    /** \brief This library is itself printable which allows it to
     *         hold information required for it to be printed.
     */
    printable printable;

    /** \brief Books currently owned by this library.
     *
     *  Whenever a book is borrowed from the ibrary, it still appears
     *  here, however, it changes its status, so it's not possible to
     *  borrow it again.
     */
    chashtable books;

    /** \brief Patrons registered in this library.
     *
     * Patrons can be dynamically added and removed (unlike books,
     * which cannot be removed).
     */
    chashtable patrons;

} printable_library;

typedef printable_library* library;

/** \struct printable_patron
 *  \brief This struct represents a patron (library user).
 */
typedef struct {
    
    /** \brief This patron is itself printable which allows it to
     *         hold information required for it to be printed.
     */
    printable printable;

    /** \brief The name of this patron (serves no function).
     */
    char* name;

    /** \brief The unique identifier of this patron.
     *
     * \c library will use this field to identify those borrowing and
     * returning books.
     */
    char* id;

    /** \brief The books currently held by this patron.
     *
     * Books are represented by their string ids.
     */
    list books;
    
} printable_patron;

typedef printable_patron* patron;

/** \fn query_handler_fn
 * \brief A class of functions for handling queries generated through
 *        interaction with the user.
 */
typedef char* (*query_handler_fn)(library, query);

/** \brief Creates a new instance of library.
 */
library make_library();

/** \brief Returns one pre-existing library.
 *
 *  There is one statically allocated instance of library which is
 *  used by default when interacting with the parser, however, 
 *  it is not initialized immediately when the program starts due to
 *  complicated initializing routine, this is why you need to call
 *  this function whenever you access it.
 *
 *  \return The default instance of library.
 */
library get_library();

/** \brief Creates an instance of \c patron.
 *
 *  Patrons aren't automatically added to the library.  Once you call
 *  this function you also must make sure the patron is added to the
 *  library.  It is also possible that the patron with the \c name and
 *  \c id had already been created.  In this case, adding to library
 *  will not be possible.
 *  
 *  \param name The name of the patron being created.  Names need not
 *              be unique.
 *              
 *  \param id The unique identifier for patrons.  While you can create
 *            multiple patrons with the same \c id, only one of them
 *            can be added to the \c library.
 *
 * \return Newly created \c patron.
 */
patron make_patron(char* name, char* id);

/** \brief Adds new book to the default library.
 *
 *  In case the book with the given id already exists in the library,
 *  the book will not be duplicated, however, the new default owner
 *  will be added to the existing book.
 *
 *  \param lib The library to add the book to.
 *
 *  \param q The \c query containing information about the book to
 *           add.  This query must set field \c book_id.  Other fields
 *           are not accessed.
 *
 * \return The message indicating the fate of the book (whether it was
 *         added or not).
 */
char* library_add_book(library lib, query q);

/** \brief Print all books borrowed by the given patron.
 *
 *  In case multiple copies of the same book were borrowed by the same
 *  patron, all copies will appear in the printed response.
 *
 *  \param lib The library to look for the patron whose books are
 *             being requested.
 *
 *  \param q The \c query containing information about the patron in
 *           question.  This query must set field \c id.  The field \c
 *           patron may be accessed, but it should be possible not to
 *           set it.
 *
 *  \return The message indicating whether retrieving the requested
 *          information succeeded.  The retrieval may fail due to
 *          patron not being registered in the given library.
 */
char* library_list_books(library lib, query q);

/** \brief Add patron to the library.
 *
 *  Patrons with the same \c id and \c patron (name) cannot join the
 *  library.
 *
 *  \param lib The library to add the given patron to.
 *
 *  \param q The \c query specifying the details of the patron being
 *           added.  The query must set \c patron and \c id fields.
 *
 *  \return The message indicating whether the action succeeded.  The
 *          action may fail if such patron already is registered in
 *          the library.
 */
char* library_join(library lib, query q);

/** \brief Remove patron from the library.
 *
 *  Patrons cannot be removed from the library while they holding
 *  books.
 *  
 *  \param lib The library to remove the patron from.
 *
 *  \param q The query specifying the patron to remove.  The query
 *         must set \c id field.  The \c patron field may be accessed
 *         while processing the query, but it should be optional.
 *
 *  \return The message indicating the success status of the action.
 *          The action may fail because the patron still holds books
 *          from the library, or because the patron has never been
 *          registered in the library.
 */
char* library_leave(library lib, query q);

/** \brief Borrow a book from the library.
 *
 *  Several condition must hold in order for this action to succeed:
 *    - Specified patron must be registered in this library.
 *    - The book must exist in the library.
 *    - The book must be available for taking.
 *  
 *  \param lib The library to borrow the book from.
 *
 *  \param q The query specifying which book to borrow.  This query
 *         must set fields \c id and \c book_id.  It should be
 *         optional to set \c patron, but it may be accessed in this
 *         fucntion.
 *
 *  \return The message indicating the success of the action.
 */
char* library_borrow(library lib, query q);

/** \brief Returns the book to the library.
 *
 *  Multiple conditions must hold for this action to succeed:
 *    - The book must exist in the library.
 *    - The patron returning the book must be registered in the library.
 *    - The book must be borrowed by the patron returning it.
 *
 *  As the result of this action no new books are added to the
 *  library.  The library changes status of the book (i.e. ownership)
 *  if this action goes through.
 *
 *  \param lib The library the book is being returned to.
 *
 *  \param q The query specifying which book to return.  The query
 *         must set \c id and \c book_id fields, however, the \c
 *         patron field may be accessed too.
 *
 *  \return The message indicating the success of the action.
 */
char* library_return(library lib, query q);

/** \brief Searches for the patron who borrowed the given book.
 *
 *  This action assumes that the book being looked up exists in the
 *  library, that the patron who borrowed it is registered in the
 *  library and that this patron did, in fact, borrow it.  Since the
 *  books with the same \c book_id cannot be distinguished, the
 *  function produces a list of patrons rather than a single answer.
 *
 *  \param lib The library to look up the book in.
 *
 *  \param q The query specifying the book to look up.  The query must
 *         set \c book_id field.
 *
 *  \return The message indicating the success of the action.  Note
 *          that in case of multiple patrons borrowing the same book,
 *          all of them are printed.
 */
char* library_who_borrows(library lib, query q);

/** \brief Searches for the patron who currently borrows most books.
 *
 *  It is possible that no books have been borrowed from the library,
 *  in which case the message returned will reflect that.
 *
 *  \param lib The library to search.
 *
 *  \param q The query struct.  This parameter is ignored.
 *
 *  \return The message indicating whether the action succeeded.
 */
char* library_borrows_most(library lib, query q);

/** \brief Shows the contenst of the given library.
 *
 *  Since \c library embeds \c printable, it provides an
 *  implementation of \c to_string method.  This method (which \see
 *  to_string_library) is designed to print all relevant information.
 *
 *  \param lib The library being printed.
 *
 *  \param q The query struct.  This parameter is ignored.
 *
 *  \return The message containing the printout of \c lib.
 */
char* library_show(library lib, query q);

/** \brief Implementation of \c to_string for \c library.
 *
 *  Prints readably the contents of the library.
 *
 *  \param lib The \c library being printed.
 */
char* to_string_library(library lib);

/** \brief Implementation of \c to_string for \c patron.
 *
 *  Prints readably the contents of the patron.
 *
 *  \param p The \c patron being printed.
 */
char* to_string_patron(patron p);

/** \brief Implementation of \c comparison_fn_t to compare patrons by
 *         their id.
 *
 *  Compares patron's id in lexicographical order (similar to \c
 *  strcmp).
 *  
 *  \param a A pointer to patron to be compared.
 *  
 *  \param b A pointer to patron to be compared.
 *
 *  \return Values sutable for various sorting fucntions (negative
 *          when a < b, positive when b < a and zero when they are equal).
 */
int compare_patrons(const void* a, const void* b);

#endif // LIBRARY_H_
