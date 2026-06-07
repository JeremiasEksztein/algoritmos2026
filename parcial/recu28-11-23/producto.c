#include "producto.h"

#define BUFLEN 256

void crear_productos(void)
{
	FILE *fp;
	tProducto prods[] = {
		{"Naranjas", 100, 50.0f},
		{"Manzanas", 200, 20.0f},
		{"Ciruelas", 50, 100.0f},
	};

	fp = fopen("productos.dat", "wb");

	fwrite(prods, sizeof(prods), 1, fp);
	fflush(fp);

	fclose(fp);
}

void crear_pedidos(void)
{
	FILE *fp;
	int i;
	tPedido peds[] = {
		{101, 50, 1},
		{101, 50, 2},
		{102, 50, 3},
		{103, 50, 1},
		{103, 50, 2},
		{103, 50, 3}
	};

	fp = fopen("pedidos.txt", "wt");

	for(i = 0; i < 6; ++i) {
		fprintf(fp, "%6d%6d%3d\n", peds[i].cod_ped, peds[i].cant, peds[i].cod_prod);
	}

	fclose(fp);	
}

void debug_productos(const char *path)
{
	FILE *fp;
	tProducto prod;
	unsigned i = 0;

	fp = fopen(path, "rb");

	if(!fp) {
		return;
	}	

	printf("Contenidos de '%s':\n", path);
	while(!feof(fp)) {
		fread(&prod, sizeof(tProducto), 1, fp);
		printf("%02d|%-*s|%04d|%04.2f\n", i, 21, prod.desc, prod.stock, prod.precio);
		++i;
	}

	fclose(fp);
}

void debug_pedidos(const char *path)
{
	FILE *fp;
	tPedido ped;

	fp = fopen(path, "rt");

	if(!fp) {
		return;
	}	

	printf("Contenidos de '%s':\n", path);
	while(!feof(fp)) {
		fscanf(fp, "%6d%6d%3d\n", &ped.cod_ped, &ped.cant, &ped.cod_prod);
		printf("%06d|%06d|%03d\n", ped.cod_ped, ped.cant, ped.cod_prod);
	}

	fclose(fp);	
}

void debug_pedidos_no_realizados(const char *path);
void debug_pedidos_realizados(const char *path);

int leer_entrada(FILE *fp, tPedido *pedido)
{
	char buf[BUFLEN];

	if(!fgets(buf, BUFLEN, fp)) {
		return 1;
	}	

	sscanf(buf, "%6d%6d%3d\n", &pedido->cod_ped, &pedido->cant, &pedido->cod_prod);

	return 0;
}
