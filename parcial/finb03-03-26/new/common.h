#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdarg.h>

#define OK 		0
#define ERR		1

#define TRUE 	1
#define FALSE	0

typedef int (*fnCmp)(const void *, const void *);
typedef void (*fnAction)(void *, void *);
typedef unsigned (*fnRead)(void **, void *, unsigned, void *);

void eprintf(const char *msg, ...);

#endif
