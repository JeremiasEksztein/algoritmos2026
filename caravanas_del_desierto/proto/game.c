#include "game.h"

void rand_init(void)
{
	srand(time(NULL));
}

int roll_dice(void)
{
	return rand() % 6 + 1;
}

void player_init(struct Game *game)
{
	game->player_lives = 3;
	game->player_score = 0;
	game->turn = 0;
}

int game_init(struct Game *game)
{
	board_init(game->board);
	rand_init();
	player_init(game); /* ?? */

	game->game_ended = 0;

	return 0;
}

int	game_update(struct Game *game)
{
	game->dice_roll = roll_dice();

		
}

int game_draw(struct Game *game)
{
	
}

int game_should_end(struct Game *game)
{
	return game->game_ended;
}

void game_uninit(struct Game *game)
{
	
}
