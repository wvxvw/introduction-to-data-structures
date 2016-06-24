%{
#include <stdlib.h>
#include <stdio.h>
#include "query.h"

void yyerror(char* s);
%}

%union { query query_t; char* str; }
%start pqueries
%token PLUS;
%token MINUS;
%token QUESTION;
%token BANG;
%token PATRONID;
%token BOOKID;
%token PATRON;
%type   <query_t>       rquery;
%type   <str>           PLUS, MINUS, QUESTION, BANG, PATRONID, BOOKID, PATRON;
%type   <void>          pquery, pqueries;

%%
rquery  :       PATRON PATRONID BOOKID PLUS { $$ = make_query(BORROW, $1, $2, $3); }
        |       PATRON PATRONID BOOKID MINUS { $$ = make_query(RETURN, $1, $2, $3); }
        |       PLUS PATRON PATRONID { $$ = make_query(JOIN, $2, $3, NULL); }
        |       MINUS PATRON PATRONID { $$ = make_query(LEAVE, $2, $3, NULL); }
        |       QUESTION PATRONID { $$ = make_query(BOOKS, NULL, $2, NULL); }
        |       QUESTION BOOKID { $$ = make_query(WHO_BORROWS, NULL, NULL, $2); }
        |       QUESTION BANG { $$ = make_query(BORROWS_MOST, NULL, NULL, NULL); }
        ;
pquery  : rquery { process_query($1); }
        ;
pqueries :      pquery {;}
        |       pquery pqueries {;}
        ;

%%
