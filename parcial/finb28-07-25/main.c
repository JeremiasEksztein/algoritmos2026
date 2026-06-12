#include <stdio.h>

#if defined(EJ1)
	#include "score_table.h"
#elif defined(EJ2)
	#include "podium.h"
#else
	#error "Define either EJ1 or EJ2 during compilation"
#endif

int main(void)
{
#if defined(EJ1)
	FILE *fp;
	tScoreTable tbl;
	tScore tmp;
	unsigned n;
	char line[51], *i;

	fp = fopen("pruebas.txt", "rt");

	if(!fp) {
		return 1;
	}

	if(!fgets(line, 51, fp)) {
		fclose(fp);
		return 1;
	}

	sscanf(line, "%u\n", &n);

	scoreTableNew(&tbl, n);

	while(fgets(line, 51, fp)) {
		i = line;
		i += 4;
		*i = '\0';
		strcpy(tmp.name, line);
		i++;
		sscanf(i, "%u", &tmp.score);
		scoreTableAdd(&tbl, &tmp);
		scoreTablePrint(&tbl);
	}

	scoreTableDelete(&tbl);
	
#elif defined(EJ2)
	tParticipant tmp;
#else
	#error "Define either EJ1 or EJ2 during compilation"
#endif
	return 0;
}
