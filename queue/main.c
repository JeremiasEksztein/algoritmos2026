#include "queue.h"
#include "test.h"
#include <assert.h>

int main(void)
{
	LinkedQueue q;
	Computer tmp;
	int i;

	linkedqueue_new(&q);

	printf("%lu\n", sizeof(Computer));

	printf("First pass\n");
	for(i = 0; i < 50; ++i) {
		computer_show(arr + i);
		linkedqueue_add(&q, arr + i, sizeof(Computer)); 
	}
	
	printf("Second pass\n");
	for(i = 0; i < 50; ++i) {
		linkedqueue_rem(&q, &tmp, sizeof(Computer));
		computer_show(&tmp);
		assert(computer_eq(&tmp, arr + i));
	}

	assert(linkedqueue_rem(&q, &tmp, sizeof(Computer)) == ERR);
	assert(linkedqueue_is_empty(&q));
	
	linkedqueue_destroy(&q);

	return OK;
}
