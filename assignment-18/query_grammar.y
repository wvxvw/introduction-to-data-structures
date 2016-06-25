%{
#include <stdlib.h>
#include <stdio.h>
#include "query.h"
#include "list.h"
#include "printable_string.h"

void yyerror(char* s);
int yylex();
%}

%union { query queryt; char* str; list strlist; size_t num; }
%start pqueries
%token PLUS;
%token DOT;
%token QUOTED;
%token MINUS;
%token QUESTION;
%token BANG;
%token PATRONID;
%token BOOKID;
%token PATRON;
%token NUM;
%type   <queryt>        rquery;
%type   <num>           NUM;
%type   <str>           PLUS, MINUS, QUESTION, BANG, PATRONID, BOOKID, PATRON, DOT, QUOTED;
%type   <void>          pquery, pqueries, populate;
%type   <strlist>       books;

%%
books   :       BOOKID {
                    printable* ps = (printable*)make_printable_string($1);
                    $$ = cons(ps, NULL);
                }
        |       BOOKID books {
                    printable* ps = (printable*)make_printable_string($1);
                    $$ = cons(ps, $2);
                }
        ;

rquery  :       PATRON PATRONID BOOKID PLUS { $$ = make_query(BORROW, $1, $2, $3); }
        |       PATRON PATRONID BOOKID MINUS { $$ = make_query(RETURN, $1, $2, $3); }
        |       PLUS PATRON PATRONID { $$ = make_query(JOIN, $2, $3, NULL); }
        |       MINUS PATRON PATRONID { $$ = make_query(LEAVE, $2, $3, NULL); }
        |       QUESTION PATRONID { $$ = make_query(BOOKS, NULL, $2, NULL); }
        |       QUESTION BOOKID { $$ = make_query(WHO_BORROWS, NULL, NULL, $2); }
        |       QUESTION BANG { $$ = make_query(BORROWS_MOST, NULL, NULL, NULL); }
        |       QUESTION QUESTION { $$ = make_query(SHOW, NULL, NULL, NULL); }
        ;

populate :      DOT books PLUS { populate_library_list($2); }
        |       DOT QUOTED { populate_library_file($2); }
        |       DOT NUM { populate_library($2); }
        ;

pquery  :       rquery { process_query($1); }
        |       populate {;}
        ;

pqueries :      pquery {;}
        |       pquery pqueries {;}
        ;

%%
