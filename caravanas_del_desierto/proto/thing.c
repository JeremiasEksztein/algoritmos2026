#include "thing.h"

struct Thing *thing_new(void)
{
	struct Thing *new;

	new = calloc(1, sizeof(struct Thing));

	if(!new) {
		return NULL;
	}

	return new;
}

void thing_delete(struct Thing *thing)
{
	assert(thing);

	free(thing);
}

struct Thing *entity_new(int e_flags)
{
	struct Thing *new;

	new = thing_new();

	if(!new) {
		return NULL;
	}	

	new->kind = THING_ENTITY;
	new->entity.e_flags = e_flags;

	return new;
}

struct Thing *obstacle_new(int o_flags)
{
	struct Thing *new;

	new = thing_new();

	if(!new) {
		return NULL;
	}	

	new->kind = THING_OBSTACLE;
	new->obstacle.o_flags = o_flags;

	return new;	
}

int things_append(struct Thing **things, struct Thing *thing)
{
	while(*things) {
		*things = (*things)->next;	
	};	

	(*things)->next = thing;
	*things = thing;

	return 0;	
}

struct Thing *things_detach(struct Thing **things, struct Thing *thing)
{
	
}
