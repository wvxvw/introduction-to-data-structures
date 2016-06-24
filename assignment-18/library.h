#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "printable.h"
#include "printable_string.h"
#include "hashtable.h"
#include "heap.h"
#include "list.h"
#include "query.h"

typedef struct {

    printable printable;

    chashtable books;
    
    aheap patrons;

} printable_library;

typedef printable_library* library;

typedef struct {
    printable printable;
    char* name;
    char* id;
    list books;
} printable_patron;

typedef printable_patron* patron;

library make_library();

patron make_patron(char* name, char* id);

char* library_add_book(library lib, query q);

char* library_list_books(library lib, query q);

char* library_join(library lib, query q);

char* library_leave(library lib, query q);

char* library_borrow(library lib, query q);

char* library_return(library lib, query q);

char* library_who_borrows(library lib, query q);

char* library_borrows_most(library lib, query q);

char* to_string_library(library lib);

char* to_string_patron(patron p);

int compare_patrons(const void* a, const void* b);

#endif // LIBRARY_H_
