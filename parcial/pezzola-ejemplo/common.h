#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdarg.h>

#define OK		0
#define ERR		1

#define TRUE	1
#define FALSE	0

#define MIN(x, y) ((x) > (y) ? (y) : (x))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

void eprintf(const char *msg, ...);

#endif
