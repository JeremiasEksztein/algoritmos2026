#include "node.h"

DNode *make_dnode(DNode *next, DNode *prev, size_t n, void *buf)
{
	DNode *new;

	new = malloc(sizeof(DNode));

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

	memcpy(new->buf, buf, n);
	new->n = n;
	new->next = next;
	new->prev = prev;

	return new;
}

void delete_dnode(DNode *node)
{
	if(!node) {
		return;
	}

	if(!node->buf) {
		return;
	}

	free(node->buf);
	free(node);
}
