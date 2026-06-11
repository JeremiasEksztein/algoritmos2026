#include <stdio.h>
#include <stdlib.h>

#include "alumno.h"
#include "arbol.h"

typedef void (*print_fn)(const void*);

void print_alumno(const void *a)
{
	const tAlumno *alum = a;

	printf(
		"%8d|%-*s|%d|%-*s|%02d\n", 
		alum->dni, 
		11, alum->materia, 
		alum->anio,
		7, alum->periodo,
		alum->nota
	);
}

static void prettyPrintRec2(
    const tNodo *nodo,
    const char *prefijo,
    int esUltimo,
    print_fn print)
{
    if (!nodo)
        return;

    printf("%s", prefijo);
    printf("%s", esUltimo ? "└── " : "├── ");

    print(nodo->buf);
    printf("\n");

    char nuevoPrefijo[256];
    snprintf(
        nuevoPrefijo,
        sizeof(nuevoPrefijo),
        "%s%s",
        prefijo,
        esUltimo ? "    " : "│   "
    );

    if (nodo->izq || nodo->der) {
        prettyPrintRec2(nodo->izq, nuevoPrefijo, nodo->der == NULL, print);
        prettyPrintRec2(nodo->der, nuevoPrefijo, 1, print);
    }
}

void prettyPrintArbol(const tArbol arbol, print_fn print)
{
    if (!arbol) {
        puts("(árbol vacío)");
        return;
    }

    print(arbol->buf);
    putchar('\n');

    prettyPrintRec2(arbol->izq, "", arbol->der == NULL, print);
    prettyPrintRec2(arbol->der, "", 1, print);
}

int main(void)
{
	FILE *fp;
	tAlumno alum;
	tArbol a;

	//printf("Archivo alumnos.dat:\n");
	//debug_alumnos();
	
	fp = fopen("alumnos.dat", "rb");

	if(!fp) {
		return 1;
	}

	arbol_crear(&a);

	while(!feof(fp)) {
		fread(&alum, sizeof(tAlumno), 1, fp);
		arbol_insertar(&a, &alum, sizeof(tAlumno), alumno_cmp);
	}

	prettyPrintArbol(a, print_alumno);

	printf("")

	arbol_destruir(&a);
	
	return 0;
}
