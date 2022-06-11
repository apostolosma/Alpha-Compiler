#include "avm.h"

void avm_warning(char *warning) {
    printf("%s\n",warning);
}

void avm_error(char *error) {
    printf("%s\n",error);
    exit(1);
}

void avm_memcellclear (avm_memcell *m) {
    if(m -> type != undef_m) {
        memclear_func_t f = memclearFuncs[m->type];
        if (f)
            (*f)(m);
        m ->type = undef_m;
    }
}

void load_magicnumber(FILE *fp)
{
	fread(&magic_number,sizeof(unsigned),1,fp);
	if(magic_number != 378364499)
		printf("Magic number does not match\n");
}

double consts_getnumber(unsigned index) { return consts_numbers[index]; }
char *consts_getstring(unsigned index) { return consts_strings[index]; }
const char *consts_getlibfunc(unsigned index) { return consts_libfuncs[index]; }
/*unsigned consts_get(unsigned index) { return consts_[index]; }
unsigned consts_get(unsigned index) { return consts_[index]; }
*/
void load_arrays(FILE *fp)
{
	load_strings(fp);
	load_numbers(fp);
	load_user_functions(fp);
	load_lib_functions(fp);
}

void load_strings(FILE *fp)
{
	unsigned totals = 0;
	unsigned i,j;
	unsigned slen = 0;
	char *content = NULL;
	fread(&totals,sizeof(unsigned),1,fp);
	if(totals != 0)
	{
		for(i = 0; i < totals; i++)
		{
			fread(&slen,sizeof(unsigned),1,fp);
			if(slen != 0)
			{
				content = malloc(slen*sizeof(char));
				fread(content,slen*sizeof(char),1,fp);
				consts_newstring(content);
			}
			/*if(strlen != 0)
			{

			}*/
			//else//Beware of string "".This line is just for DEBUG since "" is len 0
			//	printf("strlen in load_strings is 0 at index i : %d with total : %d\n",i,total);
		}
	}

}

void load_numbers(FILE *fp)
{
	unsigned totals = 0;
	unsigned i ;
	double number;

	fread(&totals,sizeof(unsigned),1,fp);

	for(i = 0; i < totals; i++)
	{
		fread(&number,sizeof(double),1,fp);
		consts_newnumber(number);
	}

}

void load_user_functions(FILE *fp)
{
	unsigned totals = 0;
	unsigned i, j;
	unsigned address = 0;
	unsigned localsize = 0;
	unsigned slen = 0;
	char* id = NULL;

	fread(&totals,sizeof(unsigned),1,fp);

	for(i = 0; i < totals; i++)
	{
		fread(&address,sizeof(unsigned),1,fp);
		fread(&localsize,sizeof(unsigned),1,fp);
		fread(&slen,sizeof(unsigned),1,fp);

		id = malloc(slen*sizeof(char));
		fread(id,slen*sizeof(char),1,fp);

		consts_userfunc[userfunc_index].address = address;
		consts_userfunc[userfunc_index].localSize = localsize;
		consts_userfunc[userfunc_index].id = id;
		userfunc_index++;
	}
}

void load_lib_functions(FILE *fp)
{
	unsigned totals = 0;
	unsigned i,j;
	unsigned slen = 0;
	char *lib_id = NULL;

	fread(&totals,sizeof(unsigned),1,fp);

	if(totals != 0)
	{
		for(i = 0; i < totals; i++)
		{
			fread(&slen,sizeof(unsigned),1,fp);
			lib_id = malloc(slen*sizeof(char));
			fread(lib_id,slen*sizeof(char),1,fp);
			consts_libfuncs[clibs_index] = lib_id;
			clibs_index++;
		}
	}
}

