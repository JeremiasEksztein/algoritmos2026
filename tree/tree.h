#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define ABS(x) (((x) < 0) ? -(x) : (x))

#define OK 0
#define ERR 1

#define INORDER 0
#define POSTORDER 1
#define PREORDER 2

typedef int (*cmp_fn)(const void *, const void *);
typedef int (*pred_fn)(const void *);
typedef void (*print_fn)(const void *);

typedef struct Node Node;
struct Node {
	Node *left, *right;
	size_t n;
	void *buf;	
};

typedef Node *BinarySearchTree;

void binarysearchtree_new(BinarySearchTree *tree);

int binarysearchtree_load_from_file(BinarySearchTree *tree, const char *path, size_t reg_size);

int binarysearchtree_add_i(BinarySearchTree *tree, const void *elem, size_t n, cmp_fn cmp);
int binarysearchtree_add_r(BinarySearchTree *tree, const void *elem, size_t n, cmp_fn cmp);

int binarysearchtree_remove_i(BinarySearchTree *tree, const void *key, void *buf, size_t n, cmp_fn cmp);
int binarysearchtree_remove_r(BinarySearchTree *tree, const void *key, void *buf, size_t n, cmp_fn cmp);

int binarysearchtree_prune_i(BinarySearchTree *tree, size_t depth);
int binarysearchtree_prune_r(BinarySearchTree *tree, size_t depth);

int binarysearchtree_search_i(const BinarySearchTree *tree, const void *key, void *buf, size_t n, cmp_fn cmp);
int binarysearchtree_search_r(const BinarySearchTree *tree, const void *key, void *buf, size_t n, cmp_fn cmp);

int binarysearchtree_brute_search(const BinarySearchTree *tree, const void *key, void *buf, size_t n, cmp_fn cmp);

int binarysearchtree_min(const BinarySearchTree *tree, void *buf, size_t n);
int binarysearchtree_max(const BinarySearchTree *tree, void *buf, size_t n);

void binarysearchtree_traverse(const BinarySearchTree *tree, int method, print_fn print);

void binarysearchtree_dfs(const BinarySearchTree *tree, size_t depth, print_fn print);
void binarysearchtree_bfs(const BinarySearchTree *tree, size_t height, print_fn print);

size_t binarysearchtree_size(const BinarySearchTree *tree);
size_t binarysearchtree_height(const BinarySearchTree *tree);
size_t binarysearchtree_leaves(const BinarySearchTree *tree);
size_t binarysearchtree_branches(const BinarySearchTree *tree);
size_t binarysearchtree_count_if(const BinarySearchTree *tree, pred_fn pred);

int binarysearchtree_is_empty(const BinarySearchTree *tree);
int binarysearchtree_is_complete(const BinarySearchTree *tree);
int binarysearchtree_is_avl(const BinarySearchTree *tree);
int binarysearchtree_is_balanced(const BinarySearchTree *tree);

void binarysearchtree_destroy(BinarySearchTree *tree);

#endif
