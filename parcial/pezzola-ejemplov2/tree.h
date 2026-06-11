#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <string.h>

#include "common.h"

typedef int (*cmp_fn)(const void *, const void *);
typedef void (*print_fn)(const void *);
typedef void (*visit_fn)(const void *, void *);

typedef enum {
	INORDER,
	POSTORDER,
	PREORDER,
} eTraversal;

typedef struct sNode tNode;
struct sNode {
	tNode *left, *right;
	unsigned n;
	void *buf;
};

typedef tNode *tBinaryTree;

void binarytree_new(tBinaryTree *tree);

int binarytree_add(tBinaryTree *tree, const void *elem, unsigned n, cmp_fn);

int binarytree_rem(tBinaryTree *tree, const void *key, void *buf, unsigned n, cmp_fn cmp);

int binarytree_search(tBinaryTree *tree, const void *key, void *buf, unsigned n, cmp_fn cmp);

int binarytree_subtree(const tBinaryTree *tree, tBinaryTree *subtr, )

void binarytree_traverse(const tBinaryTree *tree, int traversal, visit_fn visit, void *user);

unsigned binarytree_height(const tBinaryTree *tree);

unsigned binarytree_size(const tBinaryTree *tree);

void binarytree_destroy(tBinaryTree *tree);

#endif
