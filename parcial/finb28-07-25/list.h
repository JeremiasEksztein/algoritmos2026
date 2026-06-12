#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>

typedef int (*fnCmp)(const void *, const void *);
typedef void (*fnPrint)(const void *, void *);

typedef struct sNode tNode;
struct sNode {
	tNode *next;
	unsigned n;
	void *buf;
};

typedef tNode *tLinkedList;

void linkedListNew(tLinkedList *ll);

int linkedListInsertOrderedUpToN(
	tLinkedList *ll, 
	const void *elem, 
	unsigned size,
	unsigned n,
	fnCmp cmp,
	int duplicates
);

void linkedListPrint(const tLinkedList *ll, fnPrint print, void *user);

void linkedListDelete(tLinkedList *ll);

#endif
