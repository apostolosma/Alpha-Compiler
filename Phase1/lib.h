#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define YY_DECL int alpha_yylex(struct alpha_token_t *yylval)

#define EOF_COM -2
#define EOF_STR -3
#define VAL_COM	2
#define VAL_TOK 1
#define UNK_ESC_CHAR -1
#define UNDEF_CHAR -4

/*

	CSD3744 HARALAMBOS VARSAMIS
	CSD3836 GEORGIA RAPOUSI
	CSD3799 APOSTOLOS MAVROGIANNAKIS

*/

struct alpha_token_t *H;
struct alpha_token_t *comments;
struct alpha_token_t *last_comment;
struct alpha_token_t *last_H;


int list_size;

struct alpha_token_t {
	unsigned int	numline;
	unsigned int	numToken;
	unsigned int	endline;
	char		*content;
	char		*type;
	char		*comment;

	struct alpha_token_t	*alpha_yylex;
};

void insert(struct alpha_token_t *t);
//void fillStruct(struct alpha_token_t *yylval, unsigned int numline, unsigned int numToken, unsigned int endline, char *content, char *type);
void fillStruct(struct alpha_token_t *yylval, unsigned int numline, unsigned int numToken, unsigned int endline, char *content, char *type, char *comment);
char *appendString(char *appendingString);
int getSize();

void updateNestStruct(unsigned int endline);
void insert_nest(struct alpha_token_t *t);
void insert_nest_token();
void print(struct alpha_token_t *first);
void printH();
