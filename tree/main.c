#include "tree.h"

int main(void)
{
	BinarySearchTree bst;

	binarysearchtree_new(&bst);

	binarysearchtree_destroy(&bst);
	
	return 0;
}
