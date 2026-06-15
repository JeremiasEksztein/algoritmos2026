#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>

typedef struct sNode tNode;
struct sNode {
	tNode *next;
	unsigned n;
	void *buf;
};

typedef tNode *tStack;

void stackNew(tStack *s);

int stackPush(tStack *s, const void *buf, unsigned n);

int stackPop(tStack *s, void *buf, unsigned n);

int stackPeek(const tStack *s, void *buf, unsigned n);

int stackIsEmpty(const tStack *s);

void stackDelete(tStack *s);

#endif
