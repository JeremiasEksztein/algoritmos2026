#define _GNU_SOURCE
/* libc headers */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <errno.h>

/* UNIX headers */

#include <unistd.h>
#include <termios.h>

/* Defines */

#define OK 0
#define ERR 1

#define MIN(x, y) (((x) > (y)) ? (y) : (x))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

/* Data Structures */

typedef struct sListNode tListNode;
struct sListNode {
	tListNode *next;
	size_t n;
	void *buf;
};

typedef tListNode *tSLinkedList;

typedef struct {
	tListNode *front, *back;
} tQueue;

void queue_new(tQueue *q);
int queue_add(tQueue *q, const void *elem, size_t n);
int queue_rem(tQueue *q, void *buf, size_t n);
int queue_front(const tQueue *q, void *buf, size_t n);
int queue_is_empty(const tQueue *q);
/*int queue_is_full(const tQueue *q, size_t n);*/
void queue_destroy(tQueue *q);

typedef struct sDListNode tDListNode2;
struct sDListNode {
	tDListNode *next, *prev;
	size_t n;
	void *buf;
};

typedef tDListNode *tCDLinkedList;

void cdlinkedlist_new(tCDLinkedList *c);

int cdlinkedlist_add(tCDLinkedList *c, const void *elem, size_t n);

void cdlinkedlist_destroy(tCDLinkedList *c);

typedef struct sTreeNode tTreeNode {
	tTreeNode *left, *right;
	size_t n;
	void *buf;
};

typedef tTreeNode *BinarySearchTree;

/* Terminal */ 

typedef struct termios tTerm;

int enable_raw_mode(tTerm *old)
{
	tTerm raw;
	
	if(tcgetattr(STDIN_FILENO, old) == -1) {
		return ERR;
	}

	raw = *old;

	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1; 

	if(tcsetattr(STDIN_FILENO, TCSANOW, &raw) == -1) {
		return ERR;
	}

	return OK;
}

int disable_raw_mode(tTerm *old)
{
	if(tcsetattr(STDIN_FILENO, TCSANOW, old) == -1) {
		return ERR;
	}

	return OK;
}

/* Thing */

#define STUNNED 	0x1
#define IMMORTAL 	0x2
#define BANDIT 		0x4
#define PLAYER 		0x8

typedef struct sThing tThing;
struct sThing {
	tThing *next;
	int lives;
	int flags;
};

tThing *thing_new(void)
{
	tThing *new;

	new = malloc(sizeof(tThing));

	if(!new) {
		return NULL;
	}	

	new->next = NULL;
	new->lives = 0;
	new->flags = 0;
	
	return new;
}

tThing *player_new(void)
{
	tThing *new;

	new = thing_new();

	new->lives = 3;
	new->flags |= (IMMORTAL | PLAYER);

	return new;	
}

tThing *bandit_new(void)
{
	tThing *new;

	new = thing_new();

	new->lives = 1;
	new->flags |= (BANDIT);

	return new;
}

/* Place & Board */

#define PLAYERHERE 0x1
#define CAMP 0x2
#define GOAL 0x4
#define PRIZE 0x8
#define XTRALIFE 0x10
#define OASIS 0x20
#define STORM 0x40

typedef struct sPlace tPlace;
struct sPlace {
	tPlace *next, *prev;
	tThing *things;
	int flags;
	int no_bandits;
};

tPlace *place_new(void)
{
	tPlace *new;

	new = malloc(sizeof(tPlace));

	if(!new) {
		return NULL;
	}

	new->next = NULL;
	new->prev = NULL;
	new->things = NULL;
	new->flags = 0;
	new->no_bandits = 0;

	return new;
}

void place_append(tPlace *place, tThing *thing)
{
	tThing **list = &(place->things);

	while((*list)->next) {
		list = &(*list)->next;
	}

	(*list)->next = thing;
}

void place_detach(tPlace *place, tThing *thing)
{
	tThing **list = &(place->things);

	while((*list)->next && *list != thing) {
		list = &(*list)->next;
	}

	*list = (*list)->next;
}

