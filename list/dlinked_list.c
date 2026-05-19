#include "list.h"
#include <assert.h>

static DNode *MAKE_NODE(DNode *next, DNode *prev, size_t n, const void *buf);
static void DELETE_NODE(DNode *node);

static DNode *MAKE_NODE(DNode *next, DNode *prev, size_t n, const void *buf) 
{
	DNode *new;
	
	new = malloc(sizeof(DNode));
	
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
	new->prev = prev;
	new->n = n;
	memcpy(new->buf, buf, n);

	return new;
}

static void DELETE_NODE(DNode *node)
{
	if(!node) {
		return;
	}

	free(node->buf);
	free(node);
}

int dlinkedlist_new(DLinkedList *list)
{
	if(!list) {
		return ERR;
	}

	*list = NULL;

	return OK;
}

size_t dlinkedlist_len(const DLinkedList *list)
{
	DNode *cur = *list, *lo, *hi;
	size_t len = 0, lo_len = 0, hi_len = 0;
	
	if(!list) {
		return -1;
	}

	if(!cur) {
		return 0;
	}

	lo = hi = cur;

	while(lo->prev && hi->next) {
		lo = lo->prev;
		lo_len++;

		hi = hi->next;
		hi_len++;
	}

	while(lo->prev) {
		lo = lo->prev;
		lo_len++;
	}

	while(hi->next) {
		hi = hi->next;
		hi_len++;
	}

	len = hi_len + lo_len + 1;

	return len;
}

