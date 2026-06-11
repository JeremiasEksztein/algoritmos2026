#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "list.h"
#include "test.h"

int computer_cmp2(const void *a, const void *b)
{
	const Computer *x = a, *y = b;
	int cap_x, cap_y;

	if(x->mips == y->mips) {
		sscanf(x->ram, "%d", &cap_x);
		sscanf(y->ram, "%d", &cap_y);
	
		return cap_x - cap_y;
	}

	return x->mips - y->mips;
}

int main(void)
{
	SLinkedList l;
	Computer tmp;
	int i;
	
	printf("First pass\n");
	
	for(i = 0; i < 50; i++) {
		slinkedlist_addlo(&l, arr + i, sizeof(Computer));
		computer_show(arr + i);
	}

	printf("Second pass\n");

	slinkedlist_sort(&l, computer_cmp2);
	printf("a\n");
	slinkedlist_print(&l, computer_print);

	for(i = 0; i < 50; i++) {
		slinkedlist_remlo(&l, &tmp, sizeof(Computer));
		computer_show(&tmp);
	}

	slinkedlist_destroy(&l);
	
	return 0;
}
