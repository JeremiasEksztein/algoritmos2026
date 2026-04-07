#include "stack.h"
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	Stack stk1;
	Stack stk2;
	Stack stk_res;
	int ch;
	int rs1;
	int rs2;
	int rd;
	int ovfl;
	FILE* no1;
	FILE* no2;
	FILE* res;

	ovfl = 0;
	stack_new(&stk1);
	stack_new(&stk2);
	stack_new(&stk_res);
	
	no1 = fopen("num1.txt", "rt");

	if(!no1) {
		return 1;
	}

	no2 = fopen("num2.txt", "rt");

	if(!no2) {
		fclose(no1);
		return 1;
	}

	res = fopen("res.txt", "wt");

	if(!res) {
		fclose(no1);
		fclose(no2);
		return 1;
	}

	while(isdigit((ch = getc(no1)))) {
		stack_push(&stk1, &ch, sizeof(ch));
	}

	while(isdigit((ch = getc(no2)))) {
		stack_push(&stk2, &ch, sizeof(ch));
	}

	while(!stack_is_empty(&stk1) && !stack_is_empty(&stk2)) {
		stack_pop(&stk1, &rs1, sizeof(rs1));
		stack_pop(&stk2, &rs2, sizeof(rs2));
		rd = rs1 + rs2 - '0' * 2 + ovfl;
		ovfl =  (rd >= 10) ? 1 : 0;
		rd = rd % 10 + '0';
		stack_push(&stk_res, &rd, sizeof(rd));
	}

	while(!stack_is_empty(&stk1)) {
		stack_pop(&stk1, &rs1, sizeof(rs1));
		rs1 -= '0';
		rs1 += ovfl;
		ovfl = (rs1 >= 10) ? 1 : 0;		
		rs1 = rs1 % 10 + '0';
		stack_push(&stk_res, &rs1, sizeof(rs1));
	}

	while(!stack_is_empty(&stk2)) {
		stack_pop(&stk2, &rs2, sizeof(rs2));
		rs2 -= '0';
		rs2 += ovfl;
		ovfl = (rs2 >= 10) ? 1 : 0;
		rs2 = rs2 % 10 + '0';
		stack_push(&stk_res, &rs2, sizeof(rs2));
	}

	if(ovfl) {
		ovfl += '0';
		stack_push(&stk_res, &ovfl, sizeof(ovfl));
		ovfl = 0;
	}

	while(!stack_is_empty(&stk_res)) {
		stack_pop(&stk_res, &ch, sizeof(ch));
		fputc(ch, res);
	}

	stack_delete(&stk1);
	stack_delete(&stk2);
	stack_delete(&stk_res);

	fclose(no1);
	fclose(no2);
	fclose(res);

	return 0;
}
