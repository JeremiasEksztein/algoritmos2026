#include "tree.h"

void binarysearchtree_new(BinarySearchTree *tree)
{
	if(!tree) {
		return;
	}

	*tree = NULL;
}

int binarysearchtree_load_from_file(BinarySearchTree *tree, const char *path, size_t reg_size);

int binarysearchtree_add_i(BinarySearchTree *tree, const void *elem, size_t n, cmp_fn cmp)
{
	int compar;

	while(*tree) {
		compar = cmp((*tree)->buf, elem);

		if(compar > 0) {
			tree = &(*tree)->right;
		} else if(compar < 0) {
			tree = &(*tree)->left;
		} else {
			return ERR;
		}
	}	

	*tree = malloc(sizeof(Node));

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
	(*tree)->left = NULL;
	(*tree)->right = NULL;

	return OK;
}

int binarysearchtree_add_r(BinarySearchTree *tree, const void *elem, size_t n, cmp_fn cmp)
{
	int compar;

	if(*tree) {
		compar = cmp((*tree)->buf, elem);

		if(compar > 0) {
			return binarysearchtree_add_r(&(*tree)->right, elem, n, cmp);
		} else if(compar < 0) {
			return binarysearchtree_add_r(&(*tree)->left, elem, n, cmp);
		} else {
			return ERR;
		}
	}

	*tree = malloc(sizeof(Node));

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
	(*tree)->left = NULL;
	(*tree)->right = NULL;

	return OK;	
}

int binarysearchtree_remove_i(BinarySearchTree *tree, const void *key, void *buf, size_t n, cmp_fn cmp)
{
	int compar;

	while(*tree) {
		compar = cmp((*tree)->buf, key);

		if(compar > 0) {
			tree = &(*tree)->right;
		} else if(compar < 0) {
			tree = &(*tree)->left;
		} else {
			memcpy(buf, (*tree)->buf, MIN((*tree)->n, n));

			/* What to do here? */

			return OK;
		}
	}	

	return ERR;	
}

int binarysearchtree_remove_r(BinarySearchTree *tree, const void *key, void *buf, size_t n, cmp_fn cmp)
{
	int compar;
	
	if(*tree) {
		compar = cmp((*tree)->buf, key);

		if(compar > 0) {
			return binarysearchtree_search_r(&(*tree)->left, key, buf, n, cmp);
		} else if(compar < 0) {
			return binarysearchtree_search_r(&(*tree)->left, key, buf, n, cmp);	
		} else {
			memcpy(buf, (*tree)->buf, MIN((*tree)->n, n));
			
			return OK;
		}
	}

	return ERR;
}

int binarysearchtree_search_i(const BinarySearchTree *tree, const void *key, void *buf, size_t n, cmp_fn cmp)
{
	int compar;

	while(*tree) {
		compar = cmp((*tree)->buf, key);

		if(compar > 0) {
			tree = &(*tree)->right;
		} else if(compar < 0) {
			tree = &(*tree)->left;
		} else {
			memcpy(buf, (*tree)->buf, MIN((*tree)->n, n));

			return OK;
		}
	}	

	return ERR;
}

int binarysearchtree_search_r(const BinarySearchTree *tree, const void *key, void *buf, size_t n, cmp_fn cmp)
{
	int compar;
	
	if(*tree) {
		compar = cmp((*tree)->buf, key);

		if(compar > 0) {
			return binarysearchtree_search_r(&(*tree)->left, key, buf, n, cmp);
		} else if(compar < 0) {
			return binarysearchtree_search_r(&(*tree)->left, key, buf, n, cmp);	
		} else {
			memcpy(buf, (*tree)->buf, MIN((*tree)->n, n));
			return OK;
		}
	}

	return ERR;
}

int binarysearchtree_brute_search(const BinarySearchTree *tree, const void *key, void *buf, size_t n, cmp_fn cmp)
{
	if(!tree || !*tree || !key || !buf || !cmp) {
		return ERR;
	}

	if(cmp((*tree)->buf, key) == 0) {
		memcpy(buf, (*tree)->buf, MIN((*tree)->n, n));
		return OK;
	}
	
	if(binarysearchtree_brute_search(&(*tree)->left, key, buf, n, cmp) == OK) {
		return OK;
	}

	return binarysearchtree_brute_search(&(*tree)->right, key, buf, n, cmp);
}

int binarysearchtree_min(const BinarySearchTree *tree, void *buf, size_t n)
{
	if(!tree || !*tree) {
		return ERR;
	}	

	while((*tree)->left) {
		tree = &(*tree)->left;
	}

	memcpy(buf, (*tree)->buf, MIN((*tree)->n, n));

	return OK;
}

int binarysearchtree_max(const BinarySearchTree *tree, void *buf, size_t n)
{
	if(!tree || !*tree) {
		return ERR;
	}	

	while((*tree)->right) {
		tree = &(*tree)->right;
	}

	memcpy(buf, (*tree)->buf, MIN((*tree)->n, n));

	return OK;	
}

void binarysearchtree_destroy(BinarySearchTree *tree)
{
	if(!tree || !*tree) {
		return;
	}

	binarysearchtree_destroy(&(*tree)->left);
	binarysearchtree_destroy(&(*tree)->left);

	free((*tree)->buf);
	free(*tree);
	*tree = NULL;
}
