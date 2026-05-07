#include "queue.h"

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

void clinkedqueue_new(CLinkedQueue *q)
{
	if(!q) {
		return;
	}

	*q = NULL;
}

int clinkedqueue_add(CLinkedQueue *q, const void *elem, size_t n)
{
	Node *tmp;

	if(!q || !elem) {
		return ERR;
	}
	
	tmp = MAKE_NODE(NULL, n, elem);

	if(!tmp) {
		return ERR;
	}

	if(!*q) {
		tmp->next = tmp;
	} else {
		tmp->next = (*q)->next;
		(*q)->next = tmp;
	}

	*q = tmp;

	return OK;
}

int clinkedqueue_rem(CLinkedQueue *q, void *buf, size_t n)
{
	Node *tmp;

	if(!q || !buf || !*q) {
		return ERR;
	}

	memcpy(buf, (*q)->next->buf, MIN((*q)->next->n, n));

	tmp = (*q)->next;
	(*q)->next = tmp->next;

	DELETE_NODE(tmp);

	return OK;
}

int clinkedqueue_first(const CLinkedQueue *q, void *buf, size_t n)
{
	if(!q || !buf || !*q) {
		return ERR;
	}

	memcpy(buf, (*q)->buf, MIN((*q)->n, n));
	
	return OK;	
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int clinkedqueue_is_full(const CLinkedQueue *q, size_t n)
{
	return UNKNOWN;	
}
#pragma GCC diagnostic pop

int clinkedqueue_is_empty(const CLinkedQueue *q)
{
	if(!q) {
		return UNKNOWN;
	}

	return (*q == NULL) ? TRUE : FALSE; 
}

void clinkedqueue_destroy(CLinkedQueue *q)
{
	Node *tmp;

	while(*q) {
		tmp = *q;
		*q = (*q)->next;

		DELETE_NODE(tmp);
	}
}
