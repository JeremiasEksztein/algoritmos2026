#ifndef THING_H
#define THING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define THINGS_BUF_SIZE 2048

enum ThingKind {
	THING_NULL,
	THING_ENTITY,
	THING_PLAYER,
	THING_OBSTACLE,
};

enum ObstacleKind {
	O_CAMP,
	O_PLAYER,
	O_CITY,
	O_PRIZE,
	O_OASIS,
	O_XTRALIFE,
	O_STORM
};

enum EntityKind {
	E_PLAYER,
	E_BANDIT,
};

struct Thing {
	enum ThingKind kind;
	union{
		struct {
			int e_flags;
		} entity;

		struct {
			int o_flags;
		} obstacle;
	};
	struct Thing *next;
};

struct Thing *thing_new(void);
void thing_delete(struct Thing *thing);

struct Thing *entity_new(int e_flags);
struct Thing *obstacle_new(int o_flags);

int things_append(struct Thing **things, struct Thing *thing);
struct Thing *things_detach(struct Thing **things, struct Thing *thing);

#endif
