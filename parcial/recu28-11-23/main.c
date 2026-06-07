#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "producto.h"
#include "cola.h"

int main(void)
{
	FILE *fp_productos, *fp_pedidos, *fp_exito, *fp_fallo;
	int exito;
	tProducto tmp;
	tPedido prev, act;
	tItem item;
	tCola items;
	float precio_total;

	crear_productos();
	crear_pedidos();

	debug_productos("productos.dat");
	debug_pedidos("pedidos.txt");

	fp_productos = fopen("productos.dat", "rb+");

	if(!fp_productos) {
		return 1;
	}

	fp_pedidos = fopen("pedidos.txt", "rt");

	if(!fp_pedidos) {
		fclose(fp_productos);
		return 1;
	}

	fp_exito = fopen("pedidos_realizados.txt", "wt");

	if(!fp_exito) {
		fclose(fp_pedidos);
		fclose(fp_productos);
		return 1;
	}
	
	fp_fallo = fopen("pedidos_no_realizados.txt", "wt");

	if(!fp_fallo) {
		fclose(fp_exito);
		fclose(fp_pedidos);
		fclose(fp_productos);
		return 1;
	}


	leer_entrada(fp_pedidos, &act);
	while(!feof(fp_pedidos)) {
		cola_crear(&items);
		memcpy(&prev, &act, sizeof(tPedido));
		exito = 1;
		precio_total = 0.0f;
		
		while(!feof(fp_pedidos) && prev.cod_ped == act.cod_ped) {
			item.cod_prod = act.cod_prod;
			item.cant = act.cant;

			fseek(fp_productos, (long)((item.cod_prod - 1) * sizeof(tProducto)), SEEK_SET);
			fread(&tmp, sizeof(tProducto), 1, fp_productos);

			if(tmp.stock >= item.cant && exito) {
				precio_total += item.cant * tmp.precio;
				cola_encolar(&items, &item, sizeof(tItem));
			} else if(tmp.stock < item.cant) {
				exito = 0;
				fprintf(fp_fallo, "%02d|%02d\n", prev.cod_ped, item.cod_prod);
			}
		
			leer_entrada(fp_pedidos, &act);
		}
 
		if(exito) {
			while(!cola_esta_vacia(&items)) {
				cola_desencolar(&items, &item, sizeof(tItem));

				fseek(fp_productos, (long)((item.cod_prod - 1) * sizeof(tProducto)), SEEK_SET);
				fread(&tmp, sizeof(tProducto), 1, fp_productos);
				tmp.stock -= item.cant;
				fseek(fp_productos, (long)(- sizeof(tProducto)), SEEK_CUR);
				fwrite(&tmp, sizeof(tProducto), 1, fp_productos);
			}

			fprintf(fp_exito, "%02d|%02.2f\n", prev.cod_ped, precio_total);
		}
	
		fflush(fp_productos);
		cola_destruir(&items);
	}

	cola_destruir(&items);

	fclose(fp_fallo);
	fclose(fp_exito);
	fclose(fp_pedidos);
	fclose(fp_productos);

	debug_productos("productos.dat");
	debug_pedidos("pedidos.txt");
	
	return 0;
}
