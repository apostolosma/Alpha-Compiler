
/*
        Apostolos Mavrogiannakis csd3799
        Varsamis Haralampos csd3744
        Georgia Rapousi csd3836
*/


%{
#include "lib.h"
#include "parser.h"

int lines = 1;
int tokeno = 0;
int nested_lvl = 0;


int b_start = 0;
int valid_string = 1;
char *my_string = "";
%}

%option noyywrap
%option yylineno

DIGIT		[0-9]
LETTER		[A-Za-z]
SPACE		[\n \t\v]
UNDERSCORE	_
NL		\"\n\"
LINE		\n
IDENTIFIER	[A-Za-z][A-Za-z0-9_]*
COMMENT1	"//".*

%x COMMENT INCLUDE

%x STRING


%%
"EXIT;" {return EXIT_COMMAND;}

if      {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "KEYWORD","enumerated"); return IF;}
else        {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "KEYWORD","enumerated"); return ELSE;}
while       {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "KEYWORD","enumerated"); return WHILE;}
for     {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "KEYWORD","enumerated"); return FOR;}
function    {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "KEYWORD","enumerated"); return FUNCTION;}
return      {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "KEYWORD","enumerated"); return RETURN;}
break       {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "KEYWORD","enumerated"); return BREAK;}
continue    {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "KEYWORD","enumerated"); return CONTINUE;}
and     {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "KEYWORD","enumerated"); return AND;}
not     {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "KEYWORD","enumerated"); return NOT;}
or      {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "KEYWORD","enumerated"); return OR;}
local       {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "KEYWORD","enumerated"); return LOCAL;}
true        {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "KEYWORD","enumerated"); return TRUE;}
false       {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "KEYWORD","enumerated"); return FALSE;}
nil     {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "KEYWORD","enumerated"); return NIL;}


{NL}            {fprintf(yyout,"%s",yytext);}
{LINE}          {++lines;}
{SPACE}		{}

{IDENTIFIER}        {tokeno++;fillStruct(yylval, yylineno, tokeno, 0, yytext, "IDENTIFIER","char*");return ID;}


\"                  { BEGIN(STRING); my_string = ""; }
<STRING>[^\\/"]*   { my_string = appendString(yytext); }
<STRING>[/]*	   { my_string = appendString(yytext);}
<STRING>\\\"         { my_string = appendString("\"");}
<STRING>\\n         { my_string = appendString("\n"); }
<STRING>\\t         { my_string = appendString("\t"); }
<STRING>\\a          { my_string = appendString("\a");}
<STRING>\\b          { my_string = appendString("\b");}
<STRING>\\e          { my_string = appendString("\e");}
<STRING>\\f          { my_string = appendString("\f");}
<STRING>\\r          { my_string = appendString("\r");}
<STRING>\\v          { my_string = appendString("\v");}
<STRING>\\\\          { my_string = appendString("\\");}
<STRING>\\'          { my_string = appendString("'");}
<STRING>\\?          { my_string = appendString("?");}
<STRING><<EOF>>     {   BEGIN(INITIAL); fprintf(stderr,"UNTERMINATED STRING.\n"); return -2;}
<STRING>\"          {  BEGIN(INITIAL); tokeno++; if(valid_string) {fillStruct(yylval, yylineno, tokeno, 0, my_string, "STRING","char *");} else { fillStruct(yylval, yylineno, tokeno, 0, "WARNING: IGNORING STRING, UNRECOGNISED ESCAPE CHARACTER.\n", "","char *"); return -1;} return STRIN; }
<STRING>\\.         { tokeno++; valid_string = 0;}



"/*"			{BEGIN(COMMENT);list_size++; tokeno++;yylval->numToken=tokeno;yylval->numline=lines;}
<COMMENT>"/"+"*"	{tokeno++;list_size++;nested_lvl++;insert_nest_token();}
<COMMENT>[^/*\n]*	
<COMMENT>"*"+[^*/\n]*	
<COMMENT>\n             ++lines;
<COMMENT><<EOF>> 	{return 1;}
<COMMENT>"*"+"/"	{if(nested_lvl>0){nested_lvl--;updateNestStruct(yylineno);}else{BEGIN(INITIAL);fillStruct(yylval,yylval->numline,yylval->numToken,yylineno,"BLOCK_COMMENT","COMMENT","enumerated");}}

{COMMENT1}      {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, "", "INLINE_COMMENT","enumerated");}

