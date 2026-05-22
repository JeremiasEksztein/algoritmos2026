#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "render.h"
#include "thing.h"
#include "board.h"

struct Game {
	struct Place **board; /* Circular Doubly linked list of places */
	struct Renderer render; /* Renderer */
	int dice_roll;
	int player_lives;
	int player_score;
	int turn;
	int game_ended;
};

int game_init(struct Game *game);
int game_update(struct Game *game);
int game_draw(struct Game *game);
int game_should_end(const struct Game *game);
void game_uninit(struct Game *game);

void rand_init(void);
int roll_dice(void);

#endif
