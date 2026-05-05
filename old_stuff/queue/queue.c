#include "queue.h"

#define MIN(x, y) (((x) > (y)) ? (y) : (x))

int queue_new(Queue* q)
{
	if(!q) {
		return ERR;
	}
	q->head = QUEUE_SIZE >> 1;
	q->tail = q->head;
	q->n = QUEUE_SIZE;
	return OK;
}

int queue_add(Queue* q, const void* elem, size_t n)
{
	size_t begin;
	size_t end;

	if(!q || !elem) {
		return ERR;
	}

	if(q->n < (sizeof(size_t) + n)) {
		return ERR;
	}

	if((begin = MIN(sizeof(n), (size_t)QUEUE_SIZE - q->tail)) != 0) {
		memcpy(q->buf + q->tail, &n, begin);
	}

	if((end = sizeof(n) - begin) != 0) {
		memcpy(q->buf, (&n + begin), end);
	}

	q->tail = end ? end : q->tail + begin;

	if((begin = MIN(n, (size_t)QUEUE_SIZE - q->tail)) != 0) {
		memcpy(q->buf + q->tail, elem, n);
	}

	if((end = n - begin) != 0) {
		memcpy(q->buf, (const char*)elem + begin, end);
	}

	q->tail = end ? end : q->tail + begin;
	q->n -= sizeof(size_t) + n;
	
	return OK;
}

int queue_first(const Queue* q, void* buf, size_t n)
{
	int tmp_head;
	size_t tmp_n;
	size_t begin;
	size_t end;
	
	if(!q || !buf) {
		return ERR;
	}

	tmp_head = q->head;

	if((begin = MIN(sizeof(n), (size_t)QUEUE_SIZE - tmp_head)) != 0) {
		memcpy(&tmp_n, q->buf + tmp_head, begin);
	}
	
	if((end = sizeof(n) - begin) != 0) {
		memcpy((char*)&tmp_n + begin, q->buf, end);
	}

	tmp_head = end ? end : tmp_head + begin;
	tmp_n = MIN(tmp_n, n);

	if((begin = MIN(tmp_n, (size_t)QUEUE_SIZE - tmp_head) != 0)) {
		memcpy(buf, q->buf + tmp_head, begin);
	}
	
	if((end = tmp_n - begin) != 0) {
		memcpy((char*)buf + begin, q->buf, end);
	}
	
	return OK;	
}

int queue_rem(Queue* q, void* buf, size_t n)
{
	size_t tmp_n;
	size_t begin;
	size_t end;
	
	if(!q || !buf) {
		return ERR;
	}

	if((begin = MIN(sizeof(n), (size_t)QUEUE_SIZE - q->head)) != 0) {
		memcpy(&tmp_n, q->buf + q->head, begin);
	}
	if((end = sizeof(n) - begin) != 0) {
		memcpy((char*)&tmp_n + begin, q->buf, end);
	}

	q->head = end ? end : q->head + begin;
	q->n += sizeof(tmp_n) + tmp_n;
	tmp_n = MIN(tmp_n, n);

	if((begin = MIN(tmp_n, (size_t)QUEUE_SIZE - q->head)) != 0) {
		memcpy(buf, q->buf + q->head, begin);
	}
	if((end = tmp_n - begin) != 0) {
		memcpy((char*)buf + begin, q->buf, end);
	}
	q->head = end ? end : q->head + begin;

	return OK;
}

Bool queue_is_empty(const Queue* q)
{
	if(!q) {
		return INVALID;
	}
	return (q->n == QUEUE_SIZE) ? TRUE : FALSE;
}

Bool queue_is_full(const Queue* q, size_t n)
{ 
	if(!q) {
		return INVALID;
	}

	return (q->n < (sizeof(n) + n)) ? TRUE : FALSE;
}

void queue_destroy(Queue* q)
{
	q->head = QUEUE_SIZE<<1;
	q->tail = q->head;
	q->n = QUEUE_SIZE;
	memset(q->buf, '0', QUEUE_SIZE);	
}