int dlinkedlist_is_empty(const DLinkedList *list)
{
	if(!list) {
		return UNKNOWN;
	}	

	return (*list == NULL) ? TRUE : FALSE;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int dlinkedlist_is_full(const DLinkedList *list, size_t n)
{
	return FALSE;	
}
#pragma GCC diagnostic pop

int dlinkedlist_set(DLinkedList *list, size_t i, const void *elem, size_t n)
{
	DNode *cur = *list;

	if(!list || !elem) {
		return ERR;
	}	

	if(!cur) {
		return ERR;
	}

	while(cur->prev) {
		cur = cur->prev;
	}

	while(cur->next && i) {
		cur = cur->next;
		i--;
	}

	if(i && !cur) {
		return ERR;
	}

	memcpy(cur->buf, elem, MIN(cur->n, n));

	*list = cur; /* Cache baby */

	return OK;
}

int dlinkedlist_get(const DLinkedList *list, size_t i, void *buf, size_t n)
{
	DNode *cur = *list;

	if(!list || !buf) {
		return ERR;
	}	

	if(!cur) {
		return ERR;
	}

	while(cur->prev) {
		cur = cur->prev;
	}

	while(cur->next && i) {
		cur = cur->next;
		i--;
	}

	if(i && !cur) {
		return ERR;
	}

	memcpy(buf, cur->buf, MIN(cur->n, n));

	/*list = cur;*/

	return OK;	
}

int dlinkedlist_addlo(DLinkedList *list, const void *elem, size_t n)
{
	DNode *cur = *list, *tmp = NULL;
	
	if(!list || !elem) {
		return ERR;
	}

	if(cur) {
		while(cur->prev) {
			cur = cur->prev;
		}
	}
	
	tmp = MAKE_NODE(NULL, NULL, n, elem);

	tmp->next = cur;

	if(cur) {
		cur->prev = tmp;
	}

	*list = tmp;

	return OK;
}

int dlinkedlist_addhi(DLinkedList *list, const void *elem, size_t n)
{
	DNode *cur = *list, *tmp = NULL;
	
	if(!list || !elem) {
		return ERR;
	}

	if(cur) {
		while(cur->next) {
			cur = cur->next;
		}
	}

	tmp = MAKE_NODE(NULL, NULL, n, elem);

	tmp->prev = cur;

	if(cur) {
		cur->next = tmp;
	}

	*list = tmp;

	return OK;
}

int dlinkedlist_add(DLinkedList *list, size_t i, const void *elem, size_t n)
{
	DNode *cur = *list, *tmp = NULL;
	
	if(!cur) {
		return 0;
	}

	while(cur->prev) {
		cur = cur->prev;
	}

	while(cur->next && i) {
		cur = cur->next;
		i--;
	}

	if(i && !cur) {
		return ERR;
	}

	tmp = MAKE_NODE(NULL, NULL, n, elem);

	tmp->prev = cur;
	tmp->next = cur->next;

	*list = tmp;

	return OK;
}

int dlinkedlist_remlo(DLinkedList *list, void *buf, size_t n)
{
	DNode *cur = *list;

	if(!list || !buf) {
		return ERR;
	}

	if(!cur) {
		return ERR;
	}

	while(cur->prev) {
		cur = cur->prev;
	}

	memcpy(buf, cur->buf, MIN(cur->n, n));

	*list = cur->next;

	if(*list) {
		(*list)->prev = NULL;
	}
	 
	DELETE_NODE(cur);

	return OK;
}

int dlinkedlist_remhi(DLinkedList *list, void *buf, size_t n)
{
	DNode *cur = *list;

	if(!list || !buf) {
		return ERR;
	}

	if(!cur) {
		return ERR;
	}

	while(cur->next) {
		cur = cur->next;
	}

	memcpy(buf, cur->buf, MIN(cur->n, n));

	*list = cur->prev;

	if(*list) {
		(*list)->next = NULL;
	}
	 
	DELETE_NODE(cur);

	return OK;
}

int dlinkedlist_rem(DLinkedList *list, size_t i, void *buf, size_t n)
{
	DNode *cur = *list, *prev, *next;
	
	if(!cur) {
		return 0;
	}

	while(cur->prev) {
		cur = cur->prev;
	}

	while(cur->next && i) {
		cur = cur->next;
		i--;
	}

	if(i && !cur) {
		return ERR;
	}

	memcpy(buf, cur->buf, MIN(cur->n, n));

	prev = cur->prev;
	next = cur->next;

	if(next) {
		next = prev;	
		*list = next;
	}

	if(prev) {
		prev = next;
		*list = prev;
	}
	
	if(!prev && !next) {
		*list = NULL;
	}

	return OK;	
}

int dlinkedlist_add_ordered(DLinkedList *list, const void *elem, size_t n, cmp_fn cmp)
{
	DNode *tmp, *cur, *prev, *next;
	int compar;

	if(!list || !elem || !cmp) {
		return ERR;
	}

	cur = *list;

	if(cur) {
		while(cur->next && cmp(cur->buf, elem) < 0) {
			cur = cur->next;
		}

		while(cur->prev && cmp(cur->buf, elem) > 0) {
			cur = cur->prev;
		}

		compar = cmp(cur->buf, elem);

		if(compar >= 0) {
			 prev = cur->prev;
			 next = cur;
		} else {
			next = cur->next;
			prev = cur;
		}
	} else {
		prev = NULL;
		next = NULL;
	}

	tmp = MAKE_NODE(next, prev, n, elem);

	if(!tmp) {
		return ERR;
	}

	if(prev) {
		prev->next = tmp;
	}

	if(next) {
		next->prev = tmp;
	}

	*list = tmp;	

	return OK;	
}

int dlinkedlist_rem_ordered(DLinkedList *list, void *buf, size_t n, const void *key, cmp_fn cmp)
{
	DNode *cur, *prev, *next;
	int compar;

	if(!list || !buf || !cmp) {
		return ERR;
	}

	cur = *list;
	
	if(cur) {
		while(cur->next && cmp(cur->buf, key) < 0) {
			cur = cur->next;
		}

		while(cur->prev && cmp(cur->buf, key) > 0) {
			cur = cur->prev;
		}

		compar = cmp(cur->buf, key);

		if(compar == 0) {
			prev = cur->prev;
			next = cur->next;
		} else {
			prev = NULL;
		 	next = NULL;
		}
	} else {
		return OK;
	}

	if(prev) {
		prev->next = next;
		*list = prev;
	}

	if(next) {
		next->prev = prev;
		*list = next;
	}

	if(!prev && !next) {
		*list = NULL;
	}

	memcpy(buf, cur->buf, MIN(cur->n, n));

	DELETE_NODE(cur);

	return OK;	
}

int dlinkedlist_add_unique(DLinkedList *list, const void *elem, size_t n, cmp_fn cmp, unique_fn unique, void *user)
{
	DNode *tmp, *cur, *prev, *next;
	int compar;

	if(!list || !elem || !cmp) {
		return ERR;
	}

	cur = *list;

	if(cur) {
		while(cur->next && cmp(cur->buf, elem) < 0) {
			cur = cur->next;
		}

		while(cur->prev && cmp(cur->buf, elem) > 0) {
			cur = cur->prev;
		}

		compar = cmp(cur->buf, elem);

		if(compar == 0 && unique) {
			unique(cur->buf, elem, user);
			return OK;
		} else if(compar > 0) {
			 prev = cur->prev;
			 next = cur;
		} else {
			next = cur->next;
			prev = cur;
		}
	} else {
		prev = NULL;
		next = NULL;
	}

	tmp = MAKE_NODE(next, prev, n, elem);

	if(!tmp) {
		return ERR;
	}

	if(prev) {
		prev->next = tmp;
	}

	if(next) {
		next->prev = tmp;
	}

	*list = tmp;	

	return OK;	
}

int dlinkedlist_rem_unique(DLinkedList *list, void *buf, size_t n, const void *key, cmp_fn cmp, unique_fn unique, void *user);

int dlinkedlist_sort(DLinkedList *list, cmp_fn cmp);
int dlinkedlist_lsearch(const DLinkedList *list, const void *key, cmp_fn cmp);
int dlinkedlist_ord_search(const DLinkedList *list, const void *key, cmp_fn cmp);

int dlinkedlist_copy(DLinkedList *dst, DLinkedList *src);
int dlinkedlist_concat(DLinkedList *dst, DLinkedList *src);
int dlinkedlist_concatv(DLinkedList *dst, ...);

int dlinkedlist_printl(DLinkedList *list, print_fn print)
{
	DNode *cur = *list;

	if(!list || !print) {
		return ERR;
	}	

	while(cur->prev) {
		cur = cur->prev;
	}

	while(cur) {
		print(cur->buf);
		cur = cur->next;
	}

	return OK;
}

int dlinkedlist_printr(DLinkedList *list, print_fn print)
{
	DNode *cur = *list;

	if(!list || !print) {
		return ERR;
	}

	while(cur->next) {
		cur = cur->next;
	}

	while(cur) {
		print(cur->buf);
		cur = cur->prev;
	}

	return OK;
}

int dlinkedlist_map(DLinkedList *dst, DLinkedList *src, map_fn map, void* user);
int dlinkedlist_filter(DLinkedList *dst, DLinkedList *src, filter_fn filter, void *user);
int dlinkedlist_reduce(void *reduction, DLinkedList *src, reduce_fn reduce, void *user);
int dlinkedlist_foreach(DLinkedList *list, foreach_fn foreach, void *user);

int dlinkedlist_into_iter(DLinkedList *list, Iterator *iter);

void dlinkedlist_destroy(DLinkedList *list)
{
	DNode *cur = *list, *prev, *next, *tmp;
	
	if(!list) {
		return;
	}

	if(!cur) {
		return;
	}

	prev = cur->prev;
	next = cur->next;

	while(prev && next) {
		tmp = prev;
		prev = prev->prev;

		DELETE_NODE(tmp);

		tmp = next;
		next = next->next;
		DELETE_NODE(tmp);
	}

	while(prev) {
		tmp = prev;
		prev = prev->prev;
		DELETE_NODE(tmp);
	}

	while(next) {
		tmp = next;
		next = next->next;
		DELETE_NODE(tmp);
	}

	DELETE_NODE(cur);

	*list = NULL;
}
