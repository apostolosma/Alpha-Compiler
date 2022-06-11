/*
	Apostolos Mavrogiannakis csd3799
	Varsamis Haralampos csd3744
	Georgia Rapousi csd3836
*/
%{

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
SymbolTableEntry * manage_term(SymbolTableEntry *entry);
SymbolTableEntry * manage_lvalue(struct alpha_token_t *token,short type);
void update_scope();
SymbolTableEntry * noname_function ( );
SymbolTableEntry * manage_function ( struct alpha_token_t *token );
SymbolTableEntry * handle_insertion ( char *name, unsigned int line, char *type );
int yylex();
void yyerror(char *s);
void manage_if();
bool check_for_loop();
SymbolTableEntry * manage_return(SymbolTableEntry *entry);
void write_rule(char* rule);
void manage_assign();
void manage_idlist(struct alpha_token_t *token);
SymbolTableEntry * manage_call(struct alpha_token_t *token);
SymbolTableEntry * manage_id(struct alpha_token_t *token);
SymbolTableEntry * manage_global_id(struct alpha_token_t *token);
SymbolTableEntry * manage_local_id(struct alpha_token_t *token);
SymbolTableEntry * check_lvalue_assex(struct alpha_token_t *token);
SymbolTableEntry * check_activity(SymbolTableEntry *entry);
SymbolTableEntry * check_type(SymbolTableEntry *entry);
struct alpha_token_t *manage_member(SymbolTableEntry *entry);

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

char err[90];
%}

%union {
	struct alpha_token_t *token;
	struct SymbolTableEntry *entry;
}

%start program

%token <token> IF
%token <token> ELSE
%token <token> STRIN
%token <token> WHILE 
%token <token> FOR
%token <token> FUNCTION 
%token <token> RETURN
%token <token> BREAK
%token <token> CONTINUE
%token <token> AND
%token <token> NOT
%token <token> OR
%token <token> LOCAL
%token <token> TRUE
%token <token> FALSE
%token <token> NIL
%token <token> INT
%token <token> REAL
%token <token> EQUAL
%token <token> PLUS
%token <token> MINUS
%token <token> MUL
%token <token> DIV
%token <token> MOD
%token <token> DE
%token <token> UNEQUAL
%token <token> UPLUS
%token <token> UMINUS
%token <token> DPLUS
%token <token> DMINUS
%token <token> GT
%token <token> LT
%token <token> GE
%token <token> LE
%token <token> LCURBRA
%token <token> RCURBRA
%token <token> LBRA
%token <token> RBRA
%token <token> LPAREN
%token <token> RPAREN
%token <token> SEMICOLON
%token <token> COMMA
%token <token> COLON
%token <token> DCOLON
%token <token> DOT
%token <token> DDOT
%token <token> ID

%token EXIT_COMMAND

%type <token> lvalue
%type <token> member
%type <entry> call
%type <entry> funcdef
%type <entry> expr
%type <entry> term
%type <entry> primary
%type <entry> assignexpr
%type <entry> methodcall
%type <entry> elist
%type <entry> elist2
%type <entry> stmt
%type <entry> returnstmt


%left EQUAL
%left OR
%left AND
%nonassoc UNEQUAL DE
%nonassoc GT GE LT LE
%left PLUS MINUS
%left MUL DIV MOD
%right NOT DPLUS DMINUS UMINUS
%left DOT DDOT
%left LBRA RBRA
%left LPAREN RPAREN

%%


program 	:	stmt program								{write_rule("program -> stmt program \n\n");}
		|	EXIT_COMMAND {return ;}
		|
		;

stmt		:	expr SEMICOLON								{write_rule("stmt -> expr ;\n"); $$ = manage_term($1); }	
		|	ifstmt									{write_rule("stmt -> ifstmt\n"); $$ = NULL; }
		|	whilestmt								{write_rule("stmt -> whilestmt\n"); $$ = NULL; }
		|	forstmt									{write_rule("stmt -> forstmt\n"); $$ = NULL; }
		| 	returnstmt								{write_rule("stmt -> returnstmt\n"); $$ = NULL; }
		| 	BREAK SEMICOLON								{write_rule("stmt -> break;\n"); check_for_loop();$$ = NULL; }		
		| 	CONTINUE SEMICOLON							{write_rule("stmt -> continue;\n"); check_for_loop();$$ = NULL; }
		| 	block          								{write_rule("stmt -> block\n"); $$ = NULL; }         
		| 	funcdef									{write_rule("stmt -> funcdef\n"); $$ = $1; }
		| 	SEMICOLON								{write_rule("stmt -> ;\n"); $$ = NULL; }
		;
		
