#include <stdio.h>
#include <string.h>

#include "queue.h"
#include "common.h"

typedef enum {
	NORTH,
	WEST,
	SOUTH,
	EAST
} eDirection;

eDirection lrot(eDirection dir)
{
	switch(dir) {
		case NORTH:
			return WEST;
		case WEST:
			return SOUTH;
		case SOUTH:
			return EAST;
		case EAST:
			return NORTH;
	}	

	return NORTH;
}

eDirection rrot(eDirection dir)
{
	switch(dir) {
		case NORTH:
			return EAST;
		case WEST:
			return NORTH;
		case SOUTH:
			return WEST;
		case EAST:
			return SOUTH;
	}	
	
	return NORTH;
}

char directionToChar(eDirection dir)
{
	switch(dir) {
		case NORTH:
			return 'N';
		case WEST:
			return 'W';
		case SOUTH:
			return 'S';
		case EAST:
			return 'E';
	}	

	return '\0';
}

int main(void)
{
	FILE *fpOrdenes, *fpSalida;
	eDirection dir = NORTH;
	int orderCancelled = FALSE, hasLaunched = FALSE, movsN = 0;
	char buf[256], *i;
	tQueue q;

	fpOrdenes = fopen("ordenes.txt", "rt");

	if(!fpOrdenes) {
		eprintf(
			"[ERROR]: Couldn't open ordenes.txt\n"
		);
		return ERR;
	}

	fpSalida = fopen("salida.txt", "wt");

	if(!fpSalida) {
		eprintf(
			"[ERROR]: Couldn't open salida.txt\n"
		);
		fclose(fpOrdenes);
		return ERR;
	}

	while(fgets(buf, 256, fpOrdenes) && dir != SOUTH) {	
		if(!(i = strrchr(buf, '\n'))) {
			eprintf(
				"[ERROR]: Order line too long\n"	
			);
			queueDelete(&q);
			fclose(fpOrdenes);
			fclose(fpSalida);
			return ERR;
		}

		*i = '\0';
		i = buf;

		if(*i == 'C') {
			orderCancelled = TRUE;
			continue;
		}

		if(orderCancelled) {
			orderCancelled = FALSE;
			continue;
		}

		if(*i == 'D') {
			movsN++;
			hasLaunched = TRUE;
			queueAdd(&q, i, sizeof(char));
			continue;
		}

		if(hasLaunched && *i == 'H') {
			movsN++;
			dir = rrot(dir);
			queueAdd(&q, i, sizeof(char));
			continue;
		}	

		if(hasLaunched && *i == 'A') {
			movsN++;
			dir = lrot(dir);
			queueAdd(&q, i, sizeof(char));
			continue;
		}

		if(*i == '#') {
			continue;
		}
	}

	if(dir == SOUTH) {
		fprintf(fpSalida, "%u\n", movsN);

		while(!queueIsEmpty(&q)) {
			queueRem(&q, i, sizeof(char));
			fprintf(fpSalida, "%c", *i);	
		}
	} else {
		fprintf(fpSalida, "-1%c", directionToChar(dir));
	}

	queueDelete(&q);
	fclose(fpSalida);
	fclose(fpOrdenes);

	return OK;
}
