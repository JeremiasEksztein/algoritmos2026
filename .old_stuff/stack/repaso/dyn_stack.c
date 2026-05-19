#include "stack.h"

typedef struct Node {
	struct Node* prev;
	void* buf;
	size_t n;
} Node;

typedef struct {
	Node* top;
	size_t n;
} DynStack;

#define MIN(x, y) ((x) > (y) ? (y) : (x))

static int STACK_PUSH(DynStack* stk, void* elem, size_t n)
{
	Node* node;
	node = malloc(sizeof(Node));

	if(!node) {
		return ERR;
	}

	node->buf = malloc(n);

	if(!node->buf) {
		free(node);
		return ERR;
	}

	memcpy(node->buf, elem, n);
	node->n = n;
	
	if(stk->n == 0) {
		node->prev = NULL;
		stk->top = node;
		stk->n = 1;
	} else {
		node->prev = stk->top;
		stk->top = node;
		stk->n++;
	}

	return OK;
}

void stack_new(Stack* stk)
{
	DynStack s;
	
	if(!stk) {
		return;
	}

	s.top = NULL;
	s.n = 0;

	memcpy(stk->impl_buf, &s, sizeof(DynStack));
	stk->impl = stk->impl_buf;
}

int stack_push(Stack* stk, void* elem, size_t n)
{
	DynStack* s;
	
	if(!stk || !elem) {
		return ERR;
	}

	s = stk->impl;

	if(STACK_PUSH(s, elem, n) == ERR) {
		return ERR;
	}

	return OK;
}


int stack_peek(Stack* stk, void* buf, size_t n)
{
	DynStack* s;
		
	if(!stk || !buf) {
		return ERR;
	}

	s = stk->impl;	

	if(s->n == 0) {
		return ERR;
	}

	memcpy(buf, s->top->buf, MIN(n, s->top->n));

	return OK;
}

int stack_pop(Stack* stk, void* buf, size_t n)
{
	DynStack* s;
	Node* tmp;

	if(!stk || !buf) {
		return ERR;
	}

	s = stk->impl;

	if(s->n == 0) {
		return ERR;
	}

	memcpy(buf, s->top->buf, MIN(n, s->top->n));
	
	s->n--;
	tmp = s->top;
	s->top = tmp->prev;
	free(tmp->buf);
	free(tmp);

	return OK;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
Bool stack_full(Stack* stk, size_t n)
{
	/* 
	How would I know, in a dynamic implentation whether or not
	there's free space in the heap
	*/
	return FALSE;
}
#pragma GCC diagnostic pop

Bool stack_empty(Stack* stk)
{
	DynStack* s;
	if(!stk) {
		return UNKNOWN;
	}

	s = stk->impl;

	return (s->n == 0) ? TRUE : FALSE;
}

void stack_destroy(Stack* stk)
{
	DynStack* s;
	Node* tmp;

	if(!stk) {
		return;
	}	

	s = stk->impl;

	while(s->top->prev) {
		tmp = s->top;
		s->top = tmp->prev;
		free(tmp->buf);
		free(tmp);
	}

	free(tmp->buf);
	free(tmp);

	stk->impl = NULL;
	memset(stk->impl_buf, 0, sizeof(stk->impl_buf));
}