void load_code(FILE *fp)
{
	unsigned totals = 0;
    unsigned i;

	fread(&totals,sizeof(unsigned),1,fp);
	codeSize = totals;
    unsigned char globals[codeSize];
    for( i = 0; i < codeSize; i++)
        globals[i] = 0;
    instructions = malloc(totals * sizeof(struct instruction));
	load_instructions(fp,totals);
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

void load_instructions(FILE *fp,unsigned totals)
{
	unsigned i;
	unsigned opcode;
	unsigned type = 0;
	unsigned srcLine;
	struct instruction *instr;
	for(i = 0; i < totals; i++)
	{
		fread(&opcode,sizeof(unsigned),1,fp);
		type = get_opc_type(opcode);
		instr = load_operands(fp,type);
		fread(&srcLine,sizeof(unsigned),1,fp);
		instr -> opcode = opcode;
		instr -> srcLine = srcLine;
		instructions[i] = *instr;
	}
}

void check_for_globals(vmarg v) {
    if(v.type == global_a) {

        if(v.val >= max_index_global) {
			max_index_global = v.val;
		}
    }
}

instruction * load_operands(FILE *fp,unsigned opc_type)
{
	unsigned char type;
	unsigned value;
	struct instruction *instr = malloc(sizeof(struct instruction));
	struct vmarg res ;
	struct vmarg arg1 ;
	struct vmarg arg2 ;
	instr -> srcLine = 0;
	if(opc_type == 1)
	{
		fread(&type,sizeof(unsigned char),1,fp);
		fread(&value,sizeof(unsigned),1,fp);
		res.type = (vmarg_t) type;
		res.val = value;

		arg1.type = -1;
		arg1.val  = -1;

		arg2.type = -1;
		arg2.val  = -1;

        check_for_globals(res);

		instr->result = res;
		instr->arg1 = arg1;
		instr->arg2 = arg2;
	}
	else if(opc_type == 2)
	{
		fread(&type,sizeof(unsigned char),1,fp);
		fread(&value,sizeof(unsigned),1,fp);
		res.type = (vmarg_t) type;
		res.val = value;

		fread(&type,sizeof(unsigned char),1,fp);
		fread(&value,sizeof(unsigned),1,fp);
		arg1.type = (vmarg_t) type;
		arg1.val= value;

		arg2.type = -1;
		arg2.val  = -1;

        check_for_globals(arg1);
        check_for_globals(res);

		instr->result = res;
		instr->arg1 = arg1;
		instr->arg2 = arg2;

	}
	else if(opc_type == 3)
	{
		fread(&type,sizeof(unsigned char),1,fp);
		fread(&value,sizeof(unsigned),1,fp);
		res.type = (vmarg_t) type;
		res.val = value;

		fread(&type,sizeof(unsigned char),1,fp);
		fread(&value,sizeof(unsigned),1,fp);
		arg1.type = (vmarg_t) type;
		arg1.val = value;

		fread(&type,sizeof(unsigned char),1,fp);
		fread(&value,sizeof(unsigned),1,fp);
		arg2.type = (vmarg_t) type;
		arg2.val = value;

        check_for_globals(arg1);
        check_for_globals(arg2);
        check_for_globals(res);

		instr->result = res;
		instr->arg1 = arg1;
		instr->arg2 = arg2;
	}
	return instr;
}

void load_avmbinaryfile()
{
	FILE *fp = NULL;

	fp = fopen("tbinary.abc","r");
	if(fp == NULL)
	{
		printf("Error!Could not open file 'tbinary.abc'\n");
		exit(1);
	}

	load_magicnumber(fp);
	load_arrays(fp);
	load_code(fp);
}

unsigned
consts_newstring( char *s) {
    consts_strings[cstring_index] = (char *) malloc(sizeof(char)*strlen(s));
    consts_strings[cstring_index] = s;
    ++cstring_index;

    return cstring_index;
}

unsigned
consts_newnumber(double n ) {
    consts_numbers[cnumbers_index] = n;
    ++cnumbers_index;
    return cnumbers_index-1;
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
	fprintf(yyout,"   instruction#\t\topcode\t\t\tresult\t\targ1\t\targ2\n");
	fprintf(yyout,"----------------------------------------------------------------------------------------------------------------------------------\n");

    for(i = 0; i < codeSize; i++) {
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

static void
avm_initavm_stack(void) {
    unsigned i;
    for(i = 0; i < AVM_STACKSIZE; i++) {
        AVM_WIPEOUT(avm_stack[i]);
        avm_stack[i].type = undef_m;
    }

    top = AVM_STACKSIZE - (max_index_global + 1) - 1;
    executionFinished = 0;
    pc = 0;
    currLine = 0;

}

void
avm_tableincrefcounter (avm_table *t) {
    ++t->refCounter;
}

void avm_tabledecrefcounter (avm_table *t) {
    assert(t->refCounter > 0);
    if(!--t->refCounter)
        avm_tabledestroy(t);
}

void
avm_tablebucketsinit (avm_table_bucket **p) {
    unsigned i;
    for(i = 0; i < AVM_TABLE_HASHSIZE; i++)
        p[i] = NULL;
}

avm_table *
avm_tablenew (void) {
    avm_table *t = malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);

    assert(t);
    t->refCounter = t->total = 0;
    avm_tablebucketsinit(t->numIndexed);
    avm_tablebucketsinit(t->strIndexed);

    return t;
}



void
avm_tablebucketsdestroy (avm_table_bucket **p) {
    unsigned i;
	avm_table_bucket *b ;
    for ( i = 0; i < AVM_TABLE_HASHSIZE; ++i, ++p) {
        for(b = *p; b;) {
            avm_table_bucket *del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del -> value);
            // free(del);
        }
        p[i] = (avm_table_bucket *) 0;
    }
}

void
avm_tabledestroy (avm_table *t) {
    avm_tablebucketsdestroy(t->strIndexed);
    avm_tablebucketsdestroy(t->numIndexed);
	t -> total = 0;
    // free(t);
}

double mod_impl (double x, double y) {return ((unsigned) x % (unsigned) y);}
double div_impl (double x, double y) {if(y == 0) {avm_error("Error cannot divide with 0!");executionFinished=1;return 0;}return x/y;}
double mul_impl (double x, double y) {return x*y;}
double sub_impl (double x, double y) {return x-y;}
double add_impl (double x, double y) {return x+y;}

arithmetic_func_t arithmeticFuncs[] = {
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl
};



memclear_func_t memclearFuncs[] = {
    0,
    memclear_string,
    0,
    memclear_table,
    0,
    0,
    0,
    0
};

bool less_number (avm_memcell *r1, avm_memcell *r2) { return r1->data.numVal < r2->data.numVal;}
bool less_string (avm_memcell *r1, avm_memcell *r2) {return !strcmp(r1->data.strVal, r2->data.strVal);}
bool less_bool (avm_memcell *r1, avm_memcell *r2) {return r1->data.boolVal < r2->data.boolVal;}
bool less_table (avm_memcell *r1, avm_memcell *r2) {return r2->data.tableVal < r2->data.tableVal;}
bool less_userfunc (avm_memcell *r1, avm_memcell *r2) {avm_error("cannot compare user functions!");}
bool less_libfunc (avm_memcell *r1, avm_memcell *r2) {avm_error("cannot compare library functions!");}
bool less_nil (avm_memcell *r1, avm_memcell *r2) { avm_error("cannot compare nil!");}
bool less_undef (avm_memcell *r1, avm_memcell *r2) {assert(0); return 0;}

less_type_t lessinstrFuncs[] = {
	less_number,
	less_string,
	less_bool,
	less_table,
	less_userfunc,
	less_libfunc,
	less_nil,
	less_undef
};



void execute_uminus(instruction *instr) { execute_arithmetic(instr); }

void execute_jeq (instruction * instr) {
	assert(instr -> result.type == label_a);

	avm_memcell *rv1 = avm_translate_operand(&instr -> arg1, &ax);
	avm_memcell *rv2 = avm_translate_operand(&instr -> arg2, &bx);

	unsigned char result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m)
		avm_error("'undef' involved in equality!");
	else
	if (rv1 -> type == nil_m || rv2 -> type == nil_m)
		result = rv1->type == nil_m && rv2 -> type == nil_m;
	else
	if (rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	else
	if (rv1 -> type != rv2 -> type)
		avm_error("comparing two different things!");
	else {
		result = (*compareinstrFuncs[rv1->type])(rv1,rv2);
	}

    if(!executionFinished && result)
        pc = instr -> result.val;

}

void execute_jne (instruction *instr) {
    assert(instr -> result.type == label_a);

    avm_memcell *rv1 = avm_translate_operand(&instr -> arg1, &ax);
    avm_memcell *rv2 = avm_translate_operand(&instr -> arg2, &bx);
    
    unsigned char result = 0;

    if(rv1->type == undef_m || rv2->type == undef_m)
		avm_error("'undef' involved in equality!");
	else
	if (rv1 -> type == nil_m || rv2 -> type == nil_m)
		result = rv1->type == nil_m && rv2 -> type == nil_m;
	else
	if (rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	else
	if (rv1 -> type != rv2 -> type)
		avm_error("comparing two different things!");
	else {
		result = (*compareinstrFuncs[rv1->type])(rv1,rv2);
	}

    if(!executionFinished && !result)
        pc = instr -> result.val;
}

void execute_jle (instruction *instr) {
    assert(instr -> result.type == label_a);

	avm_memcell *rv1 = avm_translate_operand(&instr -> arg1, &ax);
	avm_memcell *rv2 = avm_translate_operand(&instr -> arg2, &bx);

	unsigned char result1 = 0;
    unsigned char result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m)
		avm_error("'undef' involved in equality!");
	else
	if (rv1 -> type == nil_m || rv2 -> type == nil_m) {
		result = rv1->type == nil_m && rv2 -> type == nil_m;
        if(result == 1) 
            avm_error("cannot compare nil with something else"); 
    }
	else
	if (rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) <= avm_tobool(rv2));
	else
	if (rv1 -> type != rv2 -> type)
		avm_error("comparing two different things!");
	else {
		result = (*lessinstrFuncs[rv1->type])(rv1,rv2);
        result1 = (*compareinstrFuncs[rv1->type])(rv1,rv2);
	}

    if(!executionFinished && (result || result1))
        pc = instr -> result.val;
}

void execute_jge (instruction *instr) {
    assert(instr -> result.type == label_a);

	avm_memcell *rv1 = avm_translate_operand(&instr -> arg1, &ax);
	avm_memcell *rv2 = avm_translate_operand(&instr -> arg2, &bx);

	unsigned char result1 = 0;
    unsigned char result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m)
		avm_error("'undef' involved in equality!");
	else
	if (rv1 -> type == nil_m || rv2 -> type == nil_m) {
		result = rv1->type == nil_m && rv2 -> type == nil_m;
        if(result == 1) 
            avm_error("cannot compare nil with something else"); 
    }
	else
	if (rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) <= avm_tobool(rv2));
	else
	if (rv1 -> type != rv2 -> type)
		avm_error("comparing two different things!");
	else {
		result = (*lessinstrFuncs[rv1->type])(rv1,rv2);
        result1 = (*compareinstrFuncs[rv1->type])(rv1,rv2);
	}

    if(!executionFinished && (!result || result1))
        pc = instr -> result.val;
}

void execute_jlt (instruction *instr) {
    assert(instr -> result.type == label_a);

	avm_memcell *rv1 = avm_translate_operand(&instr -> arg1, &ax);
	avm_memcell *rv2 = avm_translate_operand(&instr -> arg2, &bx);

	unsigned char result = 0;

	if(rv1->type == undef_m || rv2->type == undef_m)
		avm_error("'undef' involved in equality!");
	else
	if (rv1 -> type == nil_m || rv2 -> type == nil_m) {
		result = rv1->type == nil_m && rv2 -> type == nil_m;
        if(result == 1) 
            avm_error("cannot compare nil with something else"); 
    }
	else
	if (rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) < avm_tobool(rv2));
	else
	if (rv1 -> type != rv2 -> type)
		avm_error("comparing two different things!");
	else {
		result = (*lessinstrFuncs[rv1->type])(rv1,rv2);
	}

    if(!executionFinished && result)
        pc = instr -> result.val;
    
}

