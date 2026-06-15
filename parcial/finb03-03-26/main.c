#include <stdio.h>
#include <string.h>

#include "common.h"
#include "list.h"
#include "queue.h"
#include "package.h"

#define BUFSIZE 256

int openFiles(
	FILE **fpOperaciones,
	FILE **fpIneficientes,
	FILE **fpPendientes
) {
	*fpOperaciones = fopen("operaciones.txt", "rt");

	if(!*fpOperaciones) {
		return ERR;
	}

	*fpIneficientes = fopen("despachos_ineficientes.txt", "wt");

	if(!*fpIneficientes) {
		fclose(*fpOperaciones);
		return ERR;
	}

	*fpPendientes = fopen("pendientes.txt", "wt");

	if(!*fpPendientes) {
		fclose(*fpIneficientes);
		fclose(*fpOperaciones);
		return ERR;
	}

	return OK;
}

void deleteAll(tLinkedList *ll)
{
	tLinkedQueue q;
	
	while(!linkedListIsEmpty(ll)) {
		linkedListRemlo(ll, &q, sizeof(tLinkedQueue));
		linkedQueueDelete(&q);
	}

	linkedListDelete(ll);
}

int main(void)
{
	FILE *fpOperaciones, *fpIneficientes, *fpPendientes;
	tPackage package;
	tLinkedList ll;
	tLinkedQueue q;
	char buf[BUFSIZE], *i;
	int k, d, totalDispatched;

	if(openFiles(&fpOperaciones, &fpOperaciones, &fpPendientes) != OK) {
		return ERR;
	}

	if(!fgets(buf, BUFSIZE, fpOperaciones)) {
		fclose(fpOperaciones);
		return ERR;
	}

	sscanf(buf, "%d,%d\n", &k, &d);

	while(fgets(buf, BUFSIZE, fpOperaciones)) {
		if(!(i = strrchr(buf, '\n'))) {
			fclose(fpOperaciones);
			return ERR;
		}

		*i = '\0';
		i = buf;
		totalDispatched = 0;

		if(strncmp(i, "ING", 3)) {
			sscanf(i, "ING|%[^|]|%u|%c\n", package.code, &package.dest, &package.type); /* scanPackage()? */
			linkedListInsert(&ll, &package, sizeof(tPackage), packageCmp, TRUE, packageEnqueue);
		} else if(strncmp(i, "DES", 3)) {
			sscanf(i, "DES|%d\n", &package.dest);
			linkedListFind(&ll, &package, &q, sizeof(tLinkedQueue), packageCmp);

			while(!linkedQueueIsEmpty(&q) && totalDispatched < k) {
				linkedQueueRem(&q, &package, sizeof(tPackage));
				totalDispatched++;
			}			

			if(totalDispatched < k) {
				fprintf(
					fpIneficientes,
					"DES|%d|INCOMPLETO|%d|%d\n",
					package.dest,
					k, 
					totalDispatched
				);
			} else if(totalDispatched == 0) {
				fprintf(
					fpIneficientes,
					"DES|%d|VACIO\n",
					package.dest	
				);
			}
		} else {
			eprintf("[ERROR]: Malformed 'operaciones.txt' file\n");
			deleteAll(&ll);
			fclose(fpPendientes);
			fclose(fpIneficientes);
			fclose(fpOperaciones);
			return ERR;
		}	
	}

	while(!linkedListIsEmpty(&ll)) {
		linkedListRemlo(&ll, &q, sizeof(tLinkedQueue));
		while(!linkedQueueIsEmpty(&q)) {
			linkedQueueRem(&q, &package, sizeof(tPackage));
			fprintf(
				fpPendientes,
				"ING|%s|%d|%c\n", 
				package.code,
				package.dest,
				package.type
			);
		}

		linkedQueueDelete(&q);
	}

	linkedListDelete(&ll);
	
	fclose(fpPendientes);
	fclose(fpIneficientes);
	fclose(fpOperaciones);
	
	return OK;
}
