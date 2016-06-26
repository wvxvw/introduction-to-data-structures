#include <string.h>
#include "library.h"
#include "query.h"
#include "printable_string.h"
#include "printable_int.h"
#include "generic.h"
#include "sortable.h"
#include "pair.h"
#include "iterable.h"

DEFTYPE(library);
DEFTYPE(patron);

static library lib = NULL;
static patron libpatron = NULL;
static char* libid = "******";

int compare_patrons(const void* a, const void* b) {
    patron pa = *(patron*)a;
    patron pb = *(patron*)b;

    if (pa == pb) return 0;
    if (pa == NULL) return -1;
    if (pb == NULL) return 1;
    
    size_t sa = length(pa->books);
    size_t sb = length(pb->books);
    
    return (sa > sb) - (sa < sb);
}

int compare_patron_ids(const void* a, const void* b) {
    patron pa = *(patron*)a;
    patron pb = *(patron*)b;

    if (pa == pb) return 0;
    if (pa == NULL) return -1;
    if (pb == NULL) return 1;
    
    return strcmp(pa->id, pb->id);
}

library make_library() {
    library result = ALLOCATE(sizeof(printable_library));
    result->books = make_empty_string_chashtable();
    result->patrons = make_empty_string_chashtable();
    printable* presult = (printable*)result;
    presult->type = library_type();
    define_method(presult->type, to_string, to_string_library);
    return result;
}

patron make_patron(char* name, char* id) {
    patron result = ALLOCATE(sizeof(printable_patron));
    result->name = name;
    result->id = id;
    result->books = NULL;
    printable* presult = (printable*)result;
    presult->type = patron_type();
    define_method(presult->type, to_string, to_string_patron);
    return result;
}

library get_library() {
    if (lib == NULL) lib = make_library();
    return lib;
}

patron get_libpatron() {
    if (libpatron == NULL) libpatron = make_patron("Library", libid);
    return libpatron;
}

char* library_add_book(library lib, query q) {
    printable_string* book = make_printable_string(q->book_id);
    const char* pattern = "< Added book(%s)\n";
    size_t len = strlen(pattern) + BOOK_ID_LEN + 1;
    char* result = ALLOCATE(sizeof(char) * len);
    library llib = get_library();
    patron lpatron = get_libpatron();
    list stored = (list)chashtable_get(llib->books, (printable*)book);

    stored = cons((printable*)lpatron, stored);
    chashtable_put(llib->books, (printable*)book, (printable*)stored);
    sprintf(result, pattern, q->book_id);
    return result;
}

char* library_list_books(library lib, query q) {
    printable* key = (printable*)make_printable_string(q->id);
    patron p = (patron)peek(lib->patrons, key);
    char* books, *result, *pattern;
    
    if (p == NULL) {
        pattern = "< Patron %s doesn't exist\n";
        books = "";
    }
    else {
        pattern = "< Patron %s holds books %s\n";
        books = to_string((printable*)p->books);
    }
    size_t len = strlen(pattern) + strlen(books) + strlen(q->id) + 1;
    result = ALLOCATE(sizeof(char) * len);
    int ret = sprintf(result, pattern, q->id, books);
    if (ret < 0) printf("Error printing library_list_books\n");
    return result;
}

char* library_join(library lib, query q) {
    patron v = make_patron(q->patron, q->id);
    printable_string* k = make_printable_string(q->id);
    patron existing = (patron)find(
        lib->patrons, (printable*)v, compare_patron_ids);
    char* result, *pattern;
    
    if (existing == NULL) {
        put(lib->patrons, (printable*)k, (printable*)v);
        pattern = "< Registering %s\n";
    } else pattern = "< Patron %s already registered\n";
    result = ALLOCATE(sizeof(char) * (strlen(pattern) + strlen(q->id) + 1));
    int ret = sprintf(result, pattern, q->id);
    if (ret < 0) printf("Error printing library_join\n");
    return result;
}

char* library_leave(library lib, query q) {
    patron v = make_patron(q->patron, q->id);
    patron existing = (patron)find(
        lib->patrons, (printable*)v, compare_patron_ids);
    char* result, *pattern, *pat;
    
    if (existing == NULL) pattern = "< Patron %s is not registered\n";
    else {
        printable* k = (printable*)make_printable_string(existing->id);
        list books = existing->books;
        if (books != NULL)
            pattern = "< Patron %s must return books before leaving\n";
        else {
            pop(lib->patrons, k);
            pattern = "< Patron %s was removed\n";
        }
    }
    pat = to_string((printable*)v);
    result = ALLOCATE(sizeof(char) * (strlen(pattern) + strlen(pat) + 1));
    int ret = sprintf(result, pattern, pat);
    if (ret < 0) printf("Error printing library_leave\n");
    return result;
}

char* library_borrow(library lib, query q) {
    printable* k = (printable*)make_printable_string(q->book_id);
    printable* pk = (printable*)make_printable_string(q->id);
    list books = (list)peek(lib->books, k);
    char* result, *pattern, *pat, *book;
    patron borrower = (patron)peek(lib->patrons, pk);
    
    if (books == NULL) pattern = "< Book %s is not in the library\n";
    else if (borrower == NULL)
        pattern = "< Book %s cannot be borrowed. Patron %s deosn't exist\n";
    else {
        list copy = NULL;
        pattern = "< Book %s is not available\n";
        // FIXME: This will give all books with the same id to the
        // borrower.
        while (books != NULL) {
            patron p = (patron)first(books);
            if (strcmp(p->id, libid) == 0) {
                p = borrower;
                borrower->books = cons(k, borrower->books);
                pattern = "< Book %s borrowed by %s\n";
            }
            copy = cons((printable*)p, copy);
            books = (list)rest(books);
        }
        put(lib->books, k, (printable*)copy);
    }
    book = to_string(k);
    pat = to_string((printable*)borrower);
    size_t len = strlen(pattern) + strlen(book) + strlen(pat) + 1;
    result = ALLOCATE(sizeof(char) * len);
    int ret = sprintf(result, pattern, book, pat);
    if (ret < 0) printf("Error printing library_borrow\n");
    return result;
}

