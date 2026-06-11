#include "depot.h"

int containerEq(const tContainer *a, const tContainer *b)
{
	return (memcmp(a, b, sizeof(tContainer)) == 0) ? TRUE : FALSE;
}

int openFile(FILE **fp, const char *path, const char *mode)
{
	*fp = fopen(path, mode);

	if(!*fp) {
		return ERR;
	}

	return OK;
}

int createLogFiles(FILE **in, FILE **out, FILE **err)
{
	*in = fopen("ingresos.txt", "wt");

	if(!*in) {
		return ERR;
	}

	*out = fopen("egresos.txt", "wt");

	if(!*out) {
		fclose(*in);
		return ERR;
	}

	*err = fopen("anomalias.txt", "wt");

	if(!*err) {
		fclose(*out);
		fclose(*in);
		return ERR;
	}

	return OK;
}

void readLine(char *buf, int *op, tContainer *container)
{
	char *i;
	
	if(buf[0] == 'I' && buf[1] == 'N') {
		*op = IN;
	} else {
		*op = OUT;
	}

	buf += 3;

	i = container->id;
	while(*buf != '-') {
		*i = *buf;
		i++;
		buf++;
	}
	
	buf++;

	i = container->company;
	while(*buf != '\n' && *buf) {
		*i = *buf;
		i++;
		buf++;
	}
}

int initDepotSim(tStack depot[], int maxHeight)
{
	int i, j, ret = OK;

	for(i = 0; i < 4; ++i) {
		if(stackNew(depot + i, maxHeight * (sizeof(tContainer) + sizeof(unsigned))) != OK) {
			ret = ERR;
			break;
		}
	}
	
	j = i;

	for(; j < i; ++j) {
		stackDelete(depot + j);
	}

	return ret;
}

int handleInboundContainer(tStack depot[], const tContainer *container)
{
	int i = 0, done = 0;

	while(i < 3 && !done) {
		if(!stackIsFull(depot + i, sizeof(tContainer))) {
			stackPush(depot + i, container, sizeof(tContainer));
			done = 1;
		}
		++i;
	}

	if(i == 3 && !done) {
		return IN_ERR;
	}

	return IN_OK;
}

int handleOutboundContainer(tStack depot[], const tContainer *container)
{
	tContainer tmp;
	int i = 0, eq = 0, done = 0;
	

	while(i < 3 && !done) {
		while(!stackIsEmpty(depot + i) && !eq) {
			stackPop(depot + i, &tmp, sizeof(tContainer));

			eq = containerEq(container, &tmp); 

			if(!eq) {
				stackPush(depot + 3, &tmp, sizeof(tContainer));
			}
		}

		while(!stackIsEmpty(depot + 3)) {
			stackPop(depot + 3, &tmp, sizeof(tContainer));
			stackPush(depot + i, &tmp, sizeof(tContainer));
		}

		if(eq) {
			done = 1;
			break;
		}

		++i;
	}

	if(i == 3 && !done) {
		return OUT_ERR;
	}

	return OUT_OK;
}

void writeToLogFile(FILE *logFile, const char *msg, ...)
{
	va_list ap;

	va_start(ap, msg);

	vfprintf(logFile, msg, ap);

	va_end(ap);
}

int dumpDepotStatus(tStack depot[])
{
	FILE *fpStatus = NULL;
	tContainer tmp;
	int i;

	if(openFile(&fpStatus, "estado_almacen.txt", "wt") != OK) {
		return ERR;
	}

	for(i = 0; i < 3; ++i) {
		writeToLogFile(
			fpStatus,
			"[COLUMN %d]:\n",
			i
		);

		while(!stackIsEmpty(depot + i)) {
			stackPop(depot + i, &tmp, sizeof(tContainer));
			writeToLogFile(
				fpStatus,
				"[ %-*s . %*s ]\n",
				10,
				tmp.id,
				10,
				tmp.company
			);
		}

		writeToLogFile(
			fpStatus,
			"[END OF COLUMN %d]\n\n",
			i
		);
	}

	return OK;
}

void uninitDepotSim(tStack depot[])
{
	int i;

	for(i = 0; i < 4; ++i) {
		stackDelete(depot + i);
	}
}