expr        	:   assignexpr									{write_rule("expr -> assignexpr \n"); $$ = $1; }
            	|   expr PLUS expr  								{write_rule("expr -> expr + expr\n"); $$ = $1; }
            	|   expr MINUS expr                                				{write_rule("expr -> expr - expr\n"); $$ = $1; }	 
            	|   expr MUL expr								{write_rule("expr -> expr * expr\n"); $$ = $1; }
           	|   expr DIV expr								{write_rule("expr -> expr / expr\n"); $$ = $1; }
		|   expr MOD expr                                                               {write_rule("expr -> expr % expr\n"); $$ = $1; }
            	|   expr GT expr								{write_rule("expr -> expr > expr\n"); $$ = $1; }
            	|   expr LT expr 								{write_rule("expr -> expr < expr\n"); $$ = $1; }
            	|   expr GE expr								{write_rule("expr -> expr >= expr\n"); $$ = $1; }
            	|   expr LE expr								{write_rule("expr -> expr <= expr\n"); $$ = $1; }
            	|   expr DE expr 								{write_rule("expr -> expr == expr\n"); $$ = $1; }
            	|   expr UNEQUAL expr								{write_rule("expr -> expr != expr\n"); $$ = $1; }
            	|   expr AND expr 								{write_rule("expr -> expr and expr\n"); $$ = $1; }
            	|   expr OR expr								{write_rule("expr -> expr or expr\n"); $$ = $1; }
            	|   term									{write_rule("expr -> term\n"); $$ = $1; }
            	;

term		: 	LPAREN expr RPAREN	{ write_rule("term -> ( expr ) \n"); $$ = $2; }
		| 	UMINUS expr  		{ write_rule("term -> -expr\n"); $$ = $2; }
		| 	NOT  expr 		{ write_rule("term -> !expr\n"); $$ = $2; }
		| 	DPLUS lvalue		{ write_rule("term -> ++lvalue\n"); $$ = check_lvalue_assex($2);if($$==NULL){$$ = manage_id($2);} }
		| 	lvalue DPLUS            { write_rule("term -> lvalue++\n"); $$ = check_lvalue_assex($1);if($$==NULL){$$ = manage_id($1);} }
		| 	DMINUS lvalue           { write_rule("term -> --lvalue\n"); $$ = check_lvalue_assex($2);if($$==NULL){$$ = manage_id($2);} }
		|	lvalue DMINUS          	{ write_rule("term -> lvalue--\n"); $$ = check_lvalue_assex($1);if($$==NULL){$$ = manage_id($1);} }
		| 	primary			{ write_rule("term -> primary\n"); $$ = $1;  }
		;

assignexpr	:     lvalue { manage_lvalue($1, type);   } EQUAL expr     {write_rule("assignexpr -> lvalue = expr\n");$$ = check_lvalue_assex($1);}			
		;
			 
primary		: 	lvalue				{ write_rule("primary -> lvalue\n");$$ = manage_lvalue($1, type); }
		| 	call 				{ write_rule("primary -> call\n");$$ = $1; }
		| 	objectdef			{ write_rule("primary -> objectdef\n");$$ = NULL; }
		| 	LPAREN funcdef RPAREN		{ write_rule("primary -> (funcdef)\n");$$ = $2; }
		| 	const 				{ write_rule("primary -> const\n");$$ = NULL; }
		;

lvalue 		: 	ID				{ write_rule("lvalue -> ID\n");$$ = $1; type = 0; }
		|	LOCAL ID 			{ write_rule("lvalue -> LOCAL ID\n");$$ = $2; type = 1; }
		| 	DCOLON ID 			{ write_rule("lvalue -> DCOLON ID\n");$$ = $2; type = 2; }
		| 	member				{ write_rule("lvalue -> member\n");$$ = $1; }
		;
		
member          :       lvalue DOT ID                   {write_rule("member -> lvalue.ID \n"); $$ = $1; }
                |       lvalue LBRA expr RBRA           {write_rule("member -> lvalue[expr]\n"); $$ = $1; }
		| 	call DOT ID 			{write_rule("member -> call.ID\n"); $$ = manage_member($1); }
		| 	call LBRA expr RBRA		{write_rule("member -> call.[expr]\n"); $$ = manage_member($1); }
		;

