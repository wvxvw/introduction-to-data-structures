#define PLUS 257
#define DOT 258
#define QUOTED 259
#define MINUS 260
#define QUESTION 261
#define BANG 262
#define PATRONID 263
#define BOOKID 264
#define PATRON 265
#define NUM 266
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union { query queryt; char* str; list strlist; size_t num; } YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