typedef tPlace *tBoard;

const char *placeholder[] = {
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
			".",
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
			"."	
};

int board_append(tBoard *board, tPlace *place)
{
	if(!*board) {
		place->next = *board;
		place->prev = *board;
		*board = place;
	} else {
		place->next = *board;
		place->prev = (*board)->prev;
		place->prev->next = place;
		(*board)->prev = place;	
	}
	
	return OK;
}

int board_init(tBoard *board)
{
	tPlace *place;
	tThing *thing;
	int i;
	const char *cur;

	for(i = 0; i < 25; ++i) {
		cur = placeholder[i];

		place = place_new();

		while(*cur) {
			switch(*cur) {
				case 'J':
					place->flags |= PLAYERHERE;
					thing = player_new();
					place_append(place, thing);
					break;
				case 'I':
					place->flags |= CAMP;
					break;
				case 'S':
					place->flags |= GOAL;
					break;
				case 'P':
					place->flags |= PRIZE;
					break;
				case 'V':
					place->flags |= XTRALIFE;
					break;
				case 'O':
					place->flags |= OASIS;
					break;
				case 'T':
					place->flags |= STORM;
					break;
				case 'B':
					thing = bandit_new();
					place_append(place, thing);
					break;
			}
			++cur;
			thing = NULL;
		}
		
		board_append(board, place);
		place = NULL;
	}

	return OK;
}

/* Game State */

typedef struct timespec tTimeSpec;

typedef struct {
	tTerm old;
	tTimeSpec wait;
	tBoard board;
	int score;
	int should_exit;
	int dice;
	int next_turn;
} tGameContext;

int game_init(tGameContext *game)
{
	tTimeSpec wait = {0, 17000000};
	
	srand(time(NULL));

	enable_raw_mode(&(game->old));

	board_init(&(game->board));

	game->wait = wait;
	game->score = 0;
	game->should_exit = 0;
	game->dice = rand() % 6 + 1;
	game->next_turn = 0;

	return OK;
}

char game_handle_input(tGameContext *game)
{
	char input = 0;

	if(read(STDIN_FILENO, &input, 1) == -1 && errno != EAGAIN) {
		perror("Error: read");
		disable_raw_mode(&(game->old));
		exit(1);
	}

	return input;
}

void player_move(tGameContext *game, int moves_to)
{
	tBoard board = game->board;
	tPlace *start = board;
	tPlace *curr = board;
	tThing *things = NULL;
	int break_cond = 0;
	int i;

	do {
		if((curr->flags & PLAYERHERE) == 0x1) {
			break_cond = 1;
		}

		curr = curr->next;
	} while(start != curr && break_cond);

	things = curr->things;

	while(things->next && (things->flags & PLAYER) != 0x8) {
		things = things->next;
	}

	place_detach(curr, things);

	if(moves_to < 0) {
		for(i = 0; i < moves_to; ++i) {
			if(start != curr) {
				curr = curr->prev;
			}
		}
	} else {
		for(i = 0; i < moves_to; ++i) {
			if(start != curr) {
				curr = curr->next;
			}
		}
	}

	place_append(curr, things);
}

void game_update(tGameContext *game, char input)
{
	int moves_to = 0;
	
	switch(input) {
		case 'z': 
			moves_to = game->dice;
			break;
		case 'x':
			moves_to = -game->dice;
			break;
		default:	
			return;
	}

	player_move(game, moves_to);

	bandits_move(game);

	board_eval(game);

	if(game->next_turn) {
		game->dice = rand() % 6 + 1;
		gaem->next_turn = 0;
	}
}

void game_draw(tGameContext *game)
{
	tPlace *place;
}

void game_uninit(tGameContext *game);

/* Main Function */

int main(void)
{
	tGameContext game;
	char input;

	if(game_init(&game)) {
		perror("Error initializing game\r\n");
		disable_raw_mode(&(game.old));
		return 1;
	}

	while(!game.should_exit) {
		input = game_handle_input(&game);
		game_update(&game, input);
		game_draw(&game);
	}

	game_uninit(&game);


	return 0;
}
