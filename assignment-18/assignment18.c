#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#ifdef WITH_GC
#include <gc.h>
#endif

#include "printable.h"
#include "printable_int.h"
#include "printable_string.h"
#include "array.h"
#include "list.h"
#include "generic.h"
#include "hashtable.h"
#include "files.h"
#include "iterable.h"
#include "query.h"
#include "y.tab.h"

extern int yylex();
extern int yyparse();
extern int yylineno;
extern char* yytext;

void print_usage() {
    printf("Welcome to the library!\n"
           "To use library you must follow these rules given in ABNF:\n"
           "  add_book      := book_id+ `+` | `.` file\n"
           "  join_library  := `+` patron patron_id\n"
           "  leave_library := `-` patron patron_id\n"
           "  boorow_book   := patron? patron_id book_id `+`\n"
           "  return_book   := patron? patron_id book_id `-`\n"
           "  list_books    := `?` patron_id\n"
           "  who_borrows   := `?` book_id\n"
           "  borrows_most  := `?` `!`\n"
           "  patron        := [a-zA-Z]{1,32}\n"
           "  patron_id     := [0-9]{9}\n"
           "  book_id       := [a-zA-Z]{2}[0-9]{4}\n"
           "  file          := [\"][^\"]+[\"]\n"
           );
}

int main() {
#ifdef WITH_GC
    GC_INIT();
#endif
    print_usage();
    yyparse();
    return 0;
}
