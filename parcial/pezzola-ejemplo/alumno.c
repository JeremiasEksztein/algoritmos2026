#include "alumno.h"

void debug_alumnos(void)
{
	FILE *fp;
	tAlumno alum;

	fp = fopen("alumnos.dat", "rb");

	while(!feof(fp)) {
		fread(&alum, sizeof(tAlumno), 1, fp);

		printf(
			"%8d|%-*s|%d|%-*s|%02d\n", 
			alum.dni, 
			11, alum.materia, 
			alum.anio,
			7, alum.periodo,
			alum.nota
		);
	}
}

int alumno_cmp(const void *a, const void *b)
{
	const tAlumno *x = a, *y = b;

	if(x->dni != y->dni) {
		return x->dni - y->dni;
	}

	if(x->anio != y->anio) {
		return x->anio - y->anio;
	}

	if(strcmp(x->periodo, y->periodo) != 0) {
		return strcmp(x->periodo, y->periodo);
	}

	return strcmp(x->materia, y->materia);
}

void alumno_print(const void *alumno, void *ctxt)
{
	(void)ctxt;
	const tAlumno *alum = alumno;

	printf(
		"%8d|%-*s|%d|%-*s|%02d\n", 
		alum->dni, 
		11, alum->materia, 
		alum->anio,
		7, alum->periodo,
		alum->nota
	);
}
