#include "common.h"


int charEqual(char a, char b)
{
	if(isalpha(a) && isalpha(b)) {
		return tolower(a) == tolower(b);
	}
	
	return a == b;
}
