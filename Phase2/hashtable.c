
/*
        Apostolos Mavrogiannakis csd3799
        Varsamis Haralampos csd3744
        Georgia Rapousi csd3836
*/


#include "hashtable.h"
#include "lib.h"

unsigned int
hash(const char *key) {
	int length = strlen(key), i;
	unsigned int hash_value = 0;
	for(i = 0; i < length; i++) {
		hash_value += key[i];
		hash_value = (hash_value * key[i]) % SIZE;
	}

	return hash_value;
}

char *
get_type_name(SymbolType e) {
	switch(e) {
		case	GLOBAL:
			return "global variable";
		case	LOC:
			return "local variable";
		case 	FORMAL:
			return "formal argument";
		case 	USERFUNC:
			return "user function";
		case	LIBFUNC:
			return "library function";
		default:
			assert(0); /* NO MAN'S LAND */
			break;
	}
} 

enum SymbolType 
get_type(char *type) {
	enum SymbolType e;

	if(strcmp(type, "GLOBAL") == 0) e = GLOBAL;
	else if(strcmp(type,"LOC") == 0) e = LOC;
	else if(strcmp(type,"FORMAL") == 0) e = FORMAL;
	else if(strcmp(type,"USERFUNC") == 0) e = USERFUNC;
	else if(strcmp(type,"LIBFUNC") == 0)	e = LIBFUNC;
	else assert(0); // No man's land.

	return e;
}

struct SymbolTableEntry *
lookup_entry(SymbolTableEntry *entry) {
	int hash_index;
	const char *name;

	if( FUNC(entry) ) {
		hash_index = hash( entry -> value.funcVal -> name );
		name = entry -> value.funcVal -> name;
	}
	else {
		hash_index = hash( entry -> value.varVal -> name );
		name = entry -> value.varVal -> name;
	}

	struct SymbolTableEntry *it = hash_table[hash_index];

	if(it == NULL) return NULL;

	while(it != NULL) {
		if((it -> type == USERFUNC) || (it -> type == LIBFUNC)) {
			if(strcmp(it -> value.funcVal -> name, name) == 0) {
				return it;
			}
		} else {
			if(strcmp(it -> value.varVal -> name, name) == 0) {
				return it;
			}
		}

		it = it -> scope_next;
	}

	return NULL;
}

struct SymbolTableEntry *
lookup(char *name) {
	int hash_index = hash(name);
	struct SymbolTableEntry *it = hash_table[hash_index];

	if(it == NULL) return NULL;

	while (it != NULL) {
		
		if((it -> type == USERFUNC) || (it -> type == LIBFUNC)) {
			if(strcmp(it -> value.funcVal -> name, name) == 0 && it -> isActive == true) {
				return it;
			}
		} else {
			if(strcmp(it -> value.varVal -> name, name) == 0 && it -> isActive == true) {
				return it;
			}
		}

		it = it -> hash_next;
	}
	printf("\n");

	return NULL;
}

struct SymbolTableEntry *
lookup_scope(char *name,unsigned int scope) {
	struct SymbolTableEntry *it = scope_list[scope];

	if(it == NULL) return NULL;

	while (it != NULL) {

		if((it -> type == USERFUNC) || (it -> type == LIBFUNC)) {
			if(strcmp(it -> value.funcVal -> name, name) == 0 && it -> isActive == true) {
				return it;
			}
		} else {
			if(strcmp(it -> value.varVal -> name, name) == 0 && it -> isActive == true) {
				return it;
			}
		}

		it = it -> scope_next;
	}

	return NULL;
}

/*
	name: indicates variable's name.

	index: represents the value of SymbolType 
	E.x. if variable we are searching for is local, 
	index = LOC => (int value) 1 etc.

	valid types: GLOBAL,LOC,FORMAL.

*/
struct SymbolTableEntry *
lookup_v(char *name, unsigned int index) {

	/* Checking our list is not empty. */
	if( type_lists[index] == NULL) return NULL;

	struct SymbolTableEntry *prev, *curr;

	curr = prev = type_lists[index];

	while(curr != NULL) {
		if( strcmp(name, curr -> value.varVal -> name) == 0) return curr;

		prev = curr;
		curr = curr -> typel_next;
	}

	/* We didnt find such variable. */
	return NULL;
}

/*
	name: indicates function's name.
	
	index: represents the value of SymbolType 
	E.x. if function we are searching for is userfunc, 
	index = USERFUNC => (int value) 3 etc.

	valid types: USERFUNC,LIBFUNC.
*/
struct SymbolTableEntry *
lookup_f(char *name, unsigned int index) {
	if( type_lists[index] == NULL){
		return NULL;
	}
	struct SymbolTableEntry *prev, *curr;

	curr = prev = type_lists[index];

	while(curr != NULL) {
		if( strcmp(name, curr -> value.funcVal -> name) == 0){
			return curr;
		}

		prev = curr;
		curr = curr -> typel_next;
	}

	return NULL;
}

