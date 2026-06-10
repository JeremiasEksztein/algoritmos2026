#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>

#include "defines.h"

typedef struct {
	char *buf;
	unsigned top;
	unsigned n;
} tStack;

int stackNew(tStack *stk, unsigned n);

int stackPush(tStack *stk, const void *elem, unsigned n);

int stackPop(tStack *stk, void *buf, unsigned n);

int stackPeek(const tStack *stk, void *buf, unsigned n);

int stackIsEmpty(const tStack *stk);

int stackIsFull(const tStack *stk, unsigned n);

void stackDelete(tStack *stk);

#endif
