#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "thing.h"

#define BOARD_LEN 25

static const char *_board[] = {
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

void board_eval(void);

#endif
