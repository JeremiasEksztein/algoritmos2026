#ifndef SCORE_TABLE_H
#define SCORE_TABLE_H

#include <stdio.h>

#include "list.h"

typedef struct {
	char name[4];
	unsigned score;
} tScore;

typedef struct {
	tLinkedList list;
	unsigned n;
} tScoreTable;

void scoreTableNew(tScoreTable *tbl, unsigned n);

int scoreTableAdd(tScoreTable *tbl, const tScore *score);

void scoreTablePrint(const tScoreTable *tbl);

void scoreTableDelete(tScoreTable *tbl);

#endif
