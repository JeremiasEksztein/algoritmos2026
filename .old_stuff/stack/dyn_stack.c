#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	struct Node* prev;
	void* buf;
	size_t n;
} Node;

typedef struct {
	Node* top;
	size_t n;
} DynStack;

static Node* NODE_NEW(size_t n)
{
	Node* node;
	
	node = malloc(sizeof(Node));
	
	if(!node) {
		return NULL;
	}

	node->buf = malloc(n);

	if(!node->buf) {
		free(node);
		return NULL;
	}

	node->prev = NULL;
	node->n = n;

	return node;	
}

static void NODE_DELETE(Node* node)
{
	if(!node) {
		return;
	}
	if(!node->buf) {
		return;
	}

	free(node->buf);
	free(node);
	node = NULL;
}

int stack_new(Stack* stk)
{
	DynStack impl;
	
	if(!stk) {
		return ERR;
	}

	memset(&impl, 0, sizeof(DynStack));
	memcpy(stk->impl_storage, &impl, sizeof(DynStack));

	stk->impl = stk->impl_storage;

	return OK;
}

int stack_push(Stack* stk, void* elem, size_t n)
{
	DynStack* s;
	Node* node;

	if(!stk || !elem || n == SIZE_MAX) {
		return ERR;
	}

	s = stk->impl;

	node = NODE_NEW(n);

	if(!node) {
		return ERR;
	}

	memcpy(node->buf, elem, n);

	if(s->n == 0) {
		s->top = node;
		s->n++;
		return OK;
	}
	
	node->prev = s->top;
	s->top = node;
	s->n++;
	
	return OK;
}

int stack_peek(Stack* stk, void* buf, size_t n)
{
	DynStack* s;

	if(!stk || !buf || n == SIZE_MAX) {
		return ERR;
	}

	s = stk->impl;

	if(s->n == 0) {
		return ERR;
	}

	memcpy(buf, s->top->buf, (s->top->n < n) ? s->top->n : n);

	return OK;
}

int stack_pop(Stack* stk, void* buf, size_t n)
{
	DynStack* s;
	Node* tmp_node;

	if(!stk || !buf || n == SIZE_MAX) {
		return ERR;
	}

	s = stk->impl;

	if(s->n == 0) {
		return ERR;
	}

	memcpy(buf, s->top->buf, (s->top->n < n) ? s->top->n : n);

	s->n--;
	tmp_node = s->top;

	if(!tmp_node->prev) {
		NODE_DELETE(s->top);
		return OK;
	}

	s->top = s->top->prev;
	NODE_DELETE(tmp_node);

	return OK;
}

/* Lacks sense on a dynamically allocated impl */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter" 
int stack_is_full(Stack* stk, size_t n)
{
	return FALSE;
}
#pragma GCC diagnostic pop

int stack_is_empty(Stack* stk)
{
	DynStack* s;
	if(!stk) {
		return ERR;
	}

	s = stk->impl;

	return (s->n) ? FALSE : TRUE;
}

void stack_delete(Stack* stk)
{
	DynStack* s;
	Node* tmp;
	
	if(!stk) {
		return;
	}

	s = stk->impl;

	while(s->top) {
		free(s->top->buf);
		tmp = s->top;
		s->top = s->top->prev;
		free(tmp);
	}
	
	memset(stk, 0, sizeof(Stack));
}
