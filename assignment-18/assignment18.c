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

int main() {
#ifdef WITH_GC
    GC_INIT();
#endif
    /* int k, v; */
    /* while (k = yylex()) { */
    /*     printf("k: %d\n", k); */
    /* } */
    yyparse();
    return 0;
}
