#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#ifndef BUFFER_ZEROING
#define BUFFER_ZEROING 0
#endif

typedef struct Node Node;
struct Node {
	Node *next;
	size_t n;
	void *buf;
};

Node *make_node(Node *next, size_t n, void *buf);

void delete_node(Node *node);

typedef struct DNode DNode;
struct DNode {
	DNode * next;
	DNode *prev;	
	size_t n;
	void *buf;
};

DNode *make_dnode(DNode *next, DNode *prev, size_t n, void *buf);

void delete_dnode(DNode *node);

#endif
