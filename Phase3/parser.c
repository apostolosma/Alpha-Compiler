/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 6 "syntax.y" /* yacc.c:339  */


#include "lib.h"
#include "hashtable.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


#define LIB_FUN(c) ({\
	(strcmp(c, "print") == 0) || \
	(strcmp(c, "input") == 0) || \
	(strcmp(c, "objectmemberkeys") == 0) || \
	(strcmp(c, "objecttotalmembers") == 0) || \
	(strcmp(c, "objectcopy") == 0) || \
	(strcmp(c, "totalarguments") == 0) || \
	(strcmp(c, "argument") == 0) || \
	(strcmp(c, "typeof") == 0) || \
	(strcmp(c, "strtonum") == 0) || \
	(strcmp(c, "sqrt") == 0) || \
	(strcmp(c, "cos") == 0) || \
	(strcmp(c, "sin") == 0) \
	? 1 : 0; \
})
expr * manage_term(expr *entry);
SymbolTableEntry * manage_lvalue(struct alpha_token_t *token,short type);
void update_scope();
SymbolTableEntry * noname_function ( );
SymbolTableEntry * manage_function ( struct alpha_token_t *token );
SymbolTableEntry * handle_insertion ( char *name, unsigned int line, char *type );
int yylex();
void yyerror(char *s);
void manage_if();
expr *manage_return( expr *ex);
void write_rule(char* rule);
void manage_assign();
void manage_idlist(struct alpha_token_t *token);
SymbolTableEntry * manage_call(struct alpha_token_t *token);
SymbolTableEntry * manage_id(struct alpha_token_t *token);
SymbolTableEntry * manage_global_id(struct alpha_token_t *token);
SymbolTableEntry * manage_local_id(struct alpha_token_t *token);
int check_lvalue_assex(SymbolTableEntry *sym);
SymbolTableEntry * check_activity(SymbolTableEntry *entry);
SymbolTableEntry * check_type(SymbolTableEntry *entry);
//struct alpha_token_t *manage_member(SymbolTableEntry *entry);
expr *member_item( expr *lv, char *name);
expr *make_call(expr *lv, expr *reversed_list);
expr *emit_tablecreate_indexed(pair_expr *indexed);
expr *emit_tablecreate();
call_t *emit_methodcall(expr *elist, char *name);
call_t *emit_normalcall(expr *elist);
expr *emit_iftableitem(expr *e);
expr_t get_type_op(struct alpha_token_t *op);
expr *manage_ex_op_ex_emit(expr* expr1,struct alpha_token_t *op,expr* expr2);
expr * manage_term_emition(char *type,expr* arg);
SymbolTableEntry * func_start_emit(SymbolTableEntry *func_prefix);
SymbolTableEntry * func_end_emit(SymbolTableEntry *func_prefix,unsigned int body);
SymbolTableEntry * manage_func_emition(SymbolTableEntry *entry,int body,int type);
struct stack *getscopespacestack(void);
expr * manage_assign_emition(expr* lval,expr * exp);
for_loop_pre* manage_for_pref_emition(unsigned int M,expr * expr);
void manage_for_emition(for_loop_pre* for_prefix, unsigned int N1,unsigned int N2,stmt_t * stmt,unsigned int N3);
void manage_while_emit(unsigned int while_start,unsigned int while_cond,stmt_t *whilestmt );
unsigned int manage_while_cond_emit(expr * exp);
int manage_loop_br_cont(int is_break);
int manage_if_prefix(expr *exp);
expr *manage_logical_op(char *type, expr *ex1, int M, expr *ex2);
const char* get_invalid_string(expr * err);
int check_ex_op_ex_validity(expr* expr1,struct alpha_token_t* op,expr* expr2);
expr* is_valid_numtype(expr* expr1,expr* expr2);
expr *manage_boolsuffix(expr *ex1);
void manage_stmt(expr *exp);
void patch_loopend_labels(int numof_breaks,int numof_continues);
expr *manage_empty_return();
void expr_semi_meriki(expr *exp);

extern int lines;
extern char *yytext;
extern FILE* yyin;
extern FILE* yyout;
extern int yylineno;

int noname_f = 0;
int scope = 0;
short type = 0;
SymbolTableEntry *temp;
int error_flag = 0;
bool isLoop = false;
int num_loops = 0;
int store_loops = 0;
int num_of_breaks = 0;
int num_of_continues = 0;

char err[90];

#line 162 "parser.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
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
#line 102 "syntax.y" /* yacc.c:355  */

	struct alpha_token_t *token;
	struct SymbolTableEntry *entry;
	struct expr *ex;
	struct call	*call;
	struct pair_expr *pair;
	unsigned int num;
	struct stmt_t* stmts;
    struct for_loop_pre* for_prefix;
	struct boolsuff	*boolsuff;

#line 314 "parser.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 329 "parser.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   679

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  206

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   305

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   230,   230,   231,   232,   235,   252,   259,   266,   273,
     284,   293,   301,   308,   316,   325,   338,   349,   354,   362,
     370,   378,   386,   394,   402,   410,   418,   426,   431,   437,
     437,   438,   438,   440,   449,   454,   460,   466,   480,   493,
     506,   520,   528,   542,   543,   544,   545,   551,   554,   561,
     567,   575,   582,   587,   598,   604,   619,   622,   629,   650,
     661,   662,   665,   672,   679,   693,   696,   711,   712,   715,
     721,   729,   736,   737,   738,   742,   764,   765,   768,   769,
     773,   783,   791,   792,   795,   802,   805,   814,   821,   831,
     837,   843,   849,   854,   860,   869,   871,   872,   875,   877,
     878,   879,   883,   892,   900,   908,   919,   922,   925,   937,
     940,   943,   952,   955,   961,   966,   980,   981
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "STRIN", "WHILE", "FOR",
  "FUNCTION", "RETURN", "BREAK", "CONTINUE", "AND", "NOT", "OR", "LOCAL",
  "TRUE", "FALSE", "NIL", "INT", "REAL", "EQUAL", "PLUS", "MINUS", "MUL",
  "DIV", "MOD", "DE", "UNEQUAL", "UPLUS", "UMINUS", "DPLUS", "DMINUS",
  "GT", "LT", "GE", "LE", "LCURBRA", "RCURBRA", "LBRA", "RBRA", "LPAREN",
  "RPAREN", "SEMICOLON", "COMMA", "COLON", "DCOLON", "DOT", "DDOT", "ID",
  "EXIT_COMMAND", "$accept", "program", "stmt", "break", "continue",
  "expr", "$@1", "$@2", "term", "assignexpr", "primary", "lvalue",
  "member", "callprefix", "call", "callsuffix", "normcall", "methodcall",
  "elist", "elist2", "objectdef", "indexed", "indexed2", "indexedelem",
  "block", "block2", "funcblockstart", "funcblockend", "funcname",
  "funcprefix", "upd_scp", "funcargs", "funcbody", "funcdef", "const",
  "idlist_id", "idlist", "pre_idlist_suffix", "idlist_suffix", "ifprefix",
  "elseprefix", "ifstmt", "while_start", "while_cond", "whilestmt", "N",
  "M", "loopstart", "loopend", "loopstmt", "forprefix", "forstmt",
  "returnstmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

#define YYPACT_NINF -179

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-179)))

#define YYTABLE_NINF -101

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-101)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -48,  -179,    21,  -179,  -179,   -36,  -179,  -179,   -27,   -29,
      87,   -10,    -8,   316,    -7,  -179,  -179,  -179,  -179,  -179,
     316,    48,    48,  -179,   246,   281,  -179,     7,  -179,  -179,
    -179,  -179,   394,  -179,  -179,  -179,    93,  -179,   -31,    88,
    -179,  -179,    18,  -179,  -179,   211,  -179,    46,  -179,  -179,
    -179,  -179,   316,   316,  -179,  -179,  -179,   419,  -179,  -179,
    -179,  -179,    49,    82,   -32,    88,   -32,   164,   316,   344,
      53,    59,    11,   469,    66,  -179,  -179,  -179,   316,   316,
     316,   316,   316,   316,   316,   316,   316,   316,   316,  -179,
     316,  -179,  -179,   316,    60,   316,    63,  -179,  -179,  -179,
     316,   316,    64,  -179,  -179,   113,  -179,  -179,   316,   494,
      77,  -179,    80,   164,    85,   369,  -179,   316,  -179,  -179,
    -179,  -179,    94,  -179,  -179,    96,  -179,  -179,    49,    49,
    -179,  -179,  -179,   283,   283,   121,   121,   121,   121,   611,
     544,  -179,    97,   101,   569,   110,  -179,    89,    12,  -179,
     211,   316,   211,  -179,   117,  -179,  -179,    96,  -179,  -179,
     316,   344,    11,   316,   316,   316,  -179,  -179,   316,  -179,
    -179,  -179,     3,   118,  -179,  -179,  -179,   519,  -179,  -179,
     316,   594,  -179,  -179,   119,   643,   628,   122,  -179,   127,
       3,  -179,  -179,  -179,  -179,  -179,  -179,   444,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     3,     0,     1,    77,     0,    91,   106,     0,    83,
       0,     0,     0,     0,     0,    93,    94,    92,    89,    90,
       0,     0,     0,    85,    65,     0,    14,     0,    48,     2,
      10,    11,     0,    33,    17,    41,    43,    51,     0,    44,
      45,    12,     0,    13,    47,     0,     6,     0,     7,   109,
       8,     9,     0,    65,    82,    84,   116,     0,    15,    16,
      36,    49,    35,     0,    37,     0,    39,     0,     0,     0,
       0,     0,     0,     0,     0,    50,    29,    31,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       0,    38,    40,     0,     0,    65,     0,    58,    60,    61,
       0,    65,     0,    85,    80,   104,   110,   111,    65,     0,
       0,   117,     0,     0,     0,     0,    68,     0,    64,    69,
      70,    74,     0,    71,    34,    46,   110,   110,    18,    19,
      20,    21,    22,    27,    28,    23,    24,    25,    26,    42,
       0,    52,     0,     0,     0,     0,    54,    97,     0,   103,
       0,     0,     0,   108,     0,   102,   110,     0,    78,    76,
       0,     0,     0,    65,     0,     0,    53,    62,    65,    55,
      57,    95,     0,     0,    87,    81,   105,     0,   112,   109,
       0,     0,    66,    72,     0,    30,    32,     0,   101,     0,
       0,    96,    86,    88,   107,   113,   111,     0,    75,    59,
      63,    98,    99,   109,   114,   115
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -179,  -179,     1,  -179,  -179,    -2,  -179,  -179,  -179,  -179,
    -179,    47,  -179,  -179,    74,  -179,  -179,  -179,   -47,     5,
    -179,  -179,     6,    67,    37,    73,  -179,  -179,  -179,  -179,
      90,  -179,  -179,    -6,  -179,  -179,  -179,  -179,     0,  -179,
    -179,  -179,  -179,  -179,  -179,  -178,   -55,  -179,  -179,    -5,
    -179,  -179,  -179
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,   113,    30,    31,    69,   126,   127,    33,    34,
      35,    36,    37,    38,    39,    97,    98,    99,    70,   118,
      40,    71,   123,    72,    41,   114,   148,   193,    55,    42,
      67,   104,   175,    43,    44,   172,   173,   190,   191,    45,
     150,    46,    47,   107,    48,   108,   151,   152,   195,   153,
      49,    50,    51
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      32,   196,     1,    29,   188,    52,   110,    93,    57,   -56,
      95,    60,   121,     4,    53,    94,   -56,    96,    62,    74,
      54,     3,     4,    73,     5,   205,     6,     7,     8,     9,
      10,    11,    12,    58,    13,    59,    14,    15,    16,    17,
      18,    19,    61,    32,    20,  -100,   105,   189,   142,    23,
     109,   -73,    21,    22,   145,   122,    75,   112,    23,   103,
      24,   154,    25,    14,    26,    32,   115,    27,    64,    66,
      28,   164,   165,    80,    81,    82,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   106,   139,    63,
       9,   140,     6,   119,    27,    65,    65,    28,   144,   120,
      13,   180,    14,    15,    16,    17,    18,    19,   125,   141,
      20,    32,   143,   146,    90,   161,   184,   149,    21,    22,
     156,   187,   157,   159,    91,    92,    24,   100,    25,   101,
      56,    68,    93,    27,   -56,   102,    28,   163,   171,   167,
      94,   -56,   168,    78,    79,    80,    81,    82,    32,   177,
      32,   176,   170,   178,  -101,  -101,  -101,  -101,   181,   179,
     192,   199,   185,   186,   200,     4,   182,     5,   183,     6,
       7,     8,     9,    10,    11,    12,   201,    13,   197,    14,
      15,    16,    17,    18,    19,   174,   158,    20,     0,   162,
     202,   203,     0,   147,     0,    21,    22,     0,     0,     0,
       0,    23,   -79,    24,     0,    25,     0,    26,     0,     0,
      27,     0,     4,    28,     5,     0,     6,     7,     8,     9,
      10,    11,    12,     0,    13,     0,    14,    15,    16,    17,
      18,    19,     0,     0,    20,     0,     0,     0,     0,     0,
       0,     0,    21,    22,     0,     0,     0,     0,    23,     0,
      24,     6,    25,     0,    26,     0,     0,    27,     0,    13,
      28,    14,    15,    16,    17,    18,    19,     0,     0,    20,
       0,     0,     0,     0,     0,     0,     0,    21,    22,     0,
       0,     0,     0,    68,     0,    24,     6,    25,     0,     9,
       0,     0,    27,     0,    13,    28,    14,    15,    16,    17,
      18,    19,     0,     0,    20,    78,    79,    80,    81,    82,
    -101,  -101,    21,    22,     0,     0,    85,    86,    87,    88,
      24,     6,    25,     0,     0,     0,     0,    27,     0,    13,
      28,    14,    15,    16,    17,    18,    19,     0,     0,    20,
       0,     0,     0,     0,     0,   116,     0,    21,    22,     0,
       0,     0,     0,     0,     0,    24,    76,    25,    77,     0,
       0,     0,    27,     0,     0,    28,    78,    79,    80,    81,
      82,    83,    84,     0,     0,     0,     0,    85,    86,    87,
      88,    76,     0,    77,   -67,     0,   -67,   -67,   117,     0,
       0,    78,    79,    80,    81,    82,    83,    84,     0,     0,
       0,     0,    85,    86,    87,    88,    76,     0,    77,     0,
       0,     0,     0,     0,   160,     0,    78,    79,    80,    81,
      82,    83,    84,     0,     0,     0,     0,    85,    86,    87,
      88,    76,     0,    77,     0,     0,     0,    89,     0,     0,
       0,    78,    79,    80,    81,    82,    83,    84,     0,     0,
       0,     0,    85,    86,    87,    88,    76,     0,    77,     0,
       0,     0,   111,     0,     0,     0,    78,    79,    80,    81,
      82,    83,    84,     0,     0,     0,     0,    85,    86,    87,
      88,    76,     0,    77,     0,     0,     0,   204,     0,     0,
       0,    78,    79,    80,    81,    82,    83,    84,     0,     0,
       0,     0,    85,    86,    87,    88,    76,     0,    77,     0,
       0,   124,     0,     0,     0,     0,    78,    79,    80,    81,
      82,    83,    84,     0,     0,     0,     0,    85,    86,    87,
      88,    76,     0,    77,     0,     0,   155,     0,     0,     0,
       0,    78,    79,    80,    81,    82,    83,    84,     0,     0,
       0,     0,    85,    86,    87,    88,    76,     0,    77,     0,
       0,   194,     0,     0,     0,     0,    78,    79,    80,    81,
      82,    83,    84,     0,     0,     0,     0,    85,    86,    87,
      88,    76,     0,    77,   166,     0,     0,     0,     0,     0,
       0,    78,    79,    80,    81,    82,    83,    84,     0,     0,
       0,     0,    85,    86,    87,    88,    76,     0,    77,   169,
       0,     0,     0,     0,     0,     0,    78,    79,    80,    81,
      82,    83,    84,    76,     0,    77,     0,    85,    86,    87,
      88,     0,   198,    78,    79,    80,    81,    82,    83,    84,
      76,     0,     0,     0,    85,    86,    87,    88,     0,     0,
      78,    79,    80,    81,    82,    83,    84,     0,     0,     0,
       0,    85,    86,    87,    88,    78,    79,    80,    81,    82,
      83,    84,     0,     0,     0,     0,    85,    86,    87,    88
};

