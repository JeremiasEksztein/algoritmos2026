#include "stack.h"

void stackNew(tStack *s)
{
	if(!s) {
		return;
	}

	s->top = 0;
}

int stackPush(tStack *s, char ch)
{
	if(!s) {
		return ERR;
	}

	if(s->top == 54) {
		return ERR;
	} 

	s->buf[s->top++] = ch;

	return OK;
}

int stackPop(tStack *s, char *ch)
{
	if(!s || !ch) {
		return ERR;
	}

	if(s->top == 0) {
		return ERR;
	}

	*ch = s->buf[s->top-- - 1];

	return OK;
}

int stackPeek(const tStack *s, char *ch)
{
	if(!s || !ch) {
		return ERR;
	}

	if(s->top == 0) {
		return ERR;
	}

	*ch = s->buf[s->top - 1];

	return OK;
}

int stackIsEmpty(const tStack *s)
{
	if(!s) {
		return TRUE;
	}

	return (s->top == 0) ? TRUE : FALSE;
}

int stackIsFull(const tStack *s)
{
	if(!s) {
		return FALSE;
	}

	return (s->top == 54) ? TRUE : FALSE;
}

void stackDelete(tStack *s)
{
	if(!s) {
		return;
	}

	s->top = 0;
}
