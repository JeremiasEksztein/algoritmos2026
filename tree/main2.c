#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) > (y) ? (y) : (x))

typedef int (*cmp_fn)(const void*, const void*);
typedef void (*print_fn)(const void*);

typedef struct sNode tNode;
struct sNode {
	tNode *left, *right;
	size_t n;
	void *buf;
};

typedef tNode *tBinaryTree;

void binarytree_inorder(const tBinaryTree *tree, print_fn print)
{
	if(!tree || !*tree) {
		return;
	}	

	binarytree_inorder(&(*tree)->left, print);
	print((*tree)->buf);
	binarytree_inorder(&(*tree)->right, print);	
}

void binarytree_preorder(const tBinaryTree *tree, print_fn print)
{
	if(!tree || !*tree) {
		return;
	}	

	print((*tree)->buf);
	binarytree_preorder(&(*tree)->left, print);
	binarytree_preorder(&(*tree)->right, print);			
}

void binarytree_postorder(const tBinaryTree *tree, print_fn print)
{
	if(!tree || !*tree) {
		return;
	}	

	binarytree_postorder(&(*tree)->left, print);
	binarytree_postorder(&(*tree)->right, print);				
	print((*tree)->buf);
}

void binarytree_bfs(const tBinaryTree *tree, print_fn print);
void binarytree_dfs(const tBinaryTree *tree, print_fn print);

size_t binarytree_height(const tBinaryTree *tree)
{
	size_t hl, hr;

	if(!tree || !*tree) {
		return 0;
	}	

	hl = binarytree_height(&(*tree)->left);
	hr = binarytree_height(&(*tree)->right);

	return MAX(hl, hr) + 1;
}

size_t binarytree_size(const tBinaryTree *tree)
{
	if(!tree || !*tree) {
		return 0;
	}

	return binarytree_size(&(*tree)->left) + binarytree_size(&(*tree)->right);
}

void binarytree_new(tBinaryTree *tree)
{
	if(!tree) {
		return;
	}
	
	*tree = NULL;
}

int binarytree_add(tBinaryTree *tree, const void *elem, size_t n, cmp_fn cmp)
{
	int compar;	

	while((*tree)) {
		compar = cmp((*tree)->buf, elem);

		if(compar > 0) {
			tree = &(*tree)->left;
		} else if(compar < 0) {
			tree = &(*tree)->right;
		} else {
			return 1;
		}
	}

	(*tree) = malloc(sizeof(tNode));

	if(!(*tree)) {
		return 1;
	}

	(*tree)->buf = malloc(n);

	if(!(*tree)->buf) {
		free(*tree);
		*tree = NULL;
		return 1;
	}

	memcpy((*tree)->buf, elem, n);
	(*tree)->n = n;
	(*tree)->left = NULL;
	(*tree)->right = NULL;

	return 0;
}

static void _splice(tBinaryTree *tree)
{
	tBinaryTree *repl = tree;
	tNode *tmp;
	size_t hl, hr;

	hl = binarytree_height(&(*tree)->left);
	hr = binarytree_height(&(*tree)->right);

	if(hl > hr) {
		tree = &(*tree)->left;

		while((*tree)->right) {
			tree = &(*tree)->right;
		}
	} else {
		tree = &(*tree)->left;

		while((*tree)->right) {
			tree = &(*tree)->right;
		}
	}

	(*repl)->buf = (*tree)->buf;
	(*repl)->n = (*tree)->n;
	tmp = (*tree);
	(*tree) = ((*tree)->left) 
					  ? (*tree)->left
					  : (*tree)->right;

	free(tmp);	
}

int binarytree_rem(tBinaryTree *tree, const void *key, void *buf, size_t n, cmp_fn cmp)
{
	int compar;	

	while((*tree)) {
		compar = cmp((*tree)->buf, key);

		if(compar > 0) {
			tree = &(*tree)->left;
		} else if(compar < 0) {
			tree = &(*tree)->right;
		} else {
			memcpy(buf, (*tree)->buf, MIN((*tree)->n, n));

			free((*tree)->buf);

			if(!(*tree)->left && !(*tree)->right) {
				free(*tree);
				*tree = NULL;
			} else {
				_splice(tree);
			}

			return 0;
		}
	}

	return 1;	
}

int binarytree_find(const tBinaryTree *tree, const void *key, void *buf, size_t n, cmp_fn cmp)
{
	int compar;	

	while((*tree)) {
		compar = cmp((*tree)->buf, key);

		if(compar > 0) {
			tree = &(*tree)->left;
		} else if(compar < 0) {
			tree = &(*tree)->right;
		} else {
			memcpy(buf, (*tree)->buf, MIN((*tree)->n, n));

			return 0;
		}
	}

	return 1;	
}

void binarytree_destroy(tBinaryTree *tree)
{
	if(!tree || !*tree) {
		return;
	}

	binarytree_destroy(&(*tree)->left);
	binarytree_destroy(&(*tree)->right);
	free((*tree)->buf);
	free((*tree));	
}

int icmp(const void *l, const void *r)
{
	const int *a = l, *b = r;

	return *a - *b;
}

void printi(const void *n)
{
	const int *i = n;

	printf("[%d]", *i);
}

int main(void)
{
	tBinaryTree t;
	int arr[] = {100,90,80,75,85,95,92,97,110,105,103,108,120,111,130}, tmp, key = 100;
	size_t i;

	binarytree_new(&t);

	for(i = 0; i < (sizeof(arr) / sizeof(int)); ++i) {
		binarytree_add(&t, arr + i, sizeof(int), icmp);
	}

	binarytree_inorder(&t, printi);
	puts("\n");

	binarytree_rem(&t, &key, &tmp, sizeof(int), icmp);

	binarytree_inorder(&t, printi);
	puts("\n");

	binarytree_destroy(&t);
	
	return 0;
}
