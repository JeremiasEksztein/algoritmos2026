#include <stdio.h>

typedef enum {
	OPTION_DNI,
	OPTION_DNI_PATENTE,
	OPTION_EXIT	
} eOption;

void showMenu(void)
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

int handleInput(int input)
{
	FILE *fpOverdues;
	tBinaryTree bst;

	switch(input) {
		case OPTION_DNI:
			
		case OPTION_DNI_PATENTE:	
	}
}

int main(void)
{
	FILE *fpOverdues;
	tQuota tmp;
	tBinaryTree bst;
	int ch, shouldClose = FALSE;

	while(!shouldClose) {
		showMenu();

		scanf("%d", &tmp);

		if(tmp == OPTION_EXIT) {
			shouldClose = TRUE;
			continue;
		}

		handleInput(tmp);
	}

	return OK;
}
