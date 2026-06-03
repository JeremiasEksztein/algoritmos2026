#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#define MIN(x, y) ((x) > (y) ? (y) : (x))

typedef struct sNode tNode;
struct sNode {
	tNode *next;
	size_t n;
	void *buf;
};

typedef tNode *tLinkedStack;

void linkedstack_new(tLinkedStack *stk)
{
	if(!stk) {
		return;
	}	

	*stk = NULL;
}

int linkedstack_push(tLinkedStack *stk, const void *elem, size_t n)
{
	tNode *new;
	
	if(!stk || !elem) {
		return 1;
	}

	new = malloc(sizeof(tNode));

	if(!new) {
		return 1;
	}	

	new->buf = malloc(n);

	if(!new->buf) {
		free(new);
		return 1;
	}

	new->next = NULL;
	new->n = n;
	memcpy(new->buf, elem, n);

	new->next = *stk;
	*stk = new;

	return 0;
}

int linkedstack_pop(tLinkedStack *stk, void *buf, size_t n)
{
	tNode *tmp;
	
	if(!stk || !buf || !*stk) {
		return 1;
	}

	tmp = *stk;
	*stk = tmp->next;

	memcpy(buf, tmp->buf, MIN(tmp->n, n));

	free(tmp->buf);
	free(tmp);

	return 0;
}

int linkedstack_peek(const tLinkedStack *stk, void *buf, size_t n)
{
	if(!stk || !buf || !*stk) {
		return 1;
	}	

	memcpy(buf, (*stk)->buf, MIN((*stk)->n, n));
	
	return 0;
}

int linkedstack_is_empty(const tLinkedStack *stk)
{
	if(!stk || !*stk) {
		return 1;
	}

	return 0;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int linkedstack_is_full(const tLinkedStack *stk, size_t n)
{
	return 0;	
}
#pragma GCC diagnostic pop

void linkedstack_destroy(tLinkedStack *stk)
{
	tNode *tmp;

	if(!stk) {
		return;
	}

	while(*stk) {
		tmp = *stk;
		stk = &(*stk)->next;
		free(tmp->buf);
		free(tmp);
	}
	*stk = NULL;
}

int main(void)
{
	FILE *src1, *src2, *dst;
	tLinkedStack stk1, stk2, out;
	int ch, rd, rs1, rs2, ovfl = 0;

	src1 = fopen("num1.txt", "rt");

	if(!src1) {
		fprintf(stderr, "Err: could not open 'num1.txt'\n");
		return 1;
	}

	src2 = fopen("num2.txt", "rt");

	if(!src2) {
		fclose(src1);
		fprintf(stderr, "Err: could not open 'num2.txt'\n");
		return 1;
	}

	dst = fopen("resultado.txt", "wt");

	if(!dst) {
		fclose(src2);
		fclose(src1);
		fprintf(stderr, "Err: could not create 'resultado.txt'\n");
	}

	linkedstack_new(&stk1);
	while((ch = getc(src1)) >= '0' && ch <= '9') {
		linkedstack_push(&stk1, &ch, sizeof(int));
	}

	linkedstack_new(&stk2);
	while((ch = getc(src2)) >= '0' && ch <= '9') {
		linkedstack_push(&stk2, &ch, sizeof(int));
	}

	linkedstack_new(&out);
	while(!linkedstack_is_empty(&stk1) && !linkedstack_is_empty(&stk2)) {
		linkedstack_pop(&stk1, &ch, sizeof(int));
		rs1 = ch - '0';
		linkedstack_pop(&stk2, &ch, sizeof(int));
		rs2 = ch - '0';

		rd = rs1 + rs2 + ovfl;
		ovfl = (rd >= 10) ? 1 : 0;
		rd = rd % 10 + '0';
		linkedstack_push(&out, &rd, sizeof(int)); /* somewhat cursed */
	}

	while(!linkedstack_is_empty(&stk1)) {
		linkedstack_pop(&stk1, &ch, sizeof(int));
		rs1 = ch - '0';
		rd = rs1 + ovfl;
		ovfl = (rd >= 10) ? 1 : 0;
		rd = rd % 10 + '0';
		linkedstack_push(&out, &rd, sizeof(int)); /* somewhat cursed */
	}

	while(!linkedstack_is_empty(&stk2)) {
		linkedstack_pop(&stk2, &ch, sizeof(int));
		rs2 = ch - '0';
		rd = rs1 + rs2 + ovfl;
		ovfl = (rd >= 10) ? 1 : 0;
		rd = rd % 10 + '0';
		linkedstack_push(&out, &rd, sizeof(int)); /* somewhat cursed */
	}

	if(ovfl == 1) {
		rd = 1 + '0';
		linkedstack_push(&out, &rd, sizeof(int));
	}

	while(!linkedstack_is_empty(&out)) {
		linkedstack_pop(&out, &ch, sizeof(int));
		fputc(ch, dst);
	}

	linkedstack_destroy(&out);
	linkedstack_destroy(&stk2);
	linkedstack_destroy(&stk1);

	fclose(dst);
	fclose(src2);
	fclose(src1);

	return 0;
}
