#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "defines.h"
#include "stack.h"
#include "depot.h"

void eprintf(const char *msg, ...);

void eprintf(const char *msg, ...)
{
	va_list ap;

	va_start(ap, msg);

	vfprintf(stderr, msg, ap);

	va_end(ap);
}

int main(void)
{
	FILE *fpMovements = NULL, *fpInbound = NULL, *fpOutbound = NULL, *fpAnomaly = NULL;
	tStack depot[4]; 
	tContainer tmp;
	char buf[21];
	unsigned n;
	int ret, op;

	if(openFile(&fpMovements, "movimientos.txt", "rt") != OK) {
		eprintf("[ERROR] : Falla al abrir archivo de movimientos\n");
		return ERR;
	}

	if(createLogFiles(&fpInbound, &fpOutbound, &fpAnomaly) != OK) {
		eprintf("[ERROR] : Falla al crear logfiles\n");
		fclose(fpMovements);
		return ERR;
	}

	fgets(buf, 21, fpMovements);
	sscanf(buf, "%u\n", &n);
	
	if(initDepotSim(depot, n) != OK) {
		eprintf("[ERROR] : Falla al iniciar simulacion de almacen\n");
		fclose(fpMovements);
		fclose(fpInbound);
		fclose(fpOutbound);
		fclose(fpAnomaly);
		return ERR;
	}

	while(fgets(buf, 21, fpMovements)) {
		eprintf("[INFO] : %s\n", buf);
		readLine(buf, &op, &tmp);

		eprintf("%d\n", op);
		if(op == IN) {
			ret = handleInboundContainer(depot, &tmp);
		} else {
			ret = handleOutboundContainer(depot, &tmp);
		}		

		switch(ret) {
			case IN_OK:
				writeToLogFile(
					fpInbound, 
					"[SUCCESS] : Se ingreso con exito el contenedor\n"
					"\t[INFO] : De la compañia: %s con ID: %s\n",
					tmp.company,
					tmp.id
				);
				break;
			case IN_ERR:
				writeToLogFile(
					fpAnomaly, 
					"[ERROR] : Codigo de anomalia SCD 'Sin capacidad disponible'\n"
					"\t[INFO] : Ingresando contenedor de la compañia: %s con ID: %s\n",
					tmp.company,
					tmp.id
				);
				break;
			case OUT_OK:
				writeToLogFile(
					fpOutbound, 
					"[SUCCESS] : Se egreso con exito el contenedor\n"
					"\t[INFO] : De la compañia: %s con ID: %s\n",
					tmp.company,
					tmp.id
				);
				break;
			case OUT_ERR:
				writeToLogFile(
					fpAnomaly, 
					"[ERROR] : Codigo de anomalia CID 'Contenedor Inexistente'\n"
					"\t[INFO] : Ingresando contenedor de la compañia: %s con ID: %s\n",
					tmp.company,
					tmp.id
				);
				break;
		}

		memset(&tmp, 0, sizeof(tContainer));
	}

	dumpDepotStatus(depot);

	fclose(fpMovements);
	fclose(fpInbound);
	fclose(fpOutbound);
	fclose(fpAnomaly);

	uninitDepotSim(depot);

	return OK;
}
