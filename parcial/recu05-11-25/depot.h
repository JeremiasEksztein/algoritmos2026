#ifndef DEPOT_H
#define DEPOT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "stack.h"

#define IN 		0
#define OUT 	1

#define IN_OK 	0
#define IN_ERR	1
#define OUT_OK	2
#define OUT_ERR	3

typedef struct {
	char id[11];
	char company[11];
} tContainer;

int containerEq(const tContainer *a, const tContainer *b);

int openFile(FILE **fp, const char *path, const char *mode);

int createLogFiles(FILE **in, FILE **out, FILE **err);

int initDepotSim(tStack depot[], int maxHeight);

void readLine(char *buf, int *op, tContainer *container);

int handleInboundContainer(tStack depot[], const tContainer *container);

int handleOutboundContainer(tStack depot[], const tContainer *container);

void writeToLogFile(FILE *logFile, const char *msg, ...);

int dumpDepotStatus(tStack depot[]);

void uninitDepotSim(tStack depot[]);

#endif
