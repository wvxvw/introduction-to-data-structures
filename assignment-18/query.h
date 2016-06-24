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

typedef enum {
    BORROW, RETURN, JOIN, LEAVE, BOOKS, WHO_BORROWS, DONATE, BORROWS_MOST, SHOW
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

char* quote(char* in);

void populate_library_list(list in);

void populate_library_file(char* filename);

void populate_library();

query show_library();

#endif // QUERY_H_
