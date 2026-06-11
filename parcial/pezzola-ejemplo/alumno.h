#ifndef ALUMNO_H
#define ALUMNO_H

#include <stdio.h>
#include <string.h>

typedef struct {
	int dni;
	char materia[11];
	int anio;
	char periodo[7];
	int nota;
} tAlumno;

void debug_alumnos(void);

int alumno_cmp(const void *a, const void *b);
void alumno_print(const void *alumno, void *ctxt);

#endif
