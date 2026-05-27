#include "list.h"
#include "../stack/stack.h"

static Node *MAKE_NODE(Node *next, size_t n, const void *buf);
static void DELETE_NODE(Node *node);

static Node *MAKE_NODE(Node *next, size_t n, const void *buf) 
{
	Node *new;
	
	new = malloc(sizeof(Node));
	
	if(!new) {
		return NULL;
	}	

	new->buf = malloc(n);

	if(!new->buf) {
		free(new);
		return NULL;
	}

	if(BUFFER_ZEROING) {
		memset(new->buf, 0, n);
	}

	new->next = next;
	new->n = n;
	memcpy(new->buf, buf, n);

	return new;
}

static void DELETE_NODE(Node *node)
{
	if(!node) {
		return;
	}

	free(node->buf);
	free(node);
}

/*
static Node *merge_sort(Node *node, cmp_fn cmp);
static Node *merge(Node *lo, Node *hi, cmp_fn cmp);

static Node *merge_sort(Node *node, cmp_fn cmp)
{
	Node *slow = node, *fast = node, *mid = NULL;
	
	if(!node) {
		return NULL;
	}	
	
	if(!node->next) {
		return node;
	}

	while(fast->next && fast->next->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	
	while(fast && fast->next) {
		fast = fast->next->next;
		if(fast) {
			slow = slow->next;
		}
	}

	mid = slow->next;
	slow->next = NULL;

	return merge(merge_sort(node, cmp), merge_sort(mid, cmp), cmp);
}

static Node *merge(Node *lo, Node *hi, cmp_fn cmp)
{
	if(!hi) {
		return lo;
	}
	if(!lo) {
		return hi;
	}

	if(cmp(lo->buf, hi->buf) >= 0) {
		lo->next = merge(lo->next, hi, cmp);
		return lo;
	} 
	
	hi->next = merge(lo, hi->next, cmp);

	return hi;
}*/

int slinkedlist_new(SLinkedList *list)
{
	if(!list) {
		return ERR;
	}

	*list = NULL;

	return OK;
}

size_t slinkedlist_len(const SLinkedList *list)
{
	size_t n;

	n = 0;

	while(*list) {
		list = &((*list)->next);
		n++;
	}	

	return n;
}

