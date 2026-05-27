#ifndef BINARY_TREE_H_INCLUDED
#define BINARY_TREE_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y)) 

#ifndef ADD_REC
#define ADD_ITER
#endif

typedef enum {
    VIS_INORDER,
    VIS_POSTORDER,
    VIS_PREORDER
} VISIT_METHOD;

typedef void (*visit_fn)(const void*);
typedef int (*cmp_fn)(const void*, const void*);

typedef struct Node Node;
struct Node {
    Node *left, *right;
    size_t n;
    void *buf;
};

typedef Node *BinaryTree;

void binarytree_new(BinaryTree *tree);

int binarytree_add(BinaryTree *tree, const void *buf, size_t n, cmp_fn cmp);

size_t binarytree_size(const BinaryTree *tree);
size_t binarytree_height(const BinaryTree *tree);

void binarytree_visit(const BinaryTree *tree, visit_fn visit, VISIT_METHOD method);

void binarytree_destroy(BinaryTree *tree);

#endif