void execute_jgt (instruction *instr) {
    assert(instr -> result.type == label_a);

	avm_memcell *rv1 = avm_translate_operand(&instr -> arg1, &ax);
	avm_memcell *rv2 = avm_translate_operand(&instr -> arg2, &bx);

	unsigned char result = 0;
    unsigned char result1 = 0;

	if(rv1->type == undef_m || rv2->type == undef_m)
		avm_error("ERROR:'undef' involved in equality!");
	else
	if (rv1 -> type == nil_m || rv2 -> type == nil_m) {
		result = rv1->type == nil_m && rv2 -> type == nil_m;
        if(result == 1) 
            avm_error("ERROR:cannot compare nil with something else"); 
    }
	else
	if (rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) < avm_tobool(rv2));
	else
	if (rv1 -> type != rv2 -> type)
		avm_error("ERROR:comparing two different things!");
	else {
		result = (*lessinstrFuncs[rv1->type])(rv1,rv2);
        result1 = (*compareinstrFuncs[rv1->type])(rv1,rv2);
	}

    if(!executionFinished && (!result || result1)) 
        pc = instr -> result.val;
}

void execute_and(instruction *instr) {}
void execute_nop(instruction *instr) {}
void execute_or(instruction *instr) {}
void execute_not(instruction *instr) {}
void execute_jump(instruction *instr) {
    assert(instr -> result.type == label_a);
    pc = instr -> result.val;
}

execute_func_t executeFuncs[] = {
    execute_assign,
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    execute_uminus,
    execute_and,
    execute_or,
    execute_not,
    execute_jump,
    execute_jeq,
    execute_jne,
    execute_jle,
    execute_jge,
    execute_jlt,
    execute_jgt,
    execute_call,
    execute_pusharg,
    execute_funcenter,
    execute_funcexit,
    execute_newtable,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_nop
};

avm_memcell *
avm_translate_operand (vmarg *arg, avm_memcell *reg) {
    switch (arg -> type ) {
        case global_a: return &avm_stack[AVM_STACKSIZE - 1 - arg->val];
        case local_a: return &avm_stack[topsp - arg->val];
        case formal_a: return &avm_stack[topsp + AVM_STACKENV_SIZE + 1 + arg->val];

        case retval_a: return &retval;
        case number_a: {
            
            reg -> type = number_m;
            reg -> data.numVal = consts_getnumber(arg->val);
            return reg;
        }
        case string_a: {
            reg->type = string_m;
            reg->data.strVal = consts_getstring(arg->val);
            return reg;
        }

        case bool_a: {
            reg->type = bool_m;
            reg->data.boolVal = arg->val;
            return reg;
        }

        case nil_a: reg->type = nil_m; return reg;

        case userfunc_a: {
            reg->type = userfunc_m;
            reg->data.funcVal = arg->val;
            return reg;
        }

        case libfunc_a: {
            reg->type = libfunc_m;
            reg->data.libfuncVal = libfuncs_getused(arg->val);
            return reg;
        }
        
        //case label_a: return NULL;

        default: assert(0);
    }
}

char *
libfuncs_getused(unsigned index) {
	assert(consts_libfuncs[index]);
	assert(index >= 0 && index <= clibs_index);

    return consts_libfuncs[index];
}

void
execute_cycle(void) {
    while(1) {
        if(executionFinished)
            return;
        if(pc == AVM_ENDING_PC) {
            executionFinished = 1;
            return;
        }
        assert(pc < AVM_ENDING_PC);
        instruction *instr = instructions + pc;
        assert(
            instr -> opcode >= 0 &&
            instr -> opcode <= AVM_MAX_INSTRUCTIONS
        );
        if(instr->srcLine) {
            currLine = instr -> srcLine;
			
		}
        unsigned oldPC = pc;
        (*executeFuncs[instr->opcode])(instr);
        if(pc == oldPC)
            ++pc;
    }

}

extern void
memclear_string (avm_memcell *m) {
    assert(m->data.strVal);
	m -> data.strVal = NULL;
}

extern void
memclear_table (avm_memcell *m) {
	avm_table *t = m->data.tableVal;
	assert(t);
    avm_tabledecrefcounter(t);
}

void
execute_assign(instruction *instr) {
    avm_memcell* lv = avm_translate_operand(&instr -> result, (avm_memcell *) 0);
    avm_memcell* rv = avm_translate_operand(&instr -> arg1, &ax);
    
	assert(lv && (&avm_stack[AVM_STACKSIZE-1] >= lv && lv >= &avm_stack[top]) || lv == &retval);
    assert(rv);

    
    avm_assign(lv,rv);
}

void
avm_assign (avm_memcell *lv, avm_memcell *rv) {
    if(lv == rv)
        return;

    if(lv->type == table_m &&
        rv->type == table_m &&
        lv -> data.tableVal == rv -> data.tableVal
    ) {
        return;
	}
    if(rv ->type == undef_m)
        avm_warning("WARNING:assigning from 'undef' content!");
	
	avm_memcellclear(lv);
	
	memcpy(lv,rv,sizeof(avm_memcell));

	if(lv->type == string_m) {
		lv->data.strVal = rv -> data.strVal;
	}
	else
	if (lv->type == table_m) {
		avm_tableincrefcounter(lv->data.tableVal);
	}
}

void
execute_call (instruction *instr) {
    avm_memcell *func = avm_translate_operand(&instr -> result, &ax);
    assert(func);
    switch(func->type) {
        case userfunc_m: {
		    avm_callsaveenvironment();

            pc = func->data.funcVal;
            assert(pc < AVM_ENDING_PC);
            assert(instructions[pc].opcode == funcenter_v);
            break;
        }
        case string_m: {
    			avm_callsaveenvironment();
				avm_calllibfunc(func->data.strVal); 
				break;
		}
        case libfunc_m: { 
    		avm_callsaveenvironment();

			avm_calllibfunc(func->data.libfuncVal); 
			break; 
		}
		case table_m: {
			assert(func -> type == table_m);
			
			functor_call(instr -> result,avm_tablegetelement(func -> data.tableVal, "()"));
			break;
		}
		
        default: {
            char s[100];
			sprintf(s,"ERROR: cannot bind to function %d!\n", instr -> srcLine);
            avm_error(s);
            executionFinished = 1;
        }
    }
}

void functor_call(vmarg func,avm_memcell *value) {
	if(value -> type == userfunc_m) {
		// Pass this table as an argument
		instruction t;
		t.result = func;
		t.opcode = pusharg_v;
		execute_pusharg(&t);

		avm_callsaveenvironment();
		pc = value -> data.funcVal;
		assert(pc < AVM_ENDING_PC);
		assert(instructions[pc].opcode == funcenter_v);
	} else if(value->type == table_m){
		functor_call(func,avm_tablegetelement(value -> data.tableVal, "()"));
	}
	else {
		avm_error("ERROR:incorrect functor call!");
	}
}

avm_memcell *
avm_tablegetelement(avm_table *t,const char *el) {
	unsigned h_key = avm_hash_str(el);
	avm_table_bucket *it = t -> strIndexed[h_key];
	while(it != NULL) {
		if(!strcmp(it -> key.data.strVal, el)) {
			return &it -> value;
		}

		it = it -> next;
	}
}

void
avm_dec_top(void) {
    if(!top) {
        avm_error("ERROR:stack_overflow");
        executionFinished = 1;
    }
    else
        --top;
}

void
avm_push_envvalue (unsigned val) {
    avm_stack[top].type         = number_m;
    avm_stack[top].data.numVal  = val;
    avm_dec_top();
}

void avm_callsaveenvironment(void) {
	assert(top < AVM_STACKSIZE );
    avm_push_envvalue(totalActuals);
    avm_push_envvalue(pc+1);
    avm_push_envvalue(top+totalActuals+2);
    avm_push_envvalue(topsp);
}




