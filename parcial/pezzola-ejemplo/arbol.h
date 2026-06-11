#ifndef ARBOL_H
#define ARBOL_H

#include <stdlib.h>
#include <string.h>

#define MIN(x, y) (((x) > (y)) ? (y) : (x))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

#define OK 0
#define ERR 1

#define TRUE 1
#define FALSE 0

typedef int (*fCmp)(const void*, const void*);
typedef void (*fVisita)(const void*, void*);

typedef struct sNodo tNodo;
struct sNodo {
	tNodo *izq, *der;
	unsigned n;
	void *buf;	
};

typedef tNodo *tArbol;

void arbol_crear(tArbol *a);

int arbol_insertar(tArbol *a, const void *elem, size_t n, fCmp cmp);

int arbol_remover(tArbol *a, const void *clave, void *buf, size_t n, fCmp cmp);

int arbol_buscar(tArbol *a, const void *clave, void *buf, size_t n, fCmp cmp);

void arbol_inorden(tArbol *a, fVisita visita, void *ctxt);
void arbol_preorden(tArbol *a, fVisita visita, void *ctxt);
void arbol_postorden(tArbol *a, fVisita visita, void *ctxt);

size_t arbol_altura(const tArbol *a);

int arbol_rango(tArbol *a, const void *desde, const void *hasta, fVisita visita, void *ctxt);

void arbol_destruir(tArbol *a);

#endif
