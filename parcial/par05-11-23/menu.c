#include "menu.h"

typedef enum {
	DNI,
	DNI_PATENTE,
	EXIT
} eMenuOption;

void _showMenuHeader(void)
{
	printf(
		"Sistema de patentes vencidas\n"
		"--------------------------------------\n"
		"1) Calcular ordenado por DNI\n"
		"2) Calcular ordenado por DNI y Patente\n"
		"3) Salir\n"
		" > "
	);
}

void menu(void)
{
	tBinaryTree bst;
	int ch, shouldClose = FALSE;

	while(!shouldClose) {
		_showMenuHeader();

		scanf("%d", &ch);

		switch(ch) {
			case DNI:
				loadFileIntoBST(&bst, "impuestosVencidos.dat", idCmp, amountUpdate);
				writeBstToFile(&bst, "deudas.txt", idWrite);
				break;
			case DNI_PATENTE:
				loadFileIntoBST(&bst, "impuestosVencidos.dat", idLicenseCmp, amountUpdate);
				writeBstToFile(&bst, "deudas.txt", idLicenseWrite);
				break;
			case EXIT:
				shouldClose = TRUE;
				break;
		}
	}

	binaryTreeDelete(&bst);
}
