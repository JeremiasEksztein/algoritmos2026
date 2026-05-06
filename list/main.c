#include "list.h"
#include "test.h"
#include <assert.h>

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

	slinkedlist_sort(&l, computer_cmp);

	for(i = 0; i < 50; i++) {
		slinkedlist_remlo(&l, &tmp, sizeof(Computer));
		computer_show(&tmp);
	}

	slinkedlist_destroy(&l);
	
	return 0;
}