void execute_funcenter (instruction *instr) {
    avm_memcell *func = avm_translate_operand(&instr->result, &ax);
    assert(func);

    assert(pc == func->data.funcVal);

    totalActuals = 0;
    userfunc* funcInfo = avm_getfuncinfo(pc);
    topsp = top;
    top = top - funcInfo -> localSize;
}

unsigned avm_get_envvalue (unsigned i) {
    assert(avm_stack[i].type == number_m);
    unsigned val = (unsigned) avm_stack[i].data.numVal;
    assert(avm_stack[i].data.numVal == ((double) val));
    return val;

}

void execute_funcexit (instruction *unused) {
    unsigned oldTop = top;
    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    while( oldTop <= top) {
		
       	avm_memcellclear(&avm_stack[oldTop]);
		oldTop ++;
    }
}

void avm_calllibfunc(char *id) {
    library_func_t f = avm_getlibraryfunc(id);
    if (!f) {
        avm_error("ERROR:unsupported lib func called!");
        executionFinished = 1;
    }
    else {
        topsp = top;
        totalActuals = 0;
        (*f)();
        if(!executionFinished)
            execute_funcexit((instruction *) 0);
    }
}

unsigned avm_totalactuals(void) {
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

struct avm_memcell *avm_getactual (unsigned i) {
    assert( i < avm_totalactuals());
    return &avm_stack[AVM_STACKENV_SIZE + topsp  + 1 + i];
}

void libfunc_print(void) {
    unsigned n = avm_totalactuals();
    unsigned i;

	//printf("%d\n", n);
    for(i = 0; i < n; i++) {
        
        avm_memcell *m = avm_getactual(i);
        //printf("%d, %d. %d\n", m, &avm_stack[AVM_STACKSIZE-1], &avm_stack[top]);
        char *s = avm_tostring(m);
        fprintf(stdout, "%s", s);
		s = NULL;

    }
}

void libfunc_objectmemberkeys() {
	unsigned n = avm_totalactuals();
    
    struct avm_table_bucket *it;
    unsigned num_elem = 0;
    unsigned i;

	if(n!=1)
		avm_warning("WARNING:multiple arguments in 'objectmemberkeys'");
	else {  
	    struct avm_table *new_table = avm_tablenew();   
    	avm_memcell *actual = avm_getactual(0);
		avm_table *t = actual -> data.tableVal;
		
        for( i = 0; i < AVM_TABLE_HASHSIZE; i++) {
            if(t -> strIndexed[i] != NULL) {
                it = t->strIndexed[i];
                while(it != NULL) {
                    avm_memcell *key = (avm_memcell *) malloc(sizeof(avm_memcell));
                    key -> type = number_m;
                    key -> data.numVal = num_elem;
                    num_elem++;
                    
                    avm_memcell *value = (avm_memcell *) malloc(sizeof(avm_memcell));
                    value -> type = string_m;
                    value -> data.strVal = strdup(it -> key.data.strVal);
                    avm_tablesetelem(new_table, key, value);

                    it = it -> next;
                }
            }
            if(t -> numIndexed[i] != NULL) {
                it = t->numIndexed[i];
                while(it != NULL) {
                    avm_memcell key,value;
                    key.type = number_m;
                    key.data.numVal = num_elem;
                    num_elem++;

                    value.type = number_m;
                    value.data.numVal = it -> key.data.numVal;

                    avm_tablesetelem(new_table, &key, &value);
                    it = it -> next;
                }
            }
        }

        // Returning table through retval register
        avm_memcellclear(&retval);
        retval.type = table_m;
        retval.data.tableVal = new_table;
	}
		
}

void execute_pusharg (instruction *instr) {
    avm_memcell *arg = avm_translate_operand(&instr -> result, &ax);
    assert(arg);

    avm_assign(&avm_stack[top], arg);
    ++totalActuals;
    avm_dec_top();
}

char *avm_tostring (avm_memcell *m) {
    assert(m->type >= 0 && m->type <= undef_m);
    return (*tostringFuncs[m->type])(m);
}


void execute_arithmetic (instruction *instr) {
    avm_memcell *lv = avm_translate_operand(&instr -> result, (avm_memcell *) 0);
    avm_memcell *rv1 = avm_translate_operand(&instr->arg1,&ax);
    avm_memcell *rv2 = avm_translate_operand(&instr -> arg2, &bx);

    assert(lv && (&avm_stack[AVM_STACKSIZE-1] >= lv && lv > &avm_stack[top]) || lv == &retval);
    assert(rv1 && rv2);

    if(rv1 -> type != number_m || rv2 -> type != number_m) {
        avm_error ("ERROR:not a number in arithmetic!");
        executionFinished = 1;
    }
    else {
        arithmetic_func_t op = arithmeticFuncs [instr->opcode - add_v];
        avm_memcellclear(lv);
        lv->type        = number_m;
        lv->data.numVal = (*op) (rv1 ->data.numVal, rv2 ->data.numVal);
    }
}


unsigned char number_tobool (avm_memcell *m) {return m->data.numVal != 0;}
unsigned char string_tobool (avm_memcell *m) {return m->data.strVal[0] != 0;}
unsigned char bool_tobool (avm_memcell *m) {return m->data.boolVal;}
unsigned char table_tobool (avm_memcell *m) {return 1;}
unsigned char userfunc_tobool (avm_memcell *m) {return 1;}
unsigned char libfunc_tobool (avm_memcell *m) {return 1;}
unsigned char nil_tobool (avm_memcell *m) {return 0;}
unsigned char undef_tobool (avm_memcell *m) {return 0;}

tobool_func_t toboolFuncs[] = {
	number_tobool,
	string_tobool,
	bool_tobool,
	table_tobool,
	userfunc_tobool,
	libfunc_tobool,
	nil_tobool,
	undef_tobool
};

unsigned char
avm_tobool (avm_memcell *m) {
	assert(m -> type >= 0 && m -> type < undef_m);
	return (*toboolFuncs[m->type])(m);
}

char* typeStrings[] = {
	"number",
	"string",
	"bool",
	"table",
	"userfunc",
	"libfunc",
	"nil",
	"undef"
};



bool compare_eq_number(avm_memcell *r1, avm_memcell *r2) {return r1->data.numVal == r2->data.numVal;}
bool compare_eq_string (avm_memcell *r1, avm_memcell *r2) { return !strcmp(r1->data.strVal, r2->data.strVal);}
bool compare_eq_bool (avm_memcell *r1, avm_memcell *r2) { return r1->data.boolVal == r2->data.boolVal ;}
bool compare_eq_table (avm_memcell *r1, avm_memcell *r2) { return r1->data.tableVal == r2->data.tableVal;}
bool compare_eq_userfunc (avm_memcell *r1, avm_memcell *r2) {return r1->data.funcVal == r2->data.funcVal;}
bool compare_eq_libfunc (avm_memcell *r1, avm_memcell *r2) { return !strcmp(r1->data.strVal, r2->data.strVal);}
bool compare_eq_nil (avm_memcell *r1, avm_memcell *r2) {assert(0);}
bool compare_eq_undef (avm_memcell *r1, avm_memcell *r2) {assert(0);}

compare_type_t compareinstrFuncs[] = {
	compare_eq_number,
	compare_eq_string,
	compare_eq_bool,
	compare_eq_table,
	compare_eq_userfunc,
	compare_eq_libfunc,
	compare_eq_nil,
	compare_eq_undef
};


void libfunc_typeof(void) {
	unsigned n = avm_totalactuals();

	if(n!=1)
		avm_error("ERROR:one argument expected in 'typeof'!");
	else {
		avm_memcellclear(&retval);
		retval.type = string_m;
		retval.data.strVal = typeStrings[avm_getactual(0)->type];
	}
}

void execute_newtable (instruction *instr) {
	avm_memcell *lv = avm_translate_operand(&instr -> result, (avm_memcell *) 0);
	assert(lv && (&avm_stack[AVM_STACKSIZE-1] >= lv && lv > &avm_stack[top] || lv == &retval));

	//avm_memcellclear(lv);
	lv->type			= table_m;
	lv->data.tableVal	= avm_tablenew();
	avm_tableincrefcounter(lv->data.tableVal);
}

void execute_tablegetelem(instruction* instr) {

	avm_memcell* lv = avm_translate_operand(&instr -> result, (avm_memcell*) 0);
	avm_memcell* t = avm_translate_operand(&instr -> arg1, (avm_memcell*) 0);
	avm_memcell* i = avm_translate_operand(&instr -> arg2, &ax);
	

	assert((lv && &avm_stack[AVM_STACKSIZE - 1] >= lv && lv > &avm_stack[top]) || lv ==&retval);
	assert(t && &avm_stack[AVM_STACKSIZE - 1] >= t && t > &avm_stack[top]);
	assert(i);
	
	//avm_memcellclear(lv);
	lv -> type = nil_m; /* Default value. */
	
	if(t -> type != table_m)
		avm_error("ERROR:illegal use of type as table");
	else {
		avm_memcell* content = avm_tablegetelem(t->data.tableVal, i);
		if(content)
			avm_assign(lv,content);
		else {
			//char *ts = avm_tostring(t);
			//char *is = avm_tostring(i);
			//avm_warning("%s[%s] not found!", ts, is);
			char s[100];
			sprintf(s,"\nWARNING:index of table not found! %d\n", instr -> srcLine);
			avm_warning(s);
            //free(ts);
			//free(is);
		}
	}
}

void execute_tablesetelem(instruction* instr)
{
	avm_memcell* t = avm_translate_operand(&instr -> result, (avm_memcell*) 0);
	avm_memcell* i = avm_translate_operand(&instr -> arg1, &ax);
	avm_memcell* c = avm_translate_operand(&instr -> arg2, &bx);
	
	assert(t && &avm_stack[AVM_STACKSIZE - 1] >= t && t > &avm_stack[top]); //why don't we check retval reg? : because you never assign retval to table immediately(goes through temp first)
	assert(i && c);
	
	//assert(t -> type == table_m);
	if(t -> type != table_m)
		avm_error("ERROR:illegal use of type as table!");
	else {
        avm_tablesetelem(t->data.tableVal, i, c);
    }
}



void avm_initialize(void){
	
	avm_initavm_stack();
/*
	avm_registerlibfunc("print",libfunc_print);
	avm_registerlibfunc("typeof",libfunc_typeof);
	avm_registerlibfunc("input",libfunc_input);
	avm_registerlibfunc("objectmemberkeys",libfunc_objectmemberkeys);
	avm_registerlibfunc("objecttotalmembers",libfunc_objecttotalmembers);
	avm_registerlibfunc("objectcopy",libfunc_objectcopy);
	avm_registerlibfunc("totalarguments",libfunc_totalarguments);
	avm_registerlibfunc("argument",libfunc_argument);
	avm_registerlibfunc("strtonum",libfunc_strtonum);
	avm_registerlibfunc("sqrt",libfunc_sqrt);
	avm_registerlibfunc("cos",libfunc_cos);
	avm_registerlibfunc("sin",libfunc_sin);*/
}

void libfunc_totalarguments(void) {
	/* Get topsp of previous activation record.
	*/
	
	unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);
	
	if(!p_topsp) { /* if 0,no previous activation record */
		avm_error("ERROR:'totalarguments' called outside a function!");
		retval.type = nil_m;
	}
	else {
		/* Extract the number of actual arguments for the previous 
			activation record. */
		retval.type = number_m;
		retval.data.numVal = avm_get_envvalue(p_topsp + AVM_NUMACTUALS_OFFSET);
	}
}


