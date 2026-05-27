#include "binary_tree.h"

int main(void)
{
	BinaryTree tr;

	binarytree_new(&tr);

	binarytree_destroy(&tr);
	
	return 0;
}
