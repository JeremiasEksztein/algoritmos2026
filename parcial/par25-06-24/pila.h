#ifndef PILA_H
#define PILA_H

#include <stdlib.h>
#include <string.h>

#define MIN(x, y) (((x) > (y)) ? (y) : (x))

#define OK 0
#define ERR 1

#define PILA_TAM 256

typedef struct {
	unsigned char buf[PILA_TAM];
	unsigned tope; 
} tPila;

void pila_crear(tPila *p);

int pila_apilar(tPila *p, const void *elem, unsigned n);

int pila_desapilar(tPila *p, void *buf, unsigned n);

int pila_tope(const tPila *p, void *buf, unsigned n);

int pila_esta_vacia(const tPila *p);

int pila_esta_llena(const tPila *p, unsigned n);

void pila_destruir(tPila *p);

#endif
