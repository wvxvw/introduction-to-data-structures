%{
#include "query.h"
#include "y.tab.h"
%}

%%

[+]                      return PLUS;
[-]                      return MINUS;
[?]                      return QUESTION;
[!]                      return BANG;
[0-9]{9}                 return ACTORID;
[a-zA-Z][a-zA-Z][0-9]{4} return BOOKID;
[a-zA-Z]{1,32}           return ACTOR;
[ \t]+                   ;
.                        printf("line: %d, Unexpeced character: %s\n", yylineno, yytext);

%%

int yywrap() { return 1; }
