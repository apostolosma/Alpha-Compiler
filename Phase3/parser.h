/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    STRIN = 260,
    WHILE = 261,
    FOR = 262,
    FUNCTION = 263,
    RETURN = 264,
    BREAK = 265,
    CONTINUE = 266,
    AND = 267,
    NOT = 268,
    OR = 269,
    LOCAL = 270,
    TRUE = 271,
    FALSE = 272,
    NIL = 273,
    INT = 274,
    REAL = 275,
    EQUAL = 276,
    PLUS = 277,
    MINUS = 278,
    MUL = 279,
    DIV = 280,
    MOD = 281,
    DE = 282,
    UNEQUAL = 283,
    UPLUS = 284,
    UMINUS = 285,
    DPLUS = 286,
    DMINUS = 287,
    GT = 288,
    LT = 289,
    GE = 290,
    LE = 291,
    LCURBRA = 292,
    RCURBRA = 293,
    LBRA = 294,
    RBRA = 295,
    LPAREN = 296,
    RPAREN = 297,
    SEMICOLON = 298,
    COMMA = 299,
    COLON = 300,
    DCOLON = 301,
    DOT = 302,
    DDOT = 303,
    ID = 304,
    EXIT_COMMAND = 305
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define STRIN 260
#define WHILE 261
#define FOR 262
#define FUNCTION 263
#define RETURN 264
#define BREAK 265
#define CONTINUE 266
#define AND 267
#define NOT 268
#define OR 269
#define LOCAL 270
#define TRUE 271
#define FALSE 272
#define NIL 273
#define INT 274
#define REAL 275
#define EQUAL 276
#define PLUS 277
#define MINUS 278
#define MUL 279
#define DIV 280
#define MOD 281
#define DE 282
#define UNEQUAL 283
#define UPLUS 284
#define UMINUS 285
#define DPLUS 286
#define DMINUS 287
#define GT 288
#define LT 289
#define GE 290
#define LE 291
#define LCURBRA 292
#define RCURBRA 293
#define LBRA 294
#define RBRA 295
#define LPAREN 296
#define RPAREN 297
#define SEMICOLON 298
#define COMMA 299
#define COLON 300
#define DCOLON 301
#define DOT 302
#define DDOT 303
#define ID 304
#define EXIT_COMMAND 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 102 "syntax.y" /* yacc.c:1909  */

	struct alpha_token_t *token;
	struct SymbolTableEntry *entry;
	struct expr *ex;
	struct call	*call;
	struct pair_expr *pair;
	unsigned int num;
	struct stmt_t* stmts;
    struct for_loop_pre* for_prefix;
	struct boolsuff	*boolsuff;

#line 166 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
