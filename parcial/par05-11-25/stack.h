#ifndef STACK_H
#define STACK_H

#include <string.h>

#include "common.h"

typedef struct {
	char buf[55];
	unsigned top;
} tStack;

void stackNew(tStack *s);

int stackPush(tStack *s, char ch);

int stackPop(tStack *s, char *ch);

int stackPeek(const tStack *s, char *ch);

int stackIsEmpty(const tStack *s);

int stackIsFull(const tStack *s);

void stackDelete(tStack *s);

#endif
