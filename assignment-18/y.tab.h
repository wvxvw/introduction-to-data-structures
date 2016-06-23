#define PLUS 257
#define MINUS 258
#define QUESTION 259
#define BANG 260
#define ACTORID 261
#define BOOKID 262
#define ACTOR 263
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union { query query_t; char* str; } YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