call 		:	call LPAREN elist RPAREN					{write_rule("call -> call(elist)\n"); $$ = $1;  }
		|	lvalue {type=3; manage_lvalue($1, type);} callsuffix            {write_rule("call -> lvalue callsuffix\n");$$= lookup_scope ($1 ->content,scope); }
		| 	LPAREN funcdef RPAREN LPAREN elist RPAREN			{write_rule("call -> (funcdef)(elist)\n"); $$ = $2; }
		;
		
callsuffix 	: 	normcall	{write_rule("callsuffix -> normcall\n");}
		| 	methodcall	{write_rule("callsuffix -> methodcall\n");}
		;

normcall 	: 	LPAREN elist RPAREN 	{write_rule("normcall -> (elist)\n");}
		;
			
methodcall 	:	DDOT ID LPAREN elist RPAREN 				  	{write_rule("methodcall -> ..ID(elist)\n");$$ = lookup($2 -> content);}	
		;					

elist 		: 	expr elist2							{write_rule("elist -> expr elist2\n");} 		
		|									{write_rule("elist -> empty\n");}
		;

elist2		:	COMMA expr elist2						{write_rule("elist2 -> ,expr elist2\n");}//$$ = check_activity($2);}
		|									{write_rule("elist2 -> empty\n");}
		|	error {sprintf(err,"line %d:expected: ,expression\n",yylineno);yyerror(err);yyclearin;}
		;

objectdef 	: 	LBRA elist RBRA		{write_rule("objectdef -> {elist}\n");}
		|	LBRA indexed RBRA	{write_rule("objectdef -> {indexed}\n");}
		;


indexed 	:	indexedelem indexed2	{write_rule("indexed -> indexedelem indexed2\n");}
		;

indexed2	:	COMMA indexedelem indexed2 {write_rule("indexed2 -> ,indexedelem indexed2\n");}
		|				   {write_rule("indexed2 -> empty\n");}
		|	error {sprintf(err,"line %d:expected: ,indexedelem\n",yylineno);yyerror(err);yyclearin;}
		;


indexedelem 	: 	LCURBRA expr COLON expr RCURBRA	{write_rule("indexedelem -> {expr:expr}\n");}
		;
			
block 		:	LCURBRA	{ update_scope();} block2  RCURBRA 	{write_rule("block -> {block2}\n"); hide(scope); scope--; }
		|  	error   {sprintf(err,"line %d: Might be bad format or a missing semicolon or bracket\n",yylineno);yyerror(err);yyclearin;}	
		;
			
block2		:	 stmt block2		{write_rule("block2 -> stmt block2\n");}
		| 				{write_rule("block2 -> empty\n");}
		;


funcdef     	:    	FUNCTION ID {temp = manage_function(yylval.token);} LPAREN {update_scope();} idlist RPAREN {scope--;} block     {write_rule("funcdef -> FUNTION ID(idlist) block\n"); $$ = temp; temp = NULL;num_loops = store_loops; store_loops = 0; lcf = update_lcf(lcf);} 
            	|    	FUNCTION {temp = noname_function();} LPAREN {update_scope();} idlist RPAREN {scope--;} block         {write_rule("funcdef -> FUNCTION(idlist) block\n"); $$ = temp; temp = NULL; num_loops = store_loops; store_loops = 0; lcf = update_lcf(lcf);}
		;

const 		: 	INT	{write_rule("const -> INT\n");} 		
		| 	REAL	{write_rule("const -> REAL\n");}
		|	STRIN 	{write_rule("const -> STRIN\n");}
		|	NIL 	{write_rule("const -> NIL\n");}
		|	TRUE	{write_rule("const -> TRUE\n");}
		|	FALSE	{write_rule("const -> FALSE\n");}
		;

idlist      :   ID {manage_idlist(yylval.token);} idlist2 {write_rule("idlist -> ID idlist2\n");}
            |
            ;

idlist2     :   COMMA ID {manage_idlist(yylval.token);} idlist2 {write_rule("idlist2 -> ,ID idlist2\n");}
            |							{write_rule("idlist2 -> empty\n");}
	    |	error  {sprintf(err,"line %d: expected: ,ID\n",yylineno);yyerror(err);yyclearin;}
            ;

ifstmt 		: 	IF LPAREN expr RPAREN stmt elsestmt	{write_rule("ifstmt -> IF(expr)stmt elsestmt\n");}
		;

elsestmt	:	ELSE stmt	{write_rule("elsestmt -> ELSE stmt\n");}
		| 			{write_rule("elsestmt -> empty\n");}
		;


