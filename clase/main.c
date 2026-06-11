#include <stdio.h>
#include <stddef.h>
#include <assert.h>

#include "tree.h"
#include "test.h"

int icmp(const void *a, const void *b)
{
    const int *x = a, *y = b;
    return *x - *y;
}

void print_int(const void *x)
{
    const int *a = x;

    printf("[%d]", *a);
}

int main(void)
{
    tBinaryTree tree;
	FILE *ordered, *unordered;
	size_t i;

    binarytree_new(&tree);

	ordered = fopen()


	for(i = 0; i < 50; ++i) {
		binarytree_add(&tree, arr + i, sizeof(Computer), computer_eq2);
	}

	binarytree_print(&tree, INORDER, computer_print);
	
    binarytree_delete(&tree);

    return 0;
}
