#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include "vector.h"

void expect(int val, int exp, const char* fmt, ...);

int i32_cmp(const void* lhs, const void* rhs);
void i32_show(const void* elem);

void expect(int val, int exp, const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	if(val != exp) {
		vfprintf(stderr, fmt, ap);
	}
}

int i32_cmp(const void* lhs, const void* rhs)
{
	const int* a;
	const int* b;

	a = lhs;
	b = rhs;

	return *a - *b;
}

void i32_show(const void* elem)
{
	const int* a = elem;
	printf("%d ", *a);
}

int main(void) {
	Array arr;
	int i;
	int a;
	int b[16];
	srand(1);

	a = 0;

	for(i = 0; i < 16; i++) {
		b[i] = rand() % 100;
	}

	expect(array_create(&arr, 0), ERR, "Expected %d received %d\n", ERR, OK);
	expect(array_create(&arr, SIZE_MAX), ERR, "Expected %d received%d\n", ERR, OK);
	expect(array_create(&arr, sizeof(a)), OK, "Expected %d received%d\n", OK, ERR);

	array_debug(&arr);

	expect(array_is_empty(&arr), TRUE, "Expected TRUE found FALSE\n");

	for(i = 0; i < 16; i++) {
		array_ins_ord(&arr, b + i, i32_cmp);
	}

	array_debug(&arr);
	array_show(&arr, i32_show);

	for(i = 0; i < 16; i++) {
		fprintf(stderr, "b[%d] = %d | arr[%d] = %d\n", i, b[i], i, (expect(array_get_i(&arr, i, &a), OK, "Expected OK found ERR\n"), a));
	}

	for(i = 0; i < 16; i++) {
		expect(array_rem(&arr, b + i, i32_cmp), OK, "Expected OK, found ERR at %d\n", i);
		array_show(&arr, i32_show);
	}

	array_debug(&arr);
	
	return 0;
}
