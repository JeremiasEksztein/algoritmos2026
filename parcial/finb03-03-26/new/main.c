#include <stdio.h>
#include <string.h>

#include "common.h"
#include "package.h"

#define BUFSIZE 256

int main(void)
{
	FILE *fpOperaciones, *fpIneficientes, *fpPendientes;
	char buf[BUFSIZE], *i;

	if(openFiles(&fpOperaciones, &fpIneficientes, &fpPendientes) != OK) {
		return ERR;
	}

	if(!fgets(buf, BUFSIZE, fpOperaciones)) {
		fclose(fpPendientes);
		fclose(fpIneficientes);
		fclose(fpOperaciones);
		return ERR;
	}

	

	while(fgets(buf, BUFSIZE, fpOperaciones)) {
		if(!(i = strrchr(buf, '\n'))) {
			fclose()
		}
	}


	fclose(fpPendientes);
	fclose(fpIneficientes);
	fclose(fpOperaciones);

	return OK;
}
