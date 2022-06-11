
#ifndef AVM_H_
#define AVM_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"
#include <assert.h>
#include <unistd.h>
#include <math.h>

#define TEXPAND_SIZE 1024
#define TCURR_SIZE   (total*sizeof(instruction))
#define TNEW_SIZE    (EXPAND_SIZE*sizeof(instruction)+CURR_SIZE)
#define CONSTS_SIZE 4096

#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define AVM_TABLE_HASHSIZE 512
#define PI 3.141592654


unsigned max_index_global;
unsigned global_counter;
unsigned total;
extern int lines;
extern char *yytext;
extern FILE* yyin;
extern FILE* yyout;
extern int yylineno;

enum avm_memcell_t {
    number_m = 0,
    string_m,
    bool_m,
    table_m,
    userfunc_m,
    libfunc_m,
    nil_m,
    undef_m
}avm_memcell_t;



typedef enum vmopcode {
    assign_v = 0,       add_v,          sub_v,
    mul_v,          div_v,          mod_v,
    uminums_v,      and_v,          or_v,
    not_v,          jump_v,          jeq_v,          jne_v,
    jle_v,          jge_v,          jlt_v,
    jgt_v,          call_v,         pusharg_v, 
    funcenter_v,    funcexit_v,     newtable_v,
    tablegetelem_v, tablesetelem_v, nop_v
}vmopcode;

typedef enum vmarg_t {
    label_a =0,
    global_a,
    formal_a,
    local_a,
    number_a,
    string_a,
    bool_a,
    nil_a,
    userfunc_a,
    libfunc_a,
    retval_a
}vmarg_t;

typedef struct vmarg {
    enum vmarg_t type;
    unsigned val;
}vmarg;


typedef struct instruction {
    enum vmopcode opcode;
    struct vmarg result;
    struct vmarg arg1;
    struct vmarg arg2;
    unsigned srcLine;
}instruction;

typedef struct incomplete_jump {
    unsigned        instrNo;
    unsigned        iaddress;
    struct incomplete_jump *next;
}incomplete_jump;

typedef struct returnList {
    int label;
    struct returnList *next;
}returnList;


typedef struct userfunc {
    unsigned address;
    unsigned localSize;
    const char     *id;
    struct returnList *returnList;
    struct userfunc *next;
}userfunc;

struct userfunc *userFuncs;

void push_func(struct userfunc *new_func);

void append_return(struct userfunc *f, int instruction);
struct userfunc *pop_func(struct userfunc *s);

struct incomplete_jump *ij_head;
unsigned        ij_total; 
unsigned        totalActuals;
unsigned        currprocquad ;
instruction     *instructions;
unsigned    avm_hash_str(const char *key);
unsigned magic_number;
unsigned consts_newstring( char *s);
unsigned consts_newnumber(double n);
unsigned libfuncs_newused(const char *s);
unsigned userfuncs_newfunc( struct SymbolTableEntry *sym);
unsigned int currInstr;
unsigned userfunc_index ;
unsigned clibs_index ;
unsigned cnumbers_index ;
unsigned cstring_index;
struct userfunc consts_userfunc[CONSTS_SIZE];
const char *consts_libfuncs[CONSTS_SIZE];
double  consts_numbers[CONSTS_SIZE];
char *consts_strings[CONSTS_SIZE];
void display_instructions(FILE *yyout);
void print_vmarg(vmarg arg, FILE *yyout);

void load_magicnumber(FILE *fp);
void load_arrays(FILE *fp);
void load_strings(FILE *fp);
void load_numbers(FILE *fp);
void load_user_functions(FILE *fp);
void load_lib_functions(FILE *fp);
void load_code(FILE *fp);
unsigned get_opc_type(unsigned char opcode);
void load_instructions(FILE *fp,unsigned total);
instruction* load_operands(FILE *fp,unsigned opc_type);
void load_avmbinaryfile();

extern struct avm_table;

typedef struct avm_memcell {
    enum avm_memcell_t type;
    union {
        double              numVal;
        char                *strVal;
        unsigned char       boolVal;
        struct avm_table    *tableVal;
        unsigned            funcVal;
        char                *libfuncVal;
    } data;
}avm_memcell;

typedef struct avm_table_bucket {
    struct avm_memcell         key;
    struct avm_memcell         value;
    struct avm_table_bucket    *next;
}avm_table_bucket;

typedef struct avm_table {
    unsigned          refCounter;
    struct avm_table_bucket  *strIndexed[AVM_TABLE_HASHSIZE];
    struct avm_table_bucket  *numIndexed[AVM_TABLE_HASHSIZE];
    unsigned          total;   
}avm_table;





struct avm_memcell avm_stack[AVM_STACKSIZE];
void functor_call(vmarg func,avm_memcell *value);

