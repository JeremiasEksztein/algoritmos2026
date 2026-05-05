#include "stack.h"

void arraystack_new(ArrayStack *stk)
{
	if(!stk) {
		return;
	}

	stk->top = ARRAYSTACK_BUF_LEN - 1;
	if(BUFFER_ZEROING) {
		memset(stk->buf, 0, ARRAYSTACK_BUF_LEN);
	}
}

int arraystack_push(ArrayStack *stk, const void *elem, size_t n)
{
	if(!stk || !elem) {
		return ERR;
	}
	if((n + sizeof(size_t)) > stk->top) {
		return ERR;
	}
	
	memcpy(stk->buf + stk->top - n, elem, n);
	memcpy(stk->buf + stk->top - n - sizeof(size_t), &n, sizeof(size_t));
	
	stk->top -= n + sizeof(size_t);
	
	return OK;
}

int arraystack_pop(ArrayStack *stk, void *buf, size_t n)
{
	size_t old_n;

	if(!stk || !buf) {
		return ERR;
	}
	if(stk->top == (ARRAYSTACK_BUF_LEN - 1)) {
		return ERR;
	}
	
	memcpy(&old_n, stk->buf + stk->top, sizeof(size_t));
	memcpy(buf, stk->buf + stk->top + sizeof(size_t), MIN(old_n, n));

	if(BUFFER_ZEROING) {
		memset(stk->buf + stk->top, 0, old_n + sizeof(size_t));
	}
	
	stk->top += sizeof(size_t) + old_n;

	return OK;
}

int arraystack_peek(const ArrayStack *stk, void *buf, size_t n)
{
	size_t old_n;

	if(!stk || !buf) {
		return ERR;
	}
	if(stk->top == (ARRAYSTACK_BUF_LEN - 1)) {
		return ERR;
	}
	
	memcpy(&old_n, stk->buf + stk->top, sizeof(size_t));
	memcpy(buf, stk->buf + stk->top + sizeof(size_t), MIN(old_n, n));
	
	return OK;	
}

int arraystack_is_full(const ArrayStack *stk, size_t n)
{
	if(!stk) {
		return UNKNOWN;
	}
	if((n + sizeof(size_t)) > stk->top) {
		return TRUE;
	}

	return FALSE;
}

int arraystack_is_empty(const ArrayStack *stk)
{
	if(!stk) {
		return UNKNOWN;
	}

	return (stk->top == (ARRAYSTACK_BUF_LEN - 1)) ? TRUE : FALSE;
}

void arraystack_destroy(ArrayStack *stk)
{
	if(!stk) {
		return;
	}

	stk->top = ARRAYSTACK_BUF_LEN - 1;

	if(BUFFER_ZEROING) {
		memset(stk->buf, 0, ARRAYSTACK_BUF_LEN);
	}
}
