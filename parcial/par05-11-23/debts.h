#ifndef DEBTS_H
#define DEBTS_H

#include <string.h>
#include "tree.h"

typedef struct {
	char license[8];
	int quotaNumber;
	char name[25];
	int id;
	int dueDate;
	float amount;
} tQuota;

int idCmp(const void *, const void *);
int idLicenseCmp(const void *, const void *);

void amountUpdate(void *, void *);
int idWrite(void *, void *);
int idLicenseWrite(void *, void *);

void loadFileIntoBST(tBinaryTree *t, const char *path, int (*cmp)(const void *, const void *), void (*update)(void *, void *));

void writeBstToFile(tBinaryTree *t, const char *path, int (*write)(void *, void *));

#endif
