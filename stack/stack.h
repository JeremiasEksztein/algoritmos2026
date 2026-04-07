#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stddef.h>

#define OK 0
#define ERR 1

#define TRUE 1
#define FALSE 0

typedef struct {
	char impl_storage[512];
	void* impl;
} Stack;

extern int stack_new(Stack* stk);

extern int stack_push(Stack* stk, void* elem, size_t n);

extern int stack_peek(Stack* stk, void* buf, size_t n);

extern int stack_pop(Stack* stk, void* buf, size_t n);

extern int stack_is_full(Stack* stk, size_t n);

extern int stack_is_empty(Stack* stk);

extern void stack_delete(Stack* stk);

#endif /* STACK_H */
