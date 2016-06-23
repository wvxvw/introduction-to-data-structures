%{
#include <stdlib.h>
#include <stdio.h>
#include "query.h"

void yyerror(char* s);
%}

%union { query query_t; char* str; }
%start pquery
%token PLUS;
%token MINUS;
%token QUESTION;
%token BANG;
%token ACTORID;
%token BOOKID;
%token ACTOR;
%type   <query_t>       pquery;
%type   <str>           PLUS, MINUS, QUESTION, BANG, ACTORID, BOOKID, ACTOR;

%%
pquery  :       ACTOR ACTORID BOOKID PLUS { $$ = make_query(BORROW, $1, $2, $3); }
        |       ACTOR ACTORID BOOKID MINUS { $$ = make_query(RETURN, $1, $2, $3); }
        |       PLUS ACTOR ACTORID { $$ = make_query(JOIN, $1, $2, NULL); }
        |       MINUS ACTOR ACTORID { $$ = make_query(LEAVE, $1, $2, NULL); }
        |       QUESTION ACTORID { $$ = make_query(BOOKS, NULL, $1, NULL); }
        |       QUESTION BOOKID { $$ = make_query(BOOKS, NULL, NULL, $1); }
        |       QUESTION BANG { $$ = make_query(BOOKS, NULL, NULL, NULL); }
        ;

%%
/* void yyerror(char* s) { fprintf(stderr, "%s\n", s); } */