int slinkedlist_is_empty(const SLinkedList *list)
{
	if(!list) {
		return UNKNOWN;
	}	

	return (!*list) ? TRUE : FALSE;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int slinkedlist_is_full(const SLinkedList *list, size_t n)
{
	if(!list) {
		return UNKNOWN;
	}

	return FALSE;
}
#pragma GCC diagnostic pop

int slinkedlist_set(SLinkedList *list, size_t i, const void *elem, size_t n)
{	
	if(!list || !elem) {
		return ERR;
	}

	while(*list && i) {
		list = &(*list)->next;
		i--;
	}	

	if(i && !*list) {
		return ERR;
	}

	memcpy((*list)->buf, elem, MIN((*list)->n, n));

	return OK;
}

int slinkedlist_get(const SLinkedList *list, size_t i, void *buf, size_t n)
{
	if(!list || !buf) {
		return ERR;
	}

	while(*list && i) {
		list = &(*list)->next;
		i--;
	}	

	if(*list == NULL) {
		return ERR;
	}

	assert(i == 0 && *list != NULL);
	memcpy(buf, (*list)->buf, MIN((*list)->n, n));	

	return OK;
}

int slinkedlist_addlo(SLinkedList *list, const void *elem, size_t n)
{
	Node *tmp;
	
	if(!list || !elem) {
		return ERR;
	}	

	tmp = MAKE_NODE(NULL, n, elem);

	if(!tmp) {
		return ERR;
	}

	tmp->next = *list;
	*list = tmp;

	return OK;
}


int slinkedlist_addhi(SLinkedList *list, const void *elem, size_t n)
{
	Node *tmp;
	
	if(!list || !elem) {
		return ERR;
	}	

	tmp = MAKE_NODE(NULL, n, elem);

	if(!tmp) {
		return ERR;
	}

	while((*list)->next) {
		list = &(*list)->next;
	}

	(*list)->next = tmp;
	
	return OK;
}

int slinkedlist_add(SLinkedList *list, size_t i, const void *elem, size_t n)
{
	Node *tmp;
	
	if(!list || !elem) {
		return ERR;
	}	

	while((*list) && i) {
		list = &(*list)->next;
		i--;
	}

	if(i && !*list) {
		return ERR;
	}
	
	tmp = MAKE_NODE(NULL, n, elem);

	if(!tmp) {
		return ERR;
	}

	tmp->next = *list;
	*list = tmp;

	return OK;
}

int slinkedlist_remlo(SLinkedList *list, void *buf, size_t n)
{
	Node *tmp;

	if(!list || !buf || !*list) {
		return ERR;
	}	

	tmp = *list;
	*list = tmp->next;

	memcpy(buf, tmp->buf, MIN(tmp->n, n));

	DELETE_NODE(tmp);

	return OK;	
}

int slinkedlist_remhi(SLinkedList *list, void *buf, size_t n)
{
	Node *tmp;

	if(!list || !buf) {
		return ERR;
	}	

	while(*list) {
		list = &((*list)->next);
	}

	tmp = *list;
	
	memcpy(buf, tmp->buf, MIN(tmp->n, n));

	DELETE_NODE(tmp);

	return OK;			
}

int slinkedlist_rem(SLinkedList *list, size_t i, void *buf, size_t n)
{
	Node *tmp;

	if(!list || !buf) {
		return ERR;
	}	

	while(*list && i) {
		list = &((*list)->next);
		i--;
	}

	if(i && !(*list)) {
		return ERR;
	}

	tmp = *list;
	*list = (*list)->next;
	
	memcpy(buf, tmp->buf, MIN(tmp->n, n));

	DELETE_NODE(tmp);

	return OK;				
}

int slinkedlist_add_ordered(SLinkedList *list, const void *elem, size_t n, cmp_fn cmp)
{
	Node *tmp;
	
	if(!list || !elem || !cmp) {
		return ERR;
	}	

	tmp = MAKE_NODE(NULL, n, elem);

	if(!tmp) {
		return ERR;
	}

	while(*list && cmp((*list)->buf, elem) > 0) {
		list = &(*list)->next;
	}

	tmp->next = *list;
	*list = tmp;
	
	return OK;		
}

int slinkedlist_rem_ordered(SLinkedList *list, void *buf, size_t n, const void *key, cmp_fn cmp)
{
	Node *tmp;
	int res;


	/* What the fuck is this, why does it allocate a new node?? */
	if(!list || !buf || !cmp) {
		return ERR;
	}	

	/*

	I don't know
	
	tmp = MAKE_NODE(NULL, n, buf);

	if(!tmp) {
		return ERR;
	}
	*/

	while(*list && (res = cmp((*list)->buf, key)) > 0) {
		list = &(*list)->next;
	}

	if(res == 0 && *list) {
		tmp = *list;
		list = &tmp->next;

		memcpy(buf, tmp->buf, MIN(tmp->n, n));

		DELETE_NODE(tmp);

		return OK;
	}
	
	return ERR;		
}

int slinkedlist_add_unique(SLinkedList *list, const void *elem, size_t n, cmp_fn cmp, unique_fn unique, void *user)
{
	Node *tmp;
	int res;
	
	if(!list || !elem || !cmp) {
		return ERR;
	}	

	while(*list && (res = cmp((*list)->buf, elem)) > 0) {
		list = &(*list)->next;
	}

	if(res == 0 && *list) {
		if(unique) {
			unique((*list)->buf, elem, user);
		} else {
			memcpy((*list)->buf, elem, MIN((*list)->n, n));
		}

		return OK;
	}

	tmp = MAKE_NODE(NULL, n, elem);

	if(!tmp) {
		return ERR;
	}

	tmp->next = *list;
	*list = tmp;
	
	return OK;			
}

/* 
Got literally zero clue what this is
Think its some sort of selection sort?	
*/
int slinkedlist_sort(SLinkedList *list, cmp_fn cmp)
{
	SLinkedList *first = list, *q;
	Node *tmp;

	if(!*list) {
		return OK;
	}

	while((*list)->next) {
		if(cmp((*list)->buf, (*list)->next->buf) > 0) {
			q = first;
			tmp = (*list)->next;

			(*list)->next = tmp->next;

			while(cmp((*q)->buf, tmp->buf) > 0) {
				q = &(*q)->next;
			}

			tmp->next = *q;
			*q = tmp;
		} else {
			list = &(*list)->next;
		}
	}

	return OK;
}

int slinkedlist_lsearch(const SLinkedList *list, const void *key, cmp_fn cmp)
{
	size_t i;
	
	if(!list || !key || !cmp) {
		return -1;
	}	

	i = 0;

	while(*list && cmp((*list)->buf, key) != 0) {
		list = &(*list)->next;
		i++;
	}

	if(!*list) {
		return -1;	
	}

	return i;
}

int slinkedlist_ord_search(const SLinkedList *list, const void *key, cmp_fn cmp)
{
	size_t i;
	int res;
	
	if(!list || !key || !cmp) {
		return -1;
	}	

	i = 0;

	while(*list && (res = cmp((*list)->buf, key)) > 0) {
		list = &(*list)->next;
		i++;
	}

	if(!*list) {
		return -1;	
	}

	return i;	
}

int slinkedlist_print(const SLinkedList *list, print_fn print)
{
	if(!list || !print) {
		return ERR;
	}	

	while(*list) {
		print((*list)->buf);
		list = &(*list)->next;
	}

	return OK;
}

#ifdef REV_ITER
void slinkedlist_rev_print(const SLinkedList *list, print_fn print)
{
	LinkedStack stk;
	Node *node;
	
	if(!list || !print) {
		return;
	}

	if(*list = NULL) {
		return;
	}

	linkedstack_new(&stk);
	
	while(*list) {
		linkedstack_push(&stk, *list, sizeof(Node*));
		list = &(*list)->next;
	}

	while(!linkedstack_is_empty(&stk) {
		linkedstack_pop(&stk, node, sizeof(Node*));
		print(node->buf);
	}

	linkedstack_destroy(&stk);
}
#else
void slinkedlist_rev_print(const SLinkedList *list, print_fn print)
{
	if(!list || !print) {
		return;
	}

	if(*list == NULL) {
		return;
	}

	slinkedlist_rev_print(&(*list)->next, print);
	print((*list)->buf);
}
#endif

/*
int slinkedlist_copy(SLinkedList *dst, SLinkedList *src);
int slinkedlist_concat(SLinkedList *dst, SLinkedList *src);
int slinkedlist_concatv(SLinkedList *dst, ...);

int slinkedlist_map(SLinkedList *dst, SLinkedList *src, map_fn map, void* user);
int slinkedlist_filter(SLinkedList *dst, SLinkedList *src, filter_fn filter, void *user);
int slinkedlist_reduce(void *reduction, SLinkedList *src, reduce_fn reduce, void *user);
int slinkedlist_foreach(SLinkedList *list, foreach_fn foreach, void *user);

int slinkedlist_into_iter(SLinkedList *list, ListIterator *iter);
*/

void slinkedlist_destroy(SLinkedList *list)
{
	Node *tmp;
	
	if(!list) {
		return;
	};

	while(*list) {
		tmp = *list;
		*list = tmp->next;
		DELETE_NODE(tmp);
	}

	*list = NULL;
}
