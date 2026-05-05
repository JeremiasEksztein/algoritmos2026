#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define MIN(x, y) (((x) > (y)) ? (y) : (x))

#define OK 0
#define ERR 1

#define TRUE 1
#define FALSE 0
#define UNKNOWN -1

#ifndef BUFFER_ZEROING
#define BUFFER_ZEROING 0
#endif

typedef struct ArrayQueue {
#define ARRAYQUEUE_BUF_LEN 4096
	char buf[ARRAYQUEUE_BUF_LEN];
	size_t start;
	size_t end;
} ArrayQueue;

void arrayqueue_new(ArrayQueue *q);

int arrayqueue_add(ArrayQueue *q, const void *elem, size_t n);

int arrayqueue_rem(ArrayQueue *q, void *buf, size_t n);

int arrayqueue_first(const ArrayQueue *q, void *buf, size_t n);

int arrayqueue_is_full(const ArrayQueue *q, size_t n);

int arrayqueue_is_empty(const ArrayQueue *q);

void arrayqueue_destroy(ArrayQueue *q);

typedef struct Node Node;
struct Node {
	Node *next;
	size_t n;
	void *buf;	
};

typedef struct LinkedQueue {
	Node *start;
	Node *end;
} LinkedQueue;

void linkedqueue_new(LinkedQueue *q);

int linkedqueue_add(LinkedQueue *q, const void *elem, size_t n);

int linkedqueue_rem(LinkedQueue *q, void *buf, size_t n);

int linkedqueue_first(const LinkedQueue *q, void *buf, size_t n);

int linkedqueue_is_full(const LinkedQueue *q, size_t n);

int linkedqueue_is_empty(const LinkedQueue *q);

void linkedqueue_destroy(LinkedQueue *q);

#endif
