#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*Cmp)(const void *, const void *);
typedef void (*Map)(const void *, void *);

typedef struct sNodo tNodo;
struct sNodo {
	tNodo *sig;
	unsigned n;
	void *data;
};

typedef tNodo *tListaSimple;

void listaSimpleCrear(tListaSimple *l)
{
	if(!l) {
		return;
	}

	*l = NULL;
}

int listaSimpleInsertarOrdenado(
	tListaSimple *l,
	const void *data,
	unsigned n,
	Cmp cmp
) {
	tNodo *nuevo;

	while(*l && cmp((*l)->data, data)) {
		l = &(*l)->sig;
	}

	nuevo = malloc(sizeof(tNodo));

	if(!nuevo) {
		return 1;
	}

	nuevo->data = malloc(n);

	if(!nuevo->data) {
		free(nuevo);
		return 1;
	}

	memcpy(nuevo->data, data, n);
	nuevo->n = n;

	nuevo->sig = *l;
	*l = nuevo;
	
	return 0;
}

int listaSimpleEliminarUltimosN(tListaSimple *l, int n)
{
	tListaSimple *pri;
	tNodo *tmp, *elim;
	int i;

	if(!l || !*l || n <= 0) {
		return 1;
	}

	pri = l;
	tmp = *l;

	for(i = 0; i < n && tmp; ++i) {
		tmp = tmp->sig;
	}

	while(tmp) {
		pri = &(*pri)->sig;
		tmp = tmp->sig;
	}

	elim = *pri;
	while(elim) {
		tmp = elim;
		elim = tmp->sig;
		free(tmp->data);
		free(tmp);
		tmp = NULL;
	}
	*pri = NULL;

	return 0;
}	

int listaSimpleMap(tListaSimple *l, Map map, void *usuario)
{
	if(!l || !map) {
		return 1;
	}
	
	while(*l) {
		map((*l)->data, usuario);
		l = &(*l)->sig;
	}

	return 0;
}

void listaSimpleDestruir(tListaSimple *l)
{
	tNodo *tmp;

	while(*l) {
		tmp = *l;
		*l = tmp->sig;
		free(tmp->data);
		free(tmp);
	} 

	*l = NULL;
}

typedef struct {
	unsigned nroCuenta;
	char tipoDeCuenta[3];
	char apellidoNombreTitular[26];
	unsigned extensionClave;
	float saldo;
} tCuenta;

int cmpCuenta(const void *a, const void *b)
{
	const tCuenta *x = a, *y = b;
	int dif;

	if(x->nroCuenta != y->nroCuenta) {
		return x->nroCuenta - y->nroCuenta;
	}

	dif = strcmp(x->tipoDeCuenta, y->tipoDeCuenta);
	if(dif) {
		return dif;
	}
	
	return x->extensionClave - y->extensionClave;
}

void mapCuenta(const void *elem, void *usuario)
{
	FILE *fp = usuario;
	const tCuenta *cuenta = elem;
	
	printf(
		"%u|%s|%s|%u|%0.2f\n",
		cuenta->nroCuenta,
		cuenta->tipoDeCuenta,
		cuenta->apellidoNombreTitular,
		cuenta->extensionClave,
		cuenta->saldo
	);
	fwrite(elem, sizeof(tCuenta), 1, fp);
}

int leerCuenta(char *linea, tCuenta *c)
{
	char *i;
	
	if(!(i = strrchr(linea, '\n'))) {
		return 1;
	}

	*i = '\0';

	if(!(i = strrchr(linea, ';'))) {
		return 1;
	}

	sscanf(i + 1, "%f", &c->saldo);
	*i = '\0';

	if(!(i = strrchr(linea, ';'))) {
		return 1;
	}

	sscanf(i + 1, "%u", &c->extensionClave);
	*i = '\0';

	if(!(i = strrchr(linea, ';'))) {
		return 1;
	}

	sscanf(i + 1, "%s", c->apellidoNombreTitular);
	*i = '\0';

	if(!(i = strrchr(linea, ';'))) {
		return 1;
	}

	sscanf(i + 1, "%s", c->tipoDeCuenta);
	*i = '\0';

	sscanf(linea, "%u", &c->nroCuenta);

	return 0;
}

#define LINEA_TAM 256

int main(void)
{
	FILE *fp;
	char linea[LINEA_TAM];
	tListaSimple cuentas;
	tCuenta cuenta;

	fp = fopen("cuentas.txt", "rt");

	if(!fp) {
		return 1;
	}

	while(fgets(linea, LINEA_TAM, fp)) {
		if(leerCuenta(linea, &cuenta) != 0) {
			return 1;
		}
/*
		printf(
			"%u|%s|%s|%u|%0.2f\n",
			cuenta.nroCuenta,
			cuenta.tipoDeCuenta,
			cuenta.apellidoNombreTitular,
			cuenta.extensionClave,
			cuenta.saldo
		);		
*/
		listaSimpleInsertarOrdenado(&cuentas, &cuenta, sizeof(tCuenta), cmpCuenta);
	}

	fclose(fp);

	listaSimpleEliminarUltimosN(&cuentas, 2);

	fp = fopen("resultadoCuentas.bin", "wb");

	if(!fp) {
		return 1;
	}

	listaSimpleMap(&cuentas, mapCuenta, fp);

	fclose(fp);

	listaSimpleDestruir(&cuentas);
	
	return 0;
}