int avm_hash_num(int x) {
	if(x < 0) {
        avm_error("ERROR: negative index found!\n");
    }
    // Uncomment this if you want to run for negative indices
    // if(x < 0) {
    //     x = x * (-1);
    // }
    return ((x+257)*11) % AVM_TABLE_HASHSIZE;
}

unsigned
avm_hash_str(const char *key) {
	int length = strlen(key), i;
	unsigned int hash_value = 0;
	for(i = 0; i < length; i++) {
		hash_value += key[i];
		hash_value = (hash_value * key[i]) % AVM_TABLE_HASHSIZE;
	}

	return hash_value;
}

avm_memcell *
avm_tablegetelem (avm_table* table, avm_memcell *index) {
	assert(table);

	avm_table_bucket *it;  
	if(index->type == string_m) {
		unsigned key = avm_hash_str(index->data.strVal);
		it = table -> strIndexed[key];
		while(it != NULL) {
			if(!strcmp(it -> key.data.strVal,index->data.strVal)) {
				return &(it -> value);
			}

			it = it -> next;
		}
	}
	else
	if(index->type == number_m) {
		unsigned key = avm_hash_num( index->data.numVal);
		it = table -> numIndexed[key];

		while(it != NULL) {
			if(it -> key.data.numVal == index->data.numVal) {
				return &(it -> value);
			}

			it = it -> next;
		}
	}

	return NULL;
}


void
dup_memcell(struct avm_memcell *des,struct avm_memcell *src) {
    switch(src -> type) {
        case number_m:  des->data.numVal = src ->data.numVal; des->type = number_m;  break;
        case string_m: des ->data.strVal = strdup(src->data.strVal); des->type = string_m;  break;
        case table_m: des -> data.tableVal = src -> data.tableVal; des->type = table_m; break;
		case bool_m: des -> data.boolVal = src -> data.boolVal; des->type = bool_m; break;
		case userfunc_m: des -> data.funcVal = src -> data.funcVal; des->type = userfunc_m; break;
		case libfunc_m: assert(src -> data.libfuncVal); des -> data.libfuncVal = strdup(src->data.libfuncVal); des->type = libfunc_m;break;
		case nil_m:	des -> type = nil_m; break;
		case undef_m: des -> type = undef_m; break;
		default: printf("%d\n", src->type); assert(0); return;
    }
}

// void 
// dup_key(struct avm_memcell *des,struct avm_memcell *src) {
// 	switch(src->type) {
// 		case number_m: des->data.numVal = src->data.numVal; des->type = number_m; break;
// 		case string_m: assert(src->data.strVal);des ->data.strVal = strdup(src->data.strVal); des->type = string_m;  break;
// 		default: avm_error("ERROR:unknown type of index\n");break;
// 	}
// }


void
avm_tablesetelem(struct avm_table *t, struct avm_memcell *key, struct avm_memcell *value) {
	avm_table_bucket *it;
	avm_table_bucket *new_bucket = (avm_table_bucket *)malloc(sizeof(avm_table_bucket));
	
	if(key->type == number_m) {
		new_bucket -> key.data.numVal = key -> data.numVal;
		new_bucket -> key.type = number_m;
		// avm_assign(&new_bucket -> key, key);
	}
	else if(key->type == string_m){
		new_bucket -> key.data.strVal = strdup(key -> data.strVal);
		new_bucket -> key.type = string_m;
		// avm_assign(&new_bucket -> key, key);
	}
	else {
		avm_error("ERROR:unsupported index type\n");
	}

	if(value -> type == nil_m) {
		/* ignore nil elements */
	}
	else {
		dup_memcell(&new_bucket -> value, value);
		// avm_assign(&new_bucket -> value, value);

		assert(key->type == number_m || key->type == string_m);
		if ( key -> type == number_m )
		{
			unsigned h_key = avm_hash_num(key->data.numVal);

			if(t -> numIndexed[h_key] == NULL) {
				new_bucket -> next = NULL;
				t -> numIndexed[h_key] = new_bucket;
			}
			else {
				new_bucket -> next = t->numIndexed[h_key];
				t -> numIndexed[h_key] = new_bucket;
			}
		}
		else
		if ( key -> type == string_m ) {
			unsigned h_key = avm_hash_str(key->data.strVal);
			if(t->strIndexed[h_key] == NULL) {
				new_bucket -> next = NULL;
				t -> strIndexed[h_key] = new_bucket;
			}
			else {
				new_bucket -> next = t->strIndexed[h_key];
				t -> strIndexed[h_key] = new_bucket;
			}
		}


		if(new_bucket->value.type == table_m)
			avm_tableincrefcounter(new_bucket->value.data.tableVal);


   		t -> total++;
	}
}

