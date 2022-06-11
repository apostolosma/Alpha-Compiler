
/*
        Apostolos Mavrogiannakis csd3799
        Varsamis Haralampos csd3744
        Georgia Rapousi csd3836
*/


#include "hashtable.h"
#include "lib.h"
#include <string.h>

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
insert_variable(char *name, unsigned int line, unsigned int scope, SymbolType e, var_t scopespace, unsigned int scopeoffset) {
	SymbolTableEntry *entry = NULL;
	int hash_index = hash(name);
	if((e != USERFUNC) && (e != LIBFUNC)) {
		Variable *v = (Variable *) malloc(sizeof(Variable));
		v -> scope = scope;
		v -> name = name;
		v -> line = line;
		v -> arg_next = NULL;
		v -> ss_index = scopeoffset;
		v -> scope_space = scopespace;
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
		f -> total_locals = 0;
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
		fprintf(yyout,"(%d scope)",e->value . funcVal -> scope);
		fprintf(yyout,"(#%d of local variables)\n", e -> value.funcVal -> total_locals);
	}
	else {
		fprintf(yyout,"\"%s\" ", e->value . varVal -> name);
		fprintf(yyout,"[%s] ", name);
		fprintf(yyout,"(%d line) ",e->value .varVal -> line);
		fprintf(yyout,"(%d scope)",e->value . varVal -> scope);
		fprintf(yyout,"(%s scope space)", getscopespacename(e));
		fprintf(yyout,"(%d scope space offset)\n", e -> value.varVal -> ss_index);
	}
}

