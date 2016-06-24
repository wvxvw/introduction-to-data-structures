#ifndef QUERY_H_
#define QUERY_H_

#include "printable.h"

#define PATRON_LEN 32
#define ID_LEN 9
#define BOOK_ID_LEN 6

typedef enum {
    BORROW, RETURN, JOIN, LEAVE, BOOKS, WHO_BORROWS, BORROWS_MOST
} query_kind;

typedef struct {
    printable printable;
    query_kind kind;
    char* patron;
    char* id;
    char* book_id;
} printable_query;

typedef printable_query* query;

char* to_string_query(query q);

query make_query(query_kind kind, char* patron_name, char* patron_id, char* book_id);

void process_query(query q);

char* str(char* in);
#endif // QUERY_H_
