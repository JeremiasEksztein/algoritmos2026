#include "tree.h"

static void inorder(const BinarySearchTree *tree, print_fn print)
{
	if(!*tree) {
		return;
	}	

	inorder(&(*tree)->left, print);
	print((*tree)->buf);
	inorder(&(*tree)->right, print);
}

static void preorder(const BinarySearchTree *tree, print_fn print)
{
	if(!*tree) {
		return;
	}	

	print((*tree)->buf);
	preorder(&(*tree)->right, print);
	preorder(&(*tree)->left, print);
}

static void postorder(const BinarySearchTree *tree, print_fn print)
{
	if(!*tree) {
		return;
	}	

	postorder(&(*tree)->right, print);
	postorder(&(*tree)->left, print);
	print((*tree)->buf);
}

void binarysearchtree_traverse(const BinarySearchTree *tree, int method, print_fn print)
{
	if(!tree) {
		return;
	}

	switch(method) {
		case INORDER:
			inorder(tree, print);
			break;
		case PREORDER:
			preorder(tree, print);
			break;
		case POSTORDER:
			postorder(tree, print);
			break;
	}
}

void binarysearchtree_dfs(const BinarySearchTree *tree, size_t depth, print_fn print);
void binarysearchtree_bfs(const BinarySearchTree *tree, size_t height, print_fn print);

size_t binarysearchtree_size(const BinarySearchTree *tree)
{
	if(!tree || !*tree) {
		return 0;
	}	

	return binarysearchtree_size(&(*tree)->left) + binarysearchtree_size(&(*tree)->right) + 1;
}

size_t binarysearchtree_height(const BinarySearchTree *tree)
{
	if(!tree || !*tree) {
		return 0;
	}

	return MAX(binarysearchtree_height(&(*tree)->left), binarysearchtree_height(&(*tree)->right)) + 1;
}

size_t binarysearchtree_leaves(const BinarySearchTree *tree)
{
	if(!tree || !*tree) {
		return 0;
	}	

	if(!(*tree)->left && !(*tree)->right) {
		return 1;
	}

	return binarysearchtree_leaves(&(*tree)->left) + binarysearchtree_leaves(&(*tree)->right);
}

size_t binarysearchtree_branches(const BinarySearchTree *tree)
{
	if(!tree || !*tree) {
		return 0;
	}	

	if(!(*tree)->left && !(*tree)->right) {
		return 0;
	}

	return binarysearchtree_branches(&(*tree)->left) + binarysearchtree_branches(&(*tree)->right) + 1;
}

size_t binarysearchtree_count_if(const BinarySearchTree *tree, pred_fn pred)
{
	if(!tree || !*tree) {
		return 0;
	}	

	if(!(*tree)->left && !(*tree)->right) {
		return pred((*tree)->buf);
	}

	return binarysearchtree_count_if(&(*tree)->left, pred) + binarysearchtree_count_if(&(*tree)->right, pred) + pred((*tree)->buf);
}

int binarysearchtree_is_empty(const BinarySearchTree *tree)
{
	if(!tree) {
		return 1;
	}	

	if(!*tree) {
		return 1;
	}

	return 0;
}

int binarysearchtree_is_complete(const BinarySearchTree *tree)
{
	return (binarysearchtree_branches(tree) == (binarysearchtree_size(tree) / 2));
}
int binarysearchtree_is_avl(const BinarySearchTree *tree);

int binarysearchtree_is_balanced(const BinarySearchTree *tree)
{
	return (ABS((long)binarysearchtree_height(&(*tree)->left) - (long)binarysearchtree_height(&(*tree)->right)) <= 1);	
}

