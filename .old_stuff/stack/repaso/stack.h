#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define OK 0
#define ERR 1

typedef enum {
	FALSE = 0,
	TRUE = 1,
	UNKNOWN = 2
} Bool;

typedef struct {
	void* impl;
	char impl_buf[2<<9];
} Stack;

void stack_new(Stack* stk);

int stack_push(Stack* stk, void* elem, size_t n);

int stack_peek(Stack* stk, void* buf, size_t n);

int stack_pop(Stack* stk, void* buf, size_t n);

Bool stack_full(Stack* stk, size_t n);

Bool stack_empty(Stack* stk);

void stack_destroy(Stack* stk);

#endif