bool
avm_tablebucketdestroy (avm_table *t, avm_memcell *key) {
	assert(t);

	avm_table_bucket *it, *prev;  
	if(key -> type == string_m) {
		unsigned hkey = avm_hash_str(key -> data.strVal);
		it = t -> strIndexed[hkey];
		prev = t -> strIndexed[hkey];
		while(it != NULL) {
			if(!strcmp(it -> key.data.strVal,key->data.strVal)) {
				if(it == t->strIndexed[hkey] && it -> next == NULL) {
					// This means this is the first and only element in the bucket
					// So we initialize with NULL the bucket
					t->strIndexed[hkey] = NULL;
					avm_memcellclear(&it->key);
					avm_memcellclear(&it->value);
					free(it);
					return 1;
				}

				// If we reach here it means this is not the only element
				// in the bucket, so we must be careful how we delete this element
				// First we change previous element next pointer to point to
				// this element's next pointer, if there is one, then we clear
				// the element
				if(it->next == NULL)
					prev -> next = NULL;
				else
					prev -> next = it -> next;

				avm_memcellclear(&it->key);
				avm_memcellclear(&it->value);
				free(it);
				return 1;
			}

			prev = it;
			it = it -> next;
		}
	}
	else 
	if(key->type == number_m) {
		unsigned hkey = avm_hash_num( key->data.numVal);
		it = t -> numIndexed[hkey];
		prev = t -> numIndexed[hkey];
		while(it != NULL) {
			if(it -> key.data.numVal == key->data.numVal) {
				if(it == t->numIndexed[hkey] && it -> next == NULL) {
					// This means this is the first and only element in the bucket
					// So we initialize with NULL the bucket
					t->numIndexed[hkey] = NULL;
					avm_memcellclear(&it->key);
					avm_memcellclear(&it->value);
					free(it);
					return 1;
				}

				// If we reach here it means this is not the only element
				// in the bucket, so we must be careful how we delete this element
				// First we change previous element next pointer to point to
				// this element's next pointer, if there is one, then we clear
				// the element
				if(it->next == NULL)
					prev -> next = NULL;
				else
					prev -> next = it -> next;

				avm_memcellclear(&it->key);
				avm_memcellclear(&it->value);
				free(it);
				return 1;
			}

			prev = it;
			it = it -> next;
		}
	}

	return 0;
}

int is_digit(char c)
{
	return (c > 47 && c < 58) ;
}


int is_dot(char c)
{
	return c == '.';
}

int is_number(char *s,int type)
{
	unsigned i;
	unsigned length = strlen(s);
	char *num = NULL;
	
	int found_dot = 0;
	int found_dot_at = -1;
	
	if(!type)
		length--;
	
	//valid
	//5.333
	//.333
	//5.333,53535
	//invalid
	//,3123,313
	//
	if(length == 0)
		return 0;
	else if(length == 1 && s[0] == '.')
		return 0;
	for(i = 0; i < length; i++)
	{printf("%c \n",s[i]);
		if(i == 0 && (s[i] == ','))
			return 0;
		else if(!is_digit(s[i]) && !is_dot(s[i]))
			return 0;
		else if(!is_digit(s[i]) && is_dot(s[i]))
		{
			if(found_dot)
				return 0;
			else
				found_dot = 1;
		}
	}
	
	return 1;
	
}

int is_boolean(char *s)
{
	if(!strncmp(s,"true",strlen(s)-1) || !strncmp(s,"false",strlen(s)-1))
		return 1;
	return 0;
}

int is_nil(char *s)
{
	if(!strncmp(s,"nil",strlen(s)-1))
		return 1;
	return 0;
}

char* trim_string(char *s)
{
    unsigned len = strlen(s);
    unsigned i;
    char *trimmed_input = malloc(len*sizeof(char));

    int starts_with = 0;
    int ends_with = 0;
    int index = 0;

    for(i = 0; i < len - 1; i++)
    {
        if(i==0 && s[i] == '"')
        {
            starts_with = 1;
            continue;
        }
        else if(i==len-2  && s[i] == '"')
        {
            ends_with = 1;
            continue;
        }
    }

    if(starts_with && ends_with)
    {
        for(i = 0; i < len - 1; i++)
        {
            if(i==0 && s[i] == '"')
                continue;
            else if(i == len-2  && s[i] == '"')
                continue;
            else
                trimmed_input[index++] = s[i];
        }
        trimmed_input[len - 3] = '\0';
        return trimmed_input;
    }
    else
        return s;

}

void libfunc_input(void)
{
	char *input;
	char *num;
	unsigned length;
	ssize_t len = 0;
	int result = 0;
	
	unsigned i;
	unsigned is_double = 0;
	
	result = getline(&input,&len,stdin);
	if(result == -1)
		avm_error("Failed to read from stdin");
	else
	{
		avm_memcellclear(&retval);
		if(is_number(input,0))
		{
			length = strlen(input);
			num = malloc(length * sizeof(char));
			for(i = 0;i < length-1; i++)
			{
				if(input[i] == ',')
				{
					num[i] = '\0';
					break;
				}
				else
				{
					if(input[i] == '.')
						is_double = 1;
					num[i] = input[i];
				}
			}
			//num[i]='\0';
			
			
			if(is_double)
			{
				retval.type = number_m;
				retval.data.numVal = strtod(num,NULL);
				//should i avm_assign?
			}
			else
			{
				retval.type = number_m;
				retval.data.numVal = strtod(num,NULL);
				//should i avm_assign?
			}
				
			
		}
		else if(is_boolean(input))
		{
			retval.type = bool_m;
			if(input[0] == 't')
				retval.data.boolVal = 1;
			else
				retval.data.boolVal = 0;
		}
		else if(is_nil(input))
		{
			retval.type = nil_m;
		}
		else	
		{
            input = trim_string(input);
            retval.type = string_m;
            retval.data.strVal = strdup(input);
			
		}
	
	}	
}

