#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdlib.h>
#include <string.h>

typedef int (*fnCmp)(const void *, const void *);
typedef void (*fnUpdate)(void *, void *);
typedef void (*fnVisit)(void *, void *);

typedef struct sNode tNode;
struct sNode {
    tNode *left, *right;
    unsigned n;
    void *data;
};

typedef tNode *tBinaryTree;

void binaryTreeNew(tBinaryTree *t);

int binaryTreeInsertOrUpdate(
    tBinaryTree *t,
    const void *data,
    unsigned n,
    fnCmp cmp,
    fnUpdate update,
    void *user
);

void binaryTreeInorder(tBinaryTree *t, fnVisit visit, void *user);

void binaryTreeDelete(tBinaryTree *t);

#endif
