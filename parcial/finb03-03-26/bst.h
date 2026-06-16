#ifndef BST_H
#define BST_H

#include <stdlib.h>
#include <string.h>

#include "common.h"

#define INORDER
#define POSTORDER
#define PREORDER

typedef struct sTreeNode tTreeNode;
struct sTreeNode {
	tTreeNode *left, *right;
	unsigned n;
	void *buf;
};

typedef tTreeNode *tBinaryTree;

void binaryTreeNew(tBinaryTree *t);

int binaryTreeAdd(tBinaryTree *t, const void *data, unsigned n, fnCmp cmp);

int binaryTreeRem(
	tBinaryTree *t,
	const void *key,
	void *buf,
	unsigned n,
	fnCmp cmp	
);

int binaryTreeFind(
	tBinaryTree *t,
	const void *key,
	void *buf,
	unsigned n,
	fnCmp cmp
);

void binaryTreeVisit(tBinaryTree *t, int type, fnAction action);

void binaryTreeDelete(tBinaryTree *t);

#endif
