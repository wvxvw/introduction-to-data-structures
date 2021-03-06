/**
 * \file query.h
 *
 * \ingroup exercises
 *
 * \brief This file defines functions and data-structures needed to
 *        represent the query language used in library interactions.
 *
 * Queries are instantiated by the code generated by YACC from the
 * grammar you can find in query_grammar.y
 *
 * \author Oleg Sivokon
 *
 * \date 2016/03/05
 *
 * Contact: olegsivokon@gmail.com
 */
#ifndef QUERY_H_
#define QUERY_H_

#include "printable.h"
#include "list.h"

#define PATRON_LEN  32
#define ID_LEN      9
#define BOOK_ID_LEN 6
#define OPATRON    (1 << 0)
#define OPATRON_ID (1 << 1)
#define OBOOK_ID   (1 << 2)

/** \enum query_kind
 *  \brief This enum lists all possible kinds of queries.
 */
typedef enum {
    BORROW, RETURN, JOIN, LEAVE, BOOKS, WHO_BORROWS, DONATE, BORROWS_MOST, SHOW
} query_kind;

/** \struct printable_query
 *  \brief This struct represents a query generated by the YACC parser
 *         during interaction with the user.
 *
 *  Depending on the \c kind, you may or may not need to set all the
 *  fields of this struct.
 */
typedef struct {

    /** \brief This query is itself printable which allows it to
     *         hold information required for it to be printed.
     */
    printable printable;

    /** \brief Queries are distinguished by their kind.  Depending on
     * the kind, the associated handler will process the query and
     * print its results.
     */
    query_kind kind;

    /** \brief The patron's name.
     */
    char* patron;

    /** \brief The unique identifier for the patron.
     */
    char* id;

    /** \brief The unique identifire for the book.
     */
    char* book_id;
    
} printable_query;

typedef printable_query* query;

/** \brief Pretty prints \c query.
 *
 *  This is the necessary implementation of \c printable interface.
 *  
 *  \param q The query to be printed
 */
char* to_string_query(query q);

/** \brief Creates an instance of \c query.
 *
 *  These queries are created by YACC generated code, you wouldn't
 *  normally need to generate them by hand (unless for testing).
 *  
 *  \param kind The action requested by this query.
 *              
 *  \param patron_name The patron on whose behalf this query is
 *         executed (this parameter serves no real purpose), the \c
 *         patron_id is the one actually used.
 *
 *  \param patron_id The unique identifier for the patron on whose
 *         behalf this query is perfomred.
 *
 *  \param book_id The uniqu identifier of the book operated on.
 */
query make_query(query_kind kind, char* patron_name, char* patron_id, char* book_id);

/** \brief Send query for processing to the library and print the result.
 *  \param q The query to process.
 */
void process_query(query q);

/** \brief Same as \c strdup but ensures result is zero-terminated.
 *  \param in The original string.
 */
char* str(char* in);

/** \brief Removes first and last charactes from the string.
 *
 *  The first and the last characters are assumed to be strings.  This
 *  function is too naive to deal with quotes and escaping in the
 *  middle of the string.
 *  
 *  \param in The original string.
 *
 * \return The copy of the string with its first and last (not the
 *         null character) characters removed.
 */
char* quote(char* in);

/** \brief Adds all books in the list to the library.
 *
 *  \param in The list of books to add.
 */
void populate_library_list(list in);

/** \brief Adds all books in the file to the library.
 *
 *  Reads the given file treating every word in it as a book id.
 *  
 *  \param filename The file to read.
 */
void populate_library_file(char* filename);

/** \brief Adds generated books to library.
 *
 *  Generates given amount of random book identifiers and adds all of
 *  them to the library.
 *  
 *  \param n How many books to add.
 */
void populate_library(size_t n);

#endif // QUERY_H_
