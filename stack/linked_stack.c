#include "stack.h"

static Node *MAKE_NODE(Node *next, size_t n, const void *buf);
static void DELETE_NODE(Node *node);

static Node *MAKE_NODE(Node *next, size_t n, const void *buf) 
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

static void DELETE_NODE(Node *node)
{
	if(!node) {
		return;
	}

	free(node->buf);
	free(node);
}

void linkedstack_new(LinkedStack *stk)
{
	if(!stk) {
		return;
	}
	if(*stk) {
		return;
	}

	*stk = NULL;
}

int linkedstack_push(LinkedStack *stk, const void *elem, size_t n)
{
	Node *new;

	if(!stk || !elem) {
		return ERR;
	}

	new = MAKE_NODE(NULL, n, elem);

	if(!new) {
		return ERR;
	}

	new->next = *stk;
	*stk = new;
	
	return OK;
}

int linkedstack_pop(LinkedStack *stk, void *buf, size_t n)
{
	Node *tmp;

	if(!stk || !buf || !*stk) {
		return ERR;
	}

	tmp = *stk;
	*stk = tmp->next;

	/* stk = &(*stk)->next. Why not? */

	memcpy(buf, tmp->buf, MIN(tmp->n, n));

	DELETE_NODE(tmp);	

	return OK;
}

int linkedstack_peek(const LinkedStack *stk, void *buf, size_t n)
{
	if(!stk || !buf || !*stk) {
		return ERR;
	}

	memcpy(buf, (*stk)->buf, MIN((*stk)->n, n));

	return OK;	
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int linkedstack_is_full(const LinkedStack *stk, size_t n)
{
	return FALSE;	
}
#pragma GCC diagnostic pop

int linkedstack_is_empty(const LinkedStack *stk)
{
	if(!stk) {
		return UNKNOWN;
	}

	return (*stk) ? FALSE : TRUE;
}

void linkedstack_destroy(LinkedStack *stk)
{
	Node *tmp;
	
	if(!stk) {
		return;
	}

	while(*stk) {
		tmp = *stk;
		*stk = tmp->next;
		DELETE_NODE(tmp);
	}
	
	*stk = NULL;
}