static const yytype_int16 yycheck[] =
{
       2,   179,    50,     2,     1,    41,    53,    39,    10,    41,
      41,    13,     1,     1,    41,    47,    48,    48,    20,    25,
      49,     0,     1,    25,     3,   203,     5,     6,     7,     8,
       9,    10,    11,    43,    13,    43,    15,    16,    17,    18,
      19,    20,    49,    45,    23,    42,    45,    44,    95,    37,
      52,    40,    31,    32,   101,    44,    49,    63,    37,    41,
      39,   108,    41,    15,    43,    67,    68,    46,    21,    22,
      49,   126,   127,    24,    25,    26,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    41,    90,    41,
       8,    93,     5,    40,    46,    21,    22,    49,   100,    40,
      13,   156,    15,    16,    17,    18,    19,    20,    42,    49,
      23,   113,    49,    49,    21,   117,   163,     4,    31,    32,
      43,   168,    42,    38,    31,    32,    39,    39,    41,    41,
      43,    37,    39,    46,    41,    47,    49,    41,    49,    42,
      47,    48,    41,    22,    23,    24,    25,    26,   150,   151,
     152,   150,    42,   152,    33,    34,    35,    36,   160,    42,
      42,    42,   164,   165,    42,     1,   161,     3,   162,     5,
       6,     7,     8,     9,    10,    11,    49,    13,   180,    15,
      16,    17,    18,    19,    20,   148,   113,    23,    -1,   122,
     190,   196,    -1,   103,    -1,    31,    32,    -1,    -1,    -1,
      -1,    37,    38,    39,    -1,    41,    -1,    43,    -1,    -1,
      46,    -1,     1,    49,     3,    -1,     5,     6,     7,     8,
       9,    10,    11,    -1,    13,    -1,    15,    16,    17,    18,
      19,    20,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    32,    -1,    -1,    -1,    -1,    37,    -1,
      39,     5,    41,    -1,    43,    -1,    -1,    46,    -1,    13,
      49,    15,    16,    17,    18,    19,    20,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    -1,
      -1,    -1,    -1,    37,    -1,    39,     5,    41,    -1,     8,
      -1,    -1,    46,    -1,    13,    49,    15,    16,    17,    18,
      19,    20,    -1,    -1,    23,    22,    23,    24,    25,    26,
      27,    28,    31,    32,    -1,    -1,    33,    34,    35,    36,
      39,     5,    41,    -1,    -1,    -1,    -1,    46,    -1,    13,
      49,    15,    16,    17,    18,    19,    20,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    31,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    12,    41,    14,    -1,
      -1,    -1,    46,    -1,    -1,    49,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    12,    -1,    14,    40,    -1,    42,    43,    44,    -1,
      -1,    22,    23,    24,    25,    26,    27,    28,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    12,    -1,    14,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    12,    -1,    14,    -1,    -1,    -1,    43,    -1,    -1,
      -1,    22,    23,    24,    25,    26,    27,    28,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    12,    -1,    14,    -1,
      -1,    -1,    43,    -1,    -1,    -1,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    12,    -1,    14,    -1,    -1,    -1,    43,    -1,    -1,
      -1,    22,    23,    24,    25,    26,    27,    28,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    12,    -1,    14,    -1,
      -1,    42,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    12,    -1,    14,    -1,    -1,    42,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    26,    27,    28,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    12,    -1,    14,    -1,
      -1,    42,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    12,    -1,    14,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    22,    23,    24,    25,    26,    27,    28,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    12,    -1,    14,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    22,    23,    24,    25,
      26,    27,    28,    12,    -1,    14,    -1,    33,    34,    35,
      36,    -1,    38,    22,    23,    24,    25,    26,    27,    28,
      12,    -1,    -1,    -1,    33,    34,    35,    36,    -1,    -1,
      22,    23,    24,    25,    26,    27,    28,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    22,    23,    24,    25,    26,
      27,    28,    -1,    -1,    -1,    -1,    33,    34,    35,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    50,    52,     0,     1,     3,     5,     6,     7,     8,
       9,    10,    11,    13,    15,    16,    17,    18,    19,    20,
      23,    31,    32,    37,    39,    41,    43,    46,    49,    53,
      54,    55,    56,    59,    60,    61,    62,    63,    64,    65,
      71,    75,    80,    84,    85,    90,    92,    93,    95,   101,
     102,   103,    41,    41,    49,    79,    43,    56,    43,    43,
      56,    49,    56,    41,    62,    65,    62,    81,    37,    56,
      69,    72,    74,    56,    84,    49,    12,    14,    22,    23,
      24,    25,    26,    27,    28,    33,    34,    35,    36,    43,
      21,    31,    32,    39,    47,    41,    48,    66,    67,    68,
      39,    41,    47,    41,    82,    53,    41,    94,    96,    56,
      69,    43,    84,    53,    76,    56,     1,    44,    70,    40,
      40,     1,    44,    73,    42,    42,    57,    58,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    49,    69,    49,    56,    69,    49,    81,    77,     4,
      91,    97,    98,   100,    69,    42,    43,    42,    76,    38,
      45,    56,    74,    41,    97,    97,    40,    42,    41,    40,
      42,    49,    86,    87,    75,    83,    53,    56,    53,    42,
      97,    56,    70,    73,    69,    56,    56,    69,     1,    44,
      88,    89,    42,    78,    42,    99,    96,    56,    38,    42,
      42,    49,    89,   100,    43,    96
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    54,    55,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    57,
      56,    58,    56,    56,    59,    59,    59,    59,    59,    59,
      59,    59,    60,    61,    61,    61,    61,    61,    62,    62,
      62,    62,    63,    63,    63,    63,    64,    65,    65,    65,
      66,    66,    67,    68,    69,    69,    70,    70,    70,    71,
      71,    72,    73,    73,    73,    74,    75,    75,    76,    76,
      77,    78,    79,    79,    80,    81,    82,    83,    84,    85,
      85,    85,    85,    85,    85,    86,    87,    87,    88,    89,
      89,    89,    90,    91,    92,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   103
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       5,     0,     5,     1,     3,     2,     2,     2,     2,     2,
       2,     1,     3,     1,     1,     1,     3,     1,     1,     2,
       2,     1,     3,     4,     3,     4,     1,     4,     2,     6,
       1,     1,     3,     5,     2,     0,     3,     0,     1,     3,
       3,     2,     3,     0,     1,     5,     4,     1,     2,     0,
       0,     0,     1,     0,     2,     0,     4,     1,     5,     1,
       1,     1,     1,     1,     1,     1,     2,     0,     2,     2,
       0,     1,     4,     1,     2,     4,     1,     4,     3,     0,
       0,     0,     0,     3,     7,     7,     2,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 230 "syntax.y" /* yacc.c:1646  */
    {write_rule("program -> stmt program \n\n");/*print_lists($1);*/ resettemp();}
#line 1655 "parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 231 "syntax.y" /* yacc.c:1646  */
    {return ;}
#line 1661 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 232 "syntax.y" /* yacc.c:1646  */
    {write_rule("program -> empty\n\n");}
#line 1667 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 236 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("stmt -> expr ;\n");
						//manage_stmt($1);

						if(manage_term((yyvsp[-1].ex))){
							if((yyvsp[-1].ex) -> type == assignexpr_e) {
								(yyval.stmts) = (stmt_t *)malloc(sizeof(stmt_t));
								(yyval.stmts) -> breaklist = 0;
								(yyval.stmts) -> contlist = 0;
							}
							if((yyvsp[-1].ex) -> type == boolexpr_e) {
								expr_semi_meriki((yyvsp[-1].ex));
								(yyval.stmts) = NULL;
							}
						}
					}
