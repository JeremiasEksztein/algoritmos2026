#include <stdio.h>
#include <stdio.h>

#include "pila.h"

int ej2(const char *buf)
{
	tPila paren, corche, llaves;
	const char *i = buf;
	char tmp;
	int flag = 1;

	pila_crear(&paren);
	pila_crear(&corche);
	pila_crear(&llaves);

	while(*i && flag) {
		switch(*i) {
			case '(':
				pila_apilar(&paren, i, sizeof(char));
				break;
			case '{':
				pila_apilar(&llaves, i, sizeof(char));
				break;
			case '[':
				pila_apilar(&corche, i, sizeof(char));
				break;
			case ')':
				if(pila_tope(&paren, &tmp, sizeof(char)) != OK) {
					flag = 0;
				}

				if(tmp == '(') {
					pila_desapilar(&paren, &tmp, sizeof(char));
				} else {
					flag = 0;
				}
				break;
			case '}':
				if(pila_tope(&llaves, &tmp, sizeof(char)) != OK) {
					flag = 0;
				}

				if(tmp == '{') {
					pila_desapilar(&llaves, &tmp, sizeof(char));
				} else {
					flag = 0;
				}
				break;
			case ']':
				if(pila_tope(&corche, &tmp, sizeof(char)) != OK) {
					flag = 0;
				}

				if(tmp == '[') {
					pila_desapilar(&corche, &tmp, sizeof(char));
				} else {
					flag = 0;
				}
				break;
		}
		++i;
	}

	if(!pila_esta_vacia(&paren)
	 	|| !pila_esta_vacia(&corche)
	 	|| !pila_esta_vacia(&llaves)) {
		flag = 0; 		
 	}

	return flag;
}
int main(void)
{
	int res[3] = {0, 0, 0};
	int i;

	res[0] = ej2("(){}[]");
	res[1] = ej2("{[()]}");
	res[2] = ej2("{");

	for(i = 0; i < 3; ++i) {
		printf("%d\n", res[i]);
	}

	return 0;
}
