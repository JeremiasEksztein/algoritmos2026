#include <stdio.h>
#include <stdlib.h>
#include "vec.h"

extern int i32_cmp(const void* lhs, const void* rhs);
extern void i32_show(const void* n);

int i32_cmp(const void* lhs, const void* rhs)
{
	return *(const int*)lhs - *(const int*)rhs;
}

void i32_show(const void* n)
{
	fprintf(stderr, "%d, ", *(const int*)n);
	return;
}

#define LEN 256

int main(void)
{
	Vec vec;
	int arr[LEN];
	/*int tmp;*/
	int i;

	srand(1);

	for(i = 0; i < LEN; i++) {
		arr[i] = rand() % 100;
	}	

	vec_new(&vec, sizeof(int));

	for(i = 0; i < LEN; i++) {
		vec_insert(&vec, arr + i, i32_cmp);
	}

	vec_debug(&vec);
	vec_show(&vec, i32_show);

	for(i = 0; i < LEN; i++) {
		vec_remove(&vec, arr + i, i32_cmp);
	}

	vec_debug(&vec);
	vec_show(&vec, i32_show);

	vec_destroy(&vec);	

	return 0;
}
