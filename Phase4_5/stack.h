/*
	Georgia Rapousi csd3836
	Varsamis Haralampos csd3744
	Apostolos Mavrogiannakis csd3799
*/

#ifndef __STACK_H_
#define __STACK_H_
#endif


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define PAIR_EXPR_SIZE sizeof(struct pair_expr)


typedef struct item {
    int item;
    struct item *next;
}item;

typedef struct pair {
    struct pair_expr *item;
    struct pair *next;
}pair;


typedef struct bunch {
    struct expr *item;
    struct bunch *next;
}bunch;

typedef struct stack {
    int size;
    item *items;
    item *top;
}stack;

typedef struct stack_expr {
    int size;
    bunch *items;
    bunch *top;
} stack_expr;



typedef struct stack_pair {
    int size;
    pair *items; // each item is <pair item, pair next>
    pair *top;
}stack_pair;

stack *create_stack(void);

stack_expr *create_stack_expr(void);

stack_pair *create_stack_pair(void);

void push(stack *s, int it);

item *pop(stack *s);

int stack_size(stack *s);

bool isEmpty(stack *s);

void print_stack(stack *s);

item *create_item(int it);

void display_stack(stack *s);

void push_ex(stack_expr *s, struct expr *it);

bunch *pop_ex(stack_expr *s);

bunch *create_expr_item(struct expr *it) ;

int   stack_size_expr(stack_expr *s) ;

bool isstackEmpty(stack_expr *s);

void empty_stack(stack_expr *s);

void empty_stack_pair(stack_pair *s);

bool ispairEmpty(stack_pair *s);