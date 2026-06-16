#include "tree.h"

void binaryTreeNew(tBinaryTree *t)
{
	if(!t) {
		return;
	}

	*t = NULL;
}

int binaryTreeInsertOrUpdate(
	tBinaryTree *t, 
	const void *data, 
	unsigned n, 
	int (*cmp)(const void *, const void *),
	int (*update)(void *, void *),
	void *user
) {
	int compar;

	while(*t) {
		compar = cmp((*t)->data, data);

		if(compar > 0) {
			t = &(*t)->left;
		} else if(compar < 0) {
			t = &(*t)->right;
		} else {
			update((*t)->data, user);
			return 2;
		}
	}

	(*t) = malloc(sizeof(tNode));

	if(!*t) {
		return 1;
	}

	(*t)->data = malloc(n);

	if(!(*t)->data) {
		free(*t);
		*t = NULL;
		return 1;
	}

	memcpy((*t)->data, data, n);
	(*t)->n = n;
	(*t)->left = (*t)->right = NULL;

	return 0;
}

void _inorder(tBinaryTree *t, int (*visit)(void *, void *), void *user)
{
	if(!*t) {
		return;
	}

	_inorder(&(*t)->left, visit, user);
	visit((*t)->data, user);
	_inorder(&(*t)->left, visit, user);
}

int binaryTreeInorder(tBinaryTree *t, int (*visit)(void *, void *), void *user)
{
	if(!t || !*t || !visit) {
		return 1;
	}	

	_inorder(t, visit, user);

	return 0;
}

void binaryTreeDelete(tBinaryTree *t)
{
	if(!t || !*t) {
		return;
	}

	binaryTreeDelete(&(*t)->left);
	binaryTreeDelete(&(*t)->right);

	free((*t)->data);
	free(*t);
	*t = NULL;
}
