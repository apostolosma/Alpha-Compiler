#include "target.h"
generator_func_t generators[] = {
    generate_ASSIGN,
    generate_ADD,
    generate_SUB,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_UMINUS,
    generate_AND,
    generate_OR,
    generate_NOT,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_LESSEQ,
    generate_IF_GREATEREQ,
    generate_IF_LESS,
    generate_IF_GREATER,
    generate_CALL,
    generate_PARAM,
    generate_RETURN,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_FUNCEND,
    generate_NEWTABLE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    generate_JUMP,
};


void
make_operand (expr *e, vmarg *arg) {
    if(e == NULL) return;
    switch (e -> type)
    {
        case var_e:
        case assignexpr_e:
        case tableitem_e:
        case arithexpr_e:
        case boolexpr_e:
        case newtable_e: {
            assert(e -> sym);
            arg->val = e -> sym -> value.varVal -> ss_index;
            switch(e -> sym -> value.varVal -> scope_space) {
                case program_v:    arg->type   = global_a; break;
                case function_l: arg-> type  = local_a; break;
                case formal_arg:     arg->type   = formal_a; break;
                default: assert(0);
            }
            break;
        }
        case constbool_e: {
            arg->val = e->boolConst;
            arg->type = bool_a; break;
        }
        case conststring_e: {
            arg->val    = consts_newstring(e->strConst);
            arg->type   = string_a; break;
        }
        case constint_e: {
            arg->val = consts_newnumber(e -> intConst);
            arg->type = number_a; break;
        }
        case constreal_e: {
            arg->val = consts_newnumber(e -> realConst);
            arg->type = number_a; break;
        }
        case nil_e: arg->type = nil_a; arg->val = 0; break;

        case programfunc_e: {
            arg->type   = userfunc_a;
            arg->val    = e->sym->value.funcVal-> taddress;
            break;
        }
        case libraryfunc_e: {
            arg->type   = libfunc_a;
            arg->val    = libfuncs_newused(e->sym->value.funcVal -> name);
            break;
        }
        default:
            printf("TYPE %d\n", e -> type);
            assert(0);
            break;
    }
}

void make_numberoperand (vmarg *arg, double val) {
    arg->val    = consts_newnumber(val);
    arg->type   = number_a;
}

void make_booloperand (vmarg *arg, unsigned val) {
    arg->val    = val;
    arg->type   = bool_a;
}

void make_retvaloperand (vmarg *arg) {
    arg->type = retval_a;
    arg->val = 0;
}

void generate(vmopcode op, quad *q) {
    instruction t;
    t.opcode = op;
    t.srcLine = q->line;
    make_operand(q->arg1, &t.arg1);
    make_operand(q->arg2, &t.arg2);
    make_operand(q->result, &t.result);

    q->taddress = nextinstructionlabel();
    temit(t);
}

void generate_u(vmopcode op, quad *q) {
    instruction t;
    t.opcode = mul_v;
    t.srcLine = q->line;
    make_operand(q->arg1, &t.arg1);
    make_numberoperand(&t.arg2, -1);
    make_operand(q->result, &t.result);
    q->taddress = nextinstructionlabel();
    temit(t);
}

int nextinstructionlabel() {
    return currInstr;
}

void temit(instruction t) {
    if(currInstr == total) {
				expand_instr();
			}

			instruction 	*p	= instructions+currInstr;
			p -> opcode	 = t.opcode;
			p -> arg1	 = t.arg1;
			p -> arg2	 = t.arg2;
			p -> result  = t.result;
			p -> srcLine = t.srcLine;
			currInstr++;
}

void generate_UMINUS(quad *q) { generate_u(mul_v, q); }
void generate_ADD(quad *q) {    generate(add_v,q); }
void generate_SUB(quad *q) {    generate(sub_v,q); }
void generate_MUL(quad *q) {    generate(mul_v,q); }
void generate_DIV(quad *q) {    generate(div_v,q); }
void generate_MOD(quad *q) {    generate(mod_v,q); }
void generate_NEWTABLE(quad *q) {    generate(newtable_v,q); }
void generate_TABLEGETELEM(quad *q) {    generate(tablegetelem_v,q); }
void generate_TABLESETELEM(quad *q) {    generate(tablesetelem_v,q); }
void generate_ASSIGN(quad *q) {    generate(assign_v,q); }
void generate_NOP(quad *q) {    instruction t; t.opcode = nop_v; temit(t); }

