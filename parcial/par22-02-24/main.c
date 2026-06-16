#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "elections.h"

int main(void)
{
	tProgramContext ctxt;
	int ch, shouldExit = FALSE;

	initProgramContext(&ctxt);

	while(!shouldExit) {
		showMenu();
	
		if(ch == '\0') {
			shouldExit = TRUE;
			continue;
		}
		
		handleInput(&ctxt, ch);		
	}

	uninitProgramContext(&ctxt);

	return OK;
}
