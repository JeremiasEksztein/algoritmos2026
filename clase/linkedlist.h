#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>

#include "defines.h"

typedef struct sNode tNode;
struct sNode {
	tNode *next;
	unsigned n;
	void *buf;	
};

typedef tNode *tLinkedList;

void linkedlist_new(tLinkedList *l);

int linkedlist_addlo(tLinkedList *l, const void *elem, unsigned n);
int linkedlist_addhi(tLinkedList *l, const void *elem, unsigned n);
int linkedlist_add(tLinkedList *l, unsigned i, const void *elem, unsigned n);

int linkedlist_remlo(tLinkedList *l, void *buf, unsigned n);
int linkedlist_remhi(tLinkedList *l, void *buf, unsigned n);
int linkedlist_rem(tLinkedList *l, unsigned i, void *buf, unsigned n);

void linkedlist_print(const tLinkedList *ll, print_fn print);

void linkedlist_delete(tLinkedList *l);


#endif
