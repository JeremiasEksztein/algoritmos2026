#include "alumno.h"

int alumno_cmp(const void *a, const void *b)
{
	const tAlumno *x = a, *y = b;
	int p_cmp;
	
	if(x->dni != y->dni) {
		return x->dni - y->dni;
	}

	if(x->anyo != y->anyo) {
		return x->anyo - y->anyo;
	} 

	p_cmp = strcmp(x->periodo, y->periodo);
	if(p_cmp != 0) {
		return p_cmp;
	}

	return strcmp(x->materia, y->materia);
}
