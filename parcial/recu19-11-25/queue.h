#ifndef QUEUE_H
#define QUEUE_H

#include <string.h>

#include "common.h"

/* 1000 * (sizeof(unsigned) + sizeof(char)) */
#define QUEUE_BUFSIZE 1000 * 5

typedef struct {
	char buf[QUEUE_BUFSIZE];
	unsigned front, back;
} tQueue;

void queueNew(tQueue *q);

int queueAdd(tQueue *q, const void *data, unsigned);

int queueRem(tQueue *q, void *buf, unsigned n);

int queueFront(const tQueue *q, void *buf, unsigned n);

int queueIsEmpty(const tQueue *q);

int queueIsFull(const tQueue *q, unsigned n); 

void queueDelete(tQueue *q);

#endif
