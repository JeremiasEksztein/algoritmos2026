#ifndef PACKAGE_H
#define PACKAGE_H

#include "common.h"
#include "tree.h"
#include "queue.h"

typedef struct {
	char code[11];
	int dest;
	char priority;
} tPackage;

typedef struct {
	tBinaryTree t;
	int destNo, maxCap;
} tDeliverySystem;

int packageCmp(const void *a, const void *b);

int initDeliverySystem(tDeliverySystem *d, int destNo, int maxCap);

int handleInbound(tDeliverySystem *d, tPackage *p);

int handleOutbound(tDeliverySystem *d, int dest);

void dumpPending(tDeliverySystem *d, FILE *fpDump);

void uninitDeliverySystem(tDeliverySystem *d);


#endif
