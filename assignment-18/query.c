#include <string.h>
#include <stdio.h>
#include <time.h>
#include "printable.h"
#include "generic.h"
#include "query.h"
#include "library.h"
#include "list.h"
#include "files.h"
#include "printable_string.h"

DEFTYPE(query);
static const char* query_strings[] = {
    "borrow(patron=%s, id=%s, book_id=%s)",
    "return(patron=%s, id=%s, book_id=%s)",
    "join(patron=%s, id=%s)",
    "leave(patron=%s, id=%s)",
    "books(id=%s)",
    "who_borrows(book_id=%s)",
    "add_book(book_id=%s)",
    "borrows_most()",
    "show_library()"
};

static const size_t query_opts[] = {
    OPATRON | OPATRON_ID | OBOOK_ID,
    OPATRON | OPATRON_ID | OBOOK_ID,
    OPATRON | OPATRON_ID,
    OPATRON | OPATRON_ID,
    OPATRON_ID,
    OBOOK_ID,
    OBOOK_ID,
    OBOOK_ID,
    0,
    0
};

static const query_handler_fn handlers[] = {
    library_borrow,
    library_return,
    library_join,
    library_leave,
    library_list_books,
    library_who_borrows,
    library_add_book,
    library_borrows_most,
    library_show
};

void yyerror(char *text) { fprintf(stderr, "%s\n", text); }

char* to_string_helper(const char* pattern, query q, size_t fields) {
    char* result, *a, *b, *c;
    size_t len = strlen(pattern) + 1;

    switch (fields) {
        case OPATRON | OPATRON_ID | OBOOK_ID:
            len += PATRON_LEN + ID_LEN + BOOK_ID_LEN;
            a = q->patron; b = q->id; c = q->book_id;
            break;
        case OPATRON | OPATRON_ID:
            len += PATRON_LEN + ID_LEN;
            a = q->patron; b = q->id;
            break;
        case OPATRON_ID:
            len += ID_LEN;
            a = q->id;
            break;
        case OBOOK_ID:
            len += BOOK_ID_LEN;
            a = q->book_id;
            break;
    }
    result = ALLOCATE(sizeof(char) * len);
    int ret = sprintf(result, pattern, a, b, c);
    if (ret < 0) printf("Error printing query\n");
    return result;
}

char* to_string_query(query q) {
    if (q == NULL) return "";
    if (q->kind > SHOW) return "Invalid query";
    return to_string_helper(query_strings[q->kind], q, query_opts[q->kind]);
}

query make_query(query_kind kind, char* patron_name, char* patron_id, char* book_id) {
    query result = ALLOCATE(sizeof(printable_query));
    result->kind = kind;
    result->patron = patron_name;
    result->id = patron_id;
    result->book_id = book_id;
    printable* presult = (printable*)result;
    presult->type = query_type();
    define_method(presult->type, to_string, to_string_query);
    return result;
}

void process_query(query q) {
    char* result = handlers[q->kind](get_library(), q);
    printf("< Processing: %s\n%s\n> ", to_string((printable*)q), result);
}

char* str(char* in) {
    size_t len = strlen(in);
    char* result = ALLOCATE(sizeof(char) * len + 1);
    strncpy(result, in, len);
    result[len] = '\0';
    return result;
}

char* quote(char* in) {
    size_t len = strlen(in);
    char* result = ALLOCATE(sizeof(char) * len - 1);
    strncpy(result, in + 1, len - 2);
    result[len] = '\0';
    return result;
}

void populate_library_list(list in) {
    list it = in;
    while (it != NULL) {
        query q = make_query(DONATE, NULL, NULL, (char*)it->car->val);
        process_query(q);
        it = it->cdr;
    }
}

void populate_library_file(char* filename) {
    populate_library_list(load_words(filename));
}

void populate_library(size_t n) {
    size_t i;
    time_t t;
    list books = NULL;

    srand((unsigned)time(&t));
    
    for (i = 0; i < n; i++) {
        size_t id = rand() % 10000;
        size_t a = 'a' + rand() % 25;
        size_t b = 'a' + rand() % 25;
        char* result = ALLOCATE(sizeof(char) * 7);
        
        sprintf(result, "%c%c%04d", a, b, id);
        printable* ps = (printable*)make_printable_string(result);
        books = cons(ps, books);
    }
    populate_library_list(books);
}
