#include "list.h"
#include "test.h"
#include <assert.h>

int main(void)
{
	DLinkedList l;
	Computer tmp;
	int i;

	dlinkedlist_new(&l);
	
	printf("First pass\n");
	
	for(i = 0; i < 50; i++) {
		dlinkedlist_add_ordered(&l, arr + i, sizeof(Computer), computer_cmp);
		computer_show(arr + i);
	}

	assert(dlinkedlist_len(&l) == 50);

	printf("Second pass\n");

	printf("Left to right\n");
	dlinkedlist_printl(&l, computer_print);
	printf("Right to left\n");
	dlinkedlist_printr(&l, computer_print);

	printf("Third pass\n");
	for(i = 0; i < 50; i++) {
		dlinkedlist_remhi(&l, &tmp, sizeof(Computer));
		printf("%d) ", i + 1);
		computer_show(&tmp);
	}

	assert(dlinkedlist_is_empty(&l) == TRUE);
	assert(dlinkedlist_len(&l) == 0);

	dlinkedlist_destroy(&l);
	
	return 0;
}
