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
    fnCmp cmp,
    fnUpdate update,
    void *user
) {
    int compar;

    while(*t) {
        compar = cmp((*t)->data, data);

        if(compar > 0) {

        } else if(compar < 0) {

        } else {
            update((*t)->data, user);
            return 2;
        }
    }

    *t = malloc(sizeof(tNode));

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

void _inorder(tBinaryTree *t, fnVisit visit, void *user)
{
    if(!*t) {
        return;
    }

    _inorder(&(*t)->left, visit, user);
    visit((*t)->data, user);
    _inorder(&(*t)->right, visit, user);
}

void binaryTreeInorder(tBinaryTree *t, fnVisit visit, void *user)
{
    if(!t || !visit || !user) {
        return;
    }

    _inorder(t, visit, user);
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