{DIGIT}+        {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "INTEGER","int"); return INT;}
{DIGIT}+"."{DIGIT}* {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "REAL","float"); return REAL;}
"="         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "EQUAL", "enumerated"); return EQUAL;}
"+"         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "PLUS", "enumerated"); return PLUS;}
"-"         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "MINUS", "enumerated"); return MINUS;}
"*"         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "MUL", "enumerated"); return MUL;}
"/"         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "DIVISION", "enumerated"); return DIV;}
"%"         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "PERCENT", "enumerated"); return MOD;}
"=="            {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "DOUBLE_EQUAL", "enumerated"); return DE;}
"!="            {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "UNEQUAL", "enumerated"); return UNEQUAL;}
"++"            {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "PLUS_PLUS", "enumerated"); return DPLUS;}
"--"            {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "MINUS_MINUS", "enumerated"); return DMINUS;}
">"         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "GREATER THAN", "enumerated"); return GT;}
"<"         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "LESS THAN", "enumerated"); return LT;}
">="            {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "GREATER_EQUAL", "enumerated"); return GE;}
"<="            {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "LESS_EQUAL", "enumerated"); return LE;}
"{"         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "LEFT_CURLY_BRACKET", "enumerated"); return LCURBRA;}
"}"         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "RIGHT_CURLY_BRACKET", "enumerated"); return RCURBRA;}     
"["         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "LEFT_BRACKET", "enumerated"); return LBRA;}
"]"         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "RIGHT_BRACKET", "enumerated"); return RBRA;}
"("         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "LEFT_PARENTHESIS", "enumerated"); return LPAREN;}
")"         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "RIGHT_PARENTHESIS", "enumerated"); return RPAREN;}
";"         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "SEMICOLON", "enumerated"); return SEMICOLON;}
","         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "COMMA", "enumerated"); return COMMA;}
":"         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "COLON", "enumerated"); return COLON;}
"::"            {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "DOUBLE_COLON", "enumerated"); return DCOLON;}
"."         {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "DOT", "enumerated"); return DOT;}
".."            {tokeno++; fillStruct(yylval, yylineno, tokeno, 0, yytext, "DOUBLE_DOT", "enumerated"); return DDOT;}

.			{fprintf(yyout, "UNDEFINED CHARACTER %s IN LINE %d\n", yytext, yylineno); return UNDEF_CHAR;}


%%

void updateNestStruct(unsigned int endline)
{
	struct alpha_token_t *tmp=NULL;
	struct alpha_token_t *tmp_p=NULL;
	tmp=comments;
	while(tmp!=NULL)
	{	
		if(tmp->endline==0)
		{
			tmp_p=tmp;
		}
		tmp=tmp->alpha_yylex;
	}

	//3rd n 4th are just for debug cases.
	if(tmp_p !=NULL)
	{
		//in valid forms,tmp_p will always be !=NULL.
		tmp_p->endline=endline;
	}
	else if(tmp_p==NULL && tmp!=NULL)
	{
		//error?CAN we reach here?
		//1)tmp==comments && endline not 0.Which means we have more
		//block comment ending */.But i don't think we can reach here cuz of nested lvl.
		printf("else if error in update\n");
	}
	else
	{
		//error
		printf("else error in update\n");
	}
}


void fillStruct(struct alpha_token_t *yylval, unsigned int numline, unsigned int numToken, unsigned int endline, char *content, char *type,char* comment)
{
	yylval -> content = strdup(content);//content;
	yylval -> numToken = numToken;
	yylval -> numline = numline;
	yylval -> type = strdup(type);
	yylval -> endline = endline;
	yylval->alpha_yylex=NULL;
	
	yylval -> comment = strdup(comment);
	
}

void insert_nest_token()
{
	struct alpha_token_t *new_nest=malloc(sizeof(struct alpha_token_t));
	assert(new_nest != NULL);	

	if(nested_lvl>0)
        {
                new_nest->content = "BLOCK_COMMENT";
                new_nest->type = "NESTED_COMMENT";
                new_nest->numline=lines;
				new_nest->comment="enumerated";
		new_nest->endline=0;
                new_nest->numToken=tokeno;
		new_nest->alpha_yylex=NULL;
        }
        else
        {
                new_nest->content = "BLOCK_COMMENT";
                new_nest->type = "COMMENT";
                new_nest->numline = lines;
				new_nest->comment="enumerated";
				new_nest->endline=0;
                new_nest->numToken = tokeno;
				new_nest->alpha_yylex = NULL;
        }

	if(comments==NULL)
	{
		comments = new_nest;
		last_comment= new_nest;
	}
	else
	{
		last_comment->alpha_yylex=new_nest;
		last_comment=new_nest;
	}

}

char *appendString(char *appendingString) {
    char *new_string = (char *)malloc(strlen(appendingString) + strlen(my_string)+1);

    strcat(new_string,my_string);
    strcat(new_string,appendingString);

    my_string = NULL;
    appendingString = NULL;

    return new_string;
}
