#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdlib.h>
#include <string.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) > (y) ? (y) : (x))

#define INORDER     0
#define PREORDER    1
#define POSTORDER   2

typedef int (*cmp_fn)(const void *, const void *);
typedef void (*print_fn)(const void *);

typedef struct sNode tNode;
struct sNode {
    tNode *left, *right;
    unsigned n;
    void *buf;
};

typedef tNode *tBinaryTree;

void binarytree_new(tBinaryTree *t);

int binarytree_add(tBinaryTree *t, const void *elem, unsigned n, cmp_fn cmp);

int binarytree_rem(tBinaryTree *t, const void *key, void *buf, unsigned n, cmp_fn cmp);

int binarytree_search(const tBinaryTree *t, const void *key, void *buf, unsigned n, cmp_fn cmp);
int binarytree_brutesearch(const tBinaryTree *t, const void *key, void *buf, unsigned n, cmp_fn cmp);

/*
    acordate
    - Funcion parametrica de encontrar por no-clave
    - Funciones relacionadas a indices
*/

unsigned binarytree_height(const tBinaryTree *t);

void binarytree_print(const tBinaryTree *t, int type, print_fn print);

void binarytree_delete(tBinaryTree *t);

#endif
