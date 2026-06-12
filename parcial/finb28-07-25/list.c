#include "list.h"

static int _insertUnique(
	tLinkedList *ll, 
	const void *elem, 
	unsigned n, 
	fnCmp cmp, 
	int dup
) {
	tNode *tmp;
	int compar;

	while(*ll && (compar = cmp((*ll)->buf, elem)) > 0) {
		ll = &(*ll)->next;
	}	

	if(*ll && compar == 0 && !dup) {
		return 0;
	}

	tmp = malloc(sizeof(tNode));

	if(!tmp) {
		return 1;
	}

	tmp->buf = malloc(n);

	if(!tmp->buf) {
		return 1;
	}

	memcpy(tmp->buf, elem, n);
	tmp->n = n;
	tmp->next = (*ll);
	(*ll) = tmp;

	return 0;
}

static int _trimUpToN(tLinkedList *ll, unsigned n, int duplicates, fnCmp cmp)
{
	unsigned len = 0;
	void *prev = NULL;

	while(*ll && len <= n) {
		prev = (*ll)->buf;

		while(*ll && cmp(prev, (*ll)->buf)) {
			ll = &(*ll)->next;
			if(!duplicates) {
				len++;
			}
		}

		len++;
	}

	linkedListDelete(ll);
	
	return 0;
}


void linkedListNew(tLinkedList *ll)
{
	if(!ll) {
		return;
	}

	*ll = NULL;
}

int linkedListInsertOrderedUpToN(
	tLinkedList *ll, 
	const void *elem, 
	unsigned size,
	unsigned n,
	fnCmp cmp,
	int duplicates
) {
	int ret;
	if(!ll || !elem || !cmp) {
		return 1;
	}
	
	ret = _insertUnique(ll, elem, size, cmp, duplicates);

	if(ret == 0) {
		ret = _trimUpToN(ll, n, duplicates, cmp);
	}
	
	return ret;
}

void linkedListPrint(const tLinkedList *ll, fnPrint print, void *user)
{
	if(!ll || !print) {
		return;
	}

	while(*ll) {
		print((*ll)->buf, user);
		ll = &(*ll)->next;
	}
}

void linkedListDelete(tLinkedList *ll)
{
	tNode *tmp;

	while(*ll) {
		tmp = *ll;
		ll = &(*ll)->next;
		free(tmp->buf);
		free(tmp);
	}

	*ll = NULL;
}
