#include "ringbuffer.h"

static tNode2 *make_node2(const void *buf, uint32_t n) 
{
	tNode2 *new;

	new = malloc(sizeof(tNode2));

	if(!new) {
		return NULL;
	}	

	new->buf = malloc(n);

	if(!new->buf) {
		free(new);
		return NULL;
	}

	new->next = NULL;
	new->prev = NULL;
	new->n = n;
	memcpy(new->buf, buf, n);

	return new;
}

static void destroy_node2(tNode2 *node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;

	free(node->buf);
	free(node);

	node = NULL;
}

void ringbuffer_new(tRingBuffer *rb)
{
	if(!rb) {
		return;
	}

	*rb = NULL;
}

int ringbuffer_add(tRingBuffer *rb, const void *elem, uint32_t n)
{
	tNode2 *new;

	if(!rb || !elem) {
		return ERR;
	}

	new = make_node2(elem, n);

	if(!new) {
		return ERR;
	}

	if(!*rb) {
		new->next = new;
		new->prev = new;
		*rb = new;
	} else {
		new->next = (*rb);
		new->prev = (*rb)->prev;
		new->prev->next = new;
		(*rb)->prev = new;
	}

	return OK;
}

void ringbuffer_destroy(tRingBuffer *rb)
{
	tNode2 *tmp;
	
	while(*rb) {
		tmp = *rb;
		rb = &(*rb)->next;
		destroy_node2(tmp);
	}
}