#line 1688 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 253 "syntax.y" /* yacc.c:1646  */
    {
					write_rule("stmt -> ifstmt\n");
					(yyval.stmts) = (stmt_t *)malloc(sizeof(stmt_t));
					(yyval.stmts) -> breaklist = 0;
					(yyval.stmts) -> contlist = 0;
				}
#line 1699 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 260 "syntax.y" /* yacc.c:1646  */
    {
				write_rule("stmt -> whilestmt\n");
				(yyval.stmts) = (stmt_t *)malloc(sizeof(stmt_t));
				(yyval.stmts) -> breaklist = 0;
				(yyval.stmts) -> contlist = 0;
			}
#line 1710 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 267 "syntax.y" /* yacc.c:1646  */
    {
					write_rule("stmt -> forstmt\n");
					(yyval.stmts) = (stmt_t *)malloc(sizeof(stmt_t));
					(yyval.stmts) -> breaklist = 0;
					(yyval.stmts) -> contlist = 0;
				}
#line 1721 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 274 "syntax.y" /* yacc.c:1646  */
    {
				write_rule("stmt -> returnstmt\n");
				if((yyvsp[0].ex) != NULL) {
                    (yyval.stmts) = (stmt_t *)malloc(sizeof(stmt_t));
                    (yyval.stmts) -> breaklist = 0;
                    (yyval.stmts) -> contlist = 0;
                }
                else
                    (yyval.stmts) = NULL;
			}
#line 1736 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 285 "syntax.y" /* yacc.c:1646  */
    {
					write_rule("stmt -> break;\n");
					if(manage_loop_br_cont(1)) {
                        (yyval.stmts) = (yyvsp[0].stmts);
					}
                    else
                        (yyval.stmts) = NULL;
				}
#line 1749 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 294 "syntax.y" /* yacc.c:1646  */
    {
					write_rule("stmt -> continue;\n");
					if(manage_loop_br_cont(0))
                        (yyval.stmts) = (yyvsp[0].stmts);
                    else
                        (yyval.stmts) = NULL;
				}
#line 1761 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 302 "syntax.y" /* yacc.c:1646  */
    {
					write_rule("stmt -> block\n");
					(yyval.stmts) = (stmt_t *)malloc(sizeof(stmt_t));
					(yyval.stmts) -> breaklist = 0;
					(yyval.stmts) -> contlist = 0;
				}
#line 1772 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 309 "syntax.y" /* yacc.c:1646  */
    {
					write_rule("stmt -> funcdef\n");

					(yyval.stmts) = (stmt_t *)malloc(sizeof(stmt_t));
					(yyval.stmts) -> breaklist = 0;
					(yyval.stmts) -> contlist = 0;
				}
#line 1784 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 317 "syntax.y" /* yacc.c:1646  */
    {
					write_rule("stmt -> ;\n");
					(yyval.stmts) = (stmt_t *)malloc(sizeof(stmt_t));
					(yyval.stmts) -> breaklist = 0;
					(yyval.stmts) -> contlist = 0;
				}
#line 1795 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 326 "syntax.y" /* yacc.c:1646  */
    {
					//$$ = (stmt_t *) malloc(sizeof(stmt_t));
					//$$->breaklist = newlist(nextquad());
					//$$->contlist = 0;
					// increase breakOffset -> should be reset when we reach a funcdef and an other loop
					// push(breakstack, nextquad());
					num_of_breaks++;
					push(breaks_inloopstack,nextquad());
					emit(jump, NULL, NULL, NULL, 0,yylineno);
				}
#line 1810 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 339 "syntax.y" /* yacc.c:1646  */
    {
					//$$ = (stmt_t *) malloc(sizeof(stmt_t));
					//$$->contlist = newlist(nextquad());
					//$$->breaklist = 0;
					num_of_continues++;
					push(continues_inloopstack,nextquad());
					emit(jump, NULL, NULL, NULL, 0, yylineno);
				}
#line 1823 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 350 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("expr -> assignexpr \n");
									(yyval.ex) = (yyvsp[0].ex);
								}
#line 1832 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 355 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("expr -> expr + expr\n");
									if(check_ex_op_ex_validity((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex)))
                                        (yyval.ex) = manage_ex_op_ex_emit((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex));
                                    else
                                        (yyval.ex) = NULL;
								}
#line 1844 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 363 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("expr -> expr - expr\n");
									if(check_ex_op_ex_validity((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex)))
                                        (yyval.ex) = manage_ex_op_ex_emit((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex));
                                    else
                                        (yyval.ex) = NULL;
								}
#line 1856 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 371 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("expr -> expr * expr\n");
									if(check_ex_op_ex_validity((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex)))
                                        (yyval.ex) = manage_ex_op_ex_emit((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex));
                                    else
                                        (yyval.ex) = NULL;
								}
#line 1868 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 379 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("expr -> expr / expr\n");
									if(check_ex_op_ex_validity((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex)))
                                        (yyval.ex) = manage_ex_op_ex_emit((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex));
                                    else
                                        (yyval.ex) = NULL;
								}
#line 1880 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 387 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("expr -> expr % expr\n");
									if(check_ex_op_ex_validity((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex)))
                                        (yyval.ex) = manage_ex_op_ex_emit((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex));
                                    else
                                        (yyval.ex) = NULL;
								}
#line 1892 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 395 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("expr -> expr > expr\n");
									if(check_ex_op_ex_validity((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex)))
                                        (yyval.ex) = manage_ex_op_ex_emit((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex));
                                    else
                                        (yyval.ex) = NULL;
								}
#line 1904 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 403 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("expr -> expr < expr\n");
									if(check_ex_op_ex_validity((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex)))
                                        (yyval.ex) = manage_ex_op_ex_emit((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex));
                                    else
                                        (yyval.ex) = NULL;
								}
#line 1916 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 411 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("expr -> expr >= expr\n");
									if(check_ex_op_ex_validity((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex)))
                                        (yyval.ex) = manage_ex_op_ex_emit((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex));
                                    else
                                        (yyval.ex) = NULL;
								}
#line 1928 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 419 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("expr -> expr <= expr\n");
									if(check_ex_op_ex_validity((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex)))
                                        (yyval.ex) = manage_ex_op_ex_emit((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex));
                                    else
                                        (yyval.ex) = NULL;
								}
#line 1940 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 427 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("expr -> expr == expr\n");
									(yyval.ex) = manage_ex_op_ex_emit((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex));
								}
#line 1949 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 432 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("expr -> expr != expr\n");
									(yyval.ex) = manage_ex_op_ex_emit((yyvsp[-2].ex),(yyvsp[-1].token),(yyvsp[0].ex));
								}
#line 1958 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 437 "syntax.y" /* yacc.c:1646  */
    { (yyvsp[-1].ex) = manage_boolsuffix((yyvsp[-1].ex));}
#line 1964 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 437 "syntax.y" /* yacc.c:1646  */
    {write_rule("expr -> expr AND expr\n"); (yyval.ex) = manage_logical_op("and",(yyvsp[-4].ex),(yyvsp[-1].num),(yyvsp[0].ex));}
#line 1970 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 438 "syntax.y" /* yacc.c:1646  */
    { (yyvsp[-1].ex) = manage_boolsuffix((yyvsp[-1].ex));}
#line 1976 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 438 "syntax.y" /* yacc.c:1646  */
    {write_rule("expr -> expr OR expr\n"); (yyval.ex) = manage_logical_op("or",(yyvsp[-4].ex),(yyvsp[-1].num),(yyvsp[0].ex));}
#line 1982 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 441 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("expr -> term\n");
								
									(yyval.ex) = (yyvsp[0].ex);
										
								}
#line 1993 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 450 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("term -> ( expr ) \n");
									(yyval.ex) = (yyvsp[-1].ex);
								}
#line 2002 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 455 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("term -> -expr\n");
									(yyval.ex) = (yyvsp[0].ex);
									(yyval.ex) = manage_term_emition("-ex",(yyval.ex));
								}
#line 2012 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 461 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("term -> !expr\n");
									(yyval.ex) = (yyvsp[0].ex);
									(yyval.ex) = manage_term_emition("n_ex",(yyval.ex));
								}
#line 2022 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 467 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("term -> ++lvalue\n");

									if((yyvsp[0].ex) != NULL)
									{
										if(check_lvalue_assex((yyvsp[0].ex)->sym))
											(yyval.ex) = manage_term_emition("dp_lv",(yyvsp[0].ex));
										else
											(yyval.ex) = NULL;
									}
									else
										(yyval.ex) = NULL;
								}
#line 2040 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 481 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("term -> lvalue++\n");
									if((yyvsp[-1].ex) != NULL)
									{
										if(check_lvalue_assex((yyvsp[-1].ex)->sym))
											(yyval.ex) = manage_term_emition("lv_dp",(yyvsp[-1].ex));
										else
											(yyval.ex) = NULL;
									}
									else
										(yyval.ex) = NULL;
								}
#line 2057 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 494 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("term -> --lvalue\n");
									if((yyvsp[0].ex) != NULL)
									{
										if(check_lvalue_assex((yyvsp[0].ex)->sym))										
											(yyval.ex) = manage_term_emition("dm_lv",(yyvsp[0].ex));
										else
											(yyval.ex) = NULL;
									}
									else
										(yyval.ex) = NULL;
								}
#line 2074 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 507 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("term -> lvalue--\n");
									/*$$ = check_lvalue_assex($1);
									if($$==NULL)*/
									if((yyvsp[-1].ex) != NULL)
									{
										if(check_lvalue_assex((yyvsp[-1].ex)->sym))
											(yyval.ex) = manage_term_emition("lv_dm",(yyvsp[-1].ex));
										else
											(yyval.ex) = NULL;
									}
									else (yyval.ex) = NULL;
								}
#line 2092 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 521 "syntax.y" /* yacc.c:1646  */
    {
									write_rule("term -> primary\n");
									(yyval.ex) = (yyvsp[0].ex);
								}
#line 2101 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 529 "syntax.y" /* yacc.c:1646  */
    {
                                            write_rule("assignexpr -> lvalue = expr\n");
                                            if((yyvsp[-2].ex) != NULL)
                                            {
                                                if(check_lvalue_assex((yyvsp[-2].ex)->sym))
                                                    (yyval.ex) = manage_assign_emition((yyvsp[-2].ex),(yyvsp[0].ex));
                                                else 
                                                    (yyval.ex) = NULL;
                                            }
                                            else
                                                (yyval.ex) = NULL;
                                        }
#line 2118 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 542 "syntax.y" /* yacc.c:1646  */
    { write_rule("primary -> lvalue\n");(yyval.ex) = emit_iftableitem((yyvsp[0].ex)); }
#line 2124 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 543 "syntax.y" /* yacc.c:1646  */
    { write_rule("primary -> call\n");(yyval.ex) = emit_iftableitem((yyvsp[0].ex)); }
#line 2130 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 544 "syntax.y" /* yacc.c:1646  */
    { write_rule("primary -> objectdef\n");(yyval.ex) = (yyvsp[0].ex); }
#line 2136 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 546 "syntax.y" /* yacc.c:1646  */
    {
					write_rule("primary -> (funcdef)\n");
					(yyval.ex) = newexpr(programfunc_e);
					(yyval.ex) -> sym = (yyvsp[-1].entry);
				}
#line 2146 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 551 "syntax.y" /* yacc.c:1646  */
    { write_rule("primary -> const\n"); (yyval.ex) = (yyvsp[0].ex); }
#line 2152 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 555 "syntax.y" /* yacc.c:1646  */
    {
					write_rule("lvalue -> ID\n");
					type = 0;
					SymbolTableEntry *e = manage_lvalue(yylval.token,type);
					(yyval.ex) = lvalue_expr(e);
				}
