#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "node.h"

typedef struct {
	Node* data;
} LinkedList;

int linkedlist_new(LinkedList* list);

int linkedlist_addlo(LinkedList* l, const void* e, size_t n); 
int linkedlist_addhi(LinkedList* l, const void* e, size_t n);
int linkedlist_insert(LinkedList* l, size_t i, const void* e, size_t n);

int linkedlist_remlo(LinkedList* l, void* buf, size_t n);
int linkedlist_remhi(LinkedList* l, void* buf, size_t n);
int linkedlist_remove(LinkedList* l, size_t i, void* buf, size_t n);

int linkedlist_get(const LinkedList* l, size_t i, void* buf, size_t n);
int linkedlist_set(LinkedList* l, size_t i, const void* e, size_t n);

void linkedlist_destroy(LinkedList* list);

#endif
