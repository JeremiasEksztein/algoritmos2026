#include "queue.h"

void arrayqueue_new(ArrayQueue *q)
{
	if(!q) {
		return;
	}

	q->start = ARRAYQUEUE_BUF_LEN / 2;
	q->end = q->start;

	if(BUFFER_ZEROING) {
		memset(q->buf, 0, ARRAYQUEUE_BUF_LEN);
	}
}

int arrayqueue_add(ArrayQueue *q, const void *elem, size_t n)
{
	size_t len0, len1;

	if(!q || !elem) {
		return ERR;
	}	

	if(((q->end + sizeof(size_t) + n) % ARRAYQUEUE_BUF_LEN) > q->start && q->end < q->start) {
		return ERR;
	}

	if((ARRAYQUEUE_BUF_LEN - (long)(q->end + sizeof(size_t))) >= 0) {
		memcpy(q->buf + q->end, &n, sizeof(size_t));
		q->end += sizeof(size_t);
	} else {
		len0 = ARRAYQUEUE_BUF_LEN - q->end;
		len1 = sizeof(size_t) - len0;

		memcpy(q->buf + q->end, &n, len0);
		memcpy(q->buf, &n + len0, len1);
		q->end = len1;
	}

	if((ARRAYQUEUE_BUF_LEN - (long)(q->end + n)) >= 0) {
		memcpy(q->buf + q->end, elem, n);
		q->end += n;
	} else {
		len0 = ARRAYQUEUE_BUF_LEN - q->end;
		len1 = n - len0;

		memcpy(q->buf + q->end, elem, len0);
		memcpy(q->buf, (const char*)elem + len0, len1);
		q->end = len1;
	}

	/*
	s := start of the queue
	e := end of the queue

	if ARRAYQUEUE_BUF_LEN - (e + sizeof(n)) >= 0 {
		buf[e..(e + sizeof(n))] := n
		e := e + sizeof(n)
	} else {
		len0 := ARRAYQUEUE_BUF_LEN - e
		len1 := sizeof(n) - len0

		buf[e..(e + len0)] := n[0..len0]
		buf[0..len1] := n[len0 + 1..(len0 + len1)]
		e := len1
	}
	*/

	return OK;
}

int arrayqueue_rem(ArrayQueue *q, void *buf, size_t n)
{
	size_t len0, len1, old_n;
	
	if(!q || !buf) {
		return ERR;
	}

	if(q->start == q->end) {
		return ERR;
	}

	if((ARRAYQUEUE_BUF_LEN - (long)(q->start + sizeof(size_t))) >= 0) {
		memcpy(&old_n, q->buf + q->start, sizeof(size_t));
		q->start += sizeof(size_t);
	} else {
		len0 = ARRAYQUEUE_BUF_LEN - q->start;
		len1 = sizeof(size_t) - len0;

		memcpy(&old_n, q->buf + q->start, len0);
		memcpy(&old_n + len0, q->buf, len1);
		q->start = len1;
	}

	if((ARRAYQUEUE_BUF_LEN - (long)(q->start + MIN(old_n, n))) >= 0) {
		memcpy(buf, q->buf + q->start, MIN(old_n, n));
		q->start += old_n;
	} else {
		len0 = ARRAYQUEUE_BUF_LEN - q->start;
		len1 = MIN(old_n, n) - len0;

		memcpy((char*)buf, q->buf + q->start, len0);
		memcpy((char*)buf + len0, q->buf, len1);
		q->start = len1;
	}

	/*
		s := start of the queue 
		e := end of the queue

		if ARRAYQUEUE_BUF_LEN - (s + sizeof(n)) >= 0 {
			n := buf[s..(s + sizeof(n))]
			s := s + sizeof(n)
		} else {
			len0 := ARRAYQUEUE_BUF_LEN - s
			len1 := sizeof(n) - len0

			n[0..len0] := buf[s..(s + len0)]
			n[(len0 + 1)..(len0 + len1)] := buf[0..len1]
			s := len1
		}
	
	*/

	return OK;
}

int arrayqueue_first(const ArrayQueue *q, void *buf, size_t n)
{
	size_t len0, len1, old_n, start;
	
	if(!q || !buf) {
		return ERR;
	}

	if(q->start == q->end) {
		return ERR;
	}

	start = q->start;

	if((ARRAYQUEUE_BUF_LEN - (long)(start + sizeof(size_t))) >= 0) {
		memcpy(&old_n, q->buf + start, sizeof(size_t));
		start += sizeof(size_t);
	} else {
		len0 = ARRAYQUEUE_BUF_LEN - start;
		len1 = sizeof(size_t) - len0;

		memcpy(&old_n, q->buf + start, len0);
		memcpy(&old_n + len0, q->buf, len1);
		start = len1;
	}

	if((ARRAYQUEUE_BUF_LEN - (long)(start + MIN(old_n, n))) >= 0) {
		memcpy(buf, q->buf + start, MIN(old_n, n));
		start += old_n;
	} else {
		len0 = ARRAYQUEUE_BUF_LEN - start;
		len1 = sizeof(size_t) - len0;

		memcpy(buf, q->buf + start, len0);
		memcpy((char*)buf + len0, q->buf, len1);
		start = len1;
	}

	return OK;
}

int arrayqueue_is_full(const ArrayQueue *q, size_t n)
{
	if(!q) {
		return UNKNOWN;
	}
	
	if((q->end + sizeof(size_t) + n) % ARRAYQUEUE_BUF_LEN > q->start) {
		return TRUE;
	}

	return FALSE;
}

int arrayqueue_is_empty(const ArrayQueue *q)
{
	if(!q) {
		return UNKNOWN;
	}

	return (q->start == q->end) ? TRUE : FALSE;
}

void arrayqueue_destroy(ArrayQueue *q)
{
	if(!q) {
		return;
	}

	q->start = ARRAYQUEUE_BUF_LEN / 2;
	q->end = q->start;

	if(BUFFER_ZEROING) {
		memset(q->buf, 0, ARRAYQUEUE_BUF_LEN);
	}
}