#line 2163 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 562 "syntax.y" /* yacc.c:1646  */
    {
				write_rule("lvalue -> LOCAL ID\n");
				type = 1;
				(yyval.ex) = lvalue_expr(manage_lvalue(yylval.token, type));
			}
#line 2173 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 568 "syntax.y" /* yacc.c:1646  */
    {
				write_rule("lvalue -> DCOLON ID\n");
				type = 2;
				SymbolTableEntry *tem = manage_lvalue(yylval.token, type);
				if(tem != NULL) (yyval.ex) = lvalue_expr(tem);
				else (yyval.ex) = NULL;
			}
#line 2185 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 576 "syntax.y" /* yacc.c:1646  */
    {
				write_rule("lvalue -> member\n");
				(yyval.ex) = (yyvsp[0].ex);
			}
#line 2194 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 583 "syntax.y" /* yacc.c:1646  */
    {
							write_rule("member -> lvalue.ID \n");
							(yyval.ex) = member_item((yyvsp[-2].ex), yylval.token -> content);
						}
#line 2203 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 588 "syntax.y" /* yacc.c:1646  */
    {
							write_rule("member -> lvalue[expr]\n");
							if((yyvsp[-3].ex) == NULL) (yyval.ex) = NULL;
							else {
								(yyvsp[-3].ex)			= emit_iftableitem((yyvsp[-3].ex));
								(yyval.ex) 			= newexpr(tableitem_e);
								(yyval.ex) -> sym 	= (yyvsp[-3].ex) -> sym;
								(yyval.ex) -> index = (yyvsp[-1].ex);
							}
						}
#line 2218 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 599 "syntax.y" /* yacc.c:1646  */
    {
							write_rule("member -> call.ID\n");
							(yyval.ex)   = member_item((yyvsp[-2].ex), yylval.token -> content);
							type = 4;
						}
#line 2228 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 605 "syntax.y" /* yacc.c:1646  */
    {
							write_rule("member -> call.[expr]\n");
							if((yyvsp[-3].ex) == NULL) (yyval.ex) = NULL;
							else {
								(yyvsp[-3].ex)			= emit_iftableitem((yyvsp[-3].ex));
								(yyval.ex)			= newexpr(tableitem_e);
								(yyval.ex) -> sym	= (yyvsp[-3].ex) -> sym;
								(yyval.ex) -> index = (yyvsp[-1].ex);
								type=4;
							}
						}
#line 2244 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 619 "syntax.y" /* yacc.c:1646  */
    {type=3; (yyval.ex) = (yyvsp[0].ex);}
#line 2250 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 623 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("call -> call(elist)\n");

						(yyval.ex) = make_call((yyvsp[-3].ex), elist_head);
						empty_stack(elist_stack);
				    }
#line 2261 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 630 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("call -> lvalue callsuffix\n");
						(yyvsp[-1].ex) = emit_iftableitem((yyvsp[-1].ex));
						if((yyvsp[-1].ex) == NULL) (yyval.ex) = NULL;
						else {
							if ((yyvsp[0].call) -> method) {
								expr *t = (yyvsp[-1].ex);
								(yyvsp[-1].ex) = emit_iftableitem(member_item(t, (yyvsp[0].call) -> name));
								if((yyvsp[0].call) -> elist == NULL) {
									(yyvsp[0].call) -> elist = t;
								} else {
									elist_tail -> next = t;
									elist_tail = t;
								}
							}
							(yyval.ex) = make_call ((yyvsp[-1].ex), (yyvsp[0].call) -> elist);
							
						}
						empty_stack(elist_stack);
					}
#line 2286 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 651 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("call -> (funcdef)(elist)\n");
						expr *func = newexpr(programfunc_e);
						func -> sym = (yyvsp[-4].entry);
						(yyval.ex) = make_call(func, elist_head);
						empty_stack(elist_stack);
					}
#line 2298 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 661 "syntax.y" /* yacc.c:1646  */
    {write_rule("callsuffix -> normcall\n"); (yyval.call) = (yyvsp[0].call); }
#line 2304 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 662 "syntax.y" /* yacc.c:1646  */
    {write_rule("callsuffix -> methodcall\n"); (yyval.call) = (yyvsp[0].call);}
#line 2310 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 666 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("normcall -> (elist)\n");
						(yyval.call) = emit_normalcall((yyvsp[-1].ex));
					}
#line 2319 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 673 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("methodcall -> ..ID(elist)\n");
						(yyval.call) = emit_methodcall((yyvsp[-1].ex), (yyvsp[-3].token) -> content);
					}
#line 2328 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 680 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("elist -> expr elist2\n");
						if(elist_head == NULL) {
							elist_head = (yyvsp[-1].ex);
							elist_tail = (yyvsp[-1].ex);
						} else {
							elist_tail -> next = (yyvsp[-1].ex);
							elist_tail = (yyvsp[-1].ex);
						}
						(yyval.ex) = elist_head;
						if((yyvsp[-1].ex) != NULL)
							push_ex(elist_stack, (yyvsp[-1].ex));
					}
#line 2346 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 693 "syntax.y" /* yacc.c:1646  */
    {write_rule("elist -> empty\n"); (yyval.ex) = NULL; elist_head = NULL; elist_tail = NULL;}
#line 2352 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 697 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("elist2 -> ,expr elist2\n");
						if(elist_head == NULL) {
							elist_head = (yyvsp[-1].ex);
							elist_tail = (yyvsp[-1].ex);
						} else {
							elist_tail -> next = (yyvsp[-1].ex);
							elist_tail = (yyvsp[-1].ex);
						}
						(yyval.ex) = (yyvsp[-1].ex);
						if((yyvsp[-1].ex) != NULL)
							push_ex(elist_stack, (yyvsp[-1].ex));

					}
#line 2371 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 711 "syntax.y" /* yacc.c:1646  */
    {write_rule("elist2 -> empty\n"); elist_head = NULL; elist_tail = NULL;}
#line 2377 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 712 "syntax.y" /* yacc.c:1646  */
    {sprintf(err,"line %d:expected: ,expression\n",yylineno);yyerror(err);yyclearin;}
#line 2383 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 716 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("objectdef -> [elist]\n");
						(yyval.ex) = emit_tablecreate();
						empty_stack(elist_stack);
					}
#line 2393 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 722 "syntax.y" /* yacc.c:1646  */
    {
					write_rule("objectdef -> [indexed]\n");
					(yyval.ex) = emit_tablecreate_indexed((yyvsp[-1].pair));
				}
#line 2402 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 730 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("indexed -> indexedelem indexed2\n");
						(yyval.pair) = pair_head;
					}
#line 2411 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 736 "syntax.y" /* yacc.c:1646  */
    {write_rule("indexed2 -> ,indexedelem indexed2\n"); (yyval.pair) = (yyvsp[-1].pair);}
#line 2417 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 737 "syntax.y" /* yacc.c:1646  */
    {write_rule("indexed2 -> empty\n");}
#line 2423 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 738 "syntax.y" /* yacc.c:1646  */
    {sprintf(err,"line %d:expected: ,indexedelem\n",yylineno);yyerror(err);yyclearin;}
#line 2429 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 743 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("indexedelem -> {expr:expr}\n");
						pair_expr *t 	= (pair_expr*)malloc(sizeof(pair_expr));
						t -> index 		= (yyvsp[-3].ex);
						t -> value		= (yyvsp[-1].ex);
						t -> pair_next	= NULL;
						if(pair_head == NULL) {
							pair_head = t;
							pair_tail = t;
						} else {
							pair_tail -> pair_next = t;
							pair_tail = t;
						}
						(yyval.pair) = t;
					}
#line 2449 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 764 "syntax.y" /* yacc.c:1646  */
    {write_rule("block -> {block2}\n"); hide(scope); scope--; }
#line 2455 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 765 "syntax.y" /* yacc.c:1646  */
    {sprintf(err,"line %d: Might be bad format or a missing semicolon or bracket\n",yylineno);yyerror(err);yyclearin;}
#line 2461 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 768 "syntax.y" /* yacc.c:1646  */
    {write_rule("block2 -> stmt block2\n");}
#line 2467 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 769 "syntax.y" /* yacc.c:1646  */
    {write_rule("block2 -> empty\n");}
#line 2473 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 773 "syntax.y" /* yacc.c:1646  */
    {
                        push(loopcounterstack,num_loops);
                        num_loops=0;
                        push(breakcounterstack,num_of_breaks);
                        num_of_breaks = 0;
                        push(continuecounterstack,num_of_continues);
                        num_of_continues = 0;
                    }
#line 2486 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 783 "syntax.y" /* yacc.c:1646  */
    {
                        num_loops = pop(loopcounterstack)->item;
                        num_of_breaks = pop(breakcounterstack)->item;
                        num_of_continues = pop(continuecounterstack)->item;
                     }
#line 2496 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 791 "syntax.y" /* yacc.c:1646  */
    { temp = manage_function(yylval.token); (yyval.entry) = temp;}
#line 2502 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 792 "syntax.y" /* yacc.c:1646  */
    { temp = noname_function(); (yyval.entry) = temp;}
#line 2508 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 796 "syntax.y" /* yacc.c:1646  */
    {
											(yyval.entry) = manage_func_emition((yyvsp[0].entry),0,0);
											
										}
#line 2517 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 802 "syntax.y" /* yacc.c:1646  */
    {update_scope();}
#line 2523 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 806 "syntax.y" /* yacc.c:1646  */
    {
														scope--;
														(yyval.entry) = (yyvsp[-1].entry);
														enterscopespace();
														resetfunctionlocalsoffset();
													}
#line 2534 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 815 "syntax.y" /* yacc.c:1646  */
    {
								(yyval.num) = currscopeoffset();
								exitscopespace();
							}
#line 2543 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 822 "syntax.y" /* yacc.c:1646  */
    {
														write_rule("funcdef -> FUNTION ID(idlist) block\n");
														(yyval.entry) = manage_func_emition((yyvsp[-4].entry),(yyvsp[-1].num),1);
														temp=NULL;
														lcf = update_lcf(lcf);
													}
#line 2554 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 832 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("const -> INT\n");
						(yyval.ex) 				= newexpr(constint_e);
						(yyval.ex) -> intConst  = atoi(yylval.token -> content);
					}
#line 2564 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 838 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("const -> REAL\n");
						(yyval.ex)				 = newexpr(constreal_e);
						(yyval.ex) -> realConst  = atof(yylval.token -> content);
					}
#line 2574 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 844 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("const -> STRIN\n");
						(yyval.ex)					= newexpr(conststring_e);
						(yyval.ex) -> strConst	= yylval.token -> content;
					}
#line 2584 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 850 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("const -> NIL\n");
						(yyval.ex)					= newexpr(nil_e);
					}
#line 2593 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 855 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("const -> TRUE\n");
						(yyval.ex)					= newexpr(constbool_e);
						(yyval.ex) -> boolConst		= true;
					}
#line 2603 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 861 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("const -> FALSE\n");
						(yyval.ex)					= newexpr(constbool_e);
						(yyval.ex) -> boolConst		= false;
					}
#line 2613 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 869 "syntax.y" /* yacc.c:1646  */
    {manage_idlist(yylval.token);}
#line 2619 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 871 "syntax.y" /* yacc.c:1646  */
    {write_rule("idlist -> ID idlist2\n");}
#line 2625 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 872 "syntax.y" /* yacc.c:1646  */
    {}
#line 2631 "parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 875 "syntax.y" /* yacc.c:1646  */
    {manage_idlist(yylval.token);}
#line 2637 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 877 "syntax.y" /* yacc.c:1646  */
    {write_rule("idlist2 -> ,ID idlist2\n");}
#line 2643 "parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 878 "syntax.y" /* yacc.c:1646  */
    {write_rule("idlist2 -> empty\n");}
#line 2649 "parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 879 "syntax.y" /* yacc.c:1646  */
    {sprintf(err,"line %d: expected: ,ID\n",yylineno);yyerror(err);yyclearin;}
#line 2655 "parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 884 "syntax.y" /* yacc.c:1646  */
    {
						if((yyvsp[-1].ex) != NULL)
							(yyval.num) = manage_if_prefix((yyvsp[-1].ex));
						else
							(yyval.num) = -1;
					}
