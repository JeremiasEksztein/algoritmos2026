#ifndef NODE_H
#define NODE_H

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct Node {
	struct Node* next;
	void* buf;
	size_t n;
} Node;

Node* node_new(Node* next, const void* buf, size_t n);
int node_resize(Node* node, size_t new);
int node_destroy(Node* n);

#endif
