#include "stack.h"

Node *MAKE_NODE(Node *next, size_t n, const void *buf);
void DELETE_NODE(Node *node);

Node *MAKE_NODE(Node *next, size_t n, const void *buf) 
{
	Node *new;
	
	new = malloc(sizeof(Node));
	
	if(!new) {
		return NULL;
	}	

	new->buf = malloc(n);

	if(!new->buf) {
		free(new);
		return NULL;
	}

	if(BUFFER_ZEROING) {
		memset(new->buf, 0, n);
	}

	new->next = next;
	new->n = n;
	memcpy(new->buf, buf, n);

	return new;
}

void DELETE_NODE(Node *node)
{
	if(!node) {
		return;
	}

	free(node->buf);
	free(node);
}

void clinkedstack_new(CLinkedStack *s)
{
	if(!s) {
		return;
	}

	*s = NULL;
}

int clinkedstack_push(CLinkedStack *s, const void *elem, size_t n)
{
	Node *tmp;

	if(!s || !elem) {
		return ERR;
	}
	
	tmp = MAKE_NODE(NULL, n, elem);

	if(!tmp) {
		return ERR;
	}

	if(!*s) {
		tmp->next = tmp;
		*s = tmp;
	} else {
		tmp->next = (*s)->next;
		(*s)->next = tmp;
	}


	return OK;
}

int clinkedstack_pop(CLinkedStack *s, void *buf, size_t n)
{
	Node *tmp;

	if(!s || !buf || !*s) {
		return ERR;
	}

	memcpy(buf, (*s)->next->buf, MIN((*s)->next->n, n));

	tmp = (*s)->next;
	(*s)->next = tmp->next;

	DELETE_NODE(tmp);

	return OK;
}

int clinkedstack_peek(const CLinkedStack *s, void *buf, size_t n)
{
	if(!s || !buf || !*s) {
		return ERR;
	}

	memcpy(buf, (*s)->buf, MIN((*s)->n, n));
	
	return OK;	
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int clinkedstack_is_full(const CLinkedStack *s, size_t n)
{
	return UNKNOWN;	
}
#pragma GCC diagnostic pop

int clinkedstack_is_empty(const CLinkedStack *q)
{
	if(!q) {
		return UNKNOWN;
	}

	return (*q == NULL) ? TRUE : FALSE; 
}

void clinkedstack_destroy(CLinkedStack *s)
{
	Node *tmp;

	while(*s) {
		tmp = *s;
		*s = (*s)->next;

		DELETE_NODE(tmp);
	}
}
