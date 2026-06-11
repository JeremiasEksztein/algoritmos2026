#ifndef ALUMNO_H
#define ALUMNO_H

#include <string.h>

//#include "comun.h"

typedef struct {
	int dni;
	char materia[11];
	int anyo;
	char periodo[7];
	int nota;
} tAlumno;

int alumno_cmp(const void *a, const void *b);
int dni_cmp(const void *a, const void *b);

void promedio_notas(const void *a, void *user);
void contar_aprobs(const void *a, void *user);
void grabar_materias(const void *a, void *user);

#endif
