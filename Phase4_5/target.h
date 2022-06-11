#ifndef TARGET_H_
#define TARGET_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"
#include <assert.h>
#include <unistd.h>

#define TEXPAND_SIZE 2048
#define TCURR_SIZE   (total*sizeof(instruction))
#define TNEW_SIZE    (EXPAND_SIZE*sizeof(instruction)+CURR_SIZE)
#define CONSTS_SIZE 4096

unsigned total;

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

void incurrprocessedquad();
void add_incomplete_jump(unsigned instrNo, unsigned iaddress);
void make_operand(struct expr *e, struct vmarg *arg);
void make_numberoperand (struct vmarg *arg, double val);
void make_booloperand(struct vmarg *arg, unsigned val);
void make_retvaloperand(struct vmarg *argm);
void generate(vmopcode op, quad *q);
void generate_u(vmopcode op, quad *q);
int nextinstructionlabel();
void temit(instruction t);
void expand_instr(void);
void reset_operand(struct vmarg *a);
void display_instruction(FILE *yyout);
void patch_incomplete_jumps();
void print_retlist(struct returnList *rl);
void print_funcstack(struct userfunc *s);
void backpatch_ret(returnList *list, int label);

extern void generate_ADD (struct  quad *quad);
extern void generate_AND (struct quad *quad);
extern void generate_UMINUS (struct quad *quad);
extern void generate_SUB (struct quad *quad);
extern void generate_MUL (struct quad *quad);
extern void generate_DIV (struct quad *quad);
extern void generate_MOD (struct quad *quad);
extern void generate_NEWTABLE (struct quad *quad);
extern void generate_TABLEGETELEM (struct quad *quad);
extern void generate_TABLESETELEM (struct quad *quad);
extern void generate_ASSIGN (struct quad *quad);
extern void generate_NOP (struct quad *quad);
extern void generate_JUMP (struct quad *quad);
extern void generate_IF_EQ (struct quad *quad);
extern void generate_IF_NOTEQ (struct quad *quad);
extern void generate_IF_GREATER (struct quad *quad);
extern void generate_IF_GREATEREQ (struct quad *quad);
extern void generate_IF_LESS (struct quad *quad);
extern void generate_IF_LESSEQ (struct quad *quad);
extern void generate_NOT (struct quad *quad);
extern void generate_OR (struct quad *quad);
extern void generate_PARAM (struct quad *quad);
extern void generate_CALL (struct quad *quad);
extern void generate_GETRETVAL (struct quad *quad);
extern void generate_FUNCSTART (struct quad *quad);
extern void generate_RETURN (struct quad *quad);
extern void generate_FUNCEND (struct quad *quad);

typedef void (*generator_func_t)(struct quad *quad);

extern generator_func_t generators[];

void print_vmarg(vmarg arg, FILE *yyout);
void display_instructions(FILE *yyout);

void write_magicnumber();
void write_arrays();
void write_strings(FILE* fp);
void write_numbers(FILE *fp);
void write_user_functions(FILE *fp);
void write_lib_functions(FILE *fp);
void write_code();
void write_instructions(FILE *fp);
void write_operands(FILE *fp,int i,unsigned opc_type);
void write_avmbinaryfile();

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

#endif

