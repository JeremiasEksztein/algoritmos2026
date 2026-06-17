#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x, y) ((x) > (y) ? (y) : (x))

typedef int (*Cmp)(const void *, const void *);

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

int listaSimpleAgregar(tListaSimple *l, const void *data, unsigned n)
{
	tNodo *nuevo;
	
	if(!l || !data) {
		return 2;
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

int listaSimpleBuscar(const tListaSimple *l, const void *clave, void *buf, unsigned n, Cmp cmp)
{
	if(!l || !clave || !buf || !cmp) {
		return 1;
	}

	while(*l) {
		if(cmp((*l)->data, clave) == 0) {
			break;
		}

		l = &(*l)->sig;
	}

	if(*l) {
		memcpy(buf, (*l)->data, MIN((*l)->n, n));
		return 0;
	}

	return 2;
}

void listaSimpleDestruir(tListaSimple *l)
{
	tNodo *tmp;

	if(!l || !*l) {
		return;
	}

	while(*l) {
		tmp = *l;
		*l = tmp->sig;

		free(tmp->data);
		free(tmp);
	}
}

typedef struct {
	char usuario[21];
	char nombre[51];
	char apellido[51];
	int nivel;
} tCliente;

typedef struct {
	char codigo[16];
	char descripcion[51];
	float precio;
} tProducto;

typedef struct {
	int nivel;
	float porcDescuento;
	float topeDescuento;
	float minimoParaEnvioGratis;
} tRegla;

typedef struct {
	char usuario[21];
	char producto[16];
	float precio;
	int envioGratis;
} tOferta;

void crearReglas(void)
{
	FILE *fp;

	fp = fopen("reglas.txt", "wt");

	fprintf(
		fp,
		"01|0.25|100|20\n"
		"02|0.50|75|10\n"
		"03|0.75|60|90\n"
		"05|0.10|50|75\n"
	);

	fclose(fp);
}

void crearClientes(void)
{
	FILE *fp;
	tCliente clientes[] = {
		{"Jere2005", "Jeremias", "Eksztein", 5},
		{"Gabi1976", "Gabriela", "Rolon", 3},
		{"Oli2009", "Olivia", "Eksztein", 1},
		{"Ruben1959", "Ruben", "Jaime", 2}
	};

	fp = fopen("clientes.dat", "wb");

	fwrite(clientes, sizeof(clientes), 1, fp);

	fclose(fp);
}

void crearProductos(void)
{
	FILE *fp;
	tProducto productos[] = {
		{"Doom3", "FPS", 25.0f},
		{"Minecraft", "Sandbox", 25.0f},
		{"GTAVI", "FPS,Sandbox", 75.0f},
		{"Silksong", "Metroidvania", 20.0f},
		{"Hollow Knight", "Metroidvania", 15.0f}
	};

	fp = fopen("productos.dat", "wb");

	fwrite(productos, sizeof(productos), 1, fp);

	fclose(fp);
}

int cmpRegla(const void *a, const void *b)
{
	const tRegla *x = a, *y = b;

	return (x->nivel - y->nivel);
}

int leerRegla(char *linea, tRegla *regla)
{
	char *i;

	if(!(i = strrchr(linea, '\n'))) {
		return 2;
	}

	*i = '\0';

	if(!(i = strrchr(linea, '|'))) {
		return 3;
	}

	sscanf(i + 1, "%f", &regla->minimoParaEnvioGratis);
	*i = '\0';

	if(!(i = strrchr(linea, '|'))) {
		return 3;
	}

	sscanf(i + 1, "%f", &regla->topeDescuento);
	*i = '\0';

	if(!(i = strrchr(linea, '|'))) {
		return 3;
	}

	sscanf(i + 1, "%f", &regla->porcDescuento);
	*i = '\0';

	sscanf(linea, "%d", &regla->nivel);

	return 0;
}

int generarArchivoOfertasBin_ALU(tListaSimple *reglas, const char *prod, const char *cli)
{
	FILE *fpProductos, *fpClientes, *fpOfertas;
	tCliente cliente;
	tProducto producto;
	tRegla regla;
	tOferta oferta;
	float descAplicado;

	fpProductos = fopen(prod, "rb");

	if(!fpProductos) {
		return 1;
	}

	fpClientes = fopen(cli, "rb");

	if(!fpClientes) {
		fclose(fpProductos);
		return 1;
	}

	fpOfertas = fopen("ofertas.dat", "wb");

	if(!fpOfertas) {
		fclose(fpClientes);
		fclose(fpProductos);
		return 1;
	}

	while(fread(&cliente, sizeof(tCliente), 1, fpClientes)) {
		
		while(fread(&producto, sizeof(tProducto), 1, fpProductos)) {

			regla.nivel = cliente.nivel;
			listaSimpleBuscar(reglas, &regla, &regla, sizeof(tRegla), cmpRegla);

			/* Puede no existir la regla? */

			strcpy(oferta.usuario, cliente.usuario);
			strcpy(oferta.producto, producto.codigo);

			descAplicado = producto.precio * regla.porcDescuento;

			if(descAplicado > regla.topeDescuento) {
				descAplicado = regla.topeDescuento;
			}	 			

			oferta.precio = producto.precio - descAplicado;

			if(oferta.precio > regla.minimoParaEnvioGratis) {
				oferta.envioGratis = 1;
			} else {
				oferta.envioGratis = 0;
			}

			fwrite(&oferta, sizeof(tOferta), 1, fpOfertas);
		}

		fseek(fpOfertas, 0, SEEK_SET);
	}

	fclose(fpOfertas);
	fclose(fpProductos);
	fclose(fpClientes);

	return 0;
}

int generarArchivoOfertas_ALU(tListaSimple *reglas, const char *prod, const char *cli)
{
	FILE *fpProductos, *fpClientes, *fpOfertas;
	tCliente cliente;
	tProducto producto;
	tRegla regla;
	tOferta oferta;
	float descAplicado;

	fpProductos = fopen(prod, "rb");

	if(!fpProductos) {
		return 1;
	}

	fpClientes = fopen(cli, "rb");

	if(!fpClientes) {
		fclose(fpProductos);
		return 1;
	}

	fpOfertas = fopen("ofertas.txt", "wt");

	if(!fpOfertas) {
		fclose(fpClientes);
		fclose(fpProductos);
		return 1;
	}

	fprintf(fpOfertas, "Usuario\n\tProducto\t\t\tPrecio\tEnvio Gratis\n");

	while(fread(&cliente, sizeof(tCliente), 1, fpClientes)) {

		fprintf(fpOfertas, "%s\n", cliente.usuario);
		
		while(fread(&producto, sizeof(tProducto), 1, fpProductos)) {
	
			regla.nivel = cliente.nivel;
			listaSimpleBuscar(reglas, &regla, &regla, sizeof(tRegla), cmpRegla);

			/* Puede no existir la regla? */

			strcpy(oferta.usuario, cliente.usuario);
			strcpy(oferta.producto, producto.codigo);

			descAplicado = producto.precio * regla.porcDescuento;

			if(descAplicado > regla.topeDescuento) {
				descAplicado = regla.topeDescuento;
			}	 			

			oferta.precio = producto.precio - descAplicado;

			if(oferta.precio > regla.minimoParaEnvioGratis) {
				oferta.envioGratis = 1;
			} else {
				oferta.envioGratis = 0;
			}

			fprintf(
				fpOfertas, 
				"\t%-*s\t\t%0.2f\t%-*s\n", 
				16, oferta.producto,
				oferta.precio,
				2, (oferta.envioGratis) ? "Si" : "No"
			);
		}
		
		fseek(fpProductos, 0, SEEK_SET);
	}

	fclose(fpOfertas);
	fclose(fpProductos);
	fclose(fpClientes);

	return 0;
}

int main(void)
{	
	tListaSimple reglas;
	tRegla regla;
	FILE *fpReglas;
	char linea[256];

	crearReglas();
	crearClientes();
	crearProductos();
	
	fpReglas = fopen("reglas.txt", "rt");

	if(!fpReglas) {
		return 1;
	}

	listaSimpleCrear(&reglas);

	while(fgets(linea, 256, fpReglas)) {
		if(leerRegla(linea, &regla) != 0) {
			fclose(fpReglas);
			listaSimpleDestruir(&reglas);
		}

		listaSimpleAgregar(&reglas, &regla, sizeof(tRegla));
	}	

	fclose(fpReglas);

	generarArchivoOfertas_ALU(&reglas, "productos.dat", "clientes.dat");
	generarArchivoOfertasBin_ALU(&reglas, "productos.dat", "clientes.dat");

	listaSimpleDestruir(&reglas);

	return 0;
}
