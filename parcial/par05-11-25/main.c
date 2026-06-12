#include <stdio.h>
#include <string.h>

#include "common.h"
#include "stack.h"

int main(void)
{
	FILE *fpIn, *fpOut;
	char line[56], *i, tmp;
	unsigned len;
	tStack stk;
	

	fpIn = fopen("claves.txt", "rt");

	if(!fpIn) {
		return ERR;
	}

	fpOut = fopen("claves_nuevas.txt", "wt");

	if(!fpOut) {
		fclose(fpIn);
		return ERR;
	}

	stackNew(&stk);

	while(fgets(line, 56, fpIn)) {
		if((i = strrchr(line, '\n'))) {
			*i = '\0';
		}	

		i = line;
		len = 0;

		while(*i) {
			tmp = '\0';
			
			stackPeek(&stk, &tmp);

			if(charEqual(tmp, *i)) {
				stackPop(&stk, &tmp);
				len--;
			} else {
				stackPush(&stk, *i);
				len++;
			}
			
			++i;
		}

		line[len] = '\0';
		while(!stackIsEmpty(&stk)) {
			stackPop(&stk, &tmp);
			line[len-- - 1] = tmp;
		}

		fprintf(fpOut, "%s\n", line);
	}

	fclose(fpOut);
	fclose(fpIn);
	stackDelete(&stk);
		
	return OK;
}
