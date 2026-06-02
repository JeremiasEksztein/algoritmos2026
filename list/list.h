#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>

#include <assert.h>
#include <stdio.h>

#include "iterator.h"

#define MIN(x, y) (((x) > (y)) ? (y) : (x))

#define OK 0
#define ERR 1

#define TRUE 1
#define FALSE 0
#define UNKNOWN -1

typedef int (*cmp_fn)(const void *lhs, const void *rhs);
typedef void (*unique_fn)(void *old, const void *new, void *user);
typedef int (*map_fn)(const void *from, void *to, void *user);
typedef int (*print_fn)(const void *data);
typedef int (*filter_fn)(const void *elem, void *user);
typedef int (*reduce_fn)(const void *elem, void *reduc, void *user);
typedef int (*foreach_fn)(const void *elem, void *user);

#ifndef BUFFER_ZEROING
#define BUFFER_ZEROING 0
#endif

typedef struct ArrayList {
#define ARRAYLIST_DEFAULT_CAP 64
	void *buf;
	size_t n;
	size_t cap;
} ArrayList;

int arraylist_new(ArrayList *list);
int arraylist_with_cap(ArrayList *list, size_t cap);

size_t arraylist_len(const ArrayList *list);
int arraylist_is_empty(const ArrayList *list);
int arraylist_is_full(const ArrayList *list, size_t n);

int arraylist_set(ArrayList *list, size_t i, const void *elem, size_t n);
int arraylist_get(const ArrayList *list, size_t i, void *buf, size_t n);

int arraylist_addlo(ArrayList *list, const void *elem, size_t n);
int arraylist_addhi(ArrayList *list, const void *elem, size_t n);
int arraylist_add(ArrayList *list, size_t i, const void *elem, size_t n);

int arraylist_remlo(ArrayList *list, void *buf, size_t n);
int arraylist_remhi(ArrayList *list, void *buf, size_t n);
int arraylist_rem(ArrayList *list, size_t i, void *buf, size_t n);

int arraylist_add_ordered(ArrayList *list, const void *buf, size_t n, cmp_fn cmp);
int arraylist_rem_ordered(ArrayList *list, void *buf, size_t n, cmp_fn cmp);

int arraylist_add_unique(ArrayList *list, const void *buf, size_t n, cmp_fn cmp, unique_fn unique, void *user);
int arraylist_rem_unique(ArrayList *list, void *buf, size_t n, cmp_fn cmp, unique_fn unique, void *user);

int arraylist_sort(ArrayList *list, cmp_fn cmp);
int arraylist_search(const ArrayList *list, const void *key, cmp_fn cmp);

int arraylist_copy(ArrayList *dst, ArrayList *src);
int arraylist_concat(ArrayList *dst, ArrayList *src);
int arraylist_concatv(ArrayList *dst, ...);

int arraylist_map(ArrayList *dst, ArrayList *src, map_fn map, void* user);
int arraylist_filter(ArrayList *dst, ArrayList *src, filter_fn filter, void *user);
int arraylist_reduce(void *reduction, ArrayList *src, reduce_fn reduce, void *user);
int arraylist_foreach(ArrayList *list, foreach_fn foreach, void *user);

int arraylist_into_iter(ArrayList *list, Iterator *iter);

void arraylist_destroy(ArrayList *list);

typedef struct Node Node;
struct Node {
	Node *next;
	size_t n;
	void *buf;	
};

#ifndef SLINKEDLIST_CIRCULAR
#define SLINKEDLIST_CIRCULAR 0
#endif

typedef Node *SLinkedList;

int slinkedlist_new(SLinkedList *list);

size_t slinkedlist_len(const SLinkedList *list);
int slinkedlist_is_empty(const SLinkedList *list);
int slinkedlist_is_full(const SLinkedList *list, size_t n);

int slinkedlist_set(SLinkedList *list, size_t i, const void *elem, size_t n);
int slinkedlist_get(const SLinkedList *list, size_t i, void *buf, size_t n);

int slinkedlist_addlo(SLinkedList *list, const void *elem, size_t n);
int slinkedlist_addhi(SLinkedList *list, const void *elem, size_t n);
int slinkedlist_add(SLinkedList *list, size_t i, const void *elem, size_t n);

int slinkedlist_remlo(SLinkedList *list, void *buf, size_t n);
int slinkedlist_remhi(SLinkedList *list, void *buf, size_t n);
int slinkedlist_rem(SLinkedList *list, size_t i, void *buf, size_t n);

int slinkedlist_add_ordered(SLinkedList *list, const void *buf, size_t n, cmp_fn cmp);
int slinkedlist_rem_ordered(SLinkedList *list, void *buf, size_t n, const void *key, cmp_fn cmp);

int slinkedlist_add_unique(SLinkedList *list, const void *buf, size_t n, cmp_fn cmp, unique_fn unique, void *user);