int currprocessedquad() {
    return currprocquad;
}

void incurrprocessedquad() {
    currprocquad++;
}

void generate_relational(vmopcode op, quad *q) {
    instruction t;
    t.opcode = op;
    t.srcLine = q->line;
    make_operand(q->arg1,&t.arg1);
    make_operand(q->arg2,&t.arg2);

    t.result.type = label_a;
    if(q->label < currprocessedquad())
        t.result.val = quads[q -> label].taddress;
    else
        add_incomplete_jump(nextinstructionlabel(),q->label);
    q->taddress = nextinstructionlabel();
    temit(t);
}

void generate_JUMP(quad *q) { generate_relational(jump_v, q); }
void generate_IF_EQ(quad *q) { generate_relational( jeq_v, q); }
void generate_IF_NOTEQ(quad *q) { generate_relational(jne_v, q); }
void generate_IF_GREATER(quad *q) { generate_relational(jgt_v, q); }
void generate_IF_GREATEREQ(quad *q) { generate_relational(jge_v, q); }
void generate_IF_LESS(quad *q) { generate_relational(jlt_v, q); }
void generate_IF_LESSEQ(quad *q) { generate_relational(jle_v, q); }

void
generate_NOT(quad *q) {
    q->taddress = nextinstructionlabel();
    instruction t;
    t.srcLine = q->line;
    t.opcode = jeq_v;
    make_operand(q->arg1, &t.arg1);
    make_booloperand(&t.arg2, false);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel()+3;
    temit(t);

    t.opcode = assign_v;
    make_booloperand(&t.arg1,false);
    reset_operand(&t.arg2);
    make_operand(q->result, &t.result);
    temit(t);

    t.opcode = jump_v;
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel() + 2;
    temit(t);

    t.opcode = assign;
    make_booloperand(&t.arg1, true);
    reset_operand(&t.arg2);
    make_operand(q->result, &t.result);
    temit(t);
}

