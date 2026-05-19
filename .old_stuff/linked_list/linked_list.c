#include "linked_list.h"

int linkedlist_new(LinkedList* l)
{
	if(!l) {
		return 1;
	}

	l->data = NULL;

	return 0;
}

int linkedlist_addlo(LinkedList* l, const void* e, size_t n)
{
	Node* new;
	if(!l || !e) {
		return 1;
	}	

	new = node_new(NULL, e, n);

	if(!new) {
		return 1;
	}

	new->next = (!l->data)
				? NULL
				: l->data;
	
	l->data = new;

	return 0;
} 

int linkedlist_addhi(LinkedList* l, const void* e, size_t n)
{
	Node* new;
	Node* tmp;
	
	if(!l || !e) {
		return 1;
	}	

	new = node_new(NULL, e, n);

	if(!new) {
		return 1;
	}
	
	tmp = l->data;
	while(tmp->next) {
		tmp = tmp->next;
	}

	tmp->next = new;

	return 0;
}

int linkedlist_insert(LinkedList* l, size_t i, const void* e, size_t n)
{
	Node* new;
	Node* tmp;
	Node* prev;
	Node* next;

	if(!l || !e) {
		return 1;
	}

	new = node_new(NULL, e, n);

	if(!new) {
		return 1;
	}

	tmp = l->data;
	prev = tmp;
	next = tmp->next;
	while(tmp->next && i) {
		tmp = tmp->next;
		prev = tmp;
		next = tmp->next;
		i--;
	}

	prev->next = new;
	new->next = (next) 
				? next
				: NULL;

	return 0;
}

int linkedlist_remlo(LinkedList* l, void* buf, size_t n);
int linkedlist_remhi(LinkedList* l, void* buf, size_t n);
int linkedlist_remove(LinkedList* l, size_t i, void* buf, size_t n);

int linkedlist_get(const LinkedList* l, size_t i, void* buf, size_t n);
int linkedlist_set(LinkedList* l, size_t i, const void* e, size_t n);

void linkedlist_destroy(LinkedList* list);

