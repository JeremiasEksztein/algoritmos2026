#include "tree.h"

static void _splice(tBinaryTree *t);
static tNode **_binarytree_min(tBinaryTree *t);
static tNode **_binarytree_max(tBinaryTree *t);

static void _mut_inorder(tBinaryTree *t, visit_fn, void *user);
static void _mut_preorder(tBinaryTree *t, visit_fn, void *user);
static void _mut_postorder(tBinaryTree *t, visit_fn, void *user);

static void _mut_inorder(tBinaryTree *t, visit_fn visit, void *user)
{
    if(!*t) {
        return;
    }

    _mut_inorder(&(*t)->left, visit, user);
    visit((*t)->buf, user);
    _mut_inorder(&(*t)->right, visit, user);
}

static void _mut_preorder(tBinaryTree *t, visit_fn visit, void *user)
{
    if(!*t) {
        return;
    }

    visit((*t)->buf, user);
    _mut_preorder(&(*t)->left, visit, user);
    _mut_preorder(&(*t)->right, visit, user);
}


static void _mut_postorder(tBinaryTree *t, visit_fn visit, void *user)
{
    if(!*t) {
        return;
    }

    _mut_postorder(&(*t)->left, visit, user);
    _mut_postorder(&(*t)->right, visit, user);
    visit((*t)->buf, user);
}


static void _inorder(const tBinaryTree *t, print_fn print)
{
    if(!*t) {
        return;
    }

    _inorder(&(*t)->left, print);
    print((*t)->buf);
    _inorder(&(*t)->right, print);
}

static void _preorder(const tBinaryTree *t, print_fn print)
{
    if(!*t) {
        return;
    }

    print((*t)->buf);
    _preorder(&(*t)->left, print);
    _preorder(&(*t)->right, print);
}

static void _postorder(const tBinaryTree *t, print_fn print)
{
    if(!*t) {
        return;
    }

    _postorder(&(*t)->left, print);
    _postorder(&(*t)->right, print);
    print((*t)->buf);
}

static void _splice(tBinaryTree *t)
{
    tBinaryTree *repl = t;
    tNode *tmp;
    unsigned hl, hr;

    hl = binarytree_height(&(*t)->left);
    hr = binarytree_height(&(*t)->right);

    if(hl > hr) {
        t = &(*t)->left;
        t = _binarytree_max(t);
    } else {
        t = &(*t)->right;
        t = _binarytree_min(t);
    }

    (*repl)->buf = (*t)->buf;
    (*repl)->n = (*t)->n;
    tmp = (*t);
    (*t) = ((*t)->left) ? (*t)->left : (*t)->right;

    free(tmp);
}

void binarytree_new(tBinaryTree *t)
{
    if(!t) {
        return;
    }
    *t = NULL;
}

int binarytree_add(tBinaryTree *t, const void *elem, unsigned n, cmp_fn cmp)
{
    int compar;

    while(*t) {
        compar = cmp((*t)->buf, elem);

        if(compar > 0) {
            t = &(*t)->left;
        } else if(compar < 0) {
            t = &(*t)->right;
        } else {
            return 1;
        }
    }

    (*t) = malloc(sizeof(tNode));

    if(!*t) {
        return 1;
    }

    (*t)->buf = malloc(n);

    if(!(*t)->buf) {
        free(*t);
        *t = NULL;
        return 1;
    }

    memcpy((*t)->buf, elem, n);
    (*t)->n = n;
    (*t)->left = (*t)->right = NULL;

    return 0;
}

int binarytree_rem(tBinaryTree *t, const void *key, void *buf, unsigned n, cmp_fn cmp)
{
    int compar;

    if(!t || !*t || !key || !buf || !cmp) {
        return 1;
    }

    while(*t) {
        compar = cmp((*t)->buf, key);

        if(compar > 0) {
            t = &(*t)->left;
        } else if(compar < 0) {
            t = &(*t)->right;
        } else {
            memcpy(buf, (*t)->buf, MIN((*t)->n, n));

            free((*t)->buf);

            if(!(*t)->left && !(*t)->right) {
                free(*t);
                *t = NULL;
            } else {
                _splice(t);
            }

            return 0;
        }
    }

    return 1;
}

int binarytree_search(const tBinaryTree *t, const void *key, void *buf, unsigned n, cmp_fn cmp)
{
    int compar;

    if(!t || !*t || !key || !buf || !cmp) {
        return 1;
    }

    while(*t) {
        compar = cmp((*t)->buf, key);

        if(compar > 0) {
            t = &(*t)->left;
        } else if(compar < 0) {
            t = &(*t)->right;
        } else {
            memcpy(buf, (*t)->buf, MIN((*t)->n, n));

            return 0;
        }
    }

    return 1;
}

int binarytree_brutesearch(const tBinaryTree *t, const void *key, void *buf, unsigned n, cmp_fn cmp)
{
    int compar;
    if(!t || !*t || !key || !buf || !cmp) {
        return 1;
    }

    compar = cmp((*t)->buf, key);

    if(compar == 0) {
        memcpy(buf, (*t)->buf, MIN((*t)->n, n));
        return 0;
    }

    if(binarytree_brutesearch(&(*t)->left, key, buf, n, cmp) == 0) {
        return 0;
    }

    return binarytree_brutesearch(&(*t)->right, key, buf, n, cmp);
}

unsigned binarytree_height(const tBinaryTree *t)
{
    unsigned hl, hr;
    if(!t || !*t) {
        return 0;
    }

    hl = binarytree_height(&(*t)->left);
    hr = binarytree_height(&(*t)->right);

    return MAX(hl, hr) + 1;
}

tNode **_binarytree_min(tBinaryTree *t)
{
    if(!t || !*t) {
        return NULL;
    }

    while((*t)->left) {
        t = &(*t)->left;
    }

    return t;
}

tNode **_binarytree_max(tBinaryTree *t)
{
    if(!t || !*t) {
        return NULL;
    }

    while((*t)->right) {
        t = &(*t)->right;
    }

    return t;
}

void binarytree_print(const tBinaryTree *t, int type, print_fn print)
{
    if(!t || !*t || !print) {
        return;
    }

    switch(type) {
    case INORDER:
        _inorder(t, print);
        break;
    case PREORDER:
        _preorder(t, print);
        break;
    case POSTORDER:
        _postorder(t, print);
        break;
    }
}

void binarytree_visit(tBinaryTree *t, int type, visit_fn visit, void *user)
{
    if(!t || !*t || !visit) {
        return;
    }

    switch(type) {
    case INORDER:
        _mut_inorder(t, visit, user);
        break;
    case PREORDER:
        _mut_preorder(t, visit, user);
        break;
    case POSTORDER:
        _mut_postorder(t, visit, user);
        break;
    }
}

void binarytree_delete(tBinaryTree *t)
{
    if(!t || !*t) {
        return;
    }

    binarytree_delete(&(*t)->left);
    binarytree_delete(&(*t)->right);

    free((*t)->buf);
    free(*t);
    *t = NULL;
}
