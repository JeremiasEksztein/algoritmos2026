#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <string.h>

typedef struct sNode tNode;
struct sNode {
	tNode *next;
	unsigned n;
	void *buf;
};

int nodeNew(tNode *node, unsigned n, void *buf);

void nodeDelete(tNode *node);

#endif
