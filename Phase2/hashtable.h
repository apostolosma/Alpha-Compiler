
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


#define FUNC(c) 	((c->type == LIBFUNC ) || (c->type == USERFUNC) ? true : false)
#define SIZE 256 // size of hash table
#define SCOPE_SIZE 20 // Initial size of scope_size's indexes

typedef enum SymbolType {
	GLOBAL, LOC, FORMAL, USERFUNC, LIBFUNC
}SymbolType;

typedef struct Variable {
	const char *name;
	unsigned int scope;
	unsigned int line;
	struct SymbolTableEntry *arg_next;
} Variable;


typedef struct Function {
	const char *name;
	unsigned int scope;
	unsigned int line;
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

struct SymbolTableEntry *  insert_variable(char *name, unsigned line, unsigned int scope, SymbolType e);

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
