#ifndef PACKAGE_H
#define PACKAGE_H

#include "bst.h"
#include "queue.h"
#include "common.h"

typedef struct {
	char code[11];
	int dest;
	char type;
} tPackage;

int packageCmp(const void *a, const void *b);
int initQueueingSystem(tBinaryTree *buckets, int n);
int handleIncoming(tBinaryTree *buckets, tPackage *pack);
int handleDispatch(tBinaryTree *buckets, tPackage *pack);
int dumpPendingDeliveries(tBinaryTree *buckets, FILE *fpPending);
void deinitQueueingSystem(tBinaryTree *buckets);

#endif