char* library_return(library lib, query q) {
    printable_string* key = make_printable_string(q->book_id);
    printable_string* pkey = make_printable_string(q->id);
    list books = (list)peek(lib->books, (printable*)key);
    patron borrower = (patron)peek(lib->patrons, (printable*)pkey);
    list copy = NULL;
    char* result, *pattern, *pat;

    if (books == NULL) pattern = "< %s doesn't belong to this library\n";
    else {
        pattern = "< %s was not borrowed\n";
        // TODO: Add generic remove() to list.
        while (books != NULL) {
            patron p = (patron)first(books);
            if (strcmp(p->id, q->id) == 0) {
                copy = cons((printable*)get_libpatron(), copy);
                copy = append(copy, (list)rest(books));
                pattern = "< %s was returned by %s\n";
                
                list pbooks = borrower->books;
                list pcopy = NULL;
                
                while (pbooks != NULL) {
                    printable* check = (printable*)first(pbooks);
                    if (compare_strings(&key, &check) == 0) {
                        pcopy = append(pcopy, (list)rest(pbooks));
                        break;
                    }
                }
                borrower->books = pcopy;
                break;
            }
            copy = cons((printable*)p, copy);
            books = (list)rest(books);
        }
        put(lib->books, (printable*)key, (printable*)copy);
    }
    pat = to_string((printable*)borrower);
    size_t len = strlen(pattern) + strlen(q->book_id) + strlen(pat) + 1;
    result = ALLOCATE(sizeof(char) * len);
    int ret = sprintf(result, pattern, q->book_id, pat);
    if (ret < 0) printf("Error printing library_borrow\n");
    return result;
}

char* library_who_borrows(library lib, query q) {
    printable_string* key = make_printable_string(q->book_id);
    list books = (list)peek(lib->books, (printable*)key);
    list patrons = NULL;
    char* result, *pattern, *pat;
    
    if (books == NULL)
        pattern = "< Book %s is not registered in the library\n";
    else {
        pattern = "< Copies of %s book are held by %s\n";
        while (books != NULL) {
            patron p = (patron)first(books);
            if (strcmp(p->id, libid) != 0)
                patrons = cons((printable*)p, patrons);
            books = (list)rest(books);
        }
        if (patrons == NULL)
            pattern = "< The %s book is not held by anyone\n";
    }
    pat = to_string((printable*)patrons);
    size_t len = strlen(pattern) + strlen(pat) + strlen(q->book_id) + 1;
    result = ALLOCATE(sizeof(char) * len);
    int ret = sprintf(result, pattern, q->book_id, pat);
    if (ret < 0) printf("Error printing library_leave\n");
    return result;
}

char* library_borrows_most(library lib, query q) {
    iterator* it = make_hashtable_iterator(lib->patrons);
    size_t max = 0;
    patron p = get_libpatron();
    char* pattern, *result, *pat, *maxs;
    
    do {
        pair kv = (pair)((printable*)it)->val;
        patron pt = (patron)kv->last;
        size_t len = length(pt->books);
        if (len > max) {
            p = pt;
            max = len;
        }
    } while (next(it));
    if (p == get_libpatron()) pattern = "< Nobody borrowed any books yet\n";
    else pattern = "< %s has most (%s) books\n";
    
    pat = to_string((printable*)p);
    maxs = to_string((printable*)make_printable_int((int)max));
    size_t len = strlen(pattern) + strlen(pat) + strlen(maxs) + 1;
    result = ALLOCATE(sizeof(char) * len);
    int ret = sprintf(result, pattern, pat, maxs);
    if (ret < 0) printf("Error printing library_borrows_most\n");
    return result;
}

char* library_show(library lib, query q) {
    char* slib = to_string((printable*)get_library());
    size_t len = strlen(slib) + 4;
    char* result = ALLOCATE(sizeof(char) * len);
    int ret = sprintf(result, "< %s\n", slib);
    if (ret < 0) printf("Error showing library\n");
    return result;
}

char* to_string_library(library llib) {
    char* books = to_string((printable*)llib->books);
    char* patrons = to_string((printable*)llib->patrons);
    const char* pattern = "library(books=%s, patrons=%s)";
    size_t len = strlen(pattern) + strlen(books) + strlen(patrons) + 1;
    char* result = ALLOCATE(sizeof(char) * len);
    int ret = sprintf(result, pattern, books, patrons);
    if (ret < 0) printf("Error printing library\n");
    return result;
}

char* to_string_patron(patron p) {
    char* books = to_string((printable*)p->books);
    const char* pattern = "patron(books=%s, name=%s, id=%s)";
    size_t len = strlen(pattern) + strlen(books) + strlen(p->name) + ID_LEN - 3;
    char* result = ALLOCATE(sizeof(char) * len);
    int ret = sprintf(result, pattern, books, p->name, p->id);
    if (ret < 0) printf("Error printing patron\n");
    return result;
}
