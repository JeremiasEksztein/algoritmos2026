#include "podium.h"

int participant_cmp(const void *a, const void *b)
{
	const tParticipant *x = a, *y = b;

	return x->score - y->score;
}


void participant_print(const void *x, void *user)
{
	const tParticipant *a = x;
	int *n = user;

	printf("%d. %-*s ..... %d\n", *n, 4, a->desc, a->score);
	(*n)++;
}

void podiumNew(tPodium *p, unsigned n)
{
	if(!p) {
		return;
	}

	linkedListNew(&(p->list));
	p->n = n; 
}

int podiumAdd(tPodium *p, const tParticipant *new)
{
	if(!p || !new) {
		return 1;
	}

	if(linkedListInsertOrderedUpToN(&(p->list), new, sizeof(tParticipant), p->n, participant_cmp, 1)) {
		return 1;
	}

	return 0;
}

void podiumPrint(const tPodium *p)
{
	int i = 0;
	
	if(!p) {
		return;
	}


	linkedListPrint(&(p->list), participant_print, &i);
}

void podiumDelete(tPodium *p)
{
	if(!p) {
		return;
	}

	linkedListDelete(&(p->list));
	p->n = 0;
}
