#ifndef STACK_H
#define STACK_H

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

/* ArrayStack */

typedef struct ArrayStack {
	#define ARRAYSTACK_BUF_LEN 4096
	char buf[ARRAYSTACK_BUF_LEN];
	size_t top;
} ArrayStack;

void arraystack_new(ArrayStack *stk);

int arraystack_push(ArrayStack *stk, const void *elem, size_t n);

int arraystack_pop(ArrayStack *stk, void *buf, size_t n);

int arraystack_peek(const ArrayStack *stk, void *buf, size_t n);

int arraystack_is_full(const ArrayStack *stk, size_t n);

int arraystack_is_empty(const ArrayStack *stk);

void arraystack_destroy(ArrayStack *stk);

/* LinkedStack */

typedef struct Node Node;
struct Node {
	struct Node *next;
	size_t n;
	void *buf;
};

typedef Node *LinkedStack;

void linkedstack_new(LinkedStack *stk);

int linkedstack_push(LinkedStack *stk, const void *elem, size_t n);

int linkedstack_pop(LinkedStack *stk, void *buf, size_t n);

int linkedstack_peek(const LinkedStack *stk, void *buf, size_t n);

int linkedstack_is_full(const LinkedStack *stk, size_t n);

int linkedstack_is_empty(const LinkedStack *stk);

void linkedstack_destroy(LinkedStack *stk);

/* CircularLinkedStack */

typedef Node *CLinkedStack;

void clinkedstack_new(CLinkedStack *stk);

int clinkedstack_push(CLinkedStack *stk, const void *elem, size_t n);

int clinkedstack_pop(CLinkedStack *stk, void *buf, size_t n);

int clinkedstack_peek(const CLinkedStack *stk, void *buf, size_t n);

int clinkedstack_is_full(const CLinkedStack *stk, size_t n);

int clinkedstack_is_empty(const CLinkedStack *stk);

void clinkedstack_destroy(CLinkedStack *stk);

#endif