#line 2666 "parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 893 "syntax.y" /* yacc.c:1646  */
    {
						(yyval.num) = nextquad();
						emit(jump, NULL, NULL, NULL, 0, yylineno);
					}
#line 2675 "parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 901 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("ifstmt -> IF(expr)stmt \n");
						
						if((yyvsp[-1].num) != -1)
							patchlabel((yyvsp[-1].num), nextquad());
						
					}
#line 2687 "parser.c" /* yacc.c:1646  */
    break;

  case 105:
#line 909 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("ifstmt -> IF(expr)stmt elsestmt \n");
						if((yyvsp[-3].num) != -1)
						{
							patchlabel((yyvsp[-3].num), (yyvsp[-1].num) + 1);
							patchlabel((yyvsp[-1].num), nextquad());
						}
					}
#line 2700 "parser.c" /* yacc.c:1646  */
    break;

  case 106:
#line 919 "syntax.y" /* yacc.c:1646  */
    {(yyval.num) = nextquad();}
#line 2706 "parser.c" /* yacc.c:1646  */
    break;

  case 107:
#line 922 "syntax.y" /* yacc.c:1646  */
    {(yyval.num) = manage_while_cond_emit((yyvsp[-1].ex));push(continuejumpstack,(yyvsp[-2].num));}
#line 2712 "parser.c" /* yacc.c:1646  */
    break;

  case 108:
#line 926 "syntax.y" /* yacc.c:1646  */
    {
						write_rule("whilestmt -> WHILE(expr) stmt\n");
						manage_while_emit((yyvsp[-2].num), (yyvsp[-1].num), (yyvsp[0].stmts));
						//patch labels
                        patch_loopend_labels(num_of_breaks,num_of_continues);
                        //and pop to retrieve the previous ones.
                        num_of_breaks = pop(breakcounterstack)->item;
                        num_of_continues = pop(continuecounterstack)->item; 
					}
#line 2726 "parser.c" /* yacc.c:1646  */
    break;

  case 109:
#line 937 "syntax.y" /* yacc.c:1646  */
    {  (yyval.num) = nextquad(); emit(jump,NULL,NULL,NULL,0,yylineno); }
#line 2732 "parser.c" /* yacc.c:1646  */
    break;

  case 110:
#line 940 "syntax.y" /* yacc.c:1646  */
    { (yyval.num) = nextquad();}
#line 2738 "parser.c" /* yacc.c:1646  */
    break;

  case 111:
#line 943 "syntax.y" /* yacc.c:1646  */
    { 
                    ++num_loops; 
                    push(breakcounterstack,num_of_breaks);
                    num_of_breaks = 0;
                    push(continuecounterstack,num_of_continues);
                    num_of_continues = 0;
                }
#line 2750 "parser.c" /* yacc.c:1646  */
    break;

  case 112:
#line 952 "syntax.y" /* yacc.c:1646  */
    { --num_loops; }
#line 2756 "parser.c" /* yacc.c:1646  */
    break;

  case 113:
#line 956 "syntax.y" /* yacc.c:1646  */
    { 
						(yyval.stmts) = (yyvsp[-1].stmts);
					}
#line 2764 "parser.c" /* yacc.c:1646  */
    break;

  case 114:
#line 962 "syntax.y" /* yacc.c:1646  */
    { 
                        	(yyval.for_prefix) = manage_for_pref_emition((yyvsp[-2].num),(yyvsp[-1].ex));                             
                        }
#line 2772 "parser.c" /* yacc.c:1646  */
    break;

  case 115:
#line 967 "syntax.y" /* yacc.c:1646  */
    {
							write_rule("forstmt -> FOR(elist;expr;elist;)stmt\n");
							push(continuejumpstack, (yyvsp[-5].num)+1);
							manage_for_emition((yyvsp[-6].for_prefix),(yyvsp[-5].num),(yyvsp[-2].num),(yyvsp[-1].stmts),(yyvsp[0].num));
							//patch labels
							patch_loopend_labels(num_of_breaks,num_of_continues);
							//and pop to retrieve the previous ones.
							num_of_breaks = pop(breakcounterstack)->item;
							num_of_continues = pop(continuecounterstack)->item; 
							empty_stack(elist_stack);
						}
#line 2788 "parser.c" /* yacc.c:1646  */
    break;

  case 116:
#line 980 "syntax.y" /* yacc.c:1646  */
    {write_rule("returnstmt -> RETURN ;\n"); (yyval.ex) = manage_empty_return();}
#line 2794 "parser.c" /* yacc.c:1646  */
    break;

  case 117:
#line 981 "syntax.y" /* yacc.c:1646  */
    {write_rule("returnstmt -> RETURN expr;\n"); (yyval.ex) = manage_return((yyvsp[-1].ex));}
#line 2800 "parser.c" /* yacc.c:1646  */
    break;


#line 2804 "parser.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 984 "syntax.y" /* yacc.c:1906  */

void
expr_semi_meriki(expr *exp) {
	// Meriki apotimisi
		expr *meriki  = newexpr(boolexpr_e);
		meriki -> sym = newtemp(scope, LOC, yylineno);

		//print_tflist(exp -> truelist);
		//print_tflist(exp -> falselist);
		
		backpatch(exp -> truelist, nextquad());
		backpatch(exp -> falselist, nextquad()+2);
		
		emit(assign, newexpr_constbool(1), NULL, meriki, 0, yylineno);
		
		emit(jump, NULL, NULL, NULL, nextquad()+2, yylineno);

		emit(assign, newexpr_constbool(0), NULL, meriki, 0, yylineno);
}


void 
patch_loopend_labels(int numof_breaks,int numof_continues)
{
    int jump_to = 0,cont_to = 0;
    int i,brk_label,cont_label;

    jump_to = nextquad();
    cont_to = pop(continuejumpstack)->item;
    if(numof_breaks != 0)
    {
        for(i = 0; i < num_of_breaks; i++)
        {
            brk_label = pop(breaks_inloopstack)->item;
            patchlabel(brk_label,jump_to);
        }
    }

    if(numof_continues != 0)
    {
        for(i = 0; i<num_of_continues; i++)
        {
            cont_label = pop(continues_inloopstack)->item;
            patchlabel(cont_label,cont_to);
        }
    }

}

void
manage_stmt(expr *exp) {
	if(exp -> type == boolexpr_e) {
		expr *meriki = newexpr(boolexpr_e);
		meriki -> sym = newtemp(scope, LOC,yylineno);
		// Meriki apotimisi
		print_tflist(exp -> truelist);
		print_tflist(exp -> falselist);
		backpatch(exp -> truelist, nextquad());
		backpatch(exp -> falselist, nextquad()+2);

		emit(assign, newexpr_constbool(1), NULL, meriki, 0, yylineno);
						
		emit(jump, NULL, NULL, NULL, nextquad()+2, yylineno);
		emit(assign, newexpr_constbool(0), NULL, meriki, 0, yylineno);
	}
}

int check_ex_op_ex_validity(expr* expr1,struct alpha_token_t* op,expr* expr2)
{
	expr_t type = get_type_op(op);

	expr* err_expr = NULL;
	
	if(expr1 == NULL || expr2 == NULL)
		return 0;

	if(type == arithexpr_e)
	{
			err_expr = is_valid_numtype(expr1,expr2);
			if(err_expr != NULL)
			{
				char s[100];
				sprintf(s,"Error,invalid use of arithmetic operator on  %s in line %d",get_invalid_string(err_expr),yylineno);
				yyerror(s);
				return 0;
			}
	}
	else if(type == boolexpr_e)
	{
		// > < >= <= just like arithexpr_e
		//and,or,not allow everything
		//== != just like and/or but also allow NULL checking with tables~;
		
		if(!strcmp(op -> content,">") || !strcmp(op->content,"<") || !strcmp(op->content,">=") || !strcmp(op->content,"<="))
		{
			err_expr = is_valid_numtype(expr1,expr2);
			if(err_expr != NULL)
			{
				char s[100];
				sprintf(s,"Error,invalid use of arithmetic operator on %s in line %d",get_invalid_string(err_expr),yylineno);
				yyerror(s);
				return 0;
			}
		}
		else if(!strcmp(op->content,"==") || !strcmp(op->content,"!="))
		{
			//all allowed
		}
		else if(!strcmp(op->content,"and") || !strcmp(op->content,"or"))
		{
			//all allowed
		}
	}
	return 1;
}

expr* is_valid_numtype(expr* expr1,expr* expr2)
{
    expr_t type1 = expr1->type;
    expr_t type2 = expr2->type;

    if(type1 != constint_e && type1 != constreal_e && type1 != arithexpr_e && type1 != assignexpr_e && type1 != var_e  && type1 != tableitem_e)
        return expr1;
    else if(type2 != constreal_e && type2 != constint_e && type2 != arithexpr_e && type2 != assignexpr_e && type2 != var_e  && type2 != tableitem_e)
        return expr2;
    else return NULL;

}

const char* get_invalid_string(expr * err)
{

    if(err->type == var_e)
        return err->sym->value.varVal->name;
    else if(err->type == tableitem_e)
        return "table_item";
    else if(err->type == programfunc_e)
        return err->sym->value.funcVal->name;
    else if(err->type == libraryfunc_e)
        return err->sym->value.funcVal->name;
    else if(err->type == arithexpr_e)
        return err->sym->value.varVal->name;
    else if(err->type == boolexpr_e || err->type == constbool_e)
        if(err->boolConst == true)
            return "'true'";
        else 
            return "'false'";
    else if(err->type == assignexpr_e)
        return err->sym->value.varVal->name;
    else if(err->type == newtable_e)
    {
        char *c = malloc(50 * sizeof(char));
        sprintf(c,"temp '%s' : '[]'",err->sym->value.varVal->name);
        return c;
    }
    else if(err->type == constint_e )
    {
        int length = snprintf( NULL, 0, "%d", err->intConst );
        char* str = malloc( length + 1 );
        snprintf( str, length + 1, "%d", err->intConst );
        return str;
    }
    else if(err->type == constreal_e) {
        int length = snprintf( NULL, 0, "%f", err->realConst );
        char* str = malloc( length + 1 );
        snprintf( str, length + 1, "%d", err->realConst );
        return str;
    }
    else if(err->type == conststring_e)
    {
        char * c = malloc(50 * sizeof(char));
        sprintf(c,"const string '%s'",err->strConst);
        return c;
    }
}

expr *
manage_boolsuffix(expr *ex1) {
	expr *term = newexpr(boolexpr_e);
	term -> sym = newtemp(scope, LOC, yylineno);

	if(ex1 == NULL) return NULL;

	if(ex1 -> type != boolexpr_e) {
		term -> truelist = makelist(nextquad());
		term -> falselist = makelist(nextquad() + 1);

		emit(if_eq, ex1, newexpr_constbool(1), NULL, 0, yylineno);
		emit(jump, NULL, NULL, NULL, 0, yylineno);
	} else {
		return ex1;
	}

	return term;
}

expr *
manage_logical_op(char *type, expr *ex1, int M, expr *ex2) {

	expr *temp = newexpr(boolexpr_e);
	temp -> sym = newtemp(scope,LOC,yylineno);
	expr *term = newexpr(boolexpr_e);
	term -> sym = newtemp(scope, LOC, yylineno);
	
	if(ex2 -> type != boolexpr_e) {
		temp -> truelist = makelist(nextquad());
		temp -> falselist = makelist(nextquad()+1);
		emit(if_eq, ex2, newexpr_constbool(1), NULL, 0, yylineno);
		emit(jump, NULL, NULL, NULL, 0,yylineno);

		if(!strcmp(type , "and")) {
			backpatch(ex1 -> truelist, M);
			term -> truelist = temp -> truelist;
			term -> falselist = merge_tflists(ex1 -> falselist, temp -> falselist);
			print_tflist(term -> falselist);
		} else if(!strcmp(type,"or")) {
			print_tflist(ex1 -> falselist);
			backpatch(ex1 -> falselist, M);
			term -> truelist = merge_tflists(ex1 -> truelist, temp -> truelist);
			term -> falselist = temp -> falselist;
		}
	} else {

		if(!strcmp(type , "and")) {
			backpatch(ex1 -> truelist, M);
			term -> truelist = ex2 -> truelist;
			term -> falselist = merge_tflists(ex1 -> falselist, ex2 -> falselist);
		} else if(!strcmp(type,"or")) {
			backpatch(ex1 -> falselist, M);
			term -> truelist = merge_tflists(ex1 -> truelist, ex2 -> truelist);
			term -> falselist = ex2 -> falselist;
		}
	
	}

	

	return term;
}

