#include "pila.h"

void pila_crear(tPila *p)
{
	if(!p) {
		return;
	}

	p->tope = PILA_TAM - 1;
}

int pila_apilar(tPila *p, const void *elem, unsigned n)
{
	if(!p || !elem) {
		return ERR;
	}

	if(p->tope < (n + sizeof(unsigned))) {
		return ERR;
	}

	memcpy(p->buf + p->tope - n, elem, n);
	memcpy(p->buf + p->tope - n - sizeof(unsigned), &n, sizeof(unsigned));
	p->tope -= n + sizeof(unsigned);

	return OK;
}

int pila_desapilar(tPila *p, void *buf, unsigned n)
{
	unsigned tam;
	
	if(!p || !buf) {
		return ERR;
	}

	if(p->tope == (PILA_TAM - 1)) {
		return ERR;
	}

	memcpy(&tam, p->buf + p->tope, sizeof(unsigned));
	memcpy(buf, p->buf + p->tope + sizeof(unsigned), MIN(tam, n));

	p->tope += n + sizeof(unsigned);

	return OK;
}

int pila_tope(const tPila *p, void *buf, unsigned n)
{
	unsigned tam;
	
	if(!p || !buf) {
		return ERR;
	}

	if(p->tope == (PILA_TAM - 1)) {
		return ERR;
	}

	memcpy(&tam, p->buf + p->tope, sizeof(unsigned));
	memcpy(buf, p->buf + p->tope + sizeof(unsigned), MIN(tam, n));

	return OK;
}

int pila_esta_vacia(const tPila *p)
{
	if(!p || p->tope == (PILA_TAM - 1)) {
		return 1;
	}

	return 0;
}

int pila_esta_llena(const tPila *p, unsigned n)
{
	if(p->tope < (n + sizeof(unsigned))) {
		return 1;
	}

	return 0;
}

void pila_destruir(tPila *p)
{
	if(!p) {
		return;
	}

	memset(p->buf, 0, PILA_TAM);
	p->tope = PILA_TAM - 1;
}
