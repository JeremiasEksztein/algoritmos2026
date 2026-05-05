#define BUFFER_ZEROING 1
#include "stack.h"
#include "test.h"
#include <stdio.h>
#include <assert.h>

int main(void) 
{
	LinkedStack stk;
	/*Computer tmp;*/
	int i;

	linkedstack_new(&stk);

	printf("First pass\n");
	for(i = 0; i < 50; ++i) {
		computer_show(arr + i);
		linkedstack_push(&stk, arr + i, sizeof(Computer));
	}

	/*
	printf("Second pass\n");
	for(i = 49; i >= 0; --i) {
		linkedstack_pop(&stk, &tmp, sizeof(Computer));
		computer_show(&tmp);
		printf("CPU: %s\n", tmp.cpu);
		assert(computer_eq(&tmp, arr + i));
		assert(strcmp(tmp.cpu, (arr + i)->cpu) == 0);
	}

	assert(linkedstack_is_empty(&stk) == TRUE);
	assert(linkedstack_pop(&stk, &tmp, sizeof(Computer)) == ERR);
	*/
	
	linkedstack_destroy(&stk);
	
	return 0;	
}