int
manage_if_prefix(expr *exp) {
	expr *meriki = newexpr(boolexpr_e);
	meriki -> sym = newtemp(scope, LOC, yylineno);
	int res;

	if(exp == NULL) return -1;

	if(exp -> type == boolexpr_e) {
		// Meriki apotimisi
		

		backpatch(exp -> truelist, nextquad());
		backpatch(exp -> falselist, nextquad()+2);

		emit(assign, newexpr_constbool(1), NULL, meriki, 0, yylineno);
						
		emit(jump, NULL, NULL, NULL, nextquad()+2, yylineno);
		emit(assign, newexpr_constbool(0), NULL, meriki, 0, yylineno);

		emit(if_eq, meriki, newexpr_constbool(1),NULL,nextquad() + 2, yylineno);
		res = nextquad();
		emit(jump, NULL, NULL, NULL, 0, yylineno);
	} else {
		emit(if_eq, exp, newexpr_constbool(1),NULL,nextquad() + 2, yylineno);
		res = nextquad();
		emit(jump, NULL, NULL, NULL, 0,yylineno);
	}

	return res;
}

int manage_loop_br_cont( int is_break)
{
    if(is_break)//if it is break
    {
		
        if(num_loops == 0)
        {
            char s[50];
            sprintf(s,"Error breaking from non-existing loop in line %d\n", yylineno);
            yyerror(s);
			return 0;
        }
    }
    else //if it is continue
    {
        if(num_loops == 0)
        {
            char s[80];
            sprintf(s,"Error, trying to 'continue' from non-existing loop in line %d\n", yylineno);
            yyerror(s);
			return 0;
        }

    }


	return 1;
}

for_loop_pre *
manage_for_pref_emition(unsigned int M,expr * expr)
{
    for_loop_pre *prefix =(for_loop_pre *)malloc(sizeof(struct for_loop_pre));

	if(expr -> type == boolexpr_e) {
		struct expr *mer = newexpr(boolexpr_e);
		mer -> sym = newtemp(scope, LOC, yylineno);

		backpatch(expr -> truelist, nextquad());
		backpatch(expr -> falselist, nextquad()+2);

		// Meriki apotimisi
		emit(assign, newexpr_constbool(1), NULL, mer, 0, yylineno);

		emit(jump, NULL, NULL, NULL, nextquad()+2, yylineno);
		emit(assign, newexpr_constbool(0), NULL, mer, 0, yylineno);

		prefix->test = M;
    	prefix->enter = nextquad();

   	    emit(if_eq,mer,newexpr_constbool(1),NULL,0,yylineno);
	} else {
		prefix->test = M;
    	prefix->enter = nextquad();

   	    emit(if_eq,expr,newexpr_constbool(1),NULL,0,yylineno);
	}
	

    return prefix;
}

void
manage_for_emition(for_loop_pre *for_prefix, unsigned int N1,unsigned int N2,stmt_t * stmt,unsigned int N3)
{
    patchlabel(for_prefix->enter,N2+1);
    patchlabel(N1,nextquad());
    patchlabel(N2,for_prefix->test);
    patchlabel(N3,N1+1);


    patchlist(stmt->breaklist,nextquad());
    patchlist(stmt->contlist,N1+1);

}


unsigned int
manage_while_cond_emit(expr * exp)
{
    unsigned int tmp;
	

	if(exp -> type == boolexpr_e) {
		// Meriki apotimisi
		expr *meriki  = newexpr(boolexpr_e);
		meriki -> sym = newtemp(scope, LOC, yylineno);

		//print_tflist(exp -> truelist);
		//print_tflist(exp -> falselist);
		
		backpatch(exp -> truelist, nextquad());
		backpatch(exp -> falselist, nextquad()+2);
		
		emit(assign, newexpr_constbool(1), NULL, meriki, 0, yylineno);
		
		emit(jump, NULL, NULL, NULL, nextquad()+2, yylineno);

		emit(assign, newexpr_constbool(0), NULL, meriki, 0, yylineno);

		emit(
        	if_eq,meriki,newexpr_constbool(1),NULL,nextquad() +2,yylineno
   		 );
	} else {
		emit(
        	if_eq,exp,newexpr_constbool(1),NULL,nextquad() +2,yylineno
    	);
	}

    tmp = nextquad();
    emit(jump,NULL,NULL,NULL, 0, yylineno);

    return tmp;
}

void
manage_while_emit(unsigned int while_start,unsigned int while_cond,stmt_t *whilestmt )
{
    emit(jump,NULL,NULL,NULL,while_start,yylineno);
    patchlabel(while_cond,nextquad());

    patchlist(whilestmt->breaklist,nextquad());
    patchlist(whilestmt->contlist,while_start);

}

expr *
manage_assign_emition(expr* lval,expr * exp)
{
    expr * result = NULL;
	expr * meriki = newexpr(boolexpr_e);
	meriki -> sym = newtemp(scope, LOC, yylineno);
	if(lval == NULL) {
		
		return NULL;

	} else if(exp == NULL) {
		return NULL;
	}

	if(exp -> type == boolexpr_e) {
		// Meriki apotimisi
		backpatch(exp -> truelist, nextquad());
			//	print_tflist(exp -> truelist);

		backpatch(exp -> falselist, nextquad()+2);

		emit(assign, newexpr_constbool(1), NULL, meriki, 0, yylineno);
		emit(jump, NULL, NULL, NULL, nextquad()+2, yylineno);
		emit(assign, newexpr_constbool(0), NULL, meriki, 0, yylineno);

		if(lval->type == tableitem_e)
		{
			emit(tablesetelem,lval->index,exp,lval,0,yylineno);
			result = emit_iftableitem(lval);
			result -> type = assignexpr_e;
		}
		else
		{
			if(exp == NULL) return NULL;

			emit(assign,meriki,NULL,lval,0,yylineno);
			result = newexpr(assignexpr_e);
			result->sym = newtemp(scope,LOC,yylineno);

			emit(assign,lval,NULL,result,0,yylineno);

		}
	}
	else {
		if(lval->type == tableitem_e)
		{
			emit(tablesetelem,lval->index,exp,lval,0,yylineno);
			result = emit_iftableitem(lval);
			result -> type = assignexpr_e;
		}
		else
		{
			if(exp == NULL) return NULL;

			emit(assign,exp,NULL,lval,0,yylineno);
			result = newexpr(assignexpr_e);
			result->sym = newtemp(scope,LOC,yylineno);

			emit(assign,lval,NULL,result,0,yylineno);

		}
	}

    return result;
}

expr_t
get_type_op(struct alpha_token_t* op)
{
	if(!strcmp(op->content,"+") || !strcmp(op->content,"-") || !strcmp(op->content,"/") || !strcmp(op->content,"%") || !strcmp(op->content,"*"))
		return (expr_t) arithexpr_e;
	else if(!strcmp(op->content,">") || !strcmp(op->content,"<") || !strcmp(op->content,">=") || !strcmp(op->content,"<=") || !strcmp(op->content,"!=") || !strcmp(op->content,"==") || !strcmp(op->content,"and") || !strcmp(op->content,"or"))
		return (expr_t) boolexpr_e;
}

expr *
manage_ex_op_ex_emit(expr* expr1,struct alpha_token_t* op,expr* expr2)
{
	expr_t type = get_type_op(op);
	expr * expr_res =  newexpr(type);
	expr_res -> sym = newtemp(scope, LOC, yylineno);

	if(type == arithexpr_e)
	{
		if(!strcmp(op->content,"+"))
		{
				assert(expr1);
				assert(expr2);
				assert(expr_res);
				
				emit(add,expr1,expr2,expr_res,0,yylineno);
		}
		else if(!strcmp(op->content,"-"))
		{
				emit(sub,expr1,expr2,expr_res,0,yylineno);
		}
		else if(!strcmp(op->content,"*"))
		{
				emit(mul,expr1,expr2,expr_res,0,yylineno);
		}
		else if(!strcmp(op->content,"/"))
		{
				emit(divis,expr1,expr2,expr_res,0,yylineno);
		}
		else if(!strcmp(op->content,"%"))
		{
				emit(mod,expr1,expr2,expr_res,0,yylineno);
		}

	}
	else if(type == boolexpr_e)
	{
		if(!strcmp(op -> content,">"))
		{
				expr_res -> truelist = makelist(nextquad());
				expr_res -> falselist = makelist(nextquad() + 1);
				emit(if_greater, expr1, expr2, NULL, 0, yylineno);
				emit(jump, NULL, NULL, NULL, 0, yylineno);
				//emit(if_greater,expr1,expr2,NULL,nextquad()+3,0);
				//emit(assign,newexpr_constbool(0),NULL,expr_res,0,0);
				//emit(jump,NULL,NULL,NULL,0,0);
				//emit(assign,newexpr_constbool(1),NULL,expr_res,0,0);
		}
		else if(!strcmp(op->content,"<"))
		{
				expr_res -> truelist = makelist(nextquad());
				expr_res -> falselist = makelist(nextquad()+1);
				emit(if_less, expr1, expr2, NULL, 0, yylineno);
				emit(jump, NULL, NULL, NULL, 0, yylineno);
				//emit(if_less,expr1,expr2,NULL,nextquad()+3,0);
				//emit(assign,newexpr_constbool(0),NULL,expr_res,0,0);
				//emit(jump,NULL,NULL,NULL,nextquad()+2,0);
				//emit(assign,newexpr_constbool(1),NULL,expr_res,0,0);
		}
		else if(!strcmp(op->content,">="))
		{
				expr_res -> truelist = makelist(nextquad());
				expr_res -> falselist = makelist(nextquad() + 1);
				emit(if_greatereq, expr1, expr2, NULL, 0, yylineno);
				emit(jump, NULL, NULL, NULL, 0, yylineno);
				//emit(if_greatereq,expr1,expr2,NULL,nextquad()+3,0);
				//emit(assign,newexpr_constbool(0),NULL,expr_res,0,0);
				//emit(jump,NULL,NULL,NULL,nextquad()+2,0);
				//emit(assign,newexpr_constbool(1),NULL,expr_res,0,0);
		}
		else if(!strcmp(op->content,"<="))
		{
				expr_res -> truelist = makelist(nextquad());
				expr_res -> falselist = makelist(nextquad() + 1);
				emit(if_lesseq, expr1, expr2, NULL, 0, yylineno);
				emit(jump, NULL, NULL, NULL, 0, yylineno);
				//emit(if_lesseq,expr1,expr2,NULL,nextquad()+3,0);
				//emit(assign,newexpr_constbool(0),NULL,expr_res,0,0);
				//emit(jump,NULL,NULL,NULL,nextquad()+2,0);
				//emit(assign,newexpr_constbool(1),NULL,expr_res,0,0);
		}
		else if(!strcmp(op->content,"=="))
		{
				expr_res -> truelist = makelist(nextquad());
				expr_res -> falselist = makelist(nextquad() + 1);
				emit(if_eq, expr1, expr2, NULL, 0, yylineno);
				emit(jump, NULL, NULL, NULL, 0, yylineno);
				//emit(if_eq,expr1,expr2,NULL,nextquad()+3,0);
				//emit(assign,newexpr_constbool(0),NULL,expr_res,0,0);
				//emit(jump,NULL,NULL,NULL,nextquad()+2,0);
				//emit(assign,newexpr_constbool(1),NULL,expr_res,0,0);
		}
		else if(!strcmp(op->content,"!="))
		{
				expr_res -> truelist = makelist(nextquad());
				expr_res -> falselist = makelist(nextquad() + 1);
				emit(if_noteq, expr1, expr2, NULL, 0, yylineno);
				emit(jump, NULL, NULL, NULL, 0, yylineno);
				//emit(if_noteq,expr1,expr2,NULL,nextquad()+3,0);
				//emit(assign,newexpr_constbool(0),NULL,expr_res,0,0);
				//emit(jump,NULL,NULL,NULL,nextquad()+2,0);
				//emit(assign,newexpr_constbool(1),NULL,expr_res,0,0);
		}
		else
				printf("Operator not listed: %s\n",op->content);

	}

	return expr_res;
}

