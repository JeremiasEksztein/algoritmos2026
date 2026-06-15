#ifndef PACKAGE_H
#define PACKAGE_H

typedef struct {
	char code[11];
	int dest;
	char type;
} tPackage;

int packageCmp(const void *a, const void *b);

#endif
