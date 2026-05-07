#include "node.h"

Node *make_node(Node *next, size_t n, void *buf)
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

	memcpy(new->buf, buf, n);
	new->n = n;
	new->next = next;

	return new;
}

void delete_node(Node *node)
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
