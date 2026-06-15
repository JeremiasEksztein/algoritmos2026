#ifndef LIST_H
#define LIST_H

#include "common.h"
#include "node.h"

typedef tNode *tLinkedList;

void linkedListNew(tLinkedList *ll);

int linkedListInsert(
	tLinkedList *ll,
	const void *data,
	unsigned n,
	fnCmp cmp,
	int withDup,
	fnAction ifdup,
	void *user
);

int linkedListRemlo(tLinkedList *ll, void *buf, unsigned n);

int linkedListFind(
	tLinkedList *ll, 
	const void *key,
	void *buf,
	unsigned n,
	fnCmp cmp
);

int linkedListIsEmpty(tLinkedList *ll);

void linkedListDelete(tLinkedList *ll);

#endif
