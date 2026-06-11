#include "tree.h"

void binarytree_new(tBinaryTree *tree)
{
	if(!tree) {
		return;
	}

	*tree = NULL;
}

int binarytree_add(tBinaryTree *tree, const void *elem, unsigned n, cmp_fn cmp)
{
	int compar;
	
	if(!tree || !elem || !cmp) {
		return ERR;
	}

	while(*tree) {
		compar = cmp((*tree)->buf, elem);

		if(compar > 0) {
			tree = &(*tree)->left;
		} else if(compar < 0) {
			tree = &(*tree)->right;
		} else {
			return ERR;
		}
	}

	*tree = malloc(sizeof(tNode));

	if(!*tree) {
		return ERR;
	} 

	(*tree)->buf = malloc(n);

	if(!(*tree)->buf) {
		free(*tree);
		*tree = NULL;
		return ERR;
	}

	memcpy((*tree)->buf, elem, n);
	(*tree)->n = n;
	(*tree)->left = (*tree)->right = NULL;

	return OK;
}

static void _splice(tBinaryTree *tree)
{
	tBinaryTree *repl = tree;
	tNode *tmp;

	unsigned hl, hr;

	hl = binarytree_height(&(*tree)->left);
	hr = binarytree_height(&(*tree)->right);

	if(hl > hr) {
		tree = &(*tree)->left;

		while((*tree)->right) {
			tree = &(*tree)->right;
		}
	} else {
		tree = &(*tree)->right;

		while((*tree)->left) {
			tree = &(*tree)->left;
		}
	}

	(*repl)->buf = (*tree)->buf;
	(*repl)->n = (*tree)->n;
	tmp = *tree;

	*tree = ((*tree)->left) ? (*tree)->left : (*tree)->right;

	free(tmp);
	*tree = NULL;
}

int binarytree_rem(tBinaryTree *tree, const void *key, void *buf, unsigned n, cmp_fn cmp)
{
	int compar;
	
	if(!tree || !key || !cmp || !buf) {
		return ERR;
	}

	while(*tree) {
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

			return OK;
		}
	}

	return ERR;
}

int binarytree_search(tBinaryTree *tree, const void *key, void *buf, unsigned n, cmp_fn cmp)
{
	int compar;
	
	if(!tree || !key || !cmp || !buf) {
		return ERR;
	}

	while(*tree) {
		compar = cmp((*tree)->buf, key);

		if(compar > 0) {
			tree = &(*tree)->left;
		} else if(compar < 0) {
			tree = &(*tree)->right;
		} else {
			memcpy(buf, (*tree)->buf, MIN((*tree)->n, n));

			return OK;
		}
	}

	return ERR;	
}

static void _inorder(const tBinaryTree *tree, visit_fn visit, void *user)
{
	if(!*tree) {
		return;
	}	

	_inorder(&(*tree)->left, visit, user);
	visit((*tree)->buf, user);
	_inorder(&(*tree)->right, visit, user);
}

static void _preorder(const tBinaryTree *tree, visit_fn visit, void *user)
{
	if(!*tree) {
		return;
	}	

	visit((*tree)->buf, user);
	_preorder(&(*tree)->left, visit, user);
	_preorder(&(*tree)->right, visit, user);
}

static void _postorder(const tBinaryTree *tree, visit_fn visit, void *user)
{
	if(!*tree) {
		return;
	}	

	_postorder(&(*tree)->left, visit, user);
	_postorder(&(*tree)->right, visit, user);
	visit((*tree)->buf, user);
}

void binarytree_traverse(const tBinaryTree *tree, int traversal, visit_fn visit, void *user)
{
	if(!tree || !visit) {
		return;
	}

	switch(traversal) {
		case INORDER:
			_inorder(tree, visit, user);
			break;
		case PREORDER:
			_preorder(tree, visit, user);
			break;
		case POSTORDER:
			_postorder(tree, visit, user);
			break;
		default:
			return;
	}
}

unsigned binarytree_height(const tBinaryTree *tree)
{
	unsigned hl, hr;
	if(!tree || !*tree) {
		return 0;
	}

	hl = binarytree_height(&(*tree)->left);
	hr = binarytree_height(&(*tree)->right);

	return MAX(hl, hr) + 1;
}

unsigned binarytree_size(const tBinaryTree *tree)
{
	if(!tree || !*tree) {
		return 0;
	}

	return binarytree_size(&(*tree)->left) + binarytree_size(&(*tree)->right) + 1;
}

void binarytree_destroy(tBinaryTree *tree)
{
	if(!tree || !*tree) {
		return;
	}

	binarytree_destroy(&(*tree)->left);
	binarytree_destroy(&(*tree)->right);
	free((*tree)->buf);
	free(*tree);
	*tree = NULL;
}