SymbolTableEntry * 
insert_variable(char *name, unsigned int line, unsigned int scope, SymbolType e) {
	SymbolTableEntry *entry = NULL;
	int hash_index = hash(name);
	if((e != USERFUNC) && (e != LIBFUNC)) {
		Variable *v = (Variable *) malloc(sizeof(Variable));
		v -> scope = scope;
		v -> name = name;
		v -> line = line;
		v -> arg_next = NULL;
		entry = create_entry_v(v, e);
	}
	else {
		//printf("Inserting function with name %s\n", name);
		Function *f = (Function *) malloc(sizeof(Function));
		f -> scope = scope;
		f -> name = name;
		f -> line = line;
		f -> arguments = NULL;
		f -> arg_tail = NULL;
		entry = create_entry_f(f, e);
	}


	// Insertion in hash table
	if(hash_table[hash_index] == NULL) {
		hash_table[hash_index] = entry;
		hash_tails[hash_index] = entry; 	 // make tail point to newly created node.
		entry -> hash_next = NULL;
	}
	else {

		hash_tails[hash_index] -> hash_next = entry;
		hash_tails[hash_index] =  entry;	 // make tail point to newly created node.
		entry -> hash_next = NULL;
	}

	// Insertion in scope list
	if(scope_list[scope] == NULL) {
		scope_list[scope] = entry;
	}
	else {
		struct SymbolTableEntry *it = scope_list[scope];

		while(it -> scope_next != NULL) {
			it = it -> scope_next;
		}

		it -> scope_next = entry;
	}

	if(type_lists[e] == NULL) {
		type_lists[e] = entry;
		type_tails[e] = entry;
		entry -> typel_next = NULL;
	} else {
		
		type_tails[e] -> typel_next = entry;
		type_tails[e] = entry;
		entry -> typel_next = NULL;
	}

	assert(entry != NULL); /* NO MAN'S LAND */
	return entry;
}

/*
	updates the pointer lcf<-last created function which
	holds data that are accessible when changing scope.

	Usage: It is used to handle the case of changing scope
	by opening brackets without mediating function declaration

	To implement this we have to iterate all the lower scopes
	and find the first function that is alive.
*/
SymbolTableEntry * 
update_lcf(SymbolTableEntry *current_function)
{
	SymbolTableEntry *it = type_lists[3];
	SymbolTableEntry *func = NULL;

	if(it == NULL) {
		return NULL;
	}

	while(it != NULL) {
		if(it == current_function){ 
			return func;
		}

		if(it -> isActive == true) {
			func = it;
		}
		it = it -> typel_next;
	}
	return func;
}

SymbolTableEntry *
is_it_lcf_arg(SymbolTableEntry *last_cf,char* id)
{
	SymbolTableEntry *args;
	if(last_cf == NULL)
		return NULL;
	args=last_cf->value.funcVal->arguments;

	while(args != NULL)
	{
		if(strcmp(args->value.varVal ->name,id)==0 && args->isActive == 1)
		{
			return args;
		}
		args=args->value.varVal->arg_next;
	}

	return NULL;

}


/*
	scope: indicates current scope, we should hide all *variables*,
	except *global* variables.

	To implement this, we iterate all variable lists (LOCAL,FORMAL)
	and check which of these variables' scope are less than current scope.
*/
void 
hide(unsigned int scope){
	if(scope == 0) return;

	SymbolTableEntry *curr = scope_list[scope];

	while(curr != NULL) {		
		curr -> isActive = false;

		curr = curr -> scope_next;
	}

	return;
}

SymbolTableEntry *
search_as_argument(char *name, unsigned int scope) {
	SymbolTableEntry *e, *it;

	it = scope_list[scope];

	if(it == NULL) return NULL;

	while(it != NULL) {
		if( FUNC(it) && it -> isActive == true ) {
			e = it -> value.funcVal -> arguments;
			while( e != NULL ) {
				if(strcmp(e -> value.varVal -> name, name) == 0) return e;
				e = e ->value.varVal->arg_next;
			}
		}

		it = it -> scope_next;
	}
}
/*
SymbolTableEntry *
search_as_argument(char *name, unsigned int scope) {
	SymbolTableEntry *e, *it;

	it = type_lists[FORMAL];

	if (it == NULL) return NULL;

	while (it != NULL) {
		if (it->isActive == true && strcmp(name, it->value.varVal->name) == 0)
			return it;

		it = it->typel_next;
	}
}
*/
SymbolTableEntry *
create_entry_v(Variable * v, SymbolType type) {
	SymbolTableEntry *entry = (SymbolTableEntry *) malloc(sizeof(SymbolTableEntry) * 1);

	entry -> isActive = true;
	entry -> type = type;
	entry -> value.varVal = v;
	entry -> hash_next = NULL;
	entry -> scope_next = NULL;

	return entry;
}