void
generate_OR(quad *q) {
    q->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = jeq_v;
    t.srcLine = q->line;
    make_operand(q->arg1, &t.arg1);
    make_booloperand(&t.arg2, true);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel()+4;
    temit(t);

    make_operand(q->arg2, &t.arg1);
    t.result.val = nextinstructionlabel()+3;
    temit(t);

    t.opcode = assign_v;
    make_booloperand(&t.arg1, false);
    reset_operand(&t.arg2);
    make_operand(q->result, &t.result);
    temit(t);

    t.opcode = jump_v;
    reset_operand (&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel()+2;
    temit(t);

    t.opcode = assign;
    make_booloperand(&t.arg1, true);
    reset_operand(&t.arg2);
    make_operand(q->result, &t.result);
    temit(t);
}

void
generate_AND(quad *q) {
    q->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = jeq_v;
    t.srcLine = q->line;
    make_operand(q -> arg1, &t.arg1);
    make_booloperand(&t.arg2, false);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel()+4;
    temit(t);

    make_operand(q->arg2, &t.arg1);
    t.result.val = nextinstructionlabel()+3;
    temit(t);

    t.opcode = assign_v;
    make_booloperand(&t.arg1, true);
    reset_operand(&t.arg2);
    make_operand(q->result, &t.result);
    temit(t);

    t.opcode = jump_v;
    reset_operand (&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel()+2;
    temit(t);

    t.opcode = assign;
    make_booloperand(&t.arg1, false);
    reset_operand(&t.arg2);
    make_operand(q->result, &t.result);
    temit(t);
}

void
generate_PARAM(quad *q) {
    q->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = pusharg_v;
    t.srcLine = q->line;
    make_operand(q->arg1, &t.result);
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    temit(t);
}

void
generate_CALL(quad *q) {
    q->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = call_v;
    t.srcLine = q->line;
    make_operand(q->arg1, &t.result);
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    temit(t);
}

void
generate_GETRETVAL(quad *q)  {
    q->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = assign;
    t.srcLine = q->line;
    make_operand(q->result, &t.result);
    make_retvaloperand(&t.arg1);
    reset_operand(&t.arg2);
    temit(t);
}

void
generate_FUNCSTART(quad *q) {
    assert(q -> result);
    SymbolTableEntry *f = q -> result -> sym;
    f->value.funcVal -> taddress = nextinstructionlabel();

    userfunc *new_f = (userfunc *) malloc(sizeof(userfunc));
    new_f -> id = f -> value.funcVal -> name;
    new_f -> localSize = f -> value.funcVal -> total_locals;
    new_f -> address = f -> value.funcVal -> taddress;
    new_f -> returnList = NULL;
    push_func(new_f);
    userfuncs_newfunc(q -> result -> sym);

    instruction t;
    t.opcode = funcenter_v;
    t.srcLine = q->line;
    make_operand(q -> result, &t.result);
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    temit(t);
}

void
generate_RETURN(quad *q) {
    q -> taddress = nextinstructionlabel();
    instruction t;
    t.opcode = assign_v;
    t.srcLine = q->line;
    make_retvaloperand(&t.result);
    make_operand(q -> result, &t.arg1);
    temit(t);

    userfunc *f = userFuncs;
    assert(f);
    append_return(f, nextinstructionlabel());

    t.opcode = jump_v;
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    temit(t);

}

void
generate_FUNCEND(quad *q) {
    userfunc *f = pop_func(userFuncs);
    assert(f);
    backpatch_ret(f->returnList, nextinstructionlabel());

    q -> taddress = nextinstructionlabel();
    instruction t;
    t.opcode = funcexit_v;
    t.srcLine = q->line;
    make_operand(q -> result, &t.result);
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    temit(t);
}



void push_func(struct userfunc *new_func) {
    if ( userFuncs == NULL ) {
        userFuncs = new_func;
        new_func -> next = NULL;
    }
    else {
        new_func -> next = userFuncs;
        userFuncs = new_func;
    }
}

void print_funcstack(struct userfunc *s) {
    while(s != NULL) {
        printf("%s ->", s -> id);
        s = s -> next;
    }
    printf("\n");
}

struct userfunc *
pop_func(struct userfunc *s) {

    struct userfunc *temp = s;
    if(s == NULL) {
        printf("empty stack\n");
        return NULL;
    }

    if( s->next != NULL)
        s = s->next;
    else
        s = NULL;
    
    temp -> next = NULL;
    return temp;
}


void
append_return(struct userfunc *f,int instruction) {
    struct returnList *new_return = (struct returnList *)malloc(sizeof(struct returnList));

    new_return->label = instruction;
    new_return->next = f->returnList;
    f->returnList = new_return;
}

void
print_retlist(struct returnList *rl) {
    printf("Return list: ");
    while(rl != NULL) {
        printf("%d ->", rl -> label);

        rl = rl -> next;
    }
}

void
backpatch_ret(struct returnList *list, int label) {
	while(list != NULL) {
		if((instructions + list->label) -> result.val == 0) {
			(instructions + list->label) -> result.val = label;
		}

		list = list->next;
	}
}

void
patch_incomplete_jumps() {
    unsigned i;
    for( i = 0; i < ij_total; i++) {
        //assert(ij_head -> iaddress);
        if(ij_head -> iaddress == currQuad) {
            
            instructions[ij_head -> instrNo].result.val = currInstr;
        } else {
           
            instructions[ij_head -> instrNo].result.val = quads[ij_head -> iaddress].taddress;
        }

        ij_head = ij_head -> next;
    }
}



unsigned
consts_newstring( char *s) {
    unsigned i;
    for(i = 0; i < cstring_index; i++) {
        if(!strcmp(s, consts_strings[i])) {
            return i;
        }
    }
    //This means we have a new constant string
    consts_strings[cstring_index] = (char *) malloc(sizeof(char)*strlen(s));
    consts_strings[cstring_index] = s;
    ++cstring_index;

    return cstring_index - 1;
}

unsigned
consts_newnumber(double n ) {
    unsigned i;
    for(i = 0; i < cnumbers_index; i++) {
        if (n == consts_numbers[i]) {
            return i;
        }
    }
    //This means we have a new constant number
    consts_numbers[cnumbers_index] = n;
    cnumbers_index++;
    return cnumbers_index-1;
}
unsigned
libfuncs_newused(const char *s ) {
    unsigned i;
    for(i = 0; i < clibs_index; i++) {
        if(!strcmp(s, consts_libfuncs[i])) {
            return i;
        }
    }

    consts_libfuncs[clibs_index] = (char *) malloc(sizeof(char)*strlen(s));
    consts_libfuncs[clibs_index] = s;
    ++clibs_index;
    return clibs_index-1;
}
unsigned
userfuncs_newfunc( struct SymbolTableEntry *sym) {
    struct userfunc u;

    u.address = sym -> value.funcVal -> iaddress;
    u.id = sym -> value.funcVal -> name;
    u.localSize = sym -> value.funcVal -> total_locals;

    consts_userfunc[userfunc_index] = u;
    ++userfunc_index;
    return userfunc_index-1;
}


void expand_instr(void) {
	assert(total == currInstr);
	instruction* p = (instruction *) malloc(TNEW_SIZE);
	if(instructions) {
		memcpy(p, instructions, TCURR_SIZE);
		free(instructions);
	}
	instructions = p;
	total += TEXPAND_SIZE;
}

void
reset_operand(struct vmarg *a) {
    a->type = -1;
    a->val = -1;
}

void
add_incomplete_jump(unsigned instrNo, unsigned iaddress) {
    struct incomplete_jump* ij = (incomplete_jump *)malloc(sizeof(incomplete_jump));
    ij -> instrNo = instrNo;
    ij -> iaddress = iaddress;
    if(!ij_head)
        ij_head = ij;
    else {
        ij -> next = ij_head;
        ij_head = ij;
    }

    ij_total ++;
}

char *
get_op(vmopcode op) {
    char *s;

    switch(op) {
        case    assign_v:
            return "assign";
            break;
        case    add_v:
            return "add";
            break;
        case    sub_v:
            return "sub";
            break;
        case    mul_v:
            return "mul";
            break;
        case    div_v:
            return "div";
            break;
        case    mod_v:
            return "mod";
            break;
        case    uminums_v:
            return "uminus";
            break;
        case    and_v:
            return "and";
            break;
        case    or_v:
            return "or";
            break;
        case    not_v:
            return "not";
            break;
        case    jump_v:
            return "jump";
            break;
        case    jeq_v:
            return "jeq";
            break;
        case    jne_v:
            return "jne";
            break;
        case    jle_v:
            return "jle";
            break;
        case    jge_v:
            return "jge";
            break;
        case    jlt_v:
            return "jlt";
            break;
        case    jgt_v:
            return "jgt";
            break;
        case    call_v:
            return "call";
            break;
        case    pusharg_v:
            return "pusharg";
            break;
        case    funcenter_v:
            return "funcenter";
            break;
        case    funcexit_v:
            return "funcexit";
            break;
        case    newtable_v:
            return "newtable";
            break;
        case    tablegetelem_v:
            return "tablegetelem";
            break;
        case    tablesetelem_v:
            return "tablesetelem";
            break;
        case    nop_v:
            return "nop";
            break;
        default: assert(0);
    }
}

void
display_instructions(FILE *yyout) {
    char *op;
    int i;
    fprintf(yyout,"\t\t\t\t\t\t---INSTRUCTIONS---\n");
    fprintf(yyout,"   instruction#\t\topcode\t\t\tresult\t\targ1\t\targ2\t\tsrcLine\n");
    fprintf(yyout,"----------------------------------------------------------------------------------------------------------------------------------\n");

    for(i = 0; i < currInstr; i++) {
            op = get_op((instructions+i) -> opcode);
            fprintf(yyout,"%10d\t\t%10s", i,op);
            switch(get_opc_type((instructions+i) -> opcode)) {
                case 2: {
                    print_vmarg((instructions+i) -> result, yyout);
                    print_vmarg((instructions+i) -> arg1, yyout);
                    fprintf(yyout,"\t\t\t\t%u",(instructions+i) -> srcLine);
                    break;
                }
                case 3: {
                    print_vmarg((instructions+i) -> result, yyout);
                    print_vmarg((instructions+i) -> arg1, yyout);
                    print_vmarg((instructions+i) -> arg2, yyout);
                    fprintf(yyout,"\t\t%u",(instructions+i) -> srcLine);
                    break;
                }
                case 1: {
                    print_vmarg((instructions+i) -> result, yyout);
                    fprintf(yyout,"\t\t\t\t\t\t%u",(instructions+i) -> srcLine);
                    break;
                    
                }
                default: assert(0);

            }
            fprintf(yyout,"\n");
    }

    fprintf(yyout,"---USERFUNCS---\n");
    for (i = 0; i < userfunc_index; i++)
    {
        fprintf(yyout, "%d : %s\n", i, consts_userfunc[i].id);
    }
    fprintf(yyout,"\n---LIBFUNCS---\n");
     for (i = 0; i < clibs_index; i++)
    {
        fprintf(yyout, "%d : %s\n", i, consts_libfuncs[i]);
    }
    fprintf(yyout,"\n---NUMBERS---\n");
     for (i = 0; i < cnumbers_index; i++)
    {
        fprintf(yyout, "%d : %f\n", i, consts_numbers[i]);
    }
    fprintf(yyout,"\n---STRINGS---\n");
     for (i = 0; i < cstring_index; i++)
    {
        fprintf(yyout, "%d : %s\n", i, consts_strings[i]);
    }

}

void
print_vmarg(vmarg arg, FILE *yyout) {
    if(arg.type == -1 || arg.val == -1) {
        fprintf(yyout, "%10s","");
    }else {
        fprintf(yyout,"\t%10d,%d", arg.type,arg.val );
    }
}

void write_magicnumber()
{
	unsigned magnum= 378364499;//THE MAJESTIC OF ALL MAGIC NUMBERS 
	FILE *fp = NULL;
	
	if( access( "tbinary.abc", F_OK ) == 0 ) {
		int del = remove("tbinary.abc");
		if (!del)
			printf("The file was Deleted successfully\n");
		else
			printf("The file was not Deleted\n");
	}
	fp = fopen("tbinary.abc","a+");
	if(fp == NULL)
	{
		printf("Error!Could not open file 'tbinary.abc'\n");   
		exit(1);             
	}
	fwrite(&magnum,sizeof(unsigned),1,fp);
	fclose(fp);
}

void write_arrays()
{
	FILE *fp = NULL;
	fp = fopen("tbinary.abc","a+");
	if(fp == NULL)
	{
		printf("Error!Could not open file 'tbinary.abc'\n");   
		exit(1);             
	}
	write_strings(fp);
	write_numbers(fp);
	write_user_functions(fp);
	write_lib_functions(fp);
	fclose(fp);
}

void write_strings(FILE* fp)
{
	int i;
	unsigned slen;
	char *const_str;
	
	fwrite(&cstring_index,sizeof(unsigned),1,fp);
	for(i = 0;i < cstring_index; i++)
	{
		slen = strlen(consts_strings[i]) + 1;//1 is the null byte
		const_str = strdup(consts_strings[i]);
		fwrite(&slen,sizeof(unsigned),1,fp);
		fwrite(const_str,slen*sizeof(char),1,fp);
    }

	
}

void write_numbers(FILE *fp)
{
	int i;
	double number;
	fwrite(&cnumbers_index,sizeof(unsigned),1,fp);
	for(i = 0;i < cnumbers_index; i++)
	{
		number = consts_numbers[i];
		fwrite(&number,sizeof(double),1,fp);
	}
}

void write_user_functions(FILE *fp)
{
	int i;
	unsigned address;
	unsigned localsize;
	unsigned idlen;
	char *id;
	
	fwrite(&userfunc_index,sizeof(unsigned),1,fp);
	for(i = 0;i < userfunc_index; i++)
	{
		address = consts_userfunc[i].address;
		localsize = consts_userfunc[i].localSize;
		id = strdup(consts_userfunc[i].id);
		idlen = strlen(id) + 1;
		
		fwrite(&address,sizeof(unsigned),1,fp);
		fwrite(&localsize,sizeof(unsigned),1,fp);
		fwrite(&idlen,sizeof(unsigned),1,fp);
		fwrite(id,idlen*sizeof(char),1,fp);
	}
}

void write_lib_functions(FILE *fp)
{
	int i;
	unsigned slen;
	char *const_libstr;
	
	fwrite(&clibs_index,sizeof(unsigned),1,fp);
	for(i = 0;i < clibs_index; i++)
	{
		slen = strlen(consts_libfuncs[i]) + 1;//1 is the null byte
		const_libstr = strdup(consts_libfuncs[i]);
		fwrite(&slen,sizeof(unsigned),1,fp);
		fwrite(const_libstr,slen*sizeof(char),1,fp);
        free(const_libstr);
	}
}

void write_code()
{
	FILE *fp=NULL;
	fp = fopen("tbinary.abc","a+");
	if(fp == NULL)
	{
		printf("Error!Could not open file 'tbinary.abc'\n");   
		exit(1);             
	}
	fwrite(&currInstr,sizeof(unsigned),1,fp);
	write_instructions(fp);
	fclose(fp);
}

void write_instructions(FILE *fp)
{
	int i;
	unsigned  opcode;
	unsigned opc_type;
	unsigned srcLine;
    for(i = 0; i < currInstr; i++)
	{
		opcode = (unsigned) instructions[i].opcode;
        srcLine = instructions[i].srcLine;
		fwrite(&opcode,sizeof(unsigned),1,fp);
		opc_type = get_opc_type(opcode);
		write_operands(fp,i,opc_type);
        fwrite(&srcLine,sizeof(unsigned),1,fp);
	}
	
}

void write_operands(FILE *fp,int i,unsigned opc_type)
{
	unsigned char type;
	unsigned value;
	
	if(opc_type == 1)
	{
		type = (unsigned char) instructions[i].result.type;
		value = instructions[i].result.val;
		fwrite(&type,sizeof(unsigned char),1,fp);
		fwrite(&value,sizeof(unsigned),1,fp);
	}
	else if(opc_type == 2)
	{
		type = (unsigned char) instructions[i].result.type;
		value = instructions[i].result.val;
		fwrite(&type,sizeof(unsigned char),1,fp);
		fwrite(&value,sizeof(unsigned),1,fp);
		
		type = (unsigned char) instructions[i].arg1.type;
		value = instructions[i].arg1.val;
		fwrite(&type,sizeof(unsigned char),1,fp);
		fwrite(&value,sizeof(unsigned),1,fp);
	}
	else if(opc_type == 3)
	{
		type = (unsigned char) instructions[i].result.type;
		value = instructions[i].result.val;
		fwrite(&type,sizeof(unsigned char),1,fp);
		fwrite(&value,sizeof(unsigned),1,fp);
		
		type = (unsigned char) instructions[i].arg1.type;
		value = instructions[i].arg1.val;
		fwrite(&type,sizeof(unsigned char),1,fp);
		fwrite(&value,sizeof(unsigned),1,fp);
		
		type = (unsigned char) instructions[i].arg2.type;
		value = instructions[i].arg2.val;
		fwrite(&type,sizeof(unsigned char),1,fp);
		fwrite(&value,sizeof(unsigned),1,fp);
		
	}
}

void write_avmbinaryfile()
{
	write_magicnumber();
	write_arrays();
	write_code();
}

//nop 0?
//1 : jump, call , pusharg,funcenter,funcexit,newtable
//2 : assign,
//3 : 1-9,jeq,jne,jle,jge,jlt,jgt,tablegetelem,tablesetelem
unsigned get_opc_type(unsigned char opcode)
{
	if(opcode == 0)
	{
		return 2;
	}
	else if((opcode >= 1 && opcode <= 9) || (opcode >= 11 && opcode <= 16) || opcode == 22 || opcode == 23)
	{
		return 3;
	}
	else if(opcode == 10 || (opcode >= 17 && opcode <= 21))
	{
		return 1;
	}
	else
	{
			printf("Failed to identify opcode\n");
	}
	
}
