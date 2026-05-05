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

void linkedqueue_new(LinkedQueue *q)
{
	if(!q) {
		return;
	}	
	
	q->start = NULL;
	q->end = q->start;
}

int linkedqueue_add(LinkedQueue *q, const void *elem, size_t n)
{
	Node *new;

	if(!q || !elem) {
		return ERR;
	}

	new = MAKE_NODE(NULL, n, elem);

	if(!new) {
		return ERR;
	}

	if(!q->start) {
		q->start = new;
	} else {
		q->end->next = new;
	}

	q->end = new;

	return OK;
}

int linkedqueue_rem(LinkedQueue *q, void *buf, size_t n)
{
	Node *tmp;
	
	if(!q || !buf || !q->start || !q->end) {
		return ERR;
	}

	tmp = q->start;
	q->start = q->start->next;

	memcpy(buf, tmp->buf, MIN(tmp->n, n));

	DELETE_NODE(tmp);

	return OK;
}

int linkedqueue_first(const LinkedQueue *q, void *buf, size_t n)
{	
	if(!q || !buf) {
		return ERR;
	}

	memcpy(buf, q->start, MIN(q->start->n, n));

	return OK;	
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int linkedqueue_is_full(const LinkedQueue *q, size_t n)
{
	return FALSE;	
}
#pragma GCC diagnostic pop

int linkedqueue_is_empty(const LinkedQueue *q)
{
	if(!q) {
		return UNKNOWN;
	}

	if(!q->start) {
		return TRUE;
	}

	return FALSE;
}

void linkedqueue_destroy(LinkedQueue *q)
{
	Node *tmp;

	if(!q) {
		return;
	}

	while(q->start) {
		tmp = q->start;
		q->start = q->start->next;
		DELETE_NODE(tmp);
	}

	q->start = NULL;
	q->end = NULL;
}
