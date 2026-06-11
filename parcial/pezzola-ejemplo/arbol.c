#include "arbol.h"

void arbol_crear(tArbol *a)
{
	if(!a) {
		return;
	}

	*a = NULL;
}

void arbol_inorden(tArbol *a, fVisita visita, void *ctxt)
{
	if(!a || !*a || !visita) {
		return;
	}

	arbol_inorden(&(*a)->izq, visita, ctxt);
	visita((*a)->buf, ctxt);
	arbol_inorden(&(*a)->der, visita, ctxt);
}

void arbol_preorden(tArbol *a, fVisita visita, void *ctxt)
{
	if(!a || !*a || !visita) {
		return;
	}

	visita((*a)->buf, ctxt);
	arbol_preorden(&(*a)->izq, visita, ctxt);
	arbol_preorden(&(*a)->der, visita, ctxt);
}

void arbol_postorden(tArbol *a, fVisita visita, void *ctxt)
{
	if(!a || !*a || !visita) {
		return;
	}

	arbol_postorden(&(*a)->izq, visita, ctxt);
	arbol_postorden(&(*a)->der, visita, ctxt);
	visita((*a)->buf, ctxt);
}

int arbol_insertar(tArbol *a, const void *elem, size_t n, fCmp cmp)
{
	int compar;

	while(*a) {
		compar = cmp((*a)->buf, elem);

		if(compar > 0) {
			a = &(*a)->izq;
		} else if(compar < 0) {
			a = &(*a)->der;
		} else {
			return ERR;
		}
	}

	(*a) = malloc(sizeof(tNodo));

	if(!*a) {
		return ERR;
	}

	(*a)->buf = malloc(n);

	if(!(*a)->buf) {
		free(*a);
		*a = NULL;
		return ERR;
	}

	memcpy((*a)->buf, elem, n);
	(*a)->n = n;
	(*a)->izq = (*a)->der = NULL;

	return OK;
}

size_t arbol_altura(const tArbol *a)
{
	size_t alt_izq, alt_der;
	if(!a || !*a) {
		return 0;
	}

	alt_izq = arbol_altura(&(*a)->izq);
	alt_der = arbol_altura(&(*a)->der);

	return MAX(alt_izq, alt_der) + 1;
}

static void _injertar(tArbol *a)
{
	tArbol *reempl = a;
	tNodo *tmp;
	size_t alt_izq, alt_der;

	alt_izq = arbol_altura(&(*a)->izq);
	alt_der = arbol_altura(&(*a)->der);

	if(alt_izq > alt_der) {
		a = &(*a)->izq;

		while((*a)->der) {
			a = &(*a)->der;
		}
	} else {
		a = &(*a)->der;
		
		while((*a)->izq) {
			a = &(*a)->izq;
		}
	}

	(*reempl)->buf = (*a)->buf;
	(*reempl)->n = (*a)->n;
	tmp = (*a);

	if((*a)->izq) {
		a = &(*a)->izq;
	} else {
		a = &(*a)->der;
	}

	free(tmp);
}

int arbol_remover(tArbol *a, const void *clave, void *buf, size_t n, fCmp cmp)
{
	int compar;

	while(*a) {
		compar = cmp((*a)->buf, clave);

		if(compar > 0) {
			a = &(*a)->izq;
		} else if(compar < 0) {
			a = &(*a)->der;
		} else {
			memcpy(buf, (*a)->buf, MIN((*a)->n, n));

			free((*a)->buf);

			if(!(*a)->izq && !(*a)->der) {
				free(*a);
				*a = NULL;
			} else {
				_injertar(a);
			}

			return OK;
		}
	}

	return ERR;
}

int arbol_buscar(tArbol *a, const void *clave, void *buf, size_t n, fCmp cmp)
{
	int compar;

	while(*a) {
		compar = cmp((*a)->buf, clave);

		if(compar > 0) {
			a = &(*a)->izq;
		} else if(compar < 0) {
			a = &(*a)->der;
		} else {
			memcpy(buf, (*a)->buf, MIN((*a)->n, n));

			return OK;
		}
	}

	return ERR;
}

int arbol_rango(tArbol *a, const void *desde, const void *hasta, fVisita visita, void *ctxt);

void arbol_destruir(tArbol *a)
{
	if(!a || !*a) {
		return;
	}

	arbol_destruir(&(*a)->izq);
	arbol_destruir(&(*a)->der);
	free((*a)->buf);
	free(*a);
}