expr *
manage_term_emition(char *type,expr* arg)
{
	expr* term = NULL;

	if(!strcmp(type,"-ex"))
	{
		check_arithm(arg);
		term = newexpr(arithexpr_e);
		term->sym = newtemp(scope, LOC, yylineno);
		emit(uminus,arg,NULL,term,0,yylineno);
	}
	else if(!strcmp(type,"n_ex"))
	{
		
		tflist *temp = arg -> truelist;
		arg -> truelist = arg -> falselist;
		arg -> falselist = temp;
		if(arg -> type != boolexpr_e) {

			term = newexpr(boolexpr_e);
			term -> sym = newtemp(scope, LOC, yylineno);

			term -> truelist = makelist(nextquad() + 1);
			term -> falselist = makelist(nextquad());

			term -> truelist = merge_tflists(arg ->truelist, term-> truelist);
			term -> falselist = merge_tflists(arg -> falselist, term -> falselist);

			emit(if_eq, arg, newexpr_constbool(1), NULL, 0, yylineno );
			emit(jump, NULL, NULL, NULL, 0, yylineno);

		}


	}
	else if(!strcmp(type,"dp_lv"))
	{
		check_arithm(arg);
		if(arg->type == tableitem_e)
		{
			term = emit_iftableitem(arg);
			emit(add,term,newexpr_constnum(1),term,0,yylineno);
			emit(tablesetelem,arg->index,term,arg,0,yylineno);//set temp_term result to arg->index in arg
			//it is <arg arg res> not <res arg arg>.
		}
		else
		{
			emit(add,arg,newexpr_constnum(1),arg,0,yylineno);
			term = newexpr(arithexpr_e);
			term->sym = newtemp(scope, LOC, yylineno);
			emit(assign,arg,NULL,term,0,yylineno);
		}
	}
	else if(!strcmp(type,"lv_dp"))
	{
		check_arithm(arg);
		term = newexpr(var_e);
		term->sym = newtemp(scope, LOC, yylineno);
		if(arg->type == tableitem_e)
		{
			expr* val = emit_iftableitem(arg);
			emit(assign,val,NULL,term,0,yylineno);
			emit(add,val,newexpr_constnum(1),val,0,yylineno);
			emit(tablesetelem,arg->index,val,arg,0,yylineno);
		}
		else
		{
			emit(assign,arg,NULL,term,0,yylineno);
			emit(add,arg,newexpr_constnum(1),arg,0,yylineno);
		}
	}
	else if(!strcmp(type,"dm_lv"))
	{
		check_arithm(arg);
		if(arg->type == tableitem_e)
		{
			term = emit_iftableitem(arg);
			emit(sub,term,newexpr_constnum(1),term,0,yylineno);
			emit(tablesetelem,arg->index,term,arg,0,yylineno);//set temp_term result to arg->index in arg
			//it is <arg arg res> not <res arg arg>.

		}
		else
		{
			emit(sub,arg,newexpr_constnum(1),arg,0,yylineno);
			term = newexpr(arithexpr_e);
			term->sym = newtemp(scope, LOC, yylineno);
			emit(assign,arg,NULL,term,0,yylineno);
		}
	}
	else if(!strcmp(type,"lv_dm"))
	{
		check_arithm(arg);
		term = newexpr(var_e);
		term->sym = newtemp(scope, LOC, yylineno);
		if(arg->type == tableitem_e)
		{
			expr* val = emit_iftableitem(arg);
			emit(assign,val,NULL,term,0,0);
			emit(sub,val,newexpr_constnum(1),val,0,yylineno);
			emit(tablesetelem,arg->index,val,arg,0,yylineno);
		}
		else
		{
			emit(assign,arg,NULL,term,0,yylineno);
			emit(sub,arg,newexpr_constnum(1),arg,0,yylineno);
		}

	}

	return term;

}

struct stack *
getscopespacestack(void) {
	switch(currscopespace()) {
		case	program_v:			return prog_vars;
		case	function_l:			return func_locs;
		case	formal_arg:			return form_args;
		default			  :			assert(0);
	}
}

SymbolTableEntry *
func_start_emit(SymbolTableEntry *func_prefix)
{
	if(func_prefix == NULL)	{
		return NULL;
	}

	stack *scopeoffsetstack 					= getscopespacestack();
	push(scopeoffsetstack,currscopeoffset());
	push(returncounterstack, returnOffset);
	resetreturnoffset();
	
	push(functionlabelstack, nextquad());
	emit(jump, NULL, NULL, NULL, 0, yylineno);
	func_prefix-> value.funcVal -> iaddress 	= nextquadlabel();
	emit(funcstart,NULL,lvalue_expr(func_prefix),NULL,0,yylineno);//or (enum iopcode) funcstart
	
	enterscopespace();
	resetformalargsoffset();

	return func_prefix;
}

SymbolTableEntry *
func_end_emit(SymbolTableEntry *func_prefix,unsigned int body)
{
	int i,quad;
	if(func_prefix == NULL) return NULL;

	exitscopespace();
	func_prefix-> value.funcVal -> total_locals = body;

	for(i = 0; i < returnOffset; i++) {
		item *it = pop(returnlabelstack);

		if(it == NULL) break;

		quad = it -> item;
		patchlabel(quad, nextquad());
	}

	stack *scopeoffsetstack  = getscopespacestack();
	item *it 				 = (pop(scopeoffsetstack));
	if(it != NULL) {
		int offset 				 = it->item;
		restorecurrscopeoffset(offset);
	}
	restorereturnoffset();
	emit(funcend,NULL,lvalue_expr(func_prefix),NULL,0,yylineno);//make lvalue funprefix?

	item *it2 = pop(functionlabelstack);
	patchlabel(it2 -> item, nextquad());

	return func_prefix;
}

SymbolTableEntry *
manage_func_emition(SymbolTableEntry *entry,int body,int type)
{
	if(entry == NULL) return NULL;
	if(type == 0)
	{
		entry = func_start_emit(entry);
	}
	else if(type == 1)
	{
		entry = func_end_emit(entry,body);
	}

	return entry;
}

expr *
emit_iftableitem(expr *e) {
	if(e == NULL) return NULL;
	if (e->type != tableitem_e) {
		return e;
	}
	else {
		expr *result 	= newexpr(var_e);
		result->sym		= newtemp(scope, LOC, yylineno);
		emit(tablegetelem, e, e->index, result,0,yylineno);
		return result;
	}
}

expr *
emit_tablecreate_indexed(pair_expr *indexed) {
	expr *t  = newexpr(newtable_e);
	t -> sym = newtemp(scope, LOC, yylineno);
	emit(tablecreate, NULL, NULL, t,0,yylineno);
	while(indexed != NULL) {
		emit(tablesetelem, indexed -> index, indexed -> value, t,0,yylineno);

		indexed = indexed -> pair_next;
	}

	pair_head = NULL;
	pair_tail = NULL;

	return t;
}

expr *
emit_tablecreate() {
	int counter = 0;
	expr *t = newexpr(newtable_e);
	t -> sym = newtemp(scope, LOC, yylineno);
	emit(tablecreate, t, NULL, NULL,0,yylineno);
	
	while( !isstackEmpty(elist_stack) ) {
		bunch *elist = pop_ex(elist_stack);

		if(elist == NULL) break;

		emit(tablesetelem,  newexpr_constnum(counter), elist -> item,t,0,yylineno);

		++counter;
	}

	return t;
}

call_t *
emit_methodcall(expr *elist, char *name) {
	call_t *call = (call_t *) malloc(sizeof(call));
	call -> elist = elist;
	call -> method = 1;
	call -> name = name;

	return call;
}

call_t *
emit_normalcall(expr *elist) {
	call_t *call = (call_t *) malloc(sizeof(call));
	call -> elist = elist;
	call -> method = 0;
	call -> name = NULL;

	return call;
}

expr *
make_call(expr *lv, expr *reversed_list) {
	expr *func = emit_iftableitem(lv);
	while(reversed_list != NULL) {
		emit(param, reversed_list,NULL, NULL,0,yylineno);
		reversed_list = reversed_list->next;
	}
	emit(call,  func, NULL, NULL, 0,yylineno);
	expr *result = newexpr(var_e);
	result -> sym = newtemp(scope, LOC, yylineno);
	emit(getretval, NULL, NULL, result,0,yylineno);
	return result;
}

expr *
member_item(expr *lv, char *name) {
	if(lv == NULL) return NULL;
	lv = emit_iftableitem(lv);
	expr *ti = newexpr(tableitem_e);
	ti -> sym = lv -> sym;
	ti -> index = newexpr_conststring(name);

	return ti;
}

expr *
manage_term(expr *entry) {
	if(entry == NULL) return NULL;

	if(type == 1) {

		entry -> sym = check_type(entry -> sym);

	}

	return entry;
}

SymbolTableEntry *
manage_lvalue(struct alpha_token_t *token,short type) {
	SymbolTableEntry *entry;
	switch(type) {
		case 0:
			entry = manage_id(token);
			break;
		case 1:
			entry = manage_local_id(token);
			break;
		case 2:
			entry = manage_global_id(token);
			break;
		case 3:
			entry = manage_call(token);
			break;
		case 4:
			entry = manage_id(token);
			break;
		default:
			assert(0); /* NO MANS LAND */
			break;
	}

	return entry;
}
SymbolTableEntry *
manage_call(struct alpha_token_t *token) {
	SymbolTableEntry *flag;
	int i;

	flag = lookup_scope( token->content, scope );
	/* Checking inside function scope */
	if( flag == NULL ) {
		/* Checking if it is an argument */

		flag = is_it_lcf_arg(lcf,token->content);
		if( flag == NULL){

			for(i = 1; i < scope; i++) {
				/* Checking if it is in an other scope, except global */
				flag = lookup_scope( token -> content, i );
				if(flag != NULL) {
					return flag;
				}
			}
			/* Checking if it is global */
			flag = lookup(token->content);
			if(flag == NULL) {

				if(!scope) flag = handle_insertion(token->content, token->numline, "GLOBAL");
				else flag = handle_insertion(token->content, token->numline, "LOC");

				return flag;
			}
		}
	}

	return flag;
}

SymbolTableEntry *
check_type(SymbolTableEntry *entry) {

	if(entry == NULL) return NULL;

	if( entry -> type == LIBFUNC && scope != 0) {
		char s[50];
		sprintf(s,"Cannot shadow library function %s in line %d\n", entry -> value.funcVal ->name, yylineno);
		yyerror(s);
		return NULL;
	}

	return entry;
}


void update_scope() {

	scope++;

	if(scope > depth) depth = scope;
}

SymbolTableEntry *
check_activity(SymbolTableEntry *entry) {

	if( entry == NULL ) return NULL;

	if( entry -> isActive )	return entry;
	else {
		char s[100];
		if(!FUNC(entry)) {sprintf(s,"Error variable %s is not active in this scope, line %d", entry -> value.varVal -> name, yylineno); }
		else { sprintf(s,"Error variable %s is not active in this scope, line %d", entry -> value.funcVal -> name, yylineno); }
		yyerror(s);
	}
	return NULL;
}