SymbolTableEntry *
create_entry_f(Function *f, SymbolType type) {
	SymbolTableEntry *entry = (SymbolTableEntry *) malloc(sizeof(SymbolTableEntry) * 1);

	entry -> isActive = true;
	entry -> type = type;
	entry -> value.funcVal = f;
	entry -> hash_next = NULL;
	entry -> scope_next = NULL;

	return entry;
}

bool 
create() {
	int i;

	// Initializing hash table
	for(i = 0; i < SIZE; i++) {
		hash_table[i] = NULL;
		hash_tails[i] = NULL;
	}

	// Initializing scope list
	for(i = 0; i < SCOPE_SIZE; i++) {
		scope_list[i] = NULL;
	}

	for(i = GLOBAL; i <= LIBFUNC; i++) {
		type_lists[i] = NULL;
		type_tails[i] = NULL;
	}


	return true;
}



void 
print_table() {
	int i;
	SymbolTableEntry *it;

	for(i = 0; i < SIZE; i++) {
		it = hash_table[i];


		printf("[%d] ->\t", i);
		if(hash_table[i] == NULL) {
			printf("---");
		}else {
			while(it != NULL) {
				if((it -> type == USERFUNC) || (it -> type == LIBFUNC)) {
					printf("%s -> ",it -> value.funcVal-> name);
				} else {
					printf("%s -> ",it -> value.varVal-> name);
				}

				it = it->hash_next;
			}			
		}

		printf("\n");
	}
}



void 
print_scopes(FILE *yyout) {
	int i;
	SymbolTableEntry *it;
	
	for(i = 0; i <= depth; i++) {
		it = scope_list[i];

		fprintf(yyout,"\t---SCOPES[%d]---\n", i);
		if(scope_list[i] == NULL) {
			fprintf(yyout,"---");
		}
		else {
			while(it != NULL) {
				if((it -> type == USERFUNC) || (it -> type == LIBFUNC)) {
					print_node(it, yyout);
				} else {
					print_node(it, yyout);
				}

				it = it -> scope_next;
			}
		}

		fprintf(yyout,"\n");
	}
}

void 
print_node(SymbolTableEntry *e,FILE *yyout) {
	const char *name = get_type_name(e -> type);

	if(e -> type == LIBFUNC || e -> type == USERFUNC) {
		fprintf(yyout,"\"%s\" ", e->value . funcVal -> name);
		fprintf(yyout,"[%s] ", name);
		fprintf(yyout,"(%d line) ",e->value .funcVal -> line);
		fprintf(yyout,"(%d scope)\n",e->value . funcVal -> scope);
		
	}
	else {
		fprintf(yyout,"\"%s\" ", e->value . varVal -> name);
		fprintf(yyout,"[%s] ", name);
		fprintf(yyout,"(%d line) ",e->value .varVal -> line);
		fprintf(yyout,"(%d scope)\n",e->value . varVal -> scope);
	}
}

/* name: indicates function's name */
void 
print_arguments(char *name) {
	SymbolTableEntry *fun = lookup_f(name, USERFUNC);
	SymbolTableEntry *curr = fun -> value.funcVal -> arguments;
	int counter = 0;

	printf("Function\t:%s\n", name);
	if(curr == NULL){
		printf("No arguments found for this function.\n");
		return;	
	}
	while(curr != NULL) {
		printf("arg[%d]:%s\n", counter++, curr -> value.varVal -> name);

		curr = curr -> value.varVal -> arg_next;
	}
}

bool 
isAlive(char *name, unsigned int index) {
	SymbolTableEntry *e;

	if(index == 3 || index == 4) {
		e = lookup_f(name, index);
	}
	else {
		e = lookup_v(name, index);
	}

	assert(e != NULL); /* NO MAN'S LAND. */

	return e -> isActive;
}

bool 
set_isAlive(char *name, unsigned int index, bool value) {
	SymbolTableEntry *e = lookup(name);
	unsigned int scope;

	if(index == 3 || index == 4) {
		if(e -> value.funcVal -> scope == 0) return false;
	}
	else {
		if(e -> value.varVal -> scope == 0) return false;
	}

	if(e == NULL) return false;

	e -> isActive = value;

	return true;
}
