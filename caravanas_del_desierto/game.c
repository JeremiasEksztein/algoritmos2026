#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

/* Thanks Rogue! */

#define BOARD_LEN 25
#define THINGS_BUF_SIZE 2048

const char *_board[] = {
	"IJ",
	".",
	"P",
	"T",
	".",
	"B",
	"O",
	".",
	"P",
	".",
	"V",
	"S",
	"T",
	".",
	"O",
	"B",
	".",
	"P",
	".",
	"T",
	".",
	".",
	".",	
};

/* Thing */

enum ThingKind {
	THING_NULL,
	THING_ENTITY,
	THING_PLAYER,
	THING_OBSTACLE,
};

enum {
	O_CAMP,
	O_PLAYER,
	O_CITY,
	O_PRIZE,
	O_OASIS,
	O_XTRALIFE,
	O_STORM
};

enum {
	E_PLAYER,
	E_BANDIT,
};

union ThingInner {
	struct _e {
		int e_flags;
	} entity;

	struct _p {
		int lifes;
		int score;
	} player;

	struct _o {
		int o_flags;
	} obstacle;
} val;

struct Thing {
	enum ThingKind kind;
	union ThingInner inner;
	struct Thing *next;
};

void things_append(struct Thing **head, struct Thing *new)
{
	while((*head)->next) {
		head = &(*head)->next;
	}

	(*head)->next = new;
}

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

	new->inner.entity.e_flags = e_flags;

	return new;
}

struct Thing *player_new()
{
	struct Thing *new;

	new = thing_new();

	if(!new) {
		return NULL;
	}

	new->kind = THING_PLAYER;

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

	new->inner.obstacle.o_flags = o_flags;

	return new;		
}

/* Place */

struct Place {
	/* Later it will have to be struct Place *prev, *next */
	struct Place *prev, *next;
	struct Thing **things;
	/* More things should go here probably */	
};

void board_append(struct Place **board, struct Thing **things);

void board_init(struct Place **board)
{
	int i;
	const char *cur;
	struct Thing *new, **list;

	for(i = 0; i < BOARD_LEN; ++i) {
		cur = _board[i];

		while(*cur) {
			switch(*cur) {
				case 'I':
					new = obstacle_new(O_CAMP);
					break;
				case 'J':
					new = entity_new(E_PLAYER);
					break;
				case 'S':
					new = obstacle_new(O_CITY);
					break;
				case 'P':
					new = obstacle_new(O_PRIZE);
					break;
				case 'V':
					new = obstacle_new(O_XTRALIFE);
					break;
				case 'O':
					new = obstacle_new(O_OASIS);
					break;
				case 'T':
					new = obstacle_new(O_STORM);
					break;
				case 'B':
					new = entity_new(E_BANDIT);
					break;
				case '.':
					new = NULL;
					break;
				default:
					fprintf(stderr, "Error: malformed board example\n");
					exit(1);
			}	

			cur++;
			things_append(list, new);
		}	

		board_append(board, list);
	}
};

/* Renderer */

struct Renderer {
	char linebuf[81];
	int i;
};

void renderer_clear(struct Renderer *render)
{
	memset(*render, 0, sizeof(struct Renderer));
}

int renderer_push(struct Renderer *render, char *line, int n)
{
	if(n > (80 - i)) {
		return 1;
	}

	memcpy(render->linebuf + render->i, line, n);

	render->i += n;

	return 0;
}

int renderer_drawline(struct Renderer *render)
{
	printf("%s\n", render->linebuf);

	return 0;
}

void renderer_drawblank(struct Renderer *render)
{
	printf("%.s\n", 80, "");
}

/* Game */

void rand_init(void)
{
	srand(time(NULL));
}

int roll_dices(void)
{
	return rand() % 6 + 1;
}

struct Game {
	struct Place **board;
	int dice_roll;
	int player_lives;
	int player_score;
	struct Move **moves;
	int turn;
	int game_ended;
};

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
	player_init(game);	

	game->game_ended = 0;

	return 0;
}

int	game_update(struct Game *game)
{
	game->dice_roll = roll_dices();
	
	resolve_moves(game);
	
	eval_board(game);

	game->turn++;
	
	return 0;
}

int game_draw(struct Game *game)
{
	int i;

	draw_board(game);
	
	for(i = 0; i < BOARD_LEN; ++i) {
		draw()
	}
}

int game_should_end(struct Game *game)
{
	return game->game_ended;
}

void game_uninit(struct Game *game);

int main(void)
{
	struct Game GameContext;

	if(game_init(&GameContext) != 0) {
		fprintf(stderr, "Error: init failed!\n");
		return 1;
	}

	while(!game_should_end(&GameContext)) {
		game_update(&GameContext);
		
		game_draw(&GameContext);
	}

	game_uninit(&GameContext);
	
	return 0;
}
