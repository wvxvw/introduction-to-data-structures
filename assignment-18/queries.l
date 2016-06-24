%{
#include <string.h>
#include "query.h"
#include "y.tab.h"
%}

%%

[+]                      { yylval.str = str(yytext); return PLUS; }
[-]                      { yylval.str = str(yytext); return MINUS; }
[?]                      { yylval.str = str(yytext); return QUESTION; }
[!]                      { yylval.str = str(yytext); return BANG; }
\.                       { yylval.str = str(yytext); return DOT; }
[0-9]{9}                 { yylval.str = str(yytext); return PATRONID; }
[a-zA-Z][a-zA-Z][0-9]{4} { yylval.str = str(yytext); return BOOKID; }
[a-zA-Z]{1,32}           { yylval.str = str(yytext); return PATRON; }
[\"][^\"]+[\"]           { yylval.str = quote(yytext); return QUOTED; }
#[0-9]{1,12}             { yylval.num = atoi(yytext + 1); return NUM; }
[ \t\r\n]+               ;
.                        printf("line: %d, Unexpeced character: %s\n", yylineno, yytext);

%%

int yywrap() { return 1; }
