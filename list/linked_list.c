#include "list.h"

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
No real idea what this even means
int slinkedlist_rem_unique(SLinkedList *list, void *buf, size_t n, cmp_fn cmp, unique_fn unique, void *user);
*/



/*
	desired = 10 -> 9 -> 7 -> 6 -> 1 -> nil

	1 -> 7 -> 10 -> 9 -> 6 -> nil
	
	fn sort(l, ord) { 
		start := l
		tmp := nil

		while start != nil {
			best := start
			tmp := start->next
			
			while tmp != nil {
				if ord(best, tmp) <= 0 {
					best := tmp
				}
				tmp := tmp->next
			}

			tmp := start
			start := best
			best := tmp		

			start := start->next	
		}
	}

	1 -> 7 -> 10 -> 9 -> 6 -> nil

	fn merge_sort(l, cmp) {
		lo := nil
		hi := nil
		n := 0
		i := 0

		while l != nil {
			l = l.next
			n := n + 1
		}

		if n <= 1 {
			return l
		}

		while l != nil {
			if i < (n / 2) {
				append(lo, l)
			} else {
				append(hi, l)
			}

			i := i + 1
		}
	
		merge(merge_sort(lo, cmp), merge_sort(hi, cmp), cmp)
	}

	fn merge(lo, hi, cmp) {
		res := nil
		
		while lo != nil && hi != nil {
			if cmp(lo, hi) >= 0 {
				append(res, lo)
				lo := lo.next
			} else {
				append(res, hi)
				hi := hi.next
			}
		}

		while lo != nil {
			append(res, lo)
			lo := lo.next
		} 
		while hi != nil {
			append(res, hi)
			hi := hi.next
		}

		return res
	}

	fn append(dst, src) {
		if dst != nil {
			dst := src
		}
		dst.next := src
	}
*/

int slinkedlist_sort(SLinkedList *list, cmp_fn cmp)
{
	merge_sort(*list, cmp);

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
