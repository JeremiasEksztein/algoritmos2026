#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <stdio.h>
#include <string.h>

typedef struct {
	char desc[21];
	int stock;
	float precio;
} tProducto;

typedef struct {
	int cod_ped;
	int cant;
	int cod_prod;
} tPedido;

typedef struct {
	int cod_prod;
	int cant;
} tItem;

typedef struct {
	int cod_ped;
	float precio;
} tPedidoRealizado;

typedef struct {
	int cod_ped;
	int cod_prod;
} tPedidoNoRealizado;

void crear_productos(void);
void crear_pedidos(void);

void debug_productos(const char *path);
void debug_pedidos(const char *path);
void debug_pedidos_no_realizados(const char *path);
void debug_pedidos_realizados(const char *path);

int leer_entrada(FILE *fp, tPedido *pedido);

#endif