void libfunc_objecttotalmembers(void)
{
    avm_memcell *param = NULL;
	unsigned total_actuals = avm_totalactuals();
	
	if(!total_actuals)
		avm_error("library function 'objecttotalmembers' expected 1 argument but got none");
	param = avm_getactual(0);
	if(param -> type != table_m)
		avm_error("library function 'objecttotalmembers' expects argument of type table");
	else
	{
		avm_memcellclear(&retval);
		retval.type = number_m;
		retval.data.numVal = param -> data.tableVal -> total;
	}
}
void libfunc_objectcopy(void)
{
	avm_memcell *argument = NULL;
	avm_table *arg_table = NULL;
	avm_table_bucket *arg_tbucket = NULL;
	avm_table_bucket *it = NULL;

	avm_memcell *new_memcell = NULL;
	avm_table *new_table = NULL;
	avm_table_bucket *new_tbucket = NULL;
	avm_table_bucket *new_tbucket_list = NULL;
	avm_table_bucket *curr_tbucket = NULL;

	unsigned i;


	if(avm_totalactuals() < 1)
		avm_error("Libfunction 'Objectcopy' expects one argument and you have given none.");

	argument = avm_getactual(0);
	if(argument -> type != table_m)
		avm_error("Libfunction 'objectcopy' expects argument of type table");
	
	arg_table = argument->data.tableVal;
	
	new_table = avm_tablenew();
	
	for(i = 0; i < AVM_TABLE_HASHSIZE; i++)
	{
		
		if(arg_table -> strIndexed[i] != NULL)
		{
			//create and copy each node
			//append in head
			//connect head to i
			arg_tbucket = arg_table -> strIndexed[i];
			while(arg_tbucket != NULL)
			{
				//CREATE  n COPY	
                
				new_tbucket = malloc(sizeof(struct avm_table_bucket));
				new_tbucket -> key.type = string_m;
				new_tbucket -> key.data.strVal = strdup(arg_tbucket->key.data.strVal);
				new_tbucket -> next = NULL;
                

				if(arg_tbucket->value.type == number_m)
				{
					new_tbucket -> value.type = number_m;
					new_tbucket -> value.data.numVal = arg_tbucket->value.data.numVal;
				}
				else if(arg_tbucket->value.type == string_m)
				{
					new_tbucket -> value.type = string_m;
					new_tbucket -> value.data.strVal = strdup(arg_tbucket->value.data.strVal);
				}
				else if(arg_tbucket->value.type == bool_m)
				{
					new_tbucket -> value.type = bool_m;
					new_tbucket -> value.data.boolVal = arg_tbucket->value.data.boolVal;
				}
				else if(arg_tbucket->value.type == table_m)
				{
					new_tbucket -> value.type = table_m;
					new_tbucket -> value.data.tableVal = arg_tbucket->value.data.tableVal;
				}
				else if(arg_tbucket->value.type == userfunc_m)
				{
					new_tbucket -> value.type = userfunc_m;
					new_tbucket -> value.data.funcVal = arg_tbucket->value.data.funcVal;
				}
				else if(arg_tbucket->value.type == libfunc_m)
				{
					new_tbucket -> value.type = libfunc_m;
					new_tbucket -> value.data.libfuncVal = strdup(arg_tbucket->value.data.libfuncVal);
				}
				else if(arg_tbucket->value.type == nil_m)
					new_tbucket -> value.type = nil_m;
				
				//APPEND TO HEAD
				if(new_tbucket_list == NULL)
				{
					new_tbucket_list = new_tbucket;
					curr_tbucket = new_tbucket;
				}
				else
				{
					curr_tbucket -> next = new_tbucket;
					curr_tbucket = new_tbucket;
				}
				arg_tbucket = arg_tbucket -> next;
			}
			//CONNECT TO I-TH bucket list
			new_table -> strIndexed[i] = new_tbucket_list;
		}
		else
			new_table -> strIndexed[i] = NULL;
		
		//init to NULL
		new_tbucket_list = NULL;
		curr_tbucket = NULL;
		new_tbucket = NULL;
		
		if(arg_table -> numIndexed[i] != NULL)
		{
			//create and copy each node
			//append in head
			//connect head to i
			
		    arg_tbucket = arg_table -> numIndexed[i];
			while(arg_tbucket != NULL)
			{
				//CREATE  n COPY	
				new_tbucket = malloc(sizeof(struct avm_table_bucket));
				new_tbucket -> key.type = number_m;
				new_tbucket -> key.data.numVal = arg_tbucket->key.data.numVal;
				new_tbucket -> next = NULL;
				
				if(arg_tbucket->value.type == number_m)
				{
					new_tbucket -> value.type = number_m;
					new_tbucket -> value.data.numVal = arg_tbucket->value.data.numVal;
				}
				else if(arg_tbucket->value.type == string_m)
				{
					new_tbucket -> value.type = string_m;
					new_tbucket -> value.data.strVal = strdup(arg_tbucket->value.data.strVal);
				}
				else if(arg_tbucket->value.type == bool_m)
				{
					new_tbucket -> value.type = bool_m;
					new_tbucket -> value.data.boolVal = arg_tbucket->value.data.boolVal;
				}
				else if(arg_tbucket->value.type == table_m)
				{
					new_tbucket -> value.type = table_m;
					new_tbucket -> value.data.tableVal = arg_tbucket->value.data.tableVal;
				}
				else if(arg_tbucket->value.type == userfunc_m)
				{
					new_tbucket -> value.type = userfunc_m;
					new_tbucket -> value.data.funcVal = arg_tbucket->value.data.funcVal;
				}
				else if(arg_tbucket->value.type == libfunc_m)
				{
					new_tbucket -> value.type = libfunc_m;
					new_tbucket -> value.data.libfuncVal = strdup(arg_tbucket->value.data.libfuncVal);
				}
				else if(arg_tbucket->value.type == nil_m)
					new_tbucket -> value.type = nil_m;
				
				//APPEND TO HEAD
				if(new_tbucket_list == NULL)
				{
                   

					new_tbucket_list = new_tbucket;
					curr_tbucket = new_tbucket;
                    
				}
				else
				{
					curr_tbucket -> next = new_tbucket;
                    curr_tbucket = new_tbucket;
				}

				arg_tbucket = arg_tbucket -> next;
			}
			//CONNECT TO I-TH bucket list
			new_table -> numIndexed[i] = new_tbucket_list;
		}
		else
			new_table -> numIndexed[i] = NULL;
		
	}
    avm_memcellclear(&retval);
    retval.type = table_m;
    retval.data.tableVal = new_table;
}	


void libfunc_strtonum(void)
{
	unsigned total_actuals = avm_totalactuals();
	avm_memcell *argument = NULL;
	char *param = NULL;
	char *num;
	unsigned i,length,is_double = 0;
	
	
	if(!total_actuals)
		avm_error("library function 'strtonum' expected 1 argument but was given none");
	argument = avm_getactual(0);
	if(argument -> type != string_m)
		avm_error("Argument must be of type 'String'");
	
	param = argument -> data.strVal;
	avm_memcellclear(&retval);
	
	if(is_number(param,1))
	{
		length = strlen(param);
		num = malloc(length * sizeof(char));
		for(i = 0;i < length; i++)
		{
			if(param[i] == ',')
			{
				num[i] = '\0';
				break;
			}
			else
			{
				if(param[i] == '.')
					is_double = 1;
				num[i] = param[i];
			}
		}
		//num[i]='\0';
			
		if(is_double)
		{
			retval.type = number_m;
			retval.data.numVal = strtod(num,NULL);
			//should i avm_assign?
		}
		else
		{
			retval.type = number_m;
			retval.data.numVal = atoi(num);
			//should i avm_assign?
		}
	}
	else
		retval.type = nil_m;
}
void libfunc_sqrt(void)
{
	unsigned total_actuals = avm_totalactuals();
	avm_memcell *param = NULL;
	
	if(!total_actuals)
		avm_error("library function 'sqrt' expected 1 argument but got none");
	param = avm_getactual(0);
	if(param -> type != number_m)
		avm_error("library function 'sqrt' expects argument of type number");
	else
	{
		avm_memcellclear(&retval);
		if(param->data.numVal < 0)
			retval.type = nil_m;
		else
		{
			retval.type = number_m;
			retval.data.numVal = sqrt(param->data.numVal);
		}
	}

}	

void libfunc_cos(void)
{
	unsigned total_actuals = avm_totalactuals();
	avm_memcell *param = NULL;
	double rad,res;
	
	if(!total_actuals)
		avm_error("library function 'cos' expected 1 argument but got none");
	param = avm_getactual(0);
	if(param -> type != number_m)
		avm_error("library function 'cos' expects argument of type number");
	else
	{
		rad = (param -> data.numVal) * (PI / 180.0);
		res = cos(rad);

		avm_memcellclear(&retval);
		retval.type = number_m;
		retval.data.numVal = res;
	}
}

void libfunc_sin(void)
{
	unsigned total_actuals = avm_totalactuals();
	avm_memcell *param = NULL;
	double rad;
	
	if(!total_actuals)
		avm_error("library function 'sin' expected 1 argument but got none");
	param = avm_getactual(0);
	if(param -> type != number_m)
		avm_error("library function 'sin' expects argument of type number");
	else
	{
		avm_memcellclear(&retval);
		rad = ((param -> data.numVal) * PI) / 180;
		retval.type = number_m;
		retval.data.numVal = sin(rad);
	}
}

