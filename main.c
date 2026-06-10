#include <stdio.h>
#include <stddef.h>
#include <assert.h>

#include "tree.h"

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
    int arr[] = {100,90,80,75,85,95,92,97,110,105,103,108,120,111,130}, tmp, key = 110;
    int leaves[] = {75, 85, 92, 97, 103, 108, 111, 130};
    size_t i;

    binarytree_new(&tree);

    for(i = 0; i < (sizeof(arr) / sizeof(int)); ++i) {
        binarytree_add(&tree, arr + i, sizeof(int), icmp);
        printf("%d\n", arr[i]);
    }

    printf("\nRecorrido inorden\n");
    binarytree_print(&tree, INORDER, print_int);
    printf("\nRecorrido preorden\n");
    binarytree_print(&tree, PREORDER, print_int);
    printf("\nRecorrido postorden\n");
    binarytree_print(&tree, POSTORDER, print_int);

    binarytree_brutesearch(&tree, &key, &tmp, sizeof(int), icmp);

    printf("%d\n", tmp);

    for(i = 0; i < (sizeof(leaves) / sizeof(int)); ++i) {
        binarytree_rem(&tree, leaves + i, &tmp, sizeof(int), icmp);

        printf("\nRecorrido inorden\n");
        binarytree_print(&tree, INORDER, print_int);
        printf("\nRecorrido preorden\n");
        binarytree_print(&tree, PREORDER, print_int);
        printf("\nRecorrido postorden\n");
        binarytree_print(&tree, POSTORDER, print_int);
    }

    binarytree_rem(&tree, &key, &tmp, sizeof(int), icmp);

    binarytree_delete(&tree);

    return 0;
}