char *
getscopespacename(SymbolTableEntry *e) {
	switch(e ->value.varVal -> scope_space) {
		case program_v:		return "program_variables";
		case function_l:	return "function_locals";
		case formal_arg:	return "formal_arguments";
		default:			exit(0);
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

	if(e == NULL) return false;

	if(index == 3 || index == 4) {
		if(e -> value.funcVal -> scope == 0) return false;
	}
	else {
		if(e -> value.varVal -> scope == 0) return false;
	}

	

	e -> isActive = value;

	return true;
}

// ------------------------------

expr *
lvalue_expr (SymbolTableEntry *sym) {
	if(sym == NULL) return NULL;
	expr *e = (expr *) malloc(sizeof(expr));
	memset(e, 0, sizeof(expr));

	e -> next = (expr *)0;
	e -> sym = sym;
	switch (sym -> type) {
		case USERFUNC:	e->type = programfunc_e; break;
		case LIBFUNC :	e->type = libraryfunc_e; break;
		case GLOBAL	 :	e->type = var_e; break;
		case FORMAL	 :	e->type = var_e; break;
		case LOC	 :	e->type = var_e; break;
		default		 :	assert(0);break;
	}

	return e;
}

void
newtempname(char *name) {
	sprintf(name, "_t%d", tempcounter);
	tempcounter++;
}

void
resettemp(void) {
	tempcounter = 0;
}



struct SymbolTableEntry *
newtemp(unsigned int scope, SymbolType t, unsigned int line) {
	char *name = (char *) malloc(sizeof(char)*10);
	newtempname(name);
	struct SymbolTableEntry *e = lookup_scope(name, scope);
	if(e == NULL) {
		e = insert_variable(name, line, scope, t, currscopespace(), currscopeoffset());
		updatecurrspaceoffset();
	}

	return e;

}

void
resetformalargsoffset(void){
	formalArgOffset = 0;
}


void
resetfunctionlocalsoffset(void){
	functionLocalOffset = 0;
}

stack *
getstack(void) {
		if(scopespaceCounter == 1) 				return prog_vars;
		else if(scopespaceCounter % 2 == 0) 	return form_args;
		else									return func_locs;
}

var_t
currscopespace(void) {
	if(scopespaceCounter == 1) 			return program_v;
	else if(scopespaceCounter % 2 == 0) return formal_arg;
	else								return function_l;
}

void 
enterscopespace(void) {
	++scopespaceCounter;
}

void 
exitscopespace(void) {
	assert(scopespaceCounter > 1); --scopespaceCounter;
}

unsigned int
currscopeoffset(void) {
	switch(currscopespace()) {
		case	program_v:	return programVarOffset;
		case	formal_arg:	return formalArgOffset;
		case	function_l:	return functionLocalOffset;
		default			  : assert(0);
	}
}

void updatecurrspaceoffset(void) {
	switch(currscopespace()) {
		case	program_v:	programVarOffset++;break;
		case	formal_arg:	formalArgOffset++;break;
		case	function_l:	functionLocalOffset++;break;
		default			  : assert(0);
	}
}

void
restorecurrscopeoffset(unsigned n) {
	switch(currscopespace()) {
		case 	program_v:	programVarOffset = n; break;
		case	formal_arg:	functionLocalOffset = n; break;
		case	function_l:	formalArgOffset = n; break;
		default:	assert(0);
	}
}

unsigned int
nextquadlabel(void) {
	return currQuad;
}

unsigned int
nextquad(void) {
	return currQuad;
}

void
patchlabel(unsigned int quadNo, unsigned label) {
	assert(quadNo < currQuad);
	(quads + quadNo) -> label = label;
}

void expand(void) {
	assert(total == currQuad);
	quad* p = (quad*) malloc(NEW_SIZE);
	if(quads) {
		memcpy(p, quads, CURR_SIZE);
		free(quads);
	}
	quads = p;
	total += EXPAND_SIZE;
}

void 
emit	(
			iopcode 	op,
			expr*		arg1,
			expr*		arg2,
			expr*		result,
			unsigned	label,
			unsigned 	line
		) {
		
			if(currQuad == total) {
				expand();
			}

			quad 	*p	= quads+currQuad;
			p -> op		= op;
			p -> arg1	= arg1;
			p -> arg2	= arg2;
			p -> result = result;
			p -> label 	= label;
			p -> line	= line;
			currQuad++;
}	

void
allocate_quad(quad *q) {
	q -> op = (iopcode)malloc(sizeof(iopcode));
	q -> result = (expr *) malloc(sizeof(expr));
	q -> arg1 = (expr *) malloc(sizeof(expr));
	q -> arg2 = (expr *) malloc(sizeof(expr));
}

expr *
newexpr(expr_t t) {
	expr *e= (expr *)malloc(sizeof(expr));
	memset(e, 0, sizeof(expr));

	e -> truelist = e -> falselist = NULL;
	e -> type = t;
	e -> sym = (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
	return e;
}

expr *
newexpr_constbool(bool v) {
	expr *e = newexpr(constbool_e);
	e -> boolConst = v;

	return e;
}

expr *
newexpr_constnum(double i) {
	expr* e = newexpr(constint_e);
	e -> intConst = i;

	return e;
}

expr *
newexpr_conststring(char *s) {
	expr *e = newexpr(conststring_e);
	e -> strConst = strdup(s);
	
	return e;
}


unsigned int
istempname(const char* s) {
	return s[0] == '_';
}

unsigned int
istempexpr(expr* e) {
	if(FUNC(e -> sym)) {
		return e -> sym && istempname(e->sym-> value.funcVal -> name);
	}
	return e -> sym && istempname(e->sym->value.varVal ->name);
}

void 
check_arithm(expr *e) {
	char s[50];
	if(
		e -> type == constbool_e 	||
		e -> type == nil_e		 	||
		e -> type == newtable_e		||
		e -> type == boolexpr_e
	)	{
		sprintf(s,"Illegal expr used in %s!",e -> sym -> value.varVal -> name);
		yyerror(s);
	}
	if(
		e -> type == programfunc_e	||
		e -> type == libraryfunc_e 	
	) {
		sprintf(s,"Illegal expr used in %s!",e -> sym -> value.funcVal -> name);
		yyerror(s);
	}
}

char *
get_opcode(expr_t t) {
	switch(t) {
		case assign: return "assign";
		case add: return "add";
		case sub: return "sub";
		case mul: return "mul";
		case divis: return "divis";
		case mod: return "mod";
		case uminus: return "uminus";
		case and: return "and";
		case or: return "or";
		case not: return "not";
		case if_eq: return "if_eq";
		case if_noteq: return "if_noteq";
		case if_lesseq: return "if_lesseq";
		case if_greatereq: return "if_greatereq";
		case if_less: return "if_less";
		case if_greater: return "if_greater";
		case call: return "call";
		case param: return "param";
		case ret: return "ret";
		case getretval: return "getretval";
		case funcstart: return "funcstart";
		case funcend: return "funcend";
		case tablecreate: return "tablecreate";
		case tablegetelem: return "tablegetelem";
		case tablesetelem: return "tablesetelem";
		case jump: return "jump";
	}
}

void
display_quads(FILE *yyout) {
	char *op;
	const char *result;
	const char *arg1;
	const char *arg2;
	unsigned    label;
    unsigned    line;
	int i;
	
	fprintf(yyout,"\t\t\t\t\t\t---QUADS---\n");
	fprintf(yyout,"   quad#\t\topcode\t\t\tresult\t\targ1\t\targ2\t\tlabel\t\tline\n");
	fprintf(yyout,"------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	
	
    for(i = 0; i < currQuad; i++) {
			// fprintf(yyout,"%d\n",currQuad);
			op = get_opcode((quads+i) -> op);
			fprintf(yyout,"%8d\t\t%10s", i+1,op);
			print_expr((quads+i) -> result, yyout);
			print_expr((quads+i) -> arg1, yyout);
			print_expr((quads+i) -> arg2, yyout);
			label = (quads + i) ->label;
			line = (quads + i) ->line;
			if(label  || !strcmp(op,"jump")) fprintf(yyout,"\t\t%4d", label+1);
			else	fprintf(yyout,"\t\t%4s", "");
			fprintf(yyout,"\t\t%d\n", (quads + i) -> line);
	} 
}

void
print_expr(expr *e, FILE *yyout) {
	if(e == NULL) {
		fprintf(yyout, "\t\t%6s", "");
		return;
	}

	switch(e -> type) {
		case var_e:
				if(e -> sym) {
					fprintf(yyout, "\t\t%3s", e -> sym -> value.varVal -> name);
				}
				break;
		case programfunc_e:
				if(e -> sym) {
					fprintf(yyout, "\t\t%3s", e -> sym -> value.funcVal -> name);
				}
				break;
		case libraryfunc_e:
				fprintf(yyout, "\t\t%3s", e -> sym -> value.funcVal -> name);
				break;
		case tableitem_e:
				if(e -> sym) {
					fprintf(yyout, "\t\t%3s", e -> sym -> value.varVal -> name);
				}
				break;
		case arithexpr_e:
				if(e -> sym) {
					fprintf(yyout,"\t\t%3s", e -> sym -> value.varVal -> name);
				}
				break;
		case boolexpr_e:
				if(e -> sym) {
					fprintf(yyout,"\t\t%3s", e -> sym -> value.varVal -> name);
				}
				break;
		case assignexpr_e:
				if(e -> sym) {
					if(FUNC(e->sym)) fprintf(yyout,"\t\t%3s", e -> sym -> value.funcVal -> name);
					else fprintf(yyout,"\t\t%3s", e -> sym -> value.varVal -> name);
				}
				break;
		case newtable_e:
				if(e -> sym) {
					fprintf(yyout,"\t\t%3s", e -> sym -> value.varVal -> name);
				}
				break;
		case constreal_e:
				
				fprintf(yyout,"\t\t%3.02f", e -> realConst);
				break;
		case constint_e:
				fprintf(yyout,"\t\t%3d", e -> intConst);
				break;
		case constbool_e:
				if(e -> boolConst) {
					fprintf(yyout,"\t\t%3s", "true");
				} else {
					fprintf(yyout,"\t\t%3s", "false");
				}
				break;
		case conststring_e:
				fprintf(yyout,"\t\t%s\"%s\"","", e -> strConst);
				break;
		case nil_e:
				fprintf(yyout,"\t\t%3s", "nil");
				break;
	}
}

void 
make_stmt(stmt_t *s) {
	s = (stmt_t *) malloc(sizeof(stmt_t));
	s -> breaklist =  0;
	s -> contlist = 0;
}

int
newlist(int i) {
	(quads+i) -> label = 0; return i;
}

int
mergelist(int l1, int l2) {
	if(!l1) {

		return l2;
		}
	else if(!l2) {

		return l1;
	 }
	else {
		
		
		int i = l1;
		
		while((quads+i) -> label) i = (quads + i) -> label;
		(quads + i) -> label = l2;
		
		return l1;
	}
}

void displaypatchlist(int list) {
	while(list) {
		int next = (quads + list) -> label;
		list = next;
	}
}

void
patchlist(int list, int label) {
	while(list) {
		int next = (quads + list) -> label;
		(quads + list) -> label = label;
		list = next;
	}
}

void
backpatch(tflist *list, int label) {
	while(list != NULL) {
		if((quads + list->quad_offset) -> label == 0) {
			(quads + list->quad_offset) -> label = label;
		}

		list = list->next;
	}
	printf("\n");
}

tflist * 
merge_tflists(tflist *list1, tflist *list2) {
	if(list1 == NULL && list2 == NULL) return NULL;

	if(list1 == NULL) return list2;

	if(list2 == NULL) return list1;

	while(list1->next != NULL) {
		list1 = list1->next;
	} 

	list1 ->next = list2;

	return list1;
}

tflist *
makelist(int quad) {
	tflist *list = (tflist *)malloc(sizeof(tflist));

	list ->quad_offset = quad;
	list -> next = NULL;

	return list;
}

void
append_tflist(tflist *list, int quad) {
	

	while(list -> next != NULL)	{

		list = list -> next;
	}

	tflist *tf = (tflist *)malloc(sizeof(tflist));
	tf -> next = NULL;
	tf -> quad_offset = quad;

	list -> next = tf;
}

void
print_tflist(struct tflist *list) {
	if(list == NULL) {
		printf("tflist is empty\n");
		return;
	}
	while(list != NULL) {
		printf("%d -> ", list -> quad_offset);

		list = list -> next;
	}

	printf("\n");
}

void resetreturnoffset() {
	returnOffset = 0;
}

void restorereturnoffset() {
	item *it = pop(returncounterstack);

	if(it != NULL) 
		returnOffset = it -> item;

	returnOffset = 0;
}