whilestmt 	: 	WHILE {num_loops ++;} LPAREN expr RPAREN stmt		{write_rule("whilestmt -> WHILE(expr)stmt\n");num_loops--;}
		;
			
forstmt	 	:	FOR {num_loops ++;} LPAREN elist SEMICOLON expr SEMICOLON elist RPAREN stmt		{write_rule("forstmt -> FOR(elist;expr;elist;)stmt\n");num_loops--;}
		;

returnstmt	:	RETURN SEMICOLON		{write_rule("returnstmt -> RETURN ;\n"); $$ = manage_return((SymbolTableEntry *) NULL); }
		| 	RETURN expr SEMICOLON	{write_rule("returnstmt -> RETURN expr;\n"); $$ = manage_return($2);}
		;

%%


SymbolTableEntry *
manage_term(SymbolTableEntry *entry) {
	if(entry == NULL) return NULL;
	
	if(type == 1) {
			
		entry = check_type(entry);
		
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

SymbolTableEntry *
check_lvalue_assex(struct alpha_token_t *token) {
	SymbolTableEntry *entry=NULL;
//	entry = manage_id(token);
//	entry = manage_lvalue(token, type);
	entry = lookup_scope(token->content,scope);

	if(entry == NULL)
		entry = lookup(token->content);

	if(entry == NULL) return NULL;
	else {
		if(entry -> type == LIBFUNC || entry -> type == USERFUNC) {
			char s[150];
			//if(entry -> value.funcVal -> scope > scope ) return NULL;
			sprintf(s,"Functions are constants and their value cannot be changed: %s , in line %d",entry->value.funcVal->name, yylineno);
			yyerror(s);
			return NULL;
	}	
		else {
			if(entry -> value.varVal -> scope > scope ) return NULL;
		}
	}
	return entry;
}

/* Handles noname functions */
SymbolTableEntry *
noname_function ( ) {
	SymbolTableEntry *e;
	char *name = (char *) malloc((sizeof("noname_f") + sizeof(int)*1));

	sprintf( name,"$%d",noname_f++);

	store_loops = num_loops;
	num_loops = 0;

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

struct alpha_token_t *
manage_member(SymbolTableEntry *entry) {
	struct alpha_token_t *token = (struct alpha_token_t *) malloc(sizeof(struct alpha_token_t)*1);
	if(entry == NULL) return NULL;

	if(FUNC(entry)) {
		token->content = entry -> value.funcVal->name;
		token->numline = entry -> value.funcVal->line;
	} else {
		token->content = entry -> value.varVal->name;
		token->numline = entry -> value.varVal->line;
	}

	return token;
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
			store_loops = num_loops;
			num_loops = 0;
			e = handle_insertion( token->content, token->numline, type );
		}
		else {
			char s[50];
			sprintf(s,"Error cannot declare library function %s in line %d",token->content, yylineno);
			yyerror(s);
		}
	}
	else {
		char s[150];
		if(flag->type == LIBFUNC)
		{
			sprintf(s,"Error in line %d name %s cannot be used for function declaration cause it shadows library function.\n", yylineno, token->content);
			yyerror(s);
		}
		else
		{
			sprintf(s,"Error in line %d name %s cannot be used for function declaration cause it is already taken in this scope.\n",yylineno, token->content);
			yyerror(s);
		}
	}

	lcf = e;
	
	return e;

}

SymbolTableEntry *
handle_insertion ( char *name, unsigned int line, char *type ) {


	SymbolType e = get_type(type);
	SymbolTableEntry *entry;


	entry = insert_variable( name, line, scope, e );
	return entry;
}


void manage_idlist(struct alpha_token_t *token) {
	SymbolTableEntry *e, *flag;

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

bool
check_for_loop() {
	if(!num_loops) {
		char s[50];
		sprintf(s,"Error breaking from non-existing loop in line %d\n", yylineno);
		yyerror(s);
		return NULL;
	}
}

SymbolTableEntry * 
manage_return(SymbolTableEntry *entry) {
	if(lcf == NULL) {
		char s[50];
		sprintf(s,"Error returning from non-existing function in line %d\n", yylineno);
		yyerror(s);
		return NULL;
	}
	if(lcf -> value.funcVal -> scope == 0) {
		SymbolTableEntry *arg1 = lcf -> value.funcVal -> arguments;

		if(arg1 == NULL) return NULL;
		if(!arg1 -> isActive ) return NULL;
	}

	return entry;
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
		flag = insert_variable( *it++, 0, 0, type );
	}

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
	}
//	print_table();
}