void libfunc_argument(void)
{
	unsigned total_actuals = avm_totalactuals();
	unsigned pfunc_total_actuals ;
	int pfunc_ith_elem;
	/* Get topsp of previous activations record */
	char *error ;
	
	struct avm_memcell *curr_func = NULL;
	
	
	if(!total_actuals)
		avm_error("ERROR:library function 'argument' expected 1 argument but was given none");
	
	unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
	// avm_memcellclear(&retval);
    
	
	if(!p_topsp) { /* if 0, no previous activation record. */
		//avm_error("'argument' called outside of a function");
		avm_warning("WARNING:library function 'argument' called outside of a function!");
		retval.type = nil_m;
	}
	else
	{
		curr_func = malloc(sizeof(struct avm_memcell));
		if(curr_func == NULL)
				avm_error("ERROR:Failed to allocate memory in 'libfunc_argument'");
		curr_func = avm_getactual(0);//first is 0
		
		if(curr_func -> type != number_m)//must be number
			avm_error("library function 'argument' expects number as a parameter");
		
		
		//i-th element of prev function to get
		pfunc_ith_elem =(int) curr_func ->data.numVal;//cast double to int
		//total locals of prev function
		pfunc_total_actuals = avm_stack[p_topsp + AVM_NUMACTUALS_OFFSET].data.numVal;
		
		if(pfunc_ith_elem < 0)
			avm_error("The number you have given is below 0 and is invalid for parameter index");
		else if(pfunc_ith_elem > pfunc_total_actuals)//if ith element exceeds the num of totals
			avm_error("The function does not have so many arguments");
		else//else assign to retval the memcell of prev topsp + the offset to actuals + 1 to go to first actual + the ith_element
			avm_assign(&retval,&avm_stack[p_topsp + AVM_NUMACTUALS_OFFSET + 1 + pfunc_ith_elem]);
	}
	
}

char *libStrings[] = {
    "print",
    "input",
    "objectmemberkeys",
    "objecttotalmembers",
    "objectcopy",
    "totalarguments",
    "argument",
    "typeof",
    "strtonum",
    "sqrt",
    "cos",
    "sin"
};

userfunc *avm_getfuncinfo(unsigned instrNo) {
    unsigned i;
    for(i = 0; i < userfunc_index; i++) {
        if(consts_userfunc[i].address == instrNo) 
            return &consts_userfunc[i];
    }

    return NULL;
    
}


char * print_avmtable(avm_memcell *m) {
    char *s = "[";
    char *temp1,*temp2, *temp3, *temp4;
    unsigned i;
    avm_table *t = m->data.tableVal;
    avm_table_bucket *it;

    for(i = 0; i < AVM_TABLE_HASHSIZE; i++) {
        if(t -> strIndexed[i] != NULL) {

            it = t -> strIndexed[i];
            while(it != NULL) {
                if(it-> value.type != nil_m) {
                    if( t == it->value.data.tableVal) 
                        temp3 = strdup("self_reference");
                    else 
                            //temp3 = strdup("table");
                        temp3 = avm_tostring(&(it->value));
                }
                temp2 = (char *)malloc(sizeof(char)* (strlen(it->key.data.strVal)+ strlen(temp3)+4));
                strcpy(temp2, "{");
                strcat(temp2,it->key.data.strVal);
                strcat(temp2, ":");
                strcat(temp2, temp3);
                strcat(temp2, "}");
                temp1 = (char *) malloc(sizeof(char) * (strlen(s) + strlen(temp2))+2);
                strcat(temp1, s);
                strcat(temp1,temp2);
                strcat(temp1, ",");
                s = (char *)malloc(sizeof(char) * (strlen(s)+strlen(temp1))+2);
                strcpy(s,temp1);


                // free(temp1);
                // free(temp2);
                // free(temp4);
                it = it -> next;
            }
        }
        if(t -> numIndexed[i] != NULL) {

            it = t -> numIndexed[i];
            while(it != NULL) {
                if(&it -> value == NULL)
                    temp3 = "";
                else {
                    if(it->value.type == table_m && m->data.tableVal == it->value.data.tableVal) 
                        temp3 = strdup("self_reference");
                    else {
                        //temp3 = strdup("table");
                        temp3 = avm_tostring(&(it->value));
                    }
                }    
                temp4 = number_tostring(&it->key);
                temp2 = (char *)malloc(sizeof(char) * (strlen(temp4) + strlen(temp3)+6));

                strcpy(temp2,"{");
                strcat(temp2,temp4);
                strcat(temp2, ":");
                strcat(temp2, temp3);
                strcat(temp2, "}");
                temp1 = (char *) malloc(sizeof(char) * (strlen(s) + strlen(temp2))+3);
                strcat(temp1, s);
                strcat(temp1,temp2);
                strcat(temp1,",");

                s = (char *)malloc(sizeof(char) * (strlen(s)+strlen(temp1))+3);
                strcpy(s,temp1);

                //free(temp4);
                //free(temp3);
                //free(temp2);
                //free(temp1);
                temp4=NULL;
                temp2=NULL;
                temp3=NULL;
                temp1=NULL;

                // free(temp1);
                // free(temp2);
                // free(temp4);
                it = it -> next;
            }
        }
    }


    
    char *final = (char *)malloc(sizeof(char) * ((strlen(s))+3));
    strcat(final, s);
    // free(s);
    if(strlen(s) > 1)
    {
        final[strlen(final)] = ']';
        final[strlen(final)+1] = '\0';
    }
    else
    {
        strcat(final, "]");
       final[strlen(final)+1] = '\0';
    }
    return final;
}

bool isInteger(double v) {
    int ch = (int) v;

    return v == ch;
}

char *number_tostring (avm_memcell *m) {
    assert(m->type == number_m);

    if(isInteger((double)m->data.numVal)) 
        return int_tostring(m);
    
    return float_tostring(m);

}

char *int_tostring (avm_memcell *m) {
    int length = snprintf( NULL, 0, "%d", (int)m -> data.numVal);
    char *s = (char *)malloc(sizeof(char)*(length)+1); 
    sprintf(s,"%d", (int)m -> data.numVal); 
    return s;
}
char *float_tostring (avm_memcell *m) { 
    int length = snprintf( NULL, 0, "%lf", m -> data.numVal);
    char *s = (char *)malloc(sizeof(char)*(length)+1); 
    sprintf(s,"%.3lf", m -> data.numVal);
	return s;
}
char *string_tostring (avm_memcell *m) { return m->data.strVal;}
char *bool_tostring (avm_memcell *m) {if( m->data.boolVal == 0) return strdup("false"); return strdup("true");}
char *table_tostring (avm_memcell *m) { return print_avmtable(m); }
char *userfunc_tostring (avm_memcell *m) {
    userfunc *index = avm_getfuncinfo(m -> data.funcVal);
    if(index == NULL)
        return strdup("");

    return strdup(index -> id);
} 
char *libfunc_tostring (avm_memcell *m) {return strdup(m->data.libfuncVal);}
char *nil_tostring (avm_memcell *m) {return strdup("nil");}
char *undef_tostring (avm_memcell *m) {return strdup("undef");}


tostring_func_t tostringFuncs[]={
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    undef_tostring,
};

library_func_t libraryFuncs[] = {
    libfunc_print,
    libfunc_input,
    libfunc_objectmemberkeys,
    libfunc_objecttotalmembers,
    libfunc_objectcopy,
    libfunc_totalarguments,
    libfunc_argument,
    libfunc_typeof,
    libfunc_strtonum,
    libfunc_sqrt,
    libfunc_cos,
    libfunc_sin
};

int
get_libfuncsindex(char *id) {
    unsigned i;
    for(i = 0; i <= 11; i ++) {
        if(!strcmp(id, libStrings[i])) {
            return i;
        }
    }
    assert(0);
    return 0;
}

library_func_t 
avm_getlibraryfunc(char *id) {
    return libraryFuncs[get_libfuncsindex(id)];
}

int main(int argc, char *argv[]) {


    FILE *yyout = stdout;
    
    max_index_global = 0;

	load_avmbinaryfile();
    avm_initialize();
	// display_instructions(yyout);

    execute_cycle();
}