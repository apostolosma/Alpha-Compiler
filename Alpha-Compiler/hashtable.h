
/*
        Apostolos Mavrogiannakis csd3799
        Varsamis Haralampos csd3744
        Georgia Rapousi csd3836
*/

#ifndef __HASHTABLE_H_
#define __HASHTABLE_H_
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "stack.h"

#define FUNC(c) 	((c->type == LIBFUNC ) || (c->type == USERFUNC) ? true : false)
#define SIZE 512 // size of hash table
#define SCOPE_SIZE 20 // Initial size of scope_size's indexes

#define EXPAND_SIZE 4096
#define CURR_SIZE   (total*sizeof(quad))
#define NEW_SIZE    (EXPAND_SIZE*sizeof(quad)+CURR_SIZE)

typedef enum var_t {
	program_v = 1,	function_l,	formal_arg
}var_t;

typedef enum iopcode {
    assign = 0,     add,            sub,
    mul,            divis,          mod,
    uminus,         and,            or,
    not,            if_eq,          if_noteq,
    if_lesseq,      if_greatereq,   if_less,
    if_greater,     call,           param,
    ret,            getretval,      funcstart,
    funcend,        tablecreate,   
    tablegetelem,   tablesetelem,   jump
}iopcode;

typedef enum expr_t{
    var_e,
    tableitem_e,

    programfunc_e,
    libraryfunc_e,

    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,

    constint_e,
    constreal_e,
    constbool_e,
    conststring_e,

    nil_e,
}expr_t;

typedef struct expr {
    expr_t                    type;
    struct SymbolTableEntry   *sym;
    struct expr               *index;
    int                       intConst;
    double                    realConst;
    char*                     strConst;
    bool                      boolConst;
    struct expr               *next;
    struct tflist             *truelist,*falselist;
}expr;

typedef struct quad {
    iopcode     op;
    struct expr *result;
    struct expr *arg1;
    struct expr *arg2;
    unsigned    label;
    unsigned    line;
    unsigned    taddress;
}quad;

typedef struct call {
    struct expr *elist;
    unsigned char method;
    char* name;
}call_t;

typedef struct pair_expr {
    expr *index;
    expr *value;
    struct pair_expr  *pair_next;

}pair_expr;

typedef struct for_loop_pre {
    unsigned int test; //expr test of 
    unsigned int enter;
}for_loop_pre;

typedef struct stmt_t {
    int breaklist;
    int contlist;
}stmt_t;

typedef struct tflist{
    int quad_offset;
    struct tflist *next;
}tflist;

struct quad         *quads;
struct stack        *prog_vars, *func_locs, *form_args, *loopcounterstack, *returncounterstack, *returnlabelstack, *functionlabelstack;
struct stack        *breakcounterstack, *continuecounterstack, *continues_inloopstack, *breaks_inloopstack, *continuejumpstack;
struct stack_expr   *elist_stack;
unsigned int        total;
unsigned int        currQuad;
unsigned int        tempcounter;
unsigned int        formalArgOffset, functionLocalOffset, programVarOffset, returnOffset;
unsigned int        scopespaceCounter;
struct expr         *elist_head, *elist_tail;
struct stack_pair   *indexed_stack, *indexed_stack2;
struct pair_expr    *pair_head, *pair_tail;
stmt_t              *stmtslist;

extern void yyerror(char *s);
extern int yylineno;



//-----------------------------

typedef enum SymbolType{
	GLOBAL, LOC, FORMAL, USERFUNC, LIBFUNC
} SymbolType;

typedef struct Variable {
	var_t						scope_space;
	const char 					*name;
	unsigned int 				scope;
	unsigned int 				line;
	unsigned int				ss_index;
	struct SymbolTableEntry 	*arg_next;
} Variable;


typedef struct Function {
	const char *name;
	unsigned int scope;
	unsigned int line;
	unsigned int iaddress;
    unsigned int taddress;
	unsigned int total_locals;
	struct SymbolTableEntry *arguments;
	struct SymbolTableEntry *arg_tail;
} Function;

typedef struct SymbolTableEntry {
	bool isActive;
	union {
		Variable *varVal;
		Function *funcVal;
	} value;
	enum SymbolType type;
	struct SymbolTableEntry *hash_next;
	struct SymbolTableEntry *scope_next;
	struct SymbolTableEntry *typel_next;
} SymbolTableEntry;

struct SymbolTableEntry *hash_table[SIZE];
struct SymbolTableEntry *scope_list[SCOPE_SIZE];
struct SymbolTableEntry *type_lists[5];
struct SymbolTableEntry *type_tails[5];
struct SymbolTableEntry *hash_tails[SIZE];
int depth;

//last created function
struct SymbolTableEntry *lcf;

struct SymbolTableEntry *lookup_entry(SymbolTableEntry *entry);

struct SymbolTableEntry *lookup(char *name);

struct SymbolTableEntry *lookup_v(char *name, unsigned int index);

struct SymbolTableEntry *lookup_f(char *name, unsigned int index);

struct SymbolTableEntry *lookup_scope(char *name, unsigned int scope);

struct SymbolTableEntry *  insert_variable(char *name, unsigned line, unsigned int scope, SymbolType e, var_t scopespace, unsigned int scopeoffset);

char *expr_tostring(expr *ex);

void print_table();

void print_scopes(FILE *yyout);

void print_node(SymbolTableEntry *e,FILE *yyout);

void print_arguments(char *name);

bool create();

struct SymbolTableEntry *create_entry_v(Variable *v, SymbolType type);

struct SymbolTableEntry *create_entry_f(Function *f, SymbolType type);

enum SymbolType get_type(char *type);

bool isAlive(char *name, unsigned int index);

void hide(unsigned int scope);

SymbolTableEntry *search_as_argument(char *name, unsigned int scope);

SymbolTableEntry *is_it_lcf_arg(SymbolTableEntry *last_cf,char* id);

SymbolTableEntry *update_lcf(SymbolTableEntry *current_function);




unsigned int nextquadlabel(void);

unsigned int nextquad(void);

void resetformalargsoffset(void);

void resetfunctionlocalsoffset(void);

void restorecurrscopeoffset(unsigned int n);

var_t currscopespace(void);

void enterscopespace(void);

void exitscopespace(void);

expr* newexpr_constnum(double i);

void resettemp(void);

void newtempname(char *name);

struct SymbolTableEntry *newtemp(unsigned int scope, SymbolType t, unsigned int line);

expr *lvalue_expr(SymbolTableEntry *sym);

expr *newexpr(expr_t t);

expr *newexpr_constbool(bool v);

expr *newexpr_constnum(double i);

expr *newexpr_conststring(char *s);

void check_arithm(expr* e);

void display_quads(FILE *yyout);

unsigned int currscopeoffset(void);

void allocate_quad(quad *q);

void print_expr(expr *e, FILE *yyout);

void patchlabel(unsigned int quadNo, unsigned label);

stack *getstack(void);

char *getscopespacename(SymbolTableEntry *e);

void updatecurrspaceoffset(void);

void make_stmt(stmt_t *s);

int newlist(int i);

int mergelist(int l1, int l2);

void patchlist(int list, int label);

void backpatch(tflist *list, int label);

void merge_tflists(tflist *list1, tflist *list2);

tflist *makelist(int quad);

void append_tflist(tflist *list, int quad);

void print_tflist(tflist *list);

void resetreturncounterstack();

void restorereturnoffset();

void displaypatchlist(int list);

void push_pair(stack_pair *s, struct pair_expr *it);

pair *pop_pair(stack_pair *s);