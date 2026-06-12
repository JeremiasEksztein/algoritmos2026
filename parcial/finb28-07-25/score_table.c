#include "score_table.h"

int score_cmp(const void *a, const void *b)
{
	const tScore *x = a, *y = b;

	return x->score - y->score;
}


void score_print(const void *x, void *user)
{
	const tScore *a = x;
	int *n = user;

	printf("%d. %-*s ..... %d\n", *n, 4, a->name, a->score);
	(*n)++;
}

void scoreTableNew(tScoreTable *tbl, unsigned n)
{
	if(!tbl) {
		return;
	}

	linkedListNew(&(tbl->list));
	tbl->n = n; 
}

int scoreTableAdd(tScoreTable *tbl, const tScore *score)
{
	if(!tbl || !score) {
		return 1;
	}

	if(linkedListInsertOrderedUpToN(&(tbl->list), score, sizeof(tScore), tbl->n, score_cmp, 0)) {
		return 1;
	}

	return 0;
}

void scoreTablePrint(const tScoreTable *tbl)
{
	int i = 0;
	
	if(!tbl) {
		return;
	}


	linkedListPrint(&(tbl->list), score_print, &i);
}

void scoreTableDelete(tScoreTable *tbl)
{
	if(!tbl) {
		return;
	}

	linkedListDelete(&(tbl->list));
	tbl->n = 0;
}
