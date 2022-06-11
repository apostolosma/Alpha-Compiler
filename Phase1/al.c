
#include "lib.h"

extern int alpha_yylex(void* yyval);
extern int yylineno;
extern char* yytext;
extern FILE *yyin, *yyout;

int main(int argc, char *argv[]) {
	int ntoken=2;
	/* Initialize list. */
	H = NULL;
	comments=NULL;
	last_comment=NULL;
	last_H=NULL;
	list_size = 0;

	if(argc >= 2) {
		yyin = fopen(argv[1], "r");
		if(argc == 3) {
			yyout = fopen(argv[2], "w");
		} else {
			yyout = stderr;
		}
	}	
	fprintf(yyout,"---------------------------- Lexical Analysis ----------------------------\n");

	
	struct alpha_token_t *token=malloc(sizeof(struct alpha_token_t));
	token->alpha_yylex=NULL;
	ntoken = alpha_yylex(token);
	while(ntoken) {

		if(ntoken == 0)	break;
		else if(ntoken == VAL_COM) {
			// This is a block comment
			print(token);
			insert_nest(token);
		} else if(ntoken == EOF_COM){
			fprintf(stderr,"End of file has been reached and comment end has not been reached\n");
			return 0;
		} else if(ntoken == UNK_ESC_CHAR){
			fprintf(yyout, "%d:\t\t\t#%d\t\t\t%s\n",token->numline, token->numToken, token->content);
			ntoken = 1;
			return 0;
		}
		else if(ntoken == VAL_TOK){
			fprintf(yyout,"%d:\t\t\t#%d\t\t\t%s\t\t\t\"%s\"\t<-%s\n",token->numline, token->numToken, token->content, token->type, token->comment);
			insert(token);
		} else if(ntoken == EOF_STR || ntoken == UNDEF_CHAR) {
			return 0;
		}
		
		token=malloc(sizeof(struct alpha_token_t));
		ntoken = alpha_yylex(token);

	}
	printH();
	//printf("GETSIZE: %d\n",getSize());
}

void insert(struct alpha_token_t *t) {

	struct alpha_token_t *tmp_p;
	struct alpha_token_t *tmp;
	tmp=malloc(sizeof(struct alpha_token_t));
	tmp->content=strdup(t->content);
	tmp->type=strdup(t->type);
	tmp->comment=strdup(t->comment);
	tmp->numline=t->numline;
	tmp->endline=t->endline;
	tmp->numToken=t->numToken;

	if(H == NULL) {
		H = tmp;
		last_H=tmp;
	} else {
		//last version using last elements ,with the last_H=t
		last_H->alpha_yylex=tmp;
		last_H=tmp;
		
	}

	list_size++;
}

void insert_nest(struct alpha_token_t *t)
{

	if(comments==NULL)
	{
		comments=t;
		last_comment=t;
	}
	else
	{
		t->alpha_yylex=comments;
		comments=t;

	}

	if(H==NULL)
	{
		H=comments;
		last_H=last_comment;
	}
	else
	{
		struct alpha_token_t *tmpprev=NULL;
		struct alpha_token_t *tmp=comments;

		last_H->alpha_yylex=comments;
		last_H=last_comment;
	}
	comments=NULL;
	last_comment=NULL;
}

void print(struct alpha_token_t *first)
{
	struct alpha_token_t *token=NULL;
	token=comments;

	fprintf(yyout, "%d:\t\t\t#%d\t\t\t%d-%d\t\t\t%s\t\t\t%s\t\t\t<-%s\n", first->numline,first->numToken, first->numline, first->endline, first->content, first->type,first->comment);
	while(token!=NULL)
	{
		fprintf(yyout, "%d:\t\t\t#%d\t\t\t%d-%d\t\t\t%s\t\t\t%s\t\t\t<-%s\n", token->numline,token->numToken, token->numline, token->endline, token->content, token->type,token->comment);
		token=token->alpha_yylex;
	}

}

void printH()
{
	struct alpha_token_t *token=NULL;
        token=H;
	//Chaos.
        while(token!=NULL)
        {
		if(strcmp(token->content,"BLOCK_COMMENT")==0)
		{
                	printf("%d: #%d %d-%d %s %s <-%s\n", token->numline,token->numToken, token->numline, token->endline, token->content, token->type,token->comment);
                }
		else
		{

			printf("%d: #%d %s %s <-%s\n",token->numline, token->numToken, token->content, token->type,token->comment);
		}
		token=token->alpha_yylex;
        }

}

int getSize() {
	return list_size;
}