int
check_lvalue_assex(SymbolTableEntry *sym) {
	SymbolTableEntry *entry=NULL;

//oldphase entry = lookup_scope(token->content,scope);
	char * name;
	if(FUNC(sym)){
		name = strdup(sym->value.funcVal->name);
		entry = lookup_scope(name,scope);
		if(entry == NULL )
			entry = lookup(name);
	}
	else
	{
		name = strdup(sym->value.varVal->name);
		entry = lookup_scope(name,scope);
		if(entry == NULL )
			entry = lookup(name);
	}	

	if(entry == NULL) return 0;
	else {
		if((entry -> type == LIBFUNC || entry -> type == USERFUNC) && type != 4) {
			char s[150];
			//if(entry -> value.funcVal -> scope > scope ) return 0;
			sprintf(s,"Functions are constants and their value cannot be changed: %s , in line %d",entry->value.funcVal->name, yylineno);
			yyerror(s);
			return 0;
	}
		else {
			if(entry -> value.varVal -> scope > scope ) return 0;
		}
	}
	return 1;
}

/* Handles noname functions */
SymbolTableEntry *
noname_function ( ) {
	SymbolTableEntry *e;
	char *name = (char *) malloc((sizeof("noname_f") + sizeof(int)*1));

	sprintf( name,"$%d",noname_f++);


	e = handle_insertion(name, yylineno, "USERFUNC");

	lcf = e;

	return e;
}

SymbolTableEntry *
manage_local_id(struct alpha_token_t *token) {
	SymbolTableEntry *flag;
	int i;
	flag = lookup_scope( token->content, scope );
	/* Checking inside function scope */
	if( flag == NULL ) {
		/* Checking if it is an argument */

		if(!scope) {
			flag = handle_insertion(token->content, token->numline, "GLOBAL");
		}
		else {
			if( scope && LIB_FUN(token->content) ) {
				char s[50];
				sprintf(s, "Cannot shadow library function %s, line %d\n", token->content, yylineno);
				yyerror(s);
				return NULL;
			}
			flag = handle_insertion(token->content, token->numline, "LOC");
		}
	}
	else {
		if( scope && LIB_FUN(token->content) ) {
			char s[50];
			sprintf(s, "Cannot instansiate library function %s, line %d\n", token->content, yylineno);
			yyerror(s);
			return NULL;
		}
	}

	return flag;
}

SymbolTableEntry *
manage_id(struct alpha_token_t *token) {
	SymbolTableEntry *flag;
	int i;
	flag = lookup_scope( token->content, scope );
	/* Checking inside function scope */
	if( flag == NULL ) {
		/* Checking if it is an argument */
		flag = is_it_lcf_arg(lcf,token->content);
		if( flag == NULL){
				for(i = 1; i < scope; i++) {
				/* Checking if it is in an other scope, except global */
				flag = lookup_scope( token -> content, i );
				if(flag != NULL) {
					if(lcf == NULL) return flag;
					int lcf_scope = lcf -> value.funcVal -> scope;
					if(FUNC(flag) ) {
						return flag;
					} else {
						if(lcf_scope >= flag -> value.varVal -> scope ) {
							char s[50];
							sprintf(s, "Cannot access %s, line %d\n", token->content, yylineno);
							yyerror(s);
							return NULL;
						} else {
							return flag;
						}
					}
				}
			}
			/* Checking if it is global */
			flag = lookup(token->content);
			if(flag == NULL) {

				if(!scope) flag = handle_insertion(token->content, token->numline, "GLOBAL");
				else flag = handle_insertion(token->content, token->numline, "LOC");

				return flag;
			}
		}
	}

	return flag;
}

SymbolTableEntry *
manage_global_id(struct alpha_token_t *token) {
	SymbolTableEntry *flag = NULL;

	flag = lookup_scope( token->content, 0 );

	if( flag == NULL ) {
		char s[100];
		sprintf(s,"Error cannot use ::%s in line %d, token must already exist before calling it.",token->content, yylineno);
		yyerror(s);
	}

	return flag;
}

SymbolTableEntry *
manage_function ( struct alpha_token_t *token ) {
	char *type = (char *) malloc(sizeof(char)*10);
	SymbolTableEntry *e = NULL, *flag;

	if( LIB_FUN(token->content) ) {
		type = strdup("LIBFUNC");
	}
	else {
		type = strdup("USERFUNC");
	}

	flag = lookup_scope(token->content, scope);

	if(flag == NULL) {
		if(!LIB_FUN(token->content)){
			e = handle_insertion( token->content, token->numline, type );
		}
		else {
			char s[50];
			sprintf(s,"Error cannot declare library function %s in line %d",token->content, yylineno);
			yyerror(s);
			return NULL;
		}
	}
	else {
		char s[150];
		if(flag->type == LIBFUNC)
		{
			sprintf(s,"Error in line %d name %s cannot be used for function declaration cause it shadows library function.\n", yylineno, token->content);
			yyerror(s);
			return NULL;
		}
		else
		{
			sprintf(s,"Error in line %d name %s cannot be used for function declaration cause it is already taken in this scope.\n",yylineno, token->content);
			yyerror(s);
			return NULL;
		}
	}

	lcf = e;

	return e;

}

SymbolTableEntry *
handle_insertion ( char *name, unsigned int line, char *type ) {

	SymbolType e = get_type(type);
	SymbolTableEntry *entry;


	entry = insert_variable( name, line, scope, e, currscopespace(), currscopeoffset() );
	updatecurrspaceoffset();

	return entry;
}


void manage_idlist(struct alpha_token_t *token) {
	SymbolTableEntry *e, *flag;

	if(temp == NULL) return;

	flag = lookup_scope( token -> content, scope );
	if(flag != NULL) {
		char s[100];
		sprintf(s,"Error in line %d name \"%s\" is already taken in this scope.\n", yylineno, token->content);
		yyerror(s);
	}
	if(LIB_FUN(token->content)) {
		char s[100];
		sprintf(s,"Error in line %d name \"%s\" is a library function.\n", yylineno, token->content);
		yyerror(s);
	}

	e = handle_insertion( token->content, token->numline, "FORMAL" );
	if(e != NULL){
		if(temp != NULL)
		{

			if(temp -> value.funcVal -> arguments == NULL) {
				temp -> value.funcVal -> arguments = e;
				temp -> value.funcVal -> arg_tail = e;
				e -> value.varVal -> arg_next = NULL;

			} else {
				SymbolTableEntry *a = temp -> value.funcVal -> arg_tail;
				a -> value.varVal -> arg_next = e;
				temp -> value.funcVal -> arg_tail = e;
				e -> value.varVal -> arg_next = NULL;
			}
		}
	}
}

expr *
manage_empty_return() {
	if(lcf == NULL) {
        char s[80];
        sprintf(s,"Error returning from non-existing function in line %d\n", yylineno);
        yyerror(s);
        return NULL;
    }
	if(lcf -> value.funcVal -> scope == 0) {
        SymbolTableEntry *arg1 = lcf -> value.funcVal -> arguments;

        if(arg1 != NULL)
        {
            if(!arg1 -> isActive )
            {
                char s[80];
                sprintf(s,"Error returning from non-existing function in line %d\n", yylineno);
                yyerror(s);
                return NULL;
            }
        }
    }

	
	expr *ex = newexpr(nil_e);
	ex -> sym = newtemp(scope, LOC, yylineno);

	emit(ret, NULL, NULL, ex, 0, yylineno);
	push(returnlabelstack, nextquad());
	returnOffset++;
	emit(jump, NULL, NULL, NULL, 0, yylineno);

    return ex;
}

expr *
manage_return(expr *ex) {
	
	
    if(lcf == NULL) {
        char s[80];
        sprintf(s,"Error returning from non-existing function in line %d\n", yylineno);
        yyerror(s);
        return NULL;
    }
	if(lcf -> value.funcVal -> scope == 0) {
        SymbolTableEntry *arg1 = lcf -> value.funcVal -> arguments;

        if(arg1 != NULL)
        {
            if(!arg1 -> isActive )
            {
                char s[80];
                sprintf(s,"Error returning from non-existing function in line %d\n", yylineno);
                yyerror(s);
                return NULL;
            }
        }
    }
	if(ex == NULL) return NULL;
	
	if(ex -> type == boolexpr_e) {
		expr *meriki = newexpr(boolexpr_e);
		meriki -> sym = newtemp(scope, LOC, yylineno);

		// Meriki apotimisi
		backpatch(ex -> truelist, nextquad());
		backpatch(ex -> falselist, nextquad()+2);

		emit(assign, newexpr_constbool(1), NULL, meriki, 0, yylineno);
		emit(jump, NULL, NULL, NULL, nextquad()+2, yylineno);
		emit(assign, newexpr_constbool(0), NULL, meriki, 0, yylineno);
		
	
		emit(ret, NULL, NULL, meriki, 0, yylineno);
		push(returnlabelstack, nextquad());
		returnOffset++;
		emit(jump, NULL, NULL, NULL, 0, yylineno);

		return meriki;
	}

	emit(ret, NULL, NULL, ex, 0, yylineno);
	push(returnlabelstack, nextquad());
	returnOffset++;
	emit(jump, NULL, NULL, NULL, 0, yylineno);

    return ex;
}



bool init() {
	char *libfuncs[] =  { "print", "input", "objectmemberkeys", "objecttotalmembers", "objectcopy", "totalarguments", "argument", "typeof", "strtonum", "sqrt", "cos", "sin", ""}, **it;
	SymbolType type = LIBFUNC;
	bool flag = false;
	int counter = 0;
	depth = 0;

	it = libfuncs;

	create();

	while(*it != "") {
		flag = insert_variable( *it++, 0, 0, type, program_v, 0 );
	}

	//Initializing stacks *prog_vars, *func_locs, *form_args;
	prog_vars 				= create_stack();
	func_locs 				= create_stack();
	form_args 				= create_stack();
	loopcounterstack 		= create_stack();
	returncounterstack		= create_stack();
	returnlabelstack		= create_stack();
	functionlabelstack		= create_stack();
	breakcounterstack   	= create_stack();
    continuecounterstack    = create_stack();
    continues_inloopstack   = create_stack();
    breaks_inloopstack      = create_stack();
    continuejumpstack       = create_stack();
	elist_stack				= create_stack_expr();

	total 				= EXPAND_SIZE;
	currQuad 			= 0;
	tempcounter			= 0;
	formalArgOffset 	= 0;
	functionLocalOffset = 0;
	programVarOffset	= 0;
	returnOffset		= 0;
	scopespaceCounter	= 1;

	elist_head 	= NULL;
	pair_head 	= NULL;

	quads = (quad *)calloc(total,sizeof(quad));

	for(counter = 0; counter < total; counter++) {
		allocate_quad(quads+counter);
	}

	make_stmt(stmtslist);
	return flag;
}

void write_rule(char* rule)
{
	FILE* output = NULL;

	output = fopen("rules.txt","a");
	fprintf(output,rule);

	fclose(output);
}

void
yyerror(char *s) {
	fprintf(stderr, "%s \n", s);
	error_flag=1;
}

int yylex()
{
	int ntoken;
	yylval.token=(struct alpha_token_t *)malloc(sizeof(struct alpha_token_t));
	yylval.token->alpha_yylex=NULL;
	ntoken = alpha_yylex(yylval.token);
	return ntoken;
}

int main(int argc, char *argv[]) {
	bool flag = false;
	char* input;
	int inmode = -1;
	int outmode = -1;

	FILE* output = NULL;

	if(argc == 3) {
		if(argv[1][0] == '-')
		{
			yyin = stdin;
			inmode = 0;
		}
		else
		{
			yyin = fopen(argv[1], "r");
			inmode = 1;
		}

		if(argv[2][0] == '-')
		{
			yyout=stdout;
			outmode= 0;
		}
		else
		{
			yyout = fopen(argv[2], "w");
			outmode = 1;
		}
	}
	else
	{
		printf("Wrong number of arguments given\n");
		return 0;
	}
	flag = init();
	assert(flag != false);

	yyparse();
	if(!error_flag) {
		print_scopes(yyout);
		display_quads(yyout);
	}
//	print_table();
}

