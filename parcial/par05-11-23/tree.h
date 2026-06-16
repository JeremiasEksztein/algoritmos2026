#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <string.h>

typedef struct sNode tNode;
struct sNode {
	tNode *left, *right;
	unsigned n;
	void *data;	
};

typedef tNode *tBinaryTree;

void binaryTreeNew(tBinaryTree *t);

int binaryTreeInsertOrUpdate(
	tBinaryTree *t, 
	const void *data, 
	unsigned n, 
	int (*cmp)(const void *, const void *),
	int (*update)(void *, void *),
	void *user
);

int binaryTreeInorder(tBinaryTree *t, int (*visit)(void *, void *), void *user);

void binaryTreeDelete(tBinaryTree *t);

#endif
