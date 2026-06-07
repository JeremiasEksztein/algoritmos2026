#include "cola.h"

static tNodo *nodo_crear(unsigned n, const void *buf)
{
	tNodo *nuevo;

	nuevo = malloc(sizeof(tNodo));

	if(!nuevo) {
		return NULL;
	}

	nuevo->buf = malloc(n);

	if(!nuevo->buf) {
		free(nuevo);
		return NULL;
	}

	nuevo->sig = NULL;
	nuevo->n = n;
	memcpy(nuevo->buf, buf, n);

	return nuevo;
}

void cola_crear(tCola *cola)
{
	if(!cola) {
		return;
	}

	cola->pri = NULL;
	cola->ult = NULL;
}

int cola_encolar(tCola *cola, const void *elem, unsigned n)
{
	tNodo *tmp;
	
	if(!cola || !elem) {
		return 1;
	}

	tmp = nodo_crear(n, elem);

	if(!tmp) {
		return 1;
	}

	if(!cola->pri) {
		cola->pri = tmp;
	} else {
		cola->ult->sig = tmp;
	}

	cola->ult = tmp;

	return 0;
}

int cola_desencolar(tCola *cola, void *buf, unsigned n)
{
	tNodo *tmp;

	if(!cola || !buf || !cola->pri) {
		return 1;
	}

	tmp = cola->pri;
	cola->pri = tmp->sig;

	memcpy(buf, tmp->buf, MIN(tmp->n, n));

	free(tmp->buf);
	free(tmp);

	if(!cola->pri) {
		cola->ult = NULL;
	}

	return 0;
}

int cola_frente(const tCola *cola, void *buf, unsigned n)
{
	if(!cola || !buf || !cola->pri) {
		return 1;
	}

	memcpy(buf, cola->pri->buf, MIN(cola->pri->n, n));
	
	return 0;
}

int cola_esta_vacia(const tCola *cola)
{
	if(!cola || !cola->pri) {
		return 1;
	}

	return 0;
}

void cola_destruir(tCola *cola)
{
	tNodo *tmp;

	while(cola->pri) {
		tmp = cola->pri;
		cola->pri = cola->pri->sig;

		free(tmp->buf);
		free(tmp);
	}
}
