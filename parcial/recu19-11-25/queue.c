#include "queue.h"

void queueNew(tQueue *q)
{
	if(!q) {
		return;
	}

	memset(q->buf, 0, QUEUE_BUFSIZE);
	q->front = q->back = QUEUE_BUFSIZE / 2;
}

int queueAdd(tQueue *q, const void *data, unsigned n)
{
	unsigned len0, len1;
	
	if(!q || !data) {
		return ERR;
	}

	if((q->back + sizeof(n) + n) % QUEUE_BUFSIZE < q->front) {
		return ERR;
	}

	if(QUEUE_BUFSIZE >= (q->back + sizeof(n))) {
		memcpy(q->buf + q->back, &n, sizeof(n));
		q->back += sizeof(n);
	} else {
		len0 = QUEUE_BUFSIZE - q->back;
		len1 = sizeof(n) - len0;

		memcpy(q->buf + q->back, &n, len0);
		memcpy(q->buf, &n + len0, len1);
		q->back = len1;
	}

	if(QUEUE_BUFSIZE >= (q->back + n)) {
		memcpy(q->buf + q->back, data, n);
		q->back += n;
	} else {
		len0 = QUEUE_BUFSIZE - q->back;
		len1 = n - len0;

		memcpy(q->buf + q->back, data, len0);
		memcpy(q->buf, (char *)data + len0, len1);
		q->back = len1;
	}

	return OK;
}

int queueRem(tQueue *q, void *buf, unsigned n)
{
	unsigned len0, len1, old_n, k;

	if(!q || !buf) {
		return ERR;
	}

	if(q->front == q->back) {
		return ERR;
	}

	if(QUEUE_BUFSIZE >= (q->front + sizeof(unsigned))) {
		memcpy(&old_n, q->buf + q->front, sizeof(unsigned));
		q->front += sizeof(unsigned);
	} else {
		len0 = QUEUE_BUFSIZE - q->front;
		len1 = sizeof(unsigned) - len0;

		memcpy(&old_n, q->buf + q->front, len0);
		memcpy(&old_n + len0, q->buf, len1);

		q->front = len1;
	}

	k = MIN(old_n, n);

	if(QUEUE_BUFSIZE >= (q->front + k)) {
		memcpy(buf, q->buf + q->front, k);
		q->front += old_n;
	} else {
		len0 = QUEUE_BUFSIZE - q->front;
		len1 = k - len0;

		memcpy(buf, q->buf + q->front, len0);
		memcpy((char *)buf + len0, q->buf, len1);

		q->front = old_n - len0; /* ??? */
	}

	return OK;
}

int queueFront(const tQueue *q, void *buf, unsigned n)
{
	unsigned len0, len1, old_n, k, tmp_front;

	if(!q || !buf) {
		return ERR;
	}

	if(q->front == q->back) {
		return ERR;
	}

	tmp_front = q->front;
	
	if(QUEUE_BUFSIZE >= (tmp_front + sizeof(unsigned))) {
		memcpy(&old_n, q->buf + tmp_front, sizeof(unsigned));
		tmp_front += sizeof(unsigned);
	} else {
		len0 = QUEUE_BUFSIZE - tmp_front;
		len1 = sizeof(unsigned) - len0;

		memcpy(&old_n, q->buf + tmp_front, len0);
		memcpy(&old_n + len0, q->buf, len1);

		tmp_front = len1;
	}

	k = MIN(old_n, n);

	if(QUEUE_BUFSIZE >= (tmp_front + k)) {
		memcpy(buf, q->buf + tmp_front, k);
		tmp_front += old_n;
	} else {
		len0 = QUEUE_BUFSIZE - tmp_front;
		len1 = k - len0;

		memcpy(buf, q->buf + tmp_front, len0);
		memcpy((char *)buf + len0, q->buf, len1);
	}

	return OK;
}

int queueIsEmpty(const tQueue *q)
{
	if(!q) {
		return FALSE;
	}

	if(q->front == q->back) {
		return TRUE;
	}

	return FALSE;
}

int queueIsFull(const tQueue *q, unsigned n)
{
	if(!q) {
		return FALSE;
	}

	if((q->back + sizeof(n) + n) % QUEUE_BUFSIZE > q->front) {
		return TRUE;
	}

	return FALSE;
}

void queueDelete(tQueue *q)
{
	if(!q) {
		return;
	}

	memset(q->buf, 0, QUEUE_BUFSIZE);
	q->front = q->back = QUEUE_BUFSIZE / 2;
}
