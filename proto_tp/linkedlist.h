#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct sNode tNode;
struct sNode {
	tNode *next;
	uint32_t n;
	void *buf;
};

typedef tNode *tSLinkedList;

void slinkedlist_new(tSLinkedList *ll);

int slinkedlist_addhi(tSLinkedList *ll, const void *elem, size_t n);

int slinkedlist_rem(tSLinkedList *ll, void *buf, size_t n);

void slinkedlist_destroy(tSLinkedList *ll);

#endif
