#ifndef COLA_H
#define COLA_H

#include <stdlib.h>
#include <string.h>

#define MIN(x, y) (((x) > (y)) ? (y) : (x))

typedef struct sNodo tNodo;
struct sNodo {
	tNodo *sig;
	unsigned n;
	void *buf;
};

typedef struct {
	tNodo *pri, *ult;
} tCola;

void cola_crear(tCola *cola);

int cola_encolar(tCola *cola, const void *elem, unsigned n);

int cola_desencolar(tCola *cola, void *buf, unsigned n);

int cola_frente(const tCola *cola, void *buf, unsigned n);

int cola_esta_vacia(const tCola *cola);

void cola_destruir(tCola *cola);

#endif
