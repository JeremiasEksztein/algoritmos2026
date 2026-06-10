#include "stack.h"

int stackNew(tStack *stk, unsigned n)
{
	stk->buf = malloc(n);

	if(!stk->buf) {
		return ERR;
	}

	stk->top = n - 1;
	stk->n = n;

	return OK;
}

int stackPush(tStack *stk, const void *elem, unsigned n)
{
	if(!stk || !stk->buf || !elem) {
		return ERR;
	}

	if(stk->top < (sizeof(unsigned) + n)) {
		return ERR;
	}

	memcpy(stk->buf + stk->top - n, elem, n);
	memcpy(stk->buf + stk->top - n - sizeof(unsigned), &n, sizeof(unsigned));

	stk->top -= sizeof(unsigned) + n;

	return OK;
}

int stackPop(tStack *stk, void *buf, unsigned n)
{
	unsigned old_n;

	if(!stk || !stk->buf || !buf) {
		return ERR;
	}

	if(stk->top == (stk->n - 1)) {
		return ERR;
	}

	memcpy(&old_n, stk->buf + stk->top, sizeof(unsigned));
	memcpy(buf, stk->buf + stk->top + sizeof(unsigned), MIN(old_n, n));
	stk->top += sizeof(unsigned) + old_n;
	
	return OK;
}

int stackPeek(const tStack *stk, void *buf, unsigned n)
{
	unsigned old_n;

	if(!stk || !stk->buf || !buf) {
		return ERR;
	}

	if(stk->top == (stk->n - 1)) {
		return ERR;
	}

	memcpy(&old_n, stk->buf + stk->top, sizeof(unsigned));
	memcpy(buf, stk->buf + stk->top + sizeof(unsigned), MIN(old_n, n));
	
	return OK;
}

int stackIsEmpty(const tStack *stk)
{	
	if(!stk || !stk->buf) {
		return TRUE;
	}

	if(stk->top == (stk->n - 1)) {
		return TRUE;
	}

	return FALSE;
}

int stackIsFull(const tStack *stk, unsigned n)
{
	if(!stk || !stk->buf) {
		return FALSE;
	}

	if(stk->top < (sizeof(unsigned) + n)) {
		return TRUE;
	}

	return FALSE;
}

void stackDelete(tStack *stk)
{
	if(!stk || !stk->buf) {
		return;
	}
	
	free(stk->buf);
	stk->top = 0;
}
