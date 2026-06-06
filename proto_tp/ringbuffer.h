#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define OK 0
#define ERR 1

typedef struct sNode2 tNode2;
struct sNode2 {
	tNode2 *next, *prev;
	uint32_t n;
	void *buf;	
};

typedef tNode2 *tRingBuffer;

void ringbuffer_new(tRingBuffer *rb);

int ringbuffer_add(tRingBuffer *rb, const void *elem, uint32_t n);

void ringbuffer_destroy(tRingBuffer *rb);

#endif 
