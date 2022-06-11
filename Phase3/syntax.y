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
%}

%union {
	struct alpha_token_t *token;
	struct SymbolTableEntry *entry;
	struct expr *ex;
	struct call	*call;
	struct pair_expr *pair;
	unsigned int num;
	struct stmt_t* stmts;
    struct for_loop_pre* for_prefix;
	struct boolsuff	*boolsuff;
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

%type <call> methodcall
%type <call> normcall
%type <call> callsuffix

%type <entry> idlist
%type <ex> returnstmt
%type <ex> elist2
%type <ex> elist
%type <ex> expr
%type <ex> lvalue
%type <ex> member
%type <ex> call
%type <ex> term
%type <ex> primary
%type <ex> assignexpr
%type <ex> objectdef
%type <ex> const

%type <entry> funcname
%type <entry> funcprefix
%type <num> funcbody
%type <entry> funcargs
%type <entry> funcdef

%type <entry> idlist_id
%type <entry> pre_idlist_suffix

%type <num> N
%type <num> M

%type <stmts> break
%type <stmts> continue
%type <stmts> stmt
%type <stmts> program
%type <stmts> loopstmt


%type <for_prefix> forprefix
%type <num> while_start
%type <num> while_cond

%type <ex> callprefix

%type <pair> indexed
%type <pair> indexed2
%type <pair> indexedelem

%type <num> ifprefix
%type <num> elseprefix

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

program 	:	program stmt								{write_rule("program -> stmt program \n\n");/*print_lists($1);*/ resettemp();}
		|	EXIT_COMMAND {return ;}
		|											{write_rule("program -> empty\n\n");}
		;

stmt		:	expr SEMICOLON
					{
						write_rule("stmt -> expr ;\n");
						//manage_stmt($1);

						if(manage_term($1)){
							if($1 -> type == assignexpr_e) {
								$$ = (stmt_t *)malloc(sizeof(stmt_t));
								$$ -> breaklist = 0;
								$$ -> contlist = 0;
							}
							if($1 -> type == boolexpr_e) {
								expr_semi_meriki($1);
								$$ = NULL;
							}
						}
					}
		|	ifstmt
				{
					write_rule("stmt -> ifstmt\n");
					$$ = (stmt_t *)malloc(sizeof(stmt_t));
					$$ -> breaklist = 0;
					$$ -> contlist = 0;
				}
		|	whilestmt
			{
				write_rule("stmt -> whilestmt\n");
				$$ = (stmt_t *)malloc(sizeof(stmt_t));
				$$ -> breaklist = 0;
				$$ -> contlist = 0;
			}
		|	forstmt
				{
					write_rule("stmt -> forstmt\n");
					$$ = (stmt_t *)malloc(sizeof(stmt_t));
					$$ -> breaklist = 0;
					$$ -> contlist = 0;
				}
		| 	returnstmt
			{
				write_rule("stmt -> returnstmt\n");
				if($1 != NULL) {
                    $$ = (stmt_t *)malloc(sizeof(stmt_t));
                    $$ -> breaklist = 0;
                    $$ -> contlist = 0;
                }
                else
                    $$ = NULL;
			}
		| 	break
				{
					write_rule("stmt -> break;\n");
					if(manage_loop_br_cont(1)) {
                        $$ = $1;
					}
                    else
                        $$ = NULL;
				}
		| 	continue
				{
					write_rule("stmt -> continue;\n");
					if(manage_loop_br_cont(0))
                        $$ = $1;
                    else
                        $$ = NULL;
				}
		| 	block
				{
					write_rule("stmt -> block\n");
					$$ = (stmt_t *)malloc(sizeof(stmt_t));
					$$ -> breaklist = 0;
					$$ -> contlist = 0;
				}
		| 	funcdef
				{
					write_rule("stmt -> funcdef\n");

					$$ = (stmt_t *)malloc(sizeof(stmt_t));
					$$ -> breaklist = 0;
					$$ -> contlist = 0;
				}
		| 	SEMICOLON
				{
					write_rule("stmt -> ;\n");
					$$ = (stmt_t *)malloc(sizeof(stmt_t));
					$$ -> breaklist = 0;
					$$ -> contlist = 0;
				}
		;

break		: BREAK SEMICOLON
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
			;

continue	: CONTINUE  SEMICOLON
				{
					//$$ = (stmt_t *) malloc(sizeof(stmt_t));
					//$$->contlist = newlist(nextquad());
					//$$->breaklist = 0;
					num_of_continues++;
					push(continues_inloopstack,nextquad());
					emit(jump, NULL, NULL, NULL, 0, yylineno);
				}


expr        	:   assignexpr
								{
									write_rule("expr -> assignexpr \n");
									$$ = $1;
								}
            	|   expr PLUS expr
								{
									write_rule("expr -> expr + expr\n");
									if(check_ex_op_ex_validity($1,$2,$3))
                                        $$ = manage_ex_op_ex_emit($1,$2,$3);
                                    else
                                        $$ = NULL;
								}
            	|   expr MINUS expr
								{
									write_rule("expr -> expr - expr\n");
									if(check_ex_op_ex_validity($1,$2,$3))
                                        $$ = manage_ex_op_ex_emit($1,$2,$3);
                                    else
                                        $$ = NULL;
								}
            	|   expr MUL expr
								{
									write_rule("expr -> expr * expr\n");
									if(check_ex_op_ex_validity($1,$2,$3))
                                        $$ = manage_ex_op_ex_emit($1,$2,$3);
                                    else
                                        $$ = NULL;
								}
				|   expr DIV expr
								{
									write_rule("expr -> expr / expr\n");
									if(check_ex_op_ex_validity($1,$2,$3))
                                        $$ = manage_ex_op_ex_emit($1,$2,$3);
                                    else
                                        $$ = NULL;
								}
				|   expr MOD expr
								{
									write_rule("expr -> expr % expr\n");
									if(check_ex_op_ex_validity($1,$2,$3))
                                        $$ = manage_ex_op_ex_emit($1,$2,$3);
                                    else
                                        $$ = NULL;
								}
            	|   expr GT expr
								{
									write_rule("expr -> expr > expr\n");
									if(check_ex_op_ex_validity($1,$2,$3))
                                        $$ = manage_ex_op_ex_emit($1,$2,$3);
                                    else
                                        $$ = NULL;
								}
            	|   expr LT expr
								{
									write_rule("expr -> expr < expr\n");
									if(check_ex_op_ex_validity($1,$2,$3))
                                        $$ = manage_ex_op_ex_emit($1,$2,$3);
                                    else
                                        $$ = NULL;
								}
            	|   expr GE expr
								{
									write_rule("expr -> expr >= expr\n");
									if(check_ex_op_ex_validity($1,$2,$3))
                                        $$ = manage_ex_op_ex_emit($1,$2,$3);
                                    else
                                        $$ = NULL;
								}
            	|   expr LE expr
								{
									write_rule("expr -> expr <= expr\n");
									if(check_ex_op_ex_validity($1,$2,$3))
                                        $$ = manage_ex_op_ex_emit($1,$2,$3);
                                    else
                                        $$ = NULL;
								}
            	|   expr DE expr
								{
									write_rule("expr -> expr == expr\n");
									$$ = manage_ex_op_ex_emit($1,$2,$3);
								}
            	|   expr UNEQUAL expr
								{
									write_rule("expr -> expr != expr\n");
									$$ = manage_ex_op_ex_emit($1,$2,$3);
								}

				| 	expr  AND { $1 = manage_boolsuffix($1);} M expr		{write_rule("expr -> expr AND expr\n"); $$ = manage_logical_op("and",$1,$4,$5);}
				|	expr  OR { $1 = manage_boolsuffix($1);} M expr	 	{write_rule("expr -> expr OR expr\n"); $$ = manage_logical_op("or",$1,$4,$5);}

            	|   term
								{
									write_rule("expr -> term\n");
								
									$$ = $1;
										
								}
            	;

term		: 	LPAREN expr RPAREN
								{
									write_rule("term -> ( expr ) \n");
									$$ = $2;
								}
			| 	MINUS expr
								{
									write_rule("term -> -expr\n");
									$$ = $2;
									$$ = manage_term_emition("-ex",$$);
								}
			| 	NOT  expr
								{
									write_rule("term -> !expr\n");
									$$ = $2;
									$$ = manage_term_emition("n_ex",$$);
								}
			| 	DPLUS lvalue
								{
									write_rule("term -> ++lvalue\n");

									if($2 != NULL)
									{
										if(check_lvalue_assex($2->sym))
											$$ = manage_term_emition("dp_lv",$2);
										else
											$$ = NULL;
									}
									else
										$$ = NULL;
								}
			| 	lvalue DPLUS
								{
									write_rule("term -> lvalue++\n");
									if($1 != NULL)
									{
										if(check_lvalue_assex($1->sym))
											$$ = manage_term_emition("lv_dp",$1);
										else
											$$ = NULL;
									}
									else
										$$ = NULL;
								}
			| 	DMINUS lvalue
								{
									write_rule("term -> --lvalue\n");
									if($2 != NULL)
									{
										if(check_lvalue_assex($2->sym))										
											$$ = manage_term_emition("dm_lv",$2);
										else
											$$ = NULL;
									}
									else
										$$ = NULL;
								}
			|	lvalue DMINUS
								{
									write_rule("term -> lvalue--\n");
									/*$$ = check_lvalue_assex($1);
									if($$==NULL)*/
									if($1 != NULL)
									{
										if(check_lvalue_assex($1->sym))
											$$ = manage_term_emition("lv_dm",$1);
										else
											$$ = NULL;
									}
									else $$ = NULL;
								}
			| 	primary
								{
									write_rule("term -> primary\n");
									$$ = $1;
								}
			;


assignexpr    :     lvalue EQUAL expr
                                        {
                                            write_rule("assignexpr -> lvalue = expr\n");
                                            if($1 != NULL)
                                            {
                                                if(check_lvalue_assex($1->sym))
                                                    $$ = manage_assign_emition($1,$3);
                                                else 
                                                    $$ = NULL;
                                            }
                                            else
                                                $$ = NULL;
                                        }

primary		: 	lvalue				{ write_rule("primary -> lvalue\n");$$ = emit_iftableitem($1); }
		| 	call 				{ write_rule("primary -> call\n");$$ = emit_iftableitem($1); }
		| 	objectdef			{ write_rule("primary -> objectdef\n");$$ = $1; }
		| 	LPAREN funcdef RPAREN
				{
					write_rule("primary -> (funcdef)\n");
					$$ = newexpr(programfunc_e);
					$$ -> sym = $2;
				}
		| 	const 				{ write_rule("primary -> const\n"); $$ = $1; }
		;

lvalue 		: 	ID
				{
					write_rule("lvalue -> ID\n");
					type = 0;
					SymbolTableEntry *e = manage_lvalue(yylval.token,type);
					$$ = lvalue_expr(e);
				}
		|	LOCAL ID
			{
				write_rule("lvalue -> LOCAL ID\n");
				type = 1;
				$$ = lvalue_expr(manage_lvalue(yylval.token, type));
			}
		| 	DCOLON ID
			{
				write_rule("lvalue -> DCOLON ID\n");
				type = 2;
				SymbolTableEntry *tem = manage_lvalue(yylval.token, type);
				if(tem != NULL) $$ = lvalue_expr(tem);
				else $$ = NULL;
			}
		| 	member
			{
				write_rule("lvalue -> member\n");
				$$ = $1;
			}
		;

member          :   lvalue DOT ID
						{
							write_rule("member -> lvalue.ID \n");
							$$ = member_item($1, yylval.token -> content);
						}
                |   lvalue LBRA expr RBRA
						{
							write_rule("member -> lvalue[expr]\n");
							if($1 == NULL) $$ = NULL;
							else {
								$1			= emit_iftableitem($1);
								$$ 			= newexpr(tableitem_e);
								$$ -> sym 	= $1 -> sym;
								$$ -> index = $3;
							}
						}
				| 	call DOT ID
						{
							write_rule("member -> call.ID\n");
							$$   = member_item($1, yylval.token -> content);
							type = 4;
						}
				| 	call LBRA expr RBRA
						{
							write_rule("member -> call.[expr]\n");
							if($1 == NULL) $$ = NULL;
							else {
								$1			= emit_iftableitem($1);
								$$			= newexpr(tableitem_e);
								$$ -> sym	= $1 -> sym;
								$$ -> index = $3;
								type=4;
							}
						}
				;


callprefix	:	lvalue	{type=3; $$ = $1;}
			;

call 		:	call LPAREN elist RPAREN
					{
						write_rule("call -> call(elist)\n");

						$$ = make_call($1, elist_head);
						empty_stack(elist_stack);
				    }
			|	callprefix callsuffix
					{
						write_rule("call -> lvalue callsuffix\n");
						$1 = emit_iftableitem($1);
						if($1 == NULL) $$ = NULL;
						else {
							if ($2 -> method) {
								expr *t = $1;
								$1 = emit_iftableitem(member_item(t, $2 -> name));
								if($2 -> elist == NULL) {
									$2 -> elist = t;
								} else {
									elist_tail -> next = t;
									elist_tail = t;
								}
							}
							$call = make_call ($1, $2 -> elist);
							
						}
						empty_stack(elist_stack);
					}
			| 	LPAREN funcdef RPAREN LPAREN elist RPAREN
					{
						write_rule("call -> (funcdef)(elist)\n");
						expr *func = newexpr(programfunc_e);
						func -> sym = $2;
						$$ = make_call(func, elist_head);
						empty_stack(elist_stack);
					}
		;


callsuffix 	: 	normcall	{write_rule("callsuffix -> normcall\n"); $$ = $1; }
		| 	methodcall	{write_rule("callsuffix -> methodcall\n"); $$ = $1;}
		;

normcall 	: 	LPAREN elist RPAREN
					{
						write_rule("normcall -> (elist)\n");
						$$ = emit_normalcall($2);
					}
		;

methodcall 	:	DDOT ID LPAREN elist RPAREN
					{
						write_rule("methodcall -> ..ID(elist)\n");
						$$ = emit_methodcall($4, $2 -> content);
					}
		;

elist 		: 	expr elist2
					{
						write_rule("elist -> expr elist2\n");
						if(elist_head == NULL) {
							elist_head = $1;
							elist_tail = $1;
						} else {
							elist_tail -> next = $1;
							elist_tail = $1;
						}
						$$ = elist_head;
						if($1 != NULL)
							push_ex(elist_stack, $1);
					}
		|									{write_rule("elist -> empty\n"); $$ = NULL; elist_head = NULL; elist_tail = NULL;}
		;

elist2		:	COMMA expr elist2
					{
						write_rule("elist2 -> ,expr elist2\n");
						if(elist_head == NULL) {
							elist_head = $2;
							elist_tail = $2;
						} else {
							elist_tail -> next = $2;
							elist_tail = $2;
						}
						$$ = $2;
						if($2 != NULL)
							push_ex(elist_stack, $2);

					}
		|									{write_rule("elist2 -> empty\n"); elist_head = NULL; elist_tail = NULL;}
		|	error {sprintf(err,"line %d:expected: ,expression\n",yylineno);yyerror(err);yyclearin;}
		;

objectdef 	: 	LBRA elist RBRA
					{
						write_rule("objectdef -> [elist]\n");
						$$ = emit_tablecreate();
						empty_stack(elist_stack);
					}
		|	LBRA indexed RBRA
				{
					write_rule("objectdef -> [indexed]\n");
					$$ = emit_tablecreate_indexed($2);
				}
		;


indexed 	:	indexedelem indexed2
					{
						write_rule("indexed -> indexedelem indexed2\n");
						$$ = pair_head;
					}
		;

indexed2	:	COMMA indexedelem indexed2 {write_rule("indexed2 -> ,indexedelem indexed2\n"); $$ = $2;}
		|				   {write_rule("indexed2 -> empty\n");}
		|	error {sprintf(err,"line %d:expected: ,indexedelem\n",yylineno);yyerror(err);yyclearin;}
		;


indexedelem 	: 	LCURBRA expr COLON expr RCURBRA
					{
						write_rule("indexedelem -> {expr:expr}\n");
						pair_expr *t 	= (pair_expr*)malloc(sizeof(pair_expr));
						t -> index 		= $2;
						t -> value		= $4;
						t -> pair_next	= NULL;
						if(pair_head == NULL) {
							pair_head = t;
							pair_tail = t;
						} else {
							pair_tail -> pair_next = t;
							pair_tail = t;
						}
						$$ = t;
					}
		;

/*
		DONT FORGET TO ADD THE NEW VARS FROM TOLIZZ ( FOR SCOPE  AND TYPE ~?)
*/

block 		:	LCURBRA upd_scp block2  RCURBRA 	{write_rule("block -> {block2}\n"); hide(scope); scope--; }
			|  	error   {sprintf(err,"line %d: Might be bad format or a missing semicolon or bracket\n",yylineno);yyerror(err);yyclearin;}
			;

block2		:	 stmt block2		{write_rule("block2 -> stmt block2\n");}
			| 						{write_rule("block2 -> empty\n");}
			;

funcblockstart  :
                    {
                        push(loopcounterstack,num_loops);
                        num_loops=0;
                        push(breakcounterstack,num_of_breaks);
                        num_of_breaks = 0;
                        push(continuecounterstack,num_of_continues);
                        num_of_continues = 0;
                    }
                ;

funcblockend    :    {
                        num_loops = pop(loopcounterstack)->item;
                        num_of_breaks = pop(breakcounterstack)->item;
                        num_of_continues = pop(continuecounterstack)->item;
                     }
                ;


funcname        :       ID { temp = manage_function(yylval.token); $$ = temp;}
                |	{ temp = noname_function(); $$ = temp;}
                ;

funcprefix      :       FUNCTION funcname
										{
											$$ = manage_func_emition($2,0,0);
											
										}
                ;

upd_scp			:	{update_scope();}
				;

funcargs        :       LPAREN upd_scp idlist RPAREN
													{
														scope--;
														$$ = $3;
														enterscopespace();
														resetfunctionlocalsoffset();
													}
                ;

funcbody        :       block
							{
								$$ = currscopeoffset();
								exitscopespace();
							}
                ;

funcdef         :       funcprefix funcargs funcblockstart funcbody funcblockend
													{
														write_rule("funcdef -> FUNTION ID(idlist) block\n");
														$$ = manage_func_emition($1,$4,1);
														temp=NULL;
														lcf = update_lcf(lcf);
													}
                ;


const 		: 	INT
					{
						write_rule("const -> INT\n");
						$$ 				= newexpr(constint_e);
						$$ -> intConst  = atoi(yylval.token -> content);
					}
		| 	REAL
					{
						write_rule("const -> REAL\n");
						$$				 = newexpr(constreal_e);
						$$ -> realConst  = atof(yylval.token -> content);
					}
		|	STRIN
					{
						write_rule("const -> STRIN\n");
						$$					= newexpr(conststring_e);
						$$ -> strConst	= yylval.token -> content;
					}
		|	NIL
					{
						write_rule("const -> NIL\n");
						$$					= newexpr(nil_e);
					}
		|	TRUE
					{
						write_rule("const -> TRUE\n");
						$$					= newexpr(constbool_e);
						$$ -> boolConst		= true;
					}
		|	FALSE
					{
						write_rule("const -> FALSE\n");
						$$					= newexpr(constbool_e);
						$$ -> boolConst		= false;
					}
		;


idlist_id : 	ID {manage_idlist(yylval.token);}

idlist      :   idlist_id idlist_suffix {write_rule("idlist -> ID idlist2\n");}
            |	{}
            ;

pre_idlist_suffix : COMMA ID {manage_idlist(yylval.token);}

idlist_suffix   :   pre_idlist_suffix idlist_suffix {write_rule("idlist2 -> ,ID idlist2\n");}
				|				{write_rule("idlist2 -> empty\n");}
				|	error  {sprintf(err,"line %d: expected: ,ID\n",yylineno);yyerror(err);yyclearin;}
				;


ifprefix	:	IF LPAREN expr RPAREN
					{
						if($3 != NULL)
							$$ = manage_if_prefix($3);
						else
							$$ = -1;
					}
			;

elseprefix	: 	ELSE
					{
						$$ = nextquad();
						emit(jump, NULL, NULL, NULL, 0, yylineno);
					}
			;


ifstmt		:	ifprefix stmt
					{
						write_rule("ifstmt -> IF(expr)stmt \n");
						
						if($1 != -1)
							patchlabel($1, nextquad());
						
					}
			|	ifprefix stmt elseprefix stmt
					{
						write_rule("ifstmt -> IF(expr)stmt elsestmt \n");
						if($1 != -1)
						{
							patchlabel($1, $3 + 1);
							patchlabel($3, nextquad());
						}
					}
			;

while_start :     WHILE {$$ = nextquad();}
            ;

while_cond  :     LPAREN M expr RPAREN {$$ = manage_while_cond_emit($3);push(continuejumpstack,$2);}
            ;

whilestmt	:	while_start while_cond loopstmt  
					{
						write_rule("whilestmt -> WHILE(expr) stmt\n");
						manage_while_emit($1, $2, $3);
						//patch labels
                        patch_loopend_labels(num_of_breaks,num_of_continues);
                        //and pop to retrieve the previous ones.
                        num_of_breaks = pop(breakcounterstack)->item;
                        num_of_continues = pop(continuecounterstack)->item; 
					}
			;

N           :    {  $$ = nextquad(); emit(jump,NULL,NULL,NULL,0,yylineno); }
            ;

M           :    { $$ = nextquad();}
            ;

loopstart    :  { 
                    ++num_loops; 
                    push(breakcounterstack,num_of_breaks);
                    num_of_breaks = 0;
                    push(continuecounterstack,num_of_continues);
                    num_of_continues = 0;
                }
            ;

loopend 	:	{ --num_loops; }
			;

loopstmt 	:	loopstart stmt loopend 
					{ 
						$$ = $2;
					}
			;

forprefix    :    FOR LPAREN elist SEMICOLON M expr SEMICOLON
                        { 
                        	$$ = manage_for_pref_emition($5,$6);                             
                        }

forstmt        :    forprefix N elist RPAREN N loopstmt N    
						{
							write_rule("forstmt -> FOR(elist;expr;elist;)stmt\n");
							push(continuejumpstack, $2+1);
							manage_for_emition($1,$2,$5,$6,$7);
							//patch labels
							patch_loopend_labels(num_of_breaks,num_of_continues);
							//and pop to retrieve the previous ones.
							num_of_breaks = pop(breakcounterstack)->item;
							num_of_continues = pop(continuecounterstack)->item; 
							empty_stack(elist_stack);
						}
            ;

returnstmt	:	RETURN SEMICOLON		{write_rule("returnstmt -> RETURN ;\n"); $$ = manage_empty_return();}
		| 	RETURN expr SEMICOLON	{write_rule("returnstmt -> RETURN expr;\n"); $$ = manage_return($2);}
		;

%%
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

