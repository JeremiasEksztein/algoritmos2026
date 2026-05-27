#include "binary_tree.h"

static void inorder(const BinaryTree *tree, visit_fn visit)
{
    if(!tree || !*tree) {
        return;
    }

    inorder(&(*tree)->left, visit);
    visit((*tree)->buf);
    inorder(&(*tree)->right, visit);
}

static void postorder(const BinaryTree *tree, visit_fn visit)
{
    if(!tree || !*tree) {
        return;
    }

    postorder(&(*tree)->left, visit);
    postorder(&(*tree)->right, visit);
    visit((*tree)->buf);
}

static void preorder(const BinaryTree *tree, visit_fn visit)
{
    if(!tree || !*tree) {
        return;
    }

    visit((*tree)->buf);
    preorder(&(*tree)->left, visit);
    preorder(&(*tree)->right, visit);
}

void binarytree_new(BinaryTree *tree)
{
    *tree = NULL;
}

#ifdef ADD_REC
int binarytree_add(BinaryTree *tree, const void *buf, size_t n, cmp_fn cmp)
{
    int compar;
    if(*tree) {
        compar = cmp((*tree)->buf, buf);
        if(compar > 0) {
            return binarytree_add(&(*tree)->right, buf, n, cmp);
        } else if(compar < 0) {
            return binarytree_add(&(*tree)->left, buf, n, cmp);
        } else if(compar == 0) {
            return 2;
        }
    }

    *tree = malloc(sizeof(Node));

    if(!*tree) {
        return 1;
    }

    (*tree)->buf = malloc(n);

    if(!(*tree)->buf) {
        free(*tree);
        *tree = NULL;
        return 1;
    }

    memcpy((*tree)->buf, buf, n);
    (*tree)->n = n;
    (*tree)->left = NULL;
    (*tree)->right = NULL;

    return 0;
}
#endif

#ifdef ADD_ITER
int binarytree_add(BinaryTree *tree, const void *buf, size_t n, cmp_fn cmp)
{
    while(*tree) {
        if(cmp((*tree)->buf, buf) > 0) {
            tree = &(*tree)->right;
        } else if(cmp((*tree)->buf, buf) < 0) {
            tree = &(*tree)->left;
        } else {
            return 2;
        }
    }

    *tree = malloc(sizeof(Node));

    if(!*tree) {
        return 1;
    }

    (*tree)->buf = malloc(n);

    if(!(*tree)->buf) {
        free(*tree);
        *tree = NULL;
        return 1;
    }

    memcpy((*tree)->buf, buf, n);
    (*tree)->n = n;
    (*tree)->left = NULL;
    (*tree)->right = NULL;

    return 0;
}
#endif

size_t binarytree_size(const BinaryTree *tree)
{
    if(!*tree) {
        return 0;
    }

    return binarytree_height(&(*tree)->left) + binarytree_height(&(*tree)->right) + 1;
}

size_t binarytree_height(const BinaryTree *tree)
{
	if(!*tree) {
		return 0;
	}

	return MAX(binarytree_height(&(*tree)->left), binarytree_height(&(*tree)->right)) + 1;
}

void binarytree_visit(const BinaryTree *tree, visit_fn visit, VISIT_METHOD method)
{
    if(!tree || !visit) {
        return;
    }

    switch(method) {
        case VIS_INORDER:   inorder(tree, visit); break;
        case VIS_POSTORDER: postorder(tree, visit); break;
        case VIS_PREORDER:  preorder(tree, visit); break;
        default:        return;
    }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void binarytree_destroy(BinaryTree *tree)
{
    return;
}
#pragma GCC diagnostic pop

