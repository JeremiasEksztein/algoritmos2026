#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <string.h>

#include "common.h"

typedef struct sNode tNode;
struct sNode {
	tNode *next;
	unsigned n;
	void *buf;
};

typedef struct { 
	tNode *front, *back;
} tLinkedQueue;

void linkedQueueNew(tLinkedQueue *q);

int linkedQueueAdd(tLinkedQueue *q, const void *data, unsigned n);

int linkedQueueRem(tLinkedQueue *q, void *buf, unsigned n);

int	linkedQueueFront(const tLinkedQueue *q, void *buf, unsigned n);

int	linkedQueueIsEmpty(const tLinkedQueue *q);

void linkedQueueDelete(tLinkedQueue *q);

#endif
