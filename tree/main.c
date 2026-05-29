#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree.h"


int icmp(const void *l, const void *r)
{
	const int *a = l, *b = r;

	return *a - *b;
}

void printi(const void *a)
{
	const int *i = a;

	printf("[%d]", *i);
}

int main(void)
{
	BinarySearchTree bst;
	int arr[] = {50, 25, 75, 20, 30, 15, 23, 28, 40, 70, 80, 65, 72, 76, 85};
	int tmp;
	size_t i;

	binarysearchtree_new(&bst);

	for(i = 0; i < (sizeof(arr) / sizeof(int)); ++i) {
		printf("[%d]", arr[i]);
		binarysearchtree_add_i(&bst, arr + i, sizeof(int), icmp);
	}

	printf("\n");
	binarysearchtree_traverse(&bst, INORDER, printi);
	printf("\n");
	binarysearchtree_traverse(&bst, PREORDER, printi);
	printf("\n");
	binarysearchtree_traverse(&bst, POSTORDER, printi);
	printf("\n");

	binarysearchtree_min(&bst, &tmp, sizeof(int));
	printf("min: %d\n", tmp);
	binarysearchtree_max(&bst, &tmp, sizeof(int));
	printf("max: %d\n", tmp);

	printf("size: %lu\n", binarysearchtree_size(&bst));
	printf("height: %lu\n", binarysearchtree_height(&bst));
	printf("leaves: %lu\n", binarysearchtree_leaves(&bst));
	printf("branches: %lu\n", binarysearchtree_branches(&bst));

	for(i = 0; i < (sizeof(arr) / sizeof(int)); ++i) {
		binarysearchtree_traverse(&bst, INORDER, printi);
		printf("\n");
		binarysearchtree_remove_r(&bst, arr + i, &tmp, sizeof(int), icmp);
	}

	printf("size: %lu\n", binarysearchtree_size(&bst));
	printf("height: %lu\n", binarysearchtree_height(&bst));
	printf("leaves: %lu\n", binarysearchtree_leaves(&bst));
	printf("branches: %lu\n", binarysearchtree_branches(&bst));

	binarysearchtree_destroy(&bst);
	
	return 0;
}
