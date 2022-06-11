/*

	Apostolos Mavrogiannakis csd3799
	Georgia Rapousi csd3836
	Varsamis Haralampos csd3744
*/

#include "stack.h"
stack_expr *
create_stack_expr(void) {
    stack_expr *s = (stack_expr *) malloc(sizeof(stack_expr));

    s -> top = NULL;
    s -> items = (bunch *) malloc(sizeof(bunch));
    s -> items -> item = NULL;
    s -> items -> next = NULL;
    s -> size = 0;

    return s;
}

stack *
create_stack(void) {
    stack *s = (stack *) malloc(sizeof(stack));

    s -> top = NULL;
    s -> items = (item *)malloc(sizeof(item));
    s -> items -> item = -1;
    s -> items -> next = NULL;
    s -> size = 0;

    return s;
}

stack_pair *
create_stack_pair(void) {
    stack_pair *s = (stack_pair *) malloc(sizeof(stack));

    s -> top = NULL;
    s -> items = (pair *)malloc(sizeof(pair));
    s -> items -> item = NULL;
    s -> items -> next = NULL;
    s -> size = 0;

    return s;
}

void
push(stack *s, int it) {
    item *new_item = (item *)malloc(sizeof(item));
    new_item -> item = it;

    // Inserting new item into stack s
    new_item -> next = s -> top;

    // Making top point in our new item
    s -> top = new_item;
    s -> items = new_item;

    s -> size = s->size + 1;
}

void
push_ex(stack_expr *s, struct expr *e) {
    bunch *b = (bunch *) malloc(sizeof(bunch));
    b -> item = e;

    // Inserting new item into stack s
    b -> next = s -> top;

    // Making top point in our new item
    s -> top = b;
    s -> items = b;

    s -> size = s -> size + 1;
}



item *
pop(stack *s) {
    item *top = NULL;
    
    if(stack_size(s)) { //s -> size != 0
        top = s -> top;
        s -> top = top -> next;
        s -> items = s -> top;

        s -> size --;
    }

    return top;
}

bunch *
pop_ex(stack_expr *s) {
    bunch *top = NULL;

    if(stack_size_expr(s)) {
        top = s -> top;

        s -> top = top -> next;
        s -> items = s -> top;

        s -> size --;
    }

    return top;
}



int
stack_size(stack *s) {
    return s->size;
}

int
stack_size_expr(stack_expr *s) {
    return s-> size;
}

bool
isstackEmpty(stack_expr *s) {
    return s->size == 0;
}

bool
isEmpty(stack *s) {
    return s->size == 0;
}

bool
ispairEmpty(stack_pair *s) {
    return s->size == 0;
}

item *
create_item(int it) {
    item *i1 =  (item *) malloc(sizeof(item));
    i1 -> next = NULL;
    i1 -> item = it;

    return i1;
}


void
display_stack(stack *s) {
    item *iter = s -> items;

    printf("STACK\n");
    if(isEmpty(s)) {
        printf("------");
    }else {
        while( iter != NULL ) {
            printf("%d -> ", iter -> item);
            iter = iter->next;
        }
    }
    printf("\n");
}

void 
empty_stack(stack_expr *s) {
    s -> items = NULL;
    s -> top = NULL;
    s -> size = 0;
}

void empty_stack_pair(stack_pair *s) {
    s -> items = NULL;
    s -> top = NULL;
    s -> size = 0;
}



/*

int
main() {
    stack *s = create_stack();

    push(s,5); 
    push(s,3); 
    push(s,4);

    display_stack(s); 

    item *p = pop(s);

    printf("pop item : %d\n", p -> item);

    display_stack(s);
}
*/

