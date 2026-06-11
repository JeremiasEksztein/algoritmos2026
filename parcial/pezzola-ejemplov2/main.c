#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "tree.h"
#include "alumno.h"

int main(void)
{
	FILE *fp, *out;
	tAlumno alum;
	tBinaryTree bt;
	int dni = 1;
	const char template_name[] = "Materias_Aprobadas_XXXXXXXX.txt";
	char curr_name[64] = {0};

	fp = fopen("alumnos.dat", "rb");

	if(!fp) {
		return ERR;
	}

	binarytree_new(&bt);
	while(!feof(fp)) {
		fread(&alum, sizeof(tAlumno), 1, fp);
		binarytree_add(&bt, &alum, sizeof(tAlumno), alumno_cmp);
	}

	while(dni) {
		printf("Menu\n");
		printf("Ingrese DNI de alumno para generar su informe\n");
		printf("DNI con valor 0 para terminar consulta\n");
		printf(" > ");
		scanf("%d", &dni);

		if(!dni) {
			break;
		}

		#if defined(WIN32) || defined(WIN64)
			system("cls");
		#else
			system("clear");
		#endif

		printf("Creando informe para DNI: %d ...\n", dni);
		
		alum.dni = dni;

		if(binarytree_search(&bt, &alum, &alum, sizeof(tAlumno), dni_cmp) == ERR) {
			fprintf(stderr, "[ERROR] : 'El DNI %d no existe en la base de datos'\n", dni);
			break;
		}

		strcpy(curr_name, template_name);

		sprintf(strchr(curr_name, 'X'), "%08d.txt", dni);

		out = fopen(curr_name, "wt");

		if(!out) {
			fprintf(stderr, "[ERROR] : 'Falla en la creacion del archivo de informe'\n");
			break;
		}	
	} 

	binarytree_destroy(&bt);

	return OK;
}
