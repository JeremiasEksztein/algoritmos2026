#ifndef PODIUM_H
#define PODIUM_H

#include <stdio.h>

#include "list.h"

typedef struct {
	char desc[51];
	unsigned score;
} tParticipant;

typedef struct {
	tLinkedList list;
	unsigned n;
} tPodium;

void podiumNew(tPodium *p, unsigned n);

int podiumAdd(tPodium *p, const tParticipant *new);

void podiumPrint(const tPodium *p);

void podiumDelete(tPodium *p);

#endif