avm_memcell            *avm_tablegetelement(avm_table *t,const char *el);
struct avm_table       *avm_tablenew (void);
void            avm_tabledestroy (struct avm_table *t);
struct avm_memcell     *avm_tablegetelem (struct avm_table *t, struct avm_memcell *key);
void            avm_tablesetelem   (struct avm_table *t, struct avm_memcell *key, struct avm_memcell *value);
void            avm_tableincrefcounter  (struct avm_table *t);
void            avm_tabledecrefcounter  (struct avm_table *t);
void            avm_tablebucketsinit    (struct avm_table_bucket **p);
void            avm_memcellclear    (struct avm_memcell *m);
void            avm_tablebucketsdestroy (struct avm_table_bucket **p);
static void avm_initstack(void);


#define AVM_STACKENV_SIZE 4
#define AVM_MAX_INSTRUCTIONS (unsigned) nop_v
#define AVM_NUMACTUALS_OFFSET 4
#define AVM_SAVEDPC_OFFSET 3
#define AVM_SAVEDTOP_OFFSET 2
#define AVM_SAVEDTOPSP_OFFSET 1
#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

unsigned executionFinished;
unsigned pc,currLine,codeSize;
#define AVM_ENDING_PC codeSize

typedef void (*execute_func_t) (instruction *);
typedef void (*memclear_func_t) (avm_memcell *);
typedef void (*library_func_t) (void);
typedef char *(*tostring_func_t) (avm_memcell *);
typedef double (*arithmetic_func_t) (double x, double y);

extern library_func_t libraryFuncs[];
extern char *libStrings[];

library_func_t avm_getlibraryfunc (char *id);

extern userfunc *avm_getfuncinfo (unsigned address);


extern arithmetic_func_t arithmeticFuncs[];

extern char *number_tostring (avm_memcell *);
extern char *string_tostring(avm_memcell *);
extern char *bool_tostring (avm_memcell *);
extern char *table_tostring (avm_memcell *);
extern char *userfunc_tostring(avm_memcell *);
extern char *libfunc_tostring(avm_memcell *);
extern char *nil_tostring(avm_memcell *);
extern char *undef_tostring(avm_memcell *);
extern char *int_tostring(avm_memcell *);
extern char *float_tostring(avm_memcell *);

void check_for_globals(vmarg v);
extern tostring_func_t tostringFuncs[];
unsigned char avm_tobool (avm_memcell *m);
unsigned    avm_get_envvalue (unsigned i);
void        avm_calllibfunc(char *id);
void        libfunc_print (void);
void        avm_registerlibfunc (char *id, library_func_t addr);
unsigned    avm_totalactuals (void);
avm_memcell *avm_getactual (unsigned i);
void        avm_dec_top(void);
void        avm_push_envvalue(unsigned val);
void        avm_callsaveenvironment(void);
extern void avm_error(char *format);
extern char *avm_tostring(avm_memcell *);
extern void avm_calllibfunc(char *funcname);
extern void avm_callsaveenvironment (void);
extern void memclear_string (avm_memcell *m);
extern void memclear_table (avm_memcell *m);
extern void memclear_table (avm_memcell *m);
void        avm_memcellclear (avm_memcell *m);
bool        avm_tablebucketdestroy (avm_table *t, avm_memcell *key);
extern void execute_assign (instruction *);
extern void execute_add    (instruction *);
extern void execute_sub    (instruction *);
extern void execute_mul    (instruction *);
extern void execute_div    (instruction *);
extern void execute_mod    (instruction *);
extern void execute_uminus (instruction *);
extern void execute_and    (instruction *);
extern void execute_or     (instruction *);
extern void execute_not    (instruction *);
extern void execute_jeq    (instruction *);
extern void execute_jne    (instruction *);
extern void execute_jle    (instruction *);
extern void execute_jge    (instruction *);
extern void execute_jlt    (instruction *);
extern void execute_jgt    (instruction *);
extern void execute_call   (instruction *);
extern void execute_pusharg (instruction *);
extern void execute_funcenter (instruction *) ;
extern void execute_funcexit  (instruction *);
extern void execute_newtable  (instruction *);
extern void execute_tablegetelem (instruction *);
extern void execute_tablesetelem (instruction *);
extern void execute_nop         (instruction *);

extern memclear_func_t memclearFuncs[];

extern execute_func_t executeFuncs[];
void avm_assign (avm_memcell *lv, avm_memcell *rv);

avm_memcell ax,bx,cx; //AUXILIARY REGISTERS
avm_memcell retval;
unsigned top, topsp;

double consts_getnumber (unsigned index);
char *consts_getstring (unsigned index);
char *libfuncs_getused (unsigned index);


void execute_cycle(void);
avm_memcell *avm_translate_operand (vmarg *arg, avm_memcell *reg);

void temit (instruction *t);

typedef unsigned char (*tobool_func_t)(avm_memcell *);
extern tobool_func_t toboolFuncs[];
extern char* typeStrings[]; 
typedef bool (*compare_type_t)(avm_memcell *,avm_memcell *);
extern compare_type_t compareinstrFuncs[];
typedef bool (*less_type_t)(avm_memcell *,avm_memcell *);
extern less_type_t lessinstrFuncs[];

void avm_warning(char *warning);
void avm_error(char *error);

#endif