int slinkedlist_sort(SLinkedList *list, cmp_fn cmp);
int slinkedlist_lsearch(const SLinkedList *list, const void *key, cmp_fn cmp);
int slinkedlist_ord_search(const SLinkedList *list, const void *key, cmp_fn cmp);

int slinkedlist_copy(SLinkedList *dst, SLinkedList *src);
int slinkedlist_concat(SLinkedList *dst, SLinkedList *src);
int slinkedlist_concatv(SLinkedList *dst, ...);

int slinkedlist_print(const SLinkedList *list, print_fn print);
int slinkedlist_rev_print(const SLinkedList *list, print_fn print);

int slinkedlist_map(SLinkedList *dst, SLinkedList *src, map_fn map, void* user);
int slinkedlist_reverse(SLinkedList *dst, SLinkedList *src);
int slinkedlist_filter(SLinkedList *dst, SLinkedList *src, filter_fn filter, void *user);
int slinkedlist_reduce(void *reduction, SLinkedList *src, reduce_fn reduce, void *user);
int slinkedlist_foreach(SLinkedList *list, foreach_fn foreach, void *user);

int slinkedlist_into_iter(SLinkedList *list, Iterator *iter);

void slinkedlist_destroy(SLinkedList *list);


/* 
As taught by the professor. The DList is a pointer to the last recently used node.
I guess that makes it more cache friendly? If a bit more complicated in general
to get the lenght of a dlist I think you could get it in O(N/2) instead of O(N)
best case scenario, worst case scenario still is O(N) so
average case is bound O(N/2) < O(X) < O(N)
*/
typedef struct DNode DNode;
struct DNode {
	DNode *next;
	DNode *prev;
	size_t n;
	void *buf;
};

#ifndef DLINKEDLIST_CIRCULAR
#define DLINKEDLIST_CIRCULAR 0
#endif

typedef DNode *DLinkedList;

int dlinkedlist_new(DLinkedList *list);

size_t dlinkedlist_len(const DLinkedList *list);
int dlinkedlist_is_empty(const DLinkedList *list);
int dlinkedlist_is_full(const DLinkedList *list, size_t n);

int dlinkedlist_set(DLinkedList *list, size_t i, const void *elem, size_t n);
int dlinkedlist_get(const DLinkedList *list, size_t i, void *buf, size_t n);

int dlinkedlist_addlo(DLinkedList *list, const void *elem, size_t n);
int dlinkedlist_addhi(DLinkedList *list, const void *elem, size_t n);
int dlinkedlist_add(DLinkedList *list, size_t i, const void *elem, size_t n);

int dlinkedlist_remlo(DLinkedList *list, void *buf, size_t n);
int dlinkedlist_remhi(DLinkedList *list, void *buf, size_t n);
int dlinkedlist_rem(DLinkedList *list, size_t i, void *buf, size_t n);

int dlinkedlist_add_ordered(DLinkedList *list, const void *buf, size_t n, cmp_fn cmp);
int dlinkedlist_rem_ordered(DLinkedList *list, void *buf, size_t n, const void *key, cmp_fn cmp);

int dlinkedlist_add_unique(DLinkedList *list, const void *buf, size_t n, cmp_fn cmp, unique_fn unique, void *user);
int dlinkedlist_rem_unique(DLinkedList *list, void *buf, size_t n, const void *key, cmp_fn cmp, unique_fn unique, void *user);

int dlinkedlist_sort(DLinkedList *list, cmp_fn cmp);
int dlinkedlist_lsearch(const DLinkedList *list, const void *key, cmp_fn cmp);
int dlinkedlist_ord_search(const DLinkedList *list, const void *key, cmp_fn cmp);

int dlinkedlist_copy(DLinkedList *dst, DLinkedList *src);
int dlinkedlist_concat(DLinkedList *dst, DLinkedList *src);
int dlinkedlist_concatv(DLinkedList *dst, ...);

int dlinkedlist_printl(DLinkedList *list, print_fn print);
int dlinkedlist_printr(DLinkedList *list, print_fn print);

int dlinkedlist_map(DLinkedList *dst, DLinkedList *src, map_fn map, void* user);
int dlinkedlist_filter(DLinkedList *dst, DLinkedList *src, filter_fn filter, void *user);
int dlinkedlist_reduce(void *reduction, DLinkedList *src, reduce_fn reduce, void *user);
int dlinkedlist_foreach(DLinkedList *list, foreach_fn foreach, void *user);

int dlinkedlist_into_iter(DLinkedList *list, Iterator *iter);

void dlinkedlist_destroy(DLinkedList *list);

typedef Node *CDLinkedList;

void cdlinkedlist_new(CDLinkedList *l);

void cdlinkedlist_destroy(CDLinkedList *l);

#endif
